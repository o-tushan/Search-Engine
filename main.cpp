#include <iostream>
#include "UserInterface.h"

int main(int argc, char const *argv[])
{
    UserInterface *UI = new UserInterface();
    if(argc == 1){
        UI->help();
        return 0;
    }
    std::string command = argv[1];
    if(command == "index"){
        std::cout << "Indexing..." << std::endl;
        UI->index(argv[2]);
    }
    if(command == "query"){
        UI->query(argv[2]);
    }
    if(command == "UI"){
        UI->UI();
    }
    
    delete UI;
    return 0;
}