#ifndef DFS_HPP
#define DFS_HPP

#include <iostream>
#include "LIFO.hpp"

void find_all_traces(Lifo *list, uint32_t **path_array, int nodesnn);
bool DFSfindCycle(int start, int current, int nodesnn, uint32_t **path_array, Lifo *list);

#endif /* DFS_HPP*/