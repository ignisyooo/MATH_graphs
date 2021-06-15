#include <iostream>

#include "LIFO.hpp"
#include "DFS.hpp"


static bool *visited;
static uint32_t **cycle;


static bool DFSfindCycle(int start, int current, int nodesnn, uint32_t **path_array, Lifo *list)
{
	visited[current] = true;
	for (int i = 0; i < nodesnn; i++)
		if (path_array[current][i])
			if (i != list->TopValue())
			{
				list->Push(current);
				if (i == start) return true;
				if (!visited[i] && DFSfindCycle(start, i, nodesnn, path_array, list)) return true;
				list->Pop();
			}
	return false;
}

static void init_cycle_array(int nodesnn)
{
	cycle = new uint32_t *[nodesnn];

	for (int i = 0; i < nodesnn; ++i)
	{
		cycle[i] = new uint32_t[nodesnn];
	}

	for (int i = 0; i < nodesnn; ++i)
	{
		for (int j = 0; j < nodesnn; ++j)
		{
			cycle[i][j] = nodesnn;
		}
	}
}

static void find_all_traces(Lifo *list, uint32_t **path_array, int nodesnn)
{
	int i = 0;
	int j = 0;
	int top_value = 0;

	visited = new bool[nodesnn];

	init_cycle_array(nodesnn);

	for (i = 0; i < nodesnn; ++i)
	{
		for (j = 0; j < nodesnn; ++j)
		{
			visited[j] = false;
		}
		list->Push(-1);
		cycle[i][0] = i;
		if (!DFSfindCycle(i, i, nodesnn, path_array, list))
		{
			list->Pop();
		}
		else
		{
			j = 1;
			while (!list->IsEmpty())
			{
				top_value = list->TopValue();
				list->Pop();
				if (top_value > -1)
				{
					cycle[i][j] = top_value;
				}
				j++;
			}
		}
	}

	for (int i = 0; i < nodesnn; ++i)
    {
        for (int j = 0; j < nodesnn; ++j)
        {
            std::cout<<cycle[i][j]<<", ";
        }
        std::cout<<std::endl;
    }

}

void best_trace(Lifo *list, uint32_t **path_array, int nodesnn)
{
	find_all_traces(list, path_array, nodesnn);

}