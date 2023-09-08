#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "RPNClass/RPN.h"
#include "VariableStruc/Variable.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Reverse Polish Number Calculator
    //Alek Bronsky

    //Create RPN class with a the stack inside
    RPN rpn = RPN();
    
    //Runner Code
    cout << "\nWelcome to the RPN Calculator | Use Spaces to divide numbers and operators\n! is factorial\nType \"exit\" to quit the program.\n" << endl << ">";
    string input;
    //get the line input
    getline(cin , input);
    
    
    while (input != "exit")
    {
        //input would look like 4 3 + 4 5 + + .

        rpn.iterate_string(input);

        //Get user input for next loop
        cout << "\n> ";
        getline(cin, input);
    }

    //For variables
    // Have two different vectors one for the name and one for the value each stored at the same location so that you can
    // search for the name of the var
    //Or have a struct
    
    return 0;
}
