
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
    std::map<unsigned long ,int> indexes;

    Node() : Parent(nullptr), key(0), right(nullptr), left(nullptr), height(1) {}

    Node(unsigned long key,int DocID,int relevancy): key(key), right(nullptr), left(nullptr), height(1) {
        indexes.insert(std::make_pair(DocID,relevancy));
    }
    Node(unsigned long key, std::vector<std::pair<unsigned long,int>> indexes): key(key), right(nullptr), left(nullptr), height(1) {
        for(const auto& index : indexes){
            this->indexes.insert(std::make_pair(index.first,index.second));
        }
    }
};
#endif