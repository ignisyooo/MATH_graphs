#include <iostream>

#include "LIFO.hpp"
#include "DFS.hpp"


static bool *visited;
static uint32_t **cycle;

#define ENTER_TO_VALLEY 1

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

}

static void clean_up(int nodesnn)
{
	/* Clear empty cycles */
	int counter;
	for(int i = 0; i < nodesnn; ++i)
	{
		counter = 0;
		for(int j = 0; j < nodesnn; ++j)
		{
			if(cycle[i][j] == nodesnn)
			{
				counter++;
			}
		}

		if(counter == nodesnn - 1)
		{
			for(int j = 0; j < nodesnn; ++j)
			{
				cycle[i][j] = nodesnn;
			}
		}
	}

	/* Sorting algorithm depending on the input vertex */
	uint32_t *tmp = new uint32_t[nodesnn];
	int it_main = 0;
	int it_tmp = 0;
	int start_value = 0;

	for(int i = 0; i < nodesnn; ++i)
	{
		tmp[i] = nodesnn;
	}

	for(int i = 0; i < nodesnn; ++i)
	{
		if (cycle[i][0] == ENTER_TO_VALLEY || cycle[i][0] == nodesnn)
		{
			continue;
		}
		else
		{
			it_tmp = 0;
			start_value = cycle[i][0];
			tmp[it_tmp++] = ENTER_TO_VALLEY;
			for(it_main = 0; it_main < nodesnn; ++it_main)
			{
				if(cycle[i][it_main] == ENTER_TO_VALLEY)
				{
					break;
				}
			}

			for(int m = it_main + 1; m < nodesnn; ++m)
			{
				if(cycle[i][m] == start_value)
				{
					break;
				}
				tmp[it_tmp++] = cycle[i][m];
			}

			for(int m = 0; m <=it_main; ++m)
			{
				tmp[it_tmp++] = cycle[i][m];
			}

			tmp[--it_tmp] = ENTER_TO_VALLEY;

			for(int m = 0; m < nodesnn; ++m)
			{
				cycle[i][m] = tmp[m];
				tmp[m] = nodesnn;
			}
		}

	}

	delete[] tmp;

}

static void trace(int nodesnn)
{
	int counter = 0;
	int counter_max = 0;
	int best = 0;
	for(int i = 0; i < nodesnn; ++i)
	{
		counter = 0;
		for(int j = 0; j <nodesnn; ++j)
		{
			if(cycle[i][j] != nodesnn)
			{
				counter++;
			}
		}
		if(counter_max < counter)
		{
			counter_max = counter;
			best = i;
		}
	}

	std::cout<<"Here is your way: "<<std::endl;
	for(int i = 0; i < counter_max - 1; ++i)
	{
		std::cout<<"Tomb"<<cycle[best][i]<<" ->";
	}
	std::cout<<"Tomb"<<cycle[best][0];
	std::cout<<std::endl;
	std::cout<<"You robbed "<<counter_max - 1<<" tombs\n";
}


void best_trace(Lifo *list, uint32_t **path_array, int nodesnn)
{

	find_all_traces(list, path_array, nodesnn);
	clean_up(nodesnn);

	trace(nodesnn);

	for(int i = 0; i < nodesnn; ++i)
	{
		delete [] cycle[i];
	}

	delete [] cycle;
	delete [] visited;

}