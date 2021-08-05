#pragma once

#include "../Include/dataCreator.hpp"
#include "../Include/LIFO.hpp"


using Dim = DataCreator::_2D_Vertices::size_type;

class TombsAlgo
{
    private:
         DataCreator::_1D_Vertices visit;
         DataCreator::_2D_Vertices cycles;

         DataCreator data;
         List list;

    public:
        TombsAlgo(DataCreator &_data, List &_list)
            : data(_data), list(_list) {
                InitCycleVector();
                visit.resize(data.GetNodesNumber());
            };

    public:
        DataCreator::_2D_Vertices &GetCycles(void) { return cycles; }
        DataCreator GetData(void) const {return data;}
        void FindAllTraces(void);
        void InitCycleVector(void);
        bool DFSfindCycle(unsigned int start, unsigned int current);
        void SortCycles(void);
        DataCreator::_1D_Vertices TombsChecker(void);
        void BestTrace(const DataCreator::_1D_Vertices &tombs);

    friend std::ostream &operator << (std::ostream &o, const DataCreator::_2D_Vertices &data);
};

void Run(const string &file_path);
void Run(void);

