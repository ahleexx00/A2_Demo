#include <stdio.h>
#include <stdlib.h>
#include "cs4050.h"
#include "MST.h"

//this function is for qsort
int compare(const void* a, const void* b){
    float x=((Edge*)a)->weight;
    float y = ((Edge*)b)->weight;
    return (x-y);
    
}

//return the set that i belongs
int findSet(int parent[], int i){
    if(parent[i]== -1){
        return i;
    }
    while(parent[i] != -1){
        i = parent[i];
    }
    return i;
}

//merge two sets
void unionSets(int parent[], int u, int v){
    int rootX=findSet(parent, u);
    int rootY=findSet(parent, v);
    if(rootX != rootY){
        parent[rootX]=rootY;
    }
    
}

//Kruskal's algorithm for MST
void MST_Kruskal(Vertex vertices[], int countVertices, Edge edges[], int countEdges)
{
    //sort edges of the graph, this is the core of the Kruskal algorithm
    qsort(edges, countEdges, sizeof(Edge), compare);




    
    int* parent=(int*)malloc(sizeof(int)*countVertices);
    if(parent==NULL){ //always check for the memory allocation!!!!
        printf("memory allocation error\n");
        return;
    }

    for(int i=0; i<countVertices; i++){
        parent[i]=-1; //means that each vertex is initially in its own set
    }





    Edge MSTedges[countVertices-1]; //create an array to store the edges of MST(number of edges=|V|-1)
    int edgeCounter=0;  //keep track of the limit of number of edges

    for(int i=0; i<countEdges; i++){
        int from=edges[i].from;
        int to=edges[i].to;

        //Check if it forms a cycle
        if(findSet(parent, from) != findSet(parent, to)){
            
            MSTedges[edgeCounter]=edges[i];
            edgeCounter++;
            
            unionSets(parent, from, to);
        }
    }




    //print out the MST
    printf("\n\nMST:\n");
    for (int i = 0; i < edgeCounter; i++)
    {
        printf("\t%d->%d ( %.0lf)\n", MSTedges[i].from, MSTedges[i].to, MSTedges[i].weight);
    }

    free(parent);
}
