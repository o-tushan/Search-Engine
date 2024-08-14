#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H
#include <iostream>
#include <vector>
#include "parser.h"
class queryHandler
{
private:
    
    std::vector<std::string> *words; // words to search for
    std::vector<std::string> *orgs; // orgs to search for 
    std::vector<std::string> *names; // names to search for
        std::vector<std::string> *excludeWords; // words to exclude
        parser *parse; // parser object
        std::string *input; // user input

    public:
        
        queryHandler() // default constructor
        {
            input = new std::string; 
            words = new std::vector<std::string>;  
            orgs = new std::vector<std::string>; 
            names = new std::vector<std::string>;
            excludeWords = new std::vector<std::string>;
            parse = new parser;
        }
        queryHandler(const queryHandler &QH) // copy constructor
        {
            input = new std::string(*QH.input);
            words = new std::vector<std::string>(*QH.words);
            orgs = new std::vector<std::string>(*QH.orgs);
            names = new std::vector<std::string>(*QH.names);
            excludeWords = new std::vector<std::string>(*QH.excludeWords);
            parse = new parser(*QH.parse);
        }
        queryHandler(std::string *input) // constructor with input
        {
            this->input = new std::string(*input);
            words = new std::vector<std::string>;
            orgs = new std::vector<std::string>;
            names = new std::vector<std::string>;
            excludeWords = new std::vector<std::string>;
            parse = new parser;
        }
    queryHandler operator=(const queryHandler &QH) // assignment operator
    {
        input = QH.input;
        words = QH.words;
        orgs = QH.orgs;
        names = QH.names;
        excludeWords = QH.excludeWords;
        parse = QH.parse;
        return *this;
    }
    ~queryHandler() // destructor
    {
        delete words;
        delete orgs;
        delete names;
        delete excludeWords;
        delete parse;
        delete input;
    }
    void userInput() // gets user input
    {
        std::cout << "Enter query: ";
        std::getline(std::cin, *input);
    }
    void smartParse() // parses user input but smarter
    {
        for (size_t i = 0; i < input->length(); i++) // goes through input char by char
        {
            if(i == input->length() - 1) // if at the end of the input
            {
                break;
            }
            if (input->at(0) == 32) // if there is a space at the beginning
            {
                input->erase(0, 1);
                i = 0;
            }
            if (input->at(i) == 32 && input->at(i + 1) == 32) // if there are two spaces in a row
            {
                input->erase(i, 1);
                i = 0;
            }
            if (input->at(i) == 'O' && input->at(i + 1) == 'R' && input->at(i + 2) == 'G' && input->at(i + 3) == ':') //if org
            {
                size_t j = i + 4;
                size_t counter = 0;
                while (input->at(j) != ' ' && input->at(j) != '\n' && j < input->length() - 1)
                {
                    counter++;
                    j++;
                }
                if(j == input->length() - 1)
                {
                    counter++;
                    j++;
                }
                orgs->push_back(input->substr(i + 4, counter)); // adds org to vector
                input->erase(i, counter + 4);
                i = 0;
            }
            else if (input->at(i) == 'P' && input->at(i + 1) == 'E' && input->at(i + 2) == 'R' && input->at(i + 3) == ':') // if person
            {
                size_t j = i + 4; // Obama function
                size_t counter = 0;
                while (input->at(j) != ' ' && input->at(j) != '\n' && j < input->length() - 1)
                {
                    counter++;
                    j++;
                }
                if(j == input->length() - 1)
                {
                    counter++;
                    j++;
                }
                names->push_back(input->substr(i + 4, counter)); // adds name to vector
                input->erase(i, counter + 4);
                i = 0;
            }
            else if (input->at(i) == '-') // if exclude
            {
                size_t j = i + 1;
                size_t counter = 0;
                while (input->at(j) != ' ' && input->at(j) != '\n' && j < input->length() - 1)
                {
                    counter++;
                    j++;
                }
                if(j == input->length() - 1)
                {
                    counter++;
                    j++;
                }
                excludeWords->push_back(input->substr(i + 1, counter)); // adds exclude word to vector
                input->erase(i, counter + 1);
                i = 0;
            }
        }
    }
    void wordParse() //parses input
    {   
        if(parse != nullptr){
            delete parse;
        }
        parse = new parser(input);
        parse->toLower();
        parse->toAlpha();
        parse->parse();
        parse->stem();
        parse->stopWords();
        *words = parse->returnParse(); // toLower words/orgs

        for(size_t i = 0; i < excludeWords->size(); i++) //parses exclude words
        {
            delete parse;
            parse = new parser(&excludeWords->at(i));
            parse->toLower();
            parse->toAlpha();
            parse->parse();
            parse->stem();
            std::string temp = parse->returnParse().at(0);
            excludeWords->at(i) = temp;
        }
    }
    std::vector<std::string> getWords() // getters
    {
        return *words;
    }
    std::vector<std::string> getOrgs() // getters
    {
        return *orgs;
    }
    std::vector<std::string> getNames() // getters
    {
        return *names;
    }
    std::vector<std::string> getExcludeWords() // getters
    {
        return *excludeWords;
    }
};
#endif