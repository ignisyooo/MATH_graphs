<<<<<<< HEAD
﻿// TombsSearching.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "DataCreator.hpp"
#include "LIFO.hpp"
#include "DFS.hpp"
#include <iostream>

int main()
{
    DataCreator* d = new DataCreator("uml.txt");

    auto** path_table = d->GetTab();

    Lifo* list = new Lifo();

    best_trace(list, path_table, d->GetNodesNumber());

    system("pause");

    return 0;

}
=======
﻿// TombsSearching.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "DataCreator.hpp"
#include "LIFO.hpp"
#include "DFS.hpp"
#include <stdlib.h>

int main()
{
    DataCreator* d = new DataCreator("uml.txt");

    auto** path_table = d->GetTab();

    Lifo* list = new Lifo();

    best_trace(list, path_table, d->GetNodesNumber());

    system("pause");

    return 0;

}
>>>>>>> feature_branch
