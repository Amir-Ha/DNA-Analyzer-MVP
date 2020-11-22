#include "lastReference.h"

int LastReference::lastCalcRes = 0;

size_t LastReference::checkSharpSharp(vector<string> commands)
{
    for(size_t i = 0; i<commands.size(); i++)
    {
        if(commands.at(i) == "##")
            return i;
    }
    return -1;
}

size_t LastReference::checkDunder(vector<string> commands)
{
    for(size_t i = 0; i<commands.size(); i++)
    {
        if(commands.at(i) == "__")
            return i;
    }
    return -1;
}