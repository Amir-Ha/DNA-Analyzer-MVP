#ifndef MVP_DATAANALYZER_COMMAND_CONTROLLER_H
#define MVP_DATAANALYZER_COMMAND_CONTROLLER_H
#include "iCommand.h"

class CommandsController
{
public:
    map<string, iCommand*> commandsMap;

    explicit CommandsController();
    bool runController(string commandLine);
};

class CommandParser
{
public:
    static vector<string> parse(const string& commandLine);
};

#endif
