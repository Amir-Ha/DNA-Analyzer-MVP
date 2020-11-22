#ifndef MVP_DATAANALYZER_LASTREFERENCE_H
#define MVP_DATAANALYZER_LASTREFERENCE_H
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

class LastReference{
private:
    static int lastCalcRes;
    friend class lenClass;
    friend class CommandsController;
public:
    static size_t checkSharpSharp(vector<string> commands);
    static size_t checkDunder(vector<string> commands);
};
#endif
