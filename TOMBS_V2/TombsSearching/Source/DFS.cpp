#include <iostream>
#include <filesystem>


#include "../Include/DFS.hpp"

using Dim = DataCreator::_2D_Vertices::size_type;

DataCreator::_2D_Vertices cycles;

std::ostream &operator << (std::ostream &o, const DataCreator::_2D_Vertices &data)
{
    for(const auto &row : data)
    {
        for(const auto &val : row)
            o << val << " ";
        o << std::endl;
    }

    return o;
}

void TombsAlgo::InitCycleVector(void)
{
    cycles.resize(data.GetNodesNumber());
    for(auto &row : cycles)
    {
        row.resize(data.GetNodesNumber());
        for(auto &val : row)
            val = data.GetNodesNumber();
    }
}

bool TombsAlgo::DFSfindCycle(unsigned int start, unsigned int current)
{
	visit[current] = 1;
	for(int i = 0; i < data.GetNodesNumber(); ++i)
    {
		if(data.GetVertices()[current][i])
			if(i != list.GetTopValue())
			{
				list.push(current);
				if(i == start)
                    return true;
				if(!visit[i] && DFSfindCycle(start, i))
                    return true;
				list.pop();
			}
    }

	return false;
}


void TombsAlgo::FindAllTraces(void)
{
    for(int i = 0; i < data.GetNodesNumber(); ++i)
    {
        list.push(-1);
        cycles[i][0] = i;

        for(auto &val: visit)
            val = 0;

        if(!DFSfindCycle(i, i))
            list.pop();
        else
        {
            int j {1};
			while(!list.isEmpty())
			{
				if (list.GetTopValue() > -1)
					cycles[i][j] = list.GetTopValue();
                list.pop();
				j++;
			}
        }
    }
}

void TombsAlgo::SortCycles(void)
{
    // Remove empty cycles
    for(auto &row : cycles)
    {
        unsigned int EmptySpaceCtr {0};
        for(auto &val : row)
            if(val == data.GetNodesNumber())
                EmptySpaceCtr++;

        if(EmptySpaceCtr == data.GetNodesNumber() - 1)
            for(auto &val : row)
                val = data.GetNodesNumber();
    }

    // sort cycles from 0
    DataCreator::_1D_Vertices tmp(data.GetNodesNumber(), data.GetNodesNumber());
    int it_tmp {0}, it_main {0}, start_value {0};

    for(int i = 0; i < data.GetNodesNumber(); ++i)
    {
        if(cycles[i][0] == 0 || cycles[i][0] == data.GetNodesNumber())
            continue;
        else
        {
			it_tmp = 0;
			start_value = cycles[i][0];
			tmp[it_tmp++] = 0;
			for (it_main = 0; it_main < data.GetNodesNumber(); ++it_main)
			{
				if (cycles[i][it_main] == 0)
					break;
			}

			for (int m = it_main + 1; m < data.GetNodesNumber(); ++m)
			{
				if (cycles[i][m] == start_value)
					break;
				tmp[it_tmp++] = cycles[i][m];
			}

			for (int m = 0; m <= it_main; ++m)
				tmp[it_tmp++] = cycles[i][m];

			tmp[--it_tmp] = 0;

			for (int m = 0; m < data.GetNodesNumber(); ++m)
			{
				cycles[i][m] = tmp[m];
				tmp[m] = data.GetNodesNumber();
			}
		}
    }
}

DataCreator::_1D_Vertices TombsAlgo::TombsChecker(void)
{
    DataCreator::_1D_Vertices Tombs (data.GetNodesNumber(), 0);

    for(int i = 0; i < data.GetNodesNumber(); ++i)
    {
        unsigned int cntr {0};
        for(int j = 0; j < data.GetNodesNumber(); ++j)
            if(data.GetVertices()[i][j] == 1) cntr++;

        if(cntr == 1)
            for(int j =0; j < data.GetNodesNumber(); ++j)
                if(data.GetVertices()[i][j] == 1) Tombs[j]++;
    }

    return Tombs;
}

void TombsAlgo::BestTrace(const DataCreator::_1D_Vertices &tombs)
{
    DataCreator::_1D_Vertices best_cycle (data.GetNodesNumber(), 0);

    for(int i = 0; i < data.GetNodesNumber(); ++i)
    {
        if(cycles[i][0] == 0)
        {
            best_cycle[i] = 0;
            for(int j  = 0; j < data.GetNodesNumber(); ++j)
                if(cycles[i][j] == data.GetNodesNumber()) break;
                else best_cycle[i] += tombs[cycles[i][j]];
            best_cycle[i] -= tombs[0];
        }
    }

    int max {0}, max_index {0};

    for(int i = 0; i < data.GetNodesNumber(); ++i)
    {
        if(best_cycle[i] > max)
        {
            max = best_cycle[i];
            max_index = i;
        }
    }

    std::cout << "Follow the cycle: ";
    for(int i = 0; i < data.GetNodesNumber(); ++i)
    {
        if(cycles[max_index][i] == data.GetNodesNumber())
            break;
        std::cout<< cycles[max_index][i] <<", ";
    }

    std::cout<<std::endl;
    std::cout << "With this cycle, you will be able to rob "<< max << " tombs"<< std::endl;
}


void Run(const string &file_path)
{
    DataCreator data(file_path);
    List list;

    TombsAlgo algo(data, list);

    algo.FindAllTraces();
    algo.SortCycles();

    DataCreator::_1D_Vertices tombs = algo.TombsChecker();

    unsigned int cnt {0};

    for(const auto &elem : tombs)
        if(elem) cnt++;

    if(cnt == 0)
    {
        std::cout<< "No tombs to be robbed could be found" << std::endl;
        exit(1);
    }

    algo.BestTrace(tombs);


}

void Run(void)
{
    const string file_path ("../Tombs.txt");

    namespace fs = std::filesystem;

    if(fs::exists(file_path))
    {
        Run(file_path);
    }
}
