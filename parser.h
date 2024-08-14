#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <vector>
#include <fstream>
#include "english_stem.h"
class parser
{
private:
    std::string inParse; 
    std::vector<std::string> *outParse;

public:
    parser() // default constructor
    {
        outParse = new std::vector<std::string>;
    }
    parser(std::string *x) // constructor
    {
        inParse = *x;
        outParse = new std::vector<std::string>;
    }
    parser(const parser &P) // copy constructor
    { 
        inParse = P.inParse;
        outParse = P.outParse;
    }
    parser operator=(const parser &P) // assignment operator
    {
        inParse = P.inParse;
        outParse = P.outParse;
        return *this;
    }
    ~parser() // destructor
    {
        delete outParse;
    }
    void toLower() // converts all characters to lowercase
    {
        for (size_t i = 0; i < inParse.length(); i++)
        {
            inParse.at(i) = tolower(inParse.at(i));
        }
    }
    void toAlpha() // removes all non-alphabetic characters
    {
        for (size_t i = 0; i < inParse.length(); i++)
        {
            if (inParse.at(i) == 32)
            {
                continue;
            }
            else if (inParse.at(i) < 96 || inParse.at(i) > 122)
            {
                inParse.erase(i, 1);
                i--;
            }
        }
    }
    void parse() // parses string into individual words
    {
        for (size_t i = 0; i < inParse.length(); i++)
        {
            if (inParse.at(i) == ' ' || inParse.at(i) == '\n')
            {
                outParse->push_back(inParse.substr(0, i));
                inParse.erase(0, i + 1);
                i = 0;
            }
        }
        outParse->push_back(inParse);
    }
    void stem() // stems words
    {
        for (size_t i = 0; i < outParse->size(); i++)
        {
            std::wstring *wTemp = new std::wstring(outParse->at(i).begin(), outParse->at(i).end());
            stemming::english_stem<> *stem = new stemming::english_stem<>();
            stem->operator()(*wTemp);
            outParse->at(i) = std::string(wTemp->begin(), wTemp->end());
            delete stem;
            delete wTemp;
        }
    }
    void stopWords() // removes stop words
    {
        std::ifstream words;         // create our ifstream
        std::string stopper;         // create our stopper string
        words.open("stopWords.txt"); // open the stopWords file with all of the stop words
        if (!words.is_open())
            std::cout << "error accessing stop words" << std::endl;

        std::vector<std::string> *stops = new std::vector<std::string>; // think about ordering/binary search
        while (!words.eof())
        {
            getline(words, stopper);
            stopper = stopper.substr(0, stopper.length() - 1);
            stops->push_back(stopper);
        }
        for (size_t i = 0; i < outParse->size(); i++)
        { // iterate through each word in the article
            for (size_t j = 0; j < stops->size(); j++)
            {
                if (outParse->at(i) == stops->at(j))
                {
                    outParse->erase(outParse->begin() + i);
                    i = 0;
                }
            }
        }
        delete stops;
        words.close();
    }
    std::vector<std::string> returnParse(){ // returns the parsed vector
        for(size_t i = 0; i < outParse->size(); i++){
            if(outParse->at(i) == ""){
                outParse->erase(outParse->begin() + i);
                i = 0;
            }
        }
        return *outParse;
    }
};
#endif