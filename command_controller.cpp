#include "command_controller.h"
#include <sstream>
#include "lastReference.h"
CommandsController::CommandsController()
{
    commandsMap.insert(pair<string, iCommand*>("new", new newCommand(new newClass)));
    commandsMap.insert(pair<string, iCommand*>("load", new loadCommand(new loadClass)));
    commandsMap.insert(pair<string, iCommand*>("save", new saveCommand(new saveClass)));
    commandsMap.insert(pair<string, iCommand*>("dup", new dupCommand(new dupClass)));
    commandsMap.insert(pair<string, iCommand*>("slice", new sliceCommand(new sliceClass)));
    commandsMap.insert(pair<string, iCommand*>("replace", new replaceCommand(new replaceClass)));
    commandsMap.insert(pair<string, iCommand*>("concat", new concatCommand(new concatClass)));
    commandsMap.insert(pair<string, iCommand*>("pair", new pairCommand(new pairClass)));
//    commandsMap.insert(pair<string, iCommand*>("atindex", new atIndexCommand(new atIndexClass)));
    commandsMap.insert(pair<string, iCommand*>("len", new lenCommand(new lenClass)));
}

bool CommandsController::runController(string commandLine)
{
    size_t indexResult = -1;
    ostringstream oss;
    vector<string> commandDivided = CommandParser::parse(commandLine);
    if(commandDivided.size() < 2)
        return false;
    string operation = commandDivided.at(0);
    commandDivided.erase(commandDivided.begin());
    if((indexResult = LastReference::checkSharpSharp(commandDivided)) != -1)
    {
        oss << Indexed_DNA_Sequence::dnaVector.size();
        commandDivided.at(indexResult) = oss.str();
    }
    if((indexResult = LastReference::checkDunder(commandDivided)) != -1)
    {
        oss.str("");
        oss << LastReference::lastCalcRes;
        commandDivided.at(indexResult) = oss.str();
    }
    commandsMap.at(operation)->runCommand(commandDivided);
    return true;
}

vector<string> CommandParser::parse(const string& commandLine) {
    vector<string> tokens;
    istringstream iss(commandLine);
    copy(istream_iterator<string>(iss),istream_iterator<string>(), back_inserter(tokens));
    return tokens;
}
