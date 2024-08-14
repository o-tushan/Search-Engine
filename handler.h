#ifndef HANDLER_H
#define HANDLER_H
#include "jsonReader.h"
#include "queryHandler.h"
#include "TermsTreeV2.h"
#include "WriterTree.h"
#include "OrganizationTree.h"
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
class handler
{
private:
    std::map<int, std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>> articles; // docID, articleName, {writerNames, orgNames}
    TermsTree *termsTree = new TermsTree(); // term, docID, relevancy
    WriterTree *writersTree = new WriterTree(); // writerName, docID
    OrganizationTree *orgsTree = new OrganizationTree(); // orgName, docID
    jsonReader *reader = new jsonReader(); // jsonReader
    queryHandler *query = new queryHandler(); // queryHandler

public:
    handler() //default constructor
    {
    }
    handler(const handler &H) //copy constructor
    {
        reader = H.reader;
        query = H.query;
    }
    handler operator=(const handler &H) //copy assignment
    {
        reader = H.reader;
        query = H.query;
        return *this;
    }
    ~handler() //destructor
    {
        delete writersTree;
        delete orgsTree;
        delete termsTree;
        delete reader;
        delete query;
    }
    void jParse(std::string directory) //json parser
    {
        reader->jsonFileSystem(directory);
        std::map<int, std::map<std::string, int>> terms = reader->getTerms();     // docID, term, relevancy
        std::map<int, std::vector<std::string>> writerNames = reader->getNames(); // docID, writerNames
        std::map<int, std::vector<std::string>> orgs = reader->getOrgs();         // docID, orgs
        std::map<int, std::string> articleNames = reader->getArticleNames();      // docID, articleName
        // write a for loop that inputs into the three trees using their input functions, and the article maps
        for (const auto &term : terms)
        {
            int docID = term.first;
            if (writerNames.count(docID) > 0 && orgs.count(docID) > 0 && articleNames.count(docID) > 0) // if the article has a writer, org, and name
            {
                articles.insert({docID, {articleNames[docID], {writerNames[docID], orgs[docID]}}}); // insert the article into the articles map
            }
            for (const auto &word : term.second)
            {
                termsTree->insert(word.first, docID, word.second); // insert the term into the terms tree
            }
            for (const auto &name : writerNames[docID])
            {
                writersTree->insert(name, docID); // insert the writer into the writers tree
            }
            for (const auto &org : orgs[docID])
            {
                orgsTree->insert(org, docID); // insert the org into the orgs tree
            }
        }
    }
void store(std::string directory) //store function
{
    // Create a directory in the current working directory
    std::string path = "./stored_data/" + directory;
    mkdir(path.c_str(), 0777);

    // Store trees
    termsTree->store(path + "/Terms.txt");
    writersTree->store(path + "/Writers.txt");
    orgsTree->store(path + "/Orgs.txt");

    // Store articleNames map in a text file
    std::ofstream file(path + "/ArticleNames.txt");
    // Print articles to file
    for (const auto &article : articles)
    {
        file << article.first << "," << article.second.first << ",";
        file << "{";
        for (const auto &word : article.second.second.first)
        {
            file << word << ",";
        }
        file << "},{";
        for (const auto &org : article.second.second.second)
        {
            file << org << ",";
        }
        file << "}" << std::endl;
    }
}
    
    void load(std::string directory) //load function (from previous indexes)
    {
        termsTree->load("./stored_data/"+ directory + "/Terms.txt"); // load the terms
        writersTree->load("./stored_data/"+directory+"/Writers.txt"); // load the writers
        orgsTree->load("./stored_data/"+directory+"/Orgs.txt"); // load the orgs
        std::ifstream file("./stored_data/" + directory + "/ArticleNames.txt"); // load the article names
        std::string line;
        while (std::getline(file, line)) // for each line in the file
        {
            std::istringstream ss(line); // create a string stream
            std::string word; // create a string
            std::getline(ss, word, ','); 
            int docID = std::stoi(word); // get the docID
            std::getline(ss, word, ',');
            std::string articleName = word; // get the article name
            std::getline(ss, word, '{');
            std::getline(ss, word, '}');
            std::istringstream ss2(word); 
            std::string word2; 
            std::vector<std::string> writerNames; // create a vector of writer names
            while (std::getline(ss2, word2, ','))
            {
                writerNames.push_back(word2); // get the writer names
            }
            std::getline(ss, word, '{');
            std::getline(ss, word, '}');
            std::istringstream ss3(word);
            std::string word3;
            std::vector<std::string> orgNames; // create a vector of org names
            while (std::getline(ss3, word3, ','))
            {
                orgNames.push_back(word3); // get the org names
            }
            articles.insert({docID, {articleName, {writerNames, orgNames}}}); // insert the article into the articles map
        }
    }
    void Query(std::string input) //query function
    {
        if(query != nullptr){ // if the query is not null
            delete query;
        }
        
        query = new queryHandler(&input); // create a new query handler
        query->smartParse(); // parse the query
        query->wordParse(); // parse the query
        search(query->getWords(), query->getOrgs(), query->getNames(), query->getExcludeWords()); // search using the query
    }
    void search(std::vector<std::string> words, std::vector<std::string> orgs, std::vector<std::string> names, std::vector<std::string> excludeWords) //search function
    {
        std::map<unsigned long, int> termsOut; // create a map of terms
        std::map<unsigned long, int> orgsOut; // create a map of orgs
        std::map<unsigned long, int> writerOut; // create a map of writers
        if (words.size() > 0) // if there are words
        {
            termsOut = termsTree->search(words.at(0)); // search for the first word
            for (size_t i = 1; i < words.size(); i++)
            {
                std::map<unsigned long, int> temp;
                std::map<unsigned long, int> results;
                temp = termsTree->search(words.at(i)); // search for the next word
                for (const auto &term : temp)
                {
                    if (termsOut.count(term.first) > 0) // if the term is in the terms map
                    {
                        results.insert(std::make_pair(term.first, term.second + termsOut[term.first])); // insert the term into the results map
                    }
                }
                termsOut.clear();
                temp.clear();
                termsOut = results; // set the terms map to the results map
                results.clear();
            }
        }
        if (words.size() > 0) 
        {
            termsOut = termsTree->search(words.at(0));
            for (size_t i = 1; i < words.size(); i++)
            {
                std::map<unsigned long, int> temp;
                std::map<unsigned long, int> results;
                temp = termsTree->search(words.at(i));
                for (const auto &term : temp)
                {
                    if (termsOut.count(term.first) > 0) // if the term is in the terms map
                    {
                        results.insert(std::make_pair(term.first, term.second + termsOut[term.first])); // insert the term into the results map
                    }
                }
                termsOut.clear();
                temp.clear();
                termsOut = results;
                results.clear();
            }
        }   
        if (orgs.size() > 0)
        {
            for (size_t i = 0; i < orgs.size(); i++)
            {
                orgsOut = orgsTree->search(orgs.at(i)); // search for the org
            }
        }
        if (names.size() > 0)
        {
            for (size_t i = 0; i < names.size(); i++)
            {
                writerOut = writersTree->search(names.at(i)); // search for the writer
            } 
        }
        std::map<unsigned long, int> perfectlyMatch;
        std::map<unsigned long, int> orgMatch;
        std::map<unsigned long, int> writerMatch;
        for (const auto &term : termsOut)
        {
            unsigned long termID = term.first;
            int orgCount = orgsOut.count(termID);
            int writerCount = writerOut.count(termID);
            if(orgsOut.size()==0 && writerOut.size()==0){
                perfectlyMatch.insert(std::make_pair(termID, term.second)); // insert the term into the perfectly matched map
            }
            else if (orgCount > 0 && writerCount > 0)
            {
                perfectlyMatch.insert(std::make_pair(termID, term.second)); // insert the term into the perfectly matched map
            }
            else if(orgCount > 0 && writerOut.size() == 0){
                perfectlyMatch.insert(std::make_pair(termID, term.second)); // insert the term into the perfectly matched map
            }
            else if(orgsOut.size() == 0 && writerCount > 0){
                perfectlyMatch.insert(std::make_pair(termID, term.second)); // insert the term into the perfectly matched map
            }
            else if (orgCount > 0)
            {
                orgMatch.insert(std::make_pair(termID, term.second)); // insert the term into the org matched map
            }
            else if (writerCount > 0)
            {
                writerMatch.insert(std::make_pair(termID, term.second)); // insert the term into the writer matched map
            }
        }
        std::map<int, std::pair<int, std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>>> searchResults;
        std::map<int, std::pair<int, std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>>> partialResults;
        for (const auto &term : perfectlyMatch) // for each term in the perfectly matched map
        {
            int docID = term.first; // get the docID
            int relevancy = term.second; // get the relevancy
            std::string articleName = articles[docID].first; 
            std::vector<std::string> writerNames = articles[docID].second.first;
            std::vector<std::string> orgNames = articles[docID].second.second;
            searchResults.insert(std::make_pair(INT_MAX - relevancy, std::make_pair(docID, std::make_pair(articleName, std::make_pair(writerNames, orgNames))))); // insert the article into the search results map
        }
        for (const auto &term : orgMatch) // for each term in the org matched map
        {
            int docID = term.first; // get the docID
            int relevancy = term.second; // get the relevancy
            std::string articleName = articles[docID].first;  
            std::vector<std::string> writerNames = articles[docID].second.first;
            std::vector<std::string> orgNames = articles[docID].second.second;
            partialResults.insert(std::make_pair(INT_MAX - relevancy, std::make_pair(docID, std::make_pair(articleName, std::make_pair(writerNames, orgNames))))); // insert the article into the partial results map
        }
        for (const auto &term : writerMatch) 
        {
            int docID = term.first; // get the docID
            int relevancy = term.second; // get the relevancy
            std::string articleName = articles[docID].first;
            std::vector<std::string> writerNames = articles[docID].second.first;
            std::vector<std::string> orgNames = articles[docID].second.second;
            partialResults.insert(std::make_pair(INT_MAX - relevancy, std::make_pair(docID, std::make_pair(articleName, std::make_pair(writerNames, orgNames))))); // insert the article into the partial results map
        }

        output(searchResults, partialResults); // output the results
    }
    void output(std::map<int, std::pair<int, std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>>> searchResults, std::map<int, std::pair<int, std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>>> partialResults) //output function
    { 
        std::cout << "Search Results: " << std::endl;  
        std::cout << std::endl;
        for (const auto &term : searchResults) // for each term in the search results map
        {
            std::cout << "Title: " << term.second.second.first; 
            std::cout << ", DocID: " << term.second.first << std::endl;
            std::cout << "Writer Names: ";
            for (const auto &writer : term.second.second.second.first)
            {
                std::cout << writer << ", ";
            }
            std::cout << std::endl;
            std::cout << "Org Names: ";
            for (const auto &org : term.second.second.second.second)
            {
                std::cout << org << ", ";
            }
            std::cout << "\n"
                      << std::endl;
        }
        if (partialResults.size() > 0)
        {
            std::cout << "Partial Results: " << std::endl;
            for (const auto &term : partialResults)
            {
                std::cout << "Title: " << term.second.second.first;
                std::cout << ", DocID: " << term.second.first << std::endl;
                std::cout << "Writer Names: ";
                for (const auto &writer : term.second.second.second.first)
                {
                    std::cout << writer << ", ";
                }
                std::cout << std::endl;
                std::cout << "Org Names: ";
                for (const auto &org : term.second.second.second.second)
                {
                    std::cout << org << ", ";
                }
                std::cout << std::endl;
            }
        }
    }
    TermsTree getTermsTree(){ //get the terms tree
        return *termsTree;
    }
    WriterTree getWritersTree(){ //get the writers tree
        return *writersTree;
    }
    OrganizationTree getOrgsTree(){ //get the orgs tree
        return *orgsTree;
    }
};
#endif