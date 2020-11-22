#include <iostream>
#include "command_controller.h"

int main() {
    CommandsController commandsController;
    string input;
    cout << "[new, save, load, dup, slice, replace, concat, pair, len] \nquit to exit--\n> cmd >>> ";
    while((getline(cin, input)))
    {
        if(input == "quit"){
            cout << "Good-Bye :)" << endl;
            break;
        }
        try{
            if(!commandsController.runController(input))
                cout << "command format: command sequence (optional: name)" << endl;
        }catch(const char* msg)
        {
            cout << msg << endl;
        }
        cout << "[new, save, load, dup, slice, replace, concat, pair, len] \nquit to exit--\n> cmd >>> ";
    }
    return 0;
}