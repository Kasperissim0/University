#pragma once
#include "LinkedList.h"

LinkedList* buildAdjacencyList(int n, int m, int a[], int b[]);
bool pathExists(LinkedList* adjList, int n, int start, int target);
int connectedComponents(LinkedList* adjList, int n);
int connectedComponentsSlow(LinkedList* adjList, int n);
