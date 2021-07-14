#include <iostream>

#include "LIFO.hpp"
#include "DFS.hpp"


static bool *visited;
static uint32_t **cycle;

static int* tombs, * cycle_of_tombs;

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
	for (int i = 0; i < nodesnn; ++i)
	{
		counter = 0;
		for (int j = 0; j < nodesnn; ++j)
		{
			if (cycle[i][j] == nodesnn)
			{
				counter++;
			}
		}

		if (counter == nodesnn - 1)
		{
			for (int j = 0; j < nodesnn; ++j)
			{
				cycle[i][j] = nodesnn;
			}
		}
	}

	/* Sorting algorithm depending on the input vertex */
	uint32_t* tmp = new uint32_t[nodesnn];
	int it_main = 0;
	int it_tmp = 0;
	int start_value = 0;

	for (int i = 0; i < nodesnn; ++i)
	{
		tmp[i] = nodesnn;
	}

	for (int i = 0; i < nodesnn; ++i)
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
			for (it_main = 0; it_main < nodesnn; ++it_main)
			{
				if (cycle[i][it_main] == ENTER_TO_VALLEY)
				{
					break;
				}
			}

			for (int m = it_main + 1; m < nodesnn; ++m)
			{
				if (cycle[i][m] == start_value)
				{
					break;
				}
				tmp[it_tmp++] = cycle[i][m];
			}

			for (int m = 0; m <= it_main; ++m)
			{
				tmp[it_tmp++] = cycle[i][m];
			}

			tmp[--it_tmp] = ENTER_TO_VALLEY;

			for (int m = 0; m < nodesnn; ++m)
			{
				cycle[i][m] = tmp[m];
				tmp[m] = nodesnn;
			}
		}

	}

	delete[] tmp;

}

static void DeleteTheSameCycles(int nodesnn)
{
	int counter = 0;

	for (int i = 0; i < nodesnn; ++i)
	{
		if (cycle[i][0] == nodesnn)
		{
			continue;
		}
		else
		{
			for (int j = 0; j < nodesnn; ++j)
			{
				if (j == i)
				{
					continue;
				}
				else
				{
					counter = 0;
					for (int m = 0; m < nodesnn; ++m)
					{
						if (cycle[j][m] == cycle[i][m])
						{
							counter++;
						}
					}

					if (counter == nodesnn)
					{
						for (int m = 0; m < nodesnn; ++m)
						{
							cycle[j][m] = nodesnn;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < nodesnn; ++i)
	{
		if (cycle[i][0] == nodesnn || cycle[i][0] == 0)
		{
			continue;
		}
		else
		{
			for (int j = 0; j < nodesnn; ++j)
			{
				cycle[i][j] = nodesnn;
			}
		}
	}

}

void check_traces(int nodesnn, uint32_t** path_array)
{
	tombs = new int[nodesnn];
	int counter = 0;
	for (int i = 0; i < nodesnn; ++i)
	{
		tombs[i] = 0;
	}

	for (int i = 0; i < nodesnn; ++i)
	{
		counter = 0;
		for (int j = 0; j < nodesnn; ++j)
		{
			if (path_array[i][j] == 1)
			{
				counter++;
			}
		}

		if (counter == 1)
		{
			for (int j = 0; j < nodesnn; ++j)
			{
				if (path_array[i][j] == 1)
				{
					tombs[j]++;
				}
			}
		}
	}
}

void count_tombs(int nodesnn)
{
	cycle_of_tombs = new int[nodesnn];
	for (int i = 0; i < nodesnn; ++i)
	{
		cycle_of_tombs[i] = 0;
	}

	for (int i = 0; i < nodesnn; ++i)
	{
		if (cycle[i][0] == 0)
		{
			cycle_of_tombs[i] = 0;
			for (int j = 0; j < nodesnn; ++j)
			{
				if (cycle[i][j] == nodesnn)
				{
					break;
				}
				else
				{
					cycle_of_tombs[i] += tombs[cycle[i][j]];
				}
			}
			cycle_of_tombs[i] -= tombs[0];
		}
	}
}

void select_best_traces(int nodesnn)
{
	int max = 0;
	int max_index = 0;
	for (int i = 0; i < nodesnn; ++i)
	{
		if (cycle_of_tombs[i] > max)
		{
			max_index = i;
			max = cycle_of_tombs[i];
		}
	}

	std::cout << "Best trace: ";
	for (int i = 0; i < nodesnn; ++i)
	{
		if (cycle[max_index][i] == nodesnn)
		{
			break;
		}
		std::cout << cycle[max_index][i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "Plundered tombs: " << max << std::endl;
}

void best_trace(Lifo *list, uint32_t **path_array, int nodesnn)
{

	find_all_traces(list, path_array, nodesnn);
	clean_up(nodesnn);
	DeleteTheSameCycles(nodesnn);

	check_traces(nodesnn, path_array);
	count_tombs(nodesnn);
	select_best_traces(nodesnn);

	for(int i = 0; i < nodesnn; ++i)
	{
		delete [] cycle[i];
	}

	delete [] cycle;
	delete [] visited;
	delete[] cycle_of_tombs;
	delete[] tombs;


}