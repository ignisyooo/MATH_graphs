#ifndef DATACREATOR_HPP_INCLUDED
#define DATACREATOR_HPP_INCLUDED

#include <string>



class DataCreator
{
    public:
        DataCreator(std::string path);
        uint32_t ** GetTab (void);
        uint32_t GetNodesNumber(void);

    private:
        uint32_t ** tab;
        uint32_t nmbNodes;
};


#endif // DATACREATOR_HPP_INCLUDED
