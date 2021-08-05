#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

class DataCreator
{
    public:
        using _1D_Vertices = vector <unsigned int> ;
        using _2D_Vertices = vector <_1D_Vertices>;

    private:
        _2D_Vertices fVert;

    public:
        DataCreator(const string &filePath) { ReadVertFromFile(filePath); }

    public:
        _2D_Vertices &GetVertices(void) { return fVert; };
        unsigned int GetNodesNumber(void) const { return fVert.size(); }

        void ReadVertFromFile(const string &filePath);
};

