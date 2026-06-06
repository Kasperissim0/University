#pragma once
#include "LinkedList.h"

LinkedList* buildAdjacencyList(int n, int m, int a[], int b[]);
bool pathExists(LinkedList* adjList, int start, int target, int maxLength);