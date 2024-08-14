#ifndef JSONREADER_H
#define JSONREADER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>

#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "jsonParser.h"

using namespace rapidjson;

class jsonReader{

private:

    Document doc; 
    std::map<int, std::map<std::string, int>> terms;
    std::map<int, std::vector<std::string>> names;
    std::map<int, std::vector<std::string>> orgs;
    std::map<int, std::string> articleName;

public:
    jsonReader(){ //default constructor

    }
    void readJson(const std::string &fileName, int key){ //reads json file and stores data in maps

        std::ifstream input;

        input.open(fileName);
        if(!input.is_open()){
            std::cout << "Error opening " << fileName << std::endl;
        }

        IStreamWrapper wrapper(input);

        doc.ParseStream(wrapper);

        auto personNames = doc["entities"]["persons"].GetArray(); //gets person names from json file
        std::vector<std::string> personNamesVec;
        for(auto &p : personNames){
            personNamesVec.push_back(p["name"].GetString());
        }
        names.insert(std::pair<int, std::vector<std::string>>(key, personNamesVec)); //stores person names in map
        
        auto orgNames = doc["entities"]["organizations"].GetArray(); //gets organization names from json file
        std::vector<std::string> orgNamesVec;
        for(auto &o : orgNames){
            orgNamesVec.push_back(o["name"].GetString());
        }
        orgs.insert(std::pair<int, std::vector<std::string>>(key, orgNamesVec)); //stores organization names in map

        auto textIn = doc["text"].GetString(); //gets text from json file
        std::string text(textIn);
        auto titleIn = doc["title"].GetString(); //gets title from json file
        std::string title(titleIn);
        articleName.insert(std::pair<int, std::string>(key, title)); //stores title in map

        text.append(" ");
        text.append(title);
        jsonParser *parse = new jsonParser(&text); //creates parser object
        parse->toLower(); //calls parser functions
        parse->toAlpha(); 
        parse->parse();
        parse->stopWords();
        parse->stem();
        terms.insert(std::pair<int, std::map<std::string, int>>(key, parse->returnParse())); //stores terms in map
        delete parse;
    }

    void jsonFileSystem(std::string path){ //reads all json files in a directory and stores data in maps
        
        auto val = std::filesystem::recursive_directory_iterator(path);
        int counter = 1;
        for(auto &entry : val){
            int key = 1000000 - counter;
            counter++;
            if (entry.is_regular_file() && entry.path().extension().string() == ".json"){
                readJson(entry.path().string(), key);
            }
        }
    }

    std::map<int, std::map<std::string, int>> getTerms(){ //returns maps
        return terms;
    }

    std::map<int, std::vector<std::string>> getNames(){ 
        return names;
    }

    std::map<int, std::vector<std::string>> getOrgs(){
        return orgs;
    }

    std::map<int, std::string> getArticleNames(){
        return articleName;
    }
};
#endif