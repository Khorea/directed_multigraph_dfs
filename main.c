#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int nodeId;
    int pathId;
    struct node *nextNode;
} node_t;

typedef struct vertex {
    int vertexId;
    node_t* nextAdj;
} vertex;

int contains(int* vec, int n, int item) {
    for (int i = 0; i < n; i++) {
        if (vec[i] == item) {
            return 1;
        }
    }
    return 0;
}

void printPath(int* vec, int n, int* paths) {
    for (int i = 1; i < n; i++) {
        printf("(%d->%d, %d); ", vec[i-1], vec[i], paths[i]);
    }
    printf("\n");
}

void DFS(vertex* graph, int currentNode, int endNode, int* visited, int visitedNodesCount, int* paths) {
    visited[visitedNodesCount] = graph[currentNode].vertexId;
    visitedNodesCount++;

    if (currentNode == endNode) {
        printPath(visited, visitedNodesCount, paths);
        return;
    }

    node_t* adj = graph[currentNode].nextAdj;
    while (adj) {
        if (contains(visited, visitedNodesCount, graph[adj->nodeId].vertexId)) {
            adj = adj->nextNode;
        } else {
            paths[visitedNodesCount] = adj->pathId;
            DFS(graph, adj->nodeId, endNode, visited, visitedNodesCount, paths);
            adj = adj->nextNode;
        }
    }
}

int main()
{
    printf("Hello world!\n");
    int vertexCount = 5;
    vertex graph[vertexCount];

    for (int i = 0; i < vertexCount; i++) {
        graph[i].vertexId = i + 1;
        graph[i].nextAdj = NULL;
    }

    graph[0].nextAdj = (node_t*)malloc(sizeof(node_t));
    graph[0].nextAdj->nodeId = 1;
    graph[0].nextAdj->pathId = 1;
    graph[0].nextAdj->nextNode = (node_t*)malloc(sizeof(node_t));
    graph[0].nextAdj->nextNode->nodeId = 1;
    graph[0].nextAdj->nextNode->pathId = 2;
    graph[0].nextAdj->nextNode->nextNode = NULL;

    graph[1].nextAdj = (node_t*)malloc(sizeof(node_t));
    graph[1].nextAdj->nodeId = 2;
    graph[1].nextAdj->pathId = 2;
    graph[1].nextAdj->nextNode = (node_t*)malloc(sizeof(node_t));
    graph[1].nextAdj->nextNode->nodeId = 4;
    graph[1].nextAdj->nextNode->pathId = 1;
    graph[1].nextAdj->nextNode->nextNode = NULL;

    graph[2].nextAdj = (node_t*)malloc(sizeof(node_t));
    graph[2].nextAdj->nodeId = 3;
    graph[2].nextAdj->pathId = 2;
    graph[2].nextAdj->nextNode = NULL;

    graph[4].nextAdj = (node_t*)malloc(sizeof(node_t));
    graph[4].nextAdj->nodeId = 2;
    graph[4].nextAdj->pathId = 1;
    graph[4].nextAdj->nextNode = NULL;

    int visited[vertexCount];
    int paths[vertexCount];

    for (int i = 0; i < vertexCount; i++) {
        printf("Vertex id = %d -> ", graph[i].vertexId);
        node_t* currentAdj = graph[i].nextAdj;
        while(currentAdj) {
            printf("%d | ", graph[currentAdj->nodeId].vertexId);
            currentAdj = currentAdj->nextNode;
        }
        printf("\n");

        visited[i] = 0;
        paths[i] = -1;
    }

    DFS(graph, 0, 3, visited, 0, paths);

    int x;
    scanf("%d", &x);
    return 0;
}
