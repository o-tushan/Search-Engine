#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "handler.h"
#include <iostream>
#include <sstream>

class UserInterface{
private:
    handler *handle = new handler(); //handler object

public:
    UserInterface(){ //default constructor
    }
    UserInterface(const UserInterface &UI){ //copy constructor
        handle = UI.handle;
    }
    UserInterface operator=(const UserInterface &UI){ //assignment operator
        handle = UI.handle;
        return *this;
    }
    ~UserInterface(){ //destructor
        delete handle;
    }
    void help(){ //help function (called automatically)
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "Type supersearch followed by index, query, or UI" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "for index, type supersearch index followed by the directory" << std::endl;
        std::cout << "for query, type supersearch query followed by your search terms" << std::endl;
        std::cout << "for UI, type supersearch UI and a simple menu will pop up" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "To quit the program, simply type quit" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
    }
    void index(std::string directory){ //index function (creates an index) -quick
        if(!std::filesystem::exists("stored_data")){ //checks if directory exists, if not, creates it
            std::filesystem::create_directory("stored_data");
        }
        std::filesystem::path directoryPath = "stored_data";
        handle->jParse(directory);
        handle->store(directory);
        std::cout << "Index: "  << directory <<  " created" << std::endl;
    }
    void query(std::string terms){ //query function (queries an index) -quick
        std::filesystem::path directoryPath = "stored_data";
        std::cout << "Indexes available: " << std::endl;
                for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
                    if (entry.is_directory()) {
                        std::cout << entry.path().filename().string() << std::endl;
                    }
                }
        std::cout << "Enter the name of the index you want to query: ";
        std::string indexName;
        std::getline(std::cin, indexName);
        handle->load(indexName);
        handle->Query(terms);

    }
    void UI(){ //UI function (simple menu) - mainly used for reusing and storing indexes
        while(true){
            std::cout << "------------------------------------------------" << std::endl;
            std::cout << "Type L <index-name> to load an index" << std::endl; //load index
            std::cout << "Type I <directory> to create an index" << std::endl; //create index
            std::cout << "Type Q <query> to query an index" << std::endl; //query index
            std::cout << "Type S <index-name> to store an index" << std::endl; //store index
            std::cout << "Type D to display current indexes" << std::endl; //display indexes
            std::cout << "Type E to exit back to normal command line" << std::endl; //exit
            std::cout << "------------------------------------------------" << std::endl;
            std::string entry;
            std::getline(std::cin, entry);
            std::istringstream ss(entry);
            std::string wordOne;
            std::getline(ss, wordOne, ' ');
            for(size_t i = 0; i < wordOne.size(); i++){
                wordOne.at(i) = tolower(wordOne.at(i));
            }
            if(wordOne == "l"){ //load index
                std::string indexName;
                std::getline(ss, indexName, '\n');
                handle->load(indexName);
            }
            else if(wordOne == "i"){ //create index
                std::string directory;
                std::getline(ss, directory, '\n');
                handle->jParse(directory);
                std::cout<< "Index created" << std::endl;
            }
            else if(wordOne == "q"){ //query index
                clock_t start = clock();
                std::string query;
                std::getline(ss, query, '\n');
                if(query == ""){
                    std::cout << "Error - you didn't enter a query" << std::endl;
                    continue;
                }
                handle->Query(query);
                clock_t end = clock();
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                std::cout << "Query took " << elapsed << " seconds" << std::endl;
            }
            else if(wordOne == "s"){ //store index
                std::string indexName;
                std::getline(ss, indexName, '\n');
                handle->store(indexName);
            }
            else if ( wordOne == "d") { //display indexes
                std::filesystem::path directoryPath = "stored_data";

                for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
                    if (entry.is_directory()) {
                        std::cout << entry.path().filename().string() << std::endl;
                    }
                }
            }
            else if(wordOne == "e"){ //exit
                break;
            }
            else{
                std::cout << "Error - didn't recognize your input. Please use a recognized function,type help for more info, or type quit" << std::endl;
                
                continue;
            }
        }
    }

};
#endif