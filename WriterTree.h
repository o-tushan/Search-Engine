#ifndef WRITERTREE_H
#define WRITERTREE_H

#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <fstream>
#include <sstream>
#include "Node.h"
class WriterTree
{
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
public:
    WriterTree();
    ~WriterTree();
    WriterTree(const WriterTree &T);
    WriterTree operator=(const WriterTree &T);
    bool isEmpty();
    void insert(std::string organization, int docID);
    std::map<unsigned long, int> search(std::string term);
    void print();
    void load(std::string filename);
    void store(std::string filename);


};

#endif