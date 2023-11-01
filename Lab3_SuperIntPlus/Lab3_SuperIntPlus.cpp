#include "RPNClass/RPN.h"
#include <random>

int main(int argc, char* argv[])
{
    //Reverse Polish Number Calculator with super ints plus
    //Alek Bronsky

    // Create RPN class with a the stack inside
    RPN rpn = RPN();
    
    // Runner Code
    std::cout << "\nWelcome to the RPN Calculator | Use Spaces to divide numbers and operators\n! is factorial\nType \"exit\" to quit the program.\n" << std::endl << ">";
    std::string input;
 
    getline(std::cin , input);
    
    while (input != "exit")
    {
        // Input will look like 4 3 + 4 5 + +

        rpn.iterate_string(input);

        // Get user input for next loop
        std::cout << "\n> ";
        getline(std::cin, input);
    }
    return 0;
}
