
#include <string>
#include <fstream>
#include <cstdlib>
#include "DataCreator.hpp"
#include <iostream>


DataCreator::DataCreator(std::string path)
  {
        std::fstream file;
        std::string cmd, photo,line,tmp,nodes,tmp1,tmp2;
        uint16_t index,indexstart,indexstop;
        uint32_t number1,number2;
        cmd = "java -jar plantuml.jar " + path;
        system(cmd.c_str());
        photo = path;
        while (photo.back()!='.')
        {
           photo.pop_back();
        }
        photo.pop_back();
        photo += ".png";
        system(photo.c_str());
        file.open (path,std::ios::in);
        if( file.good() == true )
        {
            while(getline(file,line))
            {
                if (line.find("@startuml") != std::string::npos)
                    continue;
                if (line.find("@enduml") != std::string::npos)
                    continue;
                index = line.find(" ");
                tmp = line.substr(1,index-2);
                if (nodes.find(tmp) == std::string::npos)
                {
                    nodes += tmp;
                    nodes += ", ";
                    //nodes += std::to_string(nmbNodes);
                    nodes += tmp.back();
                    nodes += "; ";
                    nmbNodes++;
                }
                tmp = line.substr(index+4);
                tmp = tmp.substr(0,tmp.size()-1);
                if (nodes.find(tmp) == std::string::npos)
                {
                    nodes += tmp;
                    nodes += ", ";
                    //nodes += std::to_string(nmbNodes);
                    nodes += tmp.back();
                    nodes += "; ";
                    nmbNodes++;
                }
            }
            tab = new uint32_t * [nmbNodes];
            for (uint32_t i = 0; i<nmbNodes; i++)
                tab[i] = new uint32_t [nmbNodes];

            for (uint32_t i = 0; i<nmbNodes; i++)
            {
                for (uint32_t k = 0; k<nmbNodes; k++)
                    tab[i][k] = 0;
            }

            file.close();
        }
        std::cout << nodes << std::endl;
        file.open (path,std::ios::in);
        if( file.good() == true )
        {
            while(getline(file,line))
            {
                if (line.find("@startuml") != std::string::npos)
                    continue;
                if (line.find("@enduml") != std::string::npos)
                    continue;
               index = line.find(" ");
               tmp1 = line.substr(1,index-2);
               tmp2 = line.substr(index+5);
               tmp2 = tmp2.substr(0,tmp2.size()-1);


               index = nodes.find(tmp1);
               tmp = nodes.substr(index);
               index = tmp.find(",");
               tmp = tmp.substr(index+1);
               index = tmp.find(";");
               tmp = tmp.substr(0,index);
               number1 = std::stoi( tmp );

               index = nodes.find(tmp2);
               tmp = nodes.substr(index);
               index = tmp.find(",");
               tmp = tmp.substr(index+1);
               index = tmp.find(";");
               tmp = tmp.substr(0,index);
               number2 = std::stoi( tmp );

               tab[number1][number2] = 1;
               tab[number2][number1] = 1;
            }
        }
}

uint32_t ** DataCreator::GetTab (void)
{
    return tab;
}

uint32_t DataCreator::GetNodesNumber(void)
{
    return nmbNodes;
}