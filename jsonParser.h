#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <iostream>
#include <map>
#include <fstream>
#include "english_stem.h"

class jsonParser{ //parses json files
private:
    std::string inParse;
    std::map<std::string, int> outParse; //name and relavency 
public:
    jsonParser(){ //default constructor
        
    }
    jsonParser(std::string *x){ //constructor
        inParse = *x;

    }
    jsonParser(const jsonParser &P){ //copy constructor
        inParse = P.inParse;
        outParse = P.outParse;
    }
    jsonParser operator=(const jsonParser &P){ //assignment operator
        inParse = P.inParse;
        outParse = P.outParse;
        return *this;
    }
    ~jsonParser(){ //destructor 
    }
    void toLower(){ //converts all characters to lowercase
        for(size_t i = 0; i < inParse.length(); i++){
            inParse.at(i) = tolower(inParse.at(i));
        }
    }
    void toAlpha(){ //removes all non-alphabetic characters
        for(size_t i = 0; i < inParse.length(); i++){
            if(inParse.at(i) == 32){
                continue;
            }   
            else if(inParse.at(i) < 96 || inParse.at(i) > 122){
                inParse.erase(i, 1);
                i--;
            }
        }
    }
    void parse(){ //parses string into individual words
        for(size_t i = 0; i < inParse.length(); i++){
            if(i == inParse.length() - 1){}
            else if(inParse.at(i) == 32 && inParse.at(i + 1) == 32){
                inParse.erase(i, 1);
                i--;
            }
            else if(inParse.at(i) == ' ' || inParse.at(i) == '\n' ){
                if(outParse.find(inParse.substr(0, i)) != outParse.end()){
                    outParse.at(inParse.substr(0, i))++;
                }
                else{
                    outParse.insert(std::pair<std::string, int>(inParse.substr(0, i), 1));
                }
                inParse.erase(0, i + 1);
                i = 0;
            }
        }
        outParse.insert(std::pair<std::string, int>(inParse, 1));
    }
    void stopWords(){ //removes stop words
        std::ifstream words;
        std::string stopper;
        words.open("stopWords.txt");
        if(!words.is_open()){
            std::cout << "Error opening stopWords.txt" << std::endl;
            return;
        }
        std::map<std::string, int> stops; //think about ordering/binary search
        int counter = 1;
        while(!words.eof()){
            getline(words, stopper);
            stopper = stopper.substr(0, stopper.length() - 1);
            stops.insert(std::pair<std::string, int>(stopper, counter));
            counter++;
        }
        for(auto i : stops){
            if(outParse.find(i.first) != outParse.end()){
                outParse.erase(i.first);
            }
        }
    }
    void stem() { //stems words (porter2)
    std::map<std::string, int> tempParse;
    for(auto i : outParse){
        std::string temp = i.first;
        std::wstring *wTemp = new std::wstring(i.first.begin(), i.first.end());
        stemming::english_stem<> *stem = new stemming::english_stem<>();
        stem->operator()(*wTemp);
        std::string newKey = std::string(wTemp->begin(), wTemp->end());
        tempParse[newKey] = outParse[temp];
        delete stem;
        delete wTemp;
    }
    outParse = tempParse;
}
    std::map<std::string, int> returnParse(){ //returns map
        return outParse;
    }
};


#endif