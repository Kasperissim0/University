#include "answer.h"
#include "LinkedList.h"

LinkedList* buildAdjacencyList(int n, int m, int a[], int b[]) {
  const auto &numberOfVertices = n, &numberOfEdges = m; 
  LinkedList *adjList = new LinkedList[numberOfVertices];

  for (int current = 0; current < numberOfEdges; ++current) {
    const auto &outgoing = a[current], &incoming = b[current];

    // if ((!adjList[outgoing].search(incoming)) and (!adjList[incoming].search(outgoing))) 
      adjList[outgoing].insert(incoming), adjList[incoming].insert(outgoing);
  } return adjList;
}
bool pathExists(LinkedList* adjList, int start, int target, int maxLength) { using result = decltype(pathExists(adjList, start, target, maxLength)) ;
  if (maxLength < 0) return false; if (start == target) return true; int *activePath = new int[maxLength + 1];
  const auto search = [&](const auto& self, const int currentNode, const int currentDistance = 0) -> result {
    if (const auto travelsLeft = (maxLength - currentDistance), foundTarget = static_cast<int>(currentNode == target); 
        (foundTarget or (travelsLeft <= 1))) // found target -> true, last level & no target -> false, 1 level left -> search using method
          return (foundTarget or ((travelsLeft == 1) and adjList[currentNode].search(target)));
    for (int traversedNode = 0; traversedNode < currentDistance; ++traversedNode) 
      if (activePath[traversedNode] == currentNode) return false; // if there is a cycle this path is invalid, terminate search
    // update path and get the first edge of currentNode
    activePath[currentDistance] = currentNode; const auto *edge = adjList[currentNode].get_head();
    
    // traverse all edges of currentNode
    while (edge) { // if is an unexplored edge
      if (self(self, edge->data, (currentDistance + 1))) return true; // recursively explore connected node
      edge = edge->next; // explore next edge
    } return false; // nothing found
  }; const auto found = search(search, start); delete[] activePath; return found;
}