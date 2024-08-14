#ifndef ORGANIZATIONTREE_H
#define ORGANIZATIONTREE_H

#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <fstream>
#include <sstream>
#include "Node.h"
class OrganizationTree
{
public:
    OrganizationTree();
    ~OrganizationTree();
    OrganizationTree(const OrganizationTree &T);
    OrganizationTree operator=(const OrganizationTree &T);
    bool isEmpty();
    void insert(std::string organization, int docID);
    std::map<unsigned long, int> search(std::string term);
    void print();
    void load(std::string filename);
    void store(std::string filename);

private:
    Node *root;
    std::hash<std::string> hasher;
    Node *insert(Node *node, std::string organization, int docID);
    void insert(unsigned long key, std::vector<std::pair<unsigned long, int>> indexes);
    Node *insert(Node *node, unsigned long key, std::vector<std::pair<unsigned long, int>> indexes);
    void print(const std::string &prefix, Node *parent, bool isLeft, bool isRoot);
    Node *rotateLeft(Node *n);
    Node *rotateRight(Node *n);
    Node *rotateLeftTwice(Node *n);
    Node *rotateRightTwice(Node *n);
    int height(Node *node);
    int getBalanceFactor(Node *n);
    void levelOrderTraversal(Node *root, std::fstream &file);
    void printToFile(const std::string &filename);
    void deleteTree(Node *&node);
};

#endif