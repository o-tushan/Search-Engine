
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <map>
#include <vector>
class Node{
public:
    Node *Parent;
    unsigned long key;
    Node *right=nullptr;
    Node *left = nullptr;
    int height =0; // Added height for AVL balancing
    std::map<unsigned long, int> indexes;

    Node() : Parent(nullptr), key(0), right(nullptr), left(nullptr), height(1) {} // default constructor

    Node(unsigned long key,int DocID): key(key), right(nullptr), left(nullptr), height(1) { // constructor
        indexes.insert(std::make_pair(DocID, key));
    }
    Node(unsigned long key, std::vector<std::pair<unsigned long,int>> indexes): key(key), right(nullptr), left(nullptr), height(1) {
        for(const auto& index : indexes){
            this->indexes.insert(std::make_pair(index.first,index.second));
        }
    }
};
#endif