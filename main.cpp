#include "DataCreator.hpp"
#include "LIFO.hpp"
#include "DFS.hpp"
#include <iostream>




int main (void)
{
    DataCreator *d = new DataCreator("uml.txt");

    auto **path_table = d->GetTab();

    Lifo *list = new Lifo();

    find_all_traces(list, path_table, d->GetNodesNumber());


    return 0;
}
