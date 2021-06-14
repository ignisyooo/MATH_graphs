#ifndef DATACREATOR_HPP_INCLUDED
#define DATACREATOR_HPP_INCLUDED

#include <string>



class DataCreator
{
    public:
    DataCreator(std::string path);
    uint32_t ** GetTab (void);

    private:
        uint32_t ** tab;
};


#endif // DATACREATOR_HPP_INCLUDED
