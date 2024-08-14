#include "TermsTreeV2.h"
TermsTree::TermsTree() // default constructor
{
    root = nullptr;
}

TermsTree::~TermsTree()  // destructor
{
    deleteTree(root);
}
TermsTree::TermsTree(const TermsTree &T) // copy constructor
{
    root = T.root;
}
TermsTree TermsTree::operator=(const TermsTree &T) // assignment operator 
{
    root = T.root;
    return *this;
}

bool TermsTree::isEmpty() // checks if tree is empty
{
    return (root == nullptr);
}

void TermsTree::insert(std::string organization, int docID, int relevancy) // inserts a node into the tree
{
    root = insert(root, organization, docID, relevancy);
}

Node *TermsTree::insert(Node *node, std::string term, int docID, int relevancy)     
{
    // Standard BST insertion
    if (node == nullptr)
    {
        // Create a new node with the provided information
        return new Node(hasher(term), docID, relevancy);
        
    }

    if (hasher(term) < node->key)
    {
        // Recursive call to insert into the left subtree
        node->left = insert(node->left, term, docID, relevancy);
        if (height(node->left) - height(node->right) == 2)
        {
            if (hasher(term) < node->left->key)
            {
                node = rotateRightTwice(node);
            }

            else
            {
                node = rotateRightTwice(node);
            }
        }
    }
    else if (hasher(term) > node->key)
    {
        // Recursive call to insert into the right subtree
        node->right = insert(node->right, term, docID, relevancy);
        if (height(node->right) - height(node->left) == 2)
        {
            if (hasher(term) > node->right->key)
            {
                node = rotateLeft(node);
            }

            else
            {
                node = rotateLeftTwice(node);
            }
        }
    }
    else
    {

        node->indexes.insert(std::make_pair(docID, relevancy));
        return node;
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    return node;
}
void TermsTree::insert(unsigned long key, std::vector<std::pair<unsigned long, int>> indexes) // inserts a node into the tree
{
    root = insert(root, key, indexes);
}
Node *TermsTree::insert(Node *node, unsigned long key, std::vector<std::pair<unsigned long, int>> indexes) // inserts a node into the tree
{
    if (node == nullptr)
    {
        return new Node(key, indexes);
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key, indexes);
        if (height(node->left) - height(node->right) == 2)
        {
            if (key < node->left->key)
            {
                node = rotateRightTwice(node);
            }

            else
            {
                node = rotateRightTwice(node);
            }
        }
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key, indexes);
        if (height(node->right) - height(node->left) == 2)
        {
            if (key > node->right->key)
            {
                node = rotateLeft(node);
            }

            else
            {
                node = rotateLeftTwice(node);
            }
        }
    }
    else
    {
        for (const auto &index : indexes)
        {
            node->indexes.insert(std::make_pair(index.first, index.second));
        }
        return node;
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    return node;
}

std::map<unsigned long, int> TermsTree::search(std::string term) //searches
{
    Node *current = root;
    while (current != nullptr)
    {
        unsigned long check = hasher(term);
        if (current->key == check)
        {
            // Return the indexes if the term is found
            return current->indexes;
        }
        else if (current->key > check)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    // If the term is not found, return an empty map
    return std::map<unsigned long, int>();
}

Node *TermsTree::rotateLeft(Node *t) // rotates left
{
    if (t == nullptr)
    {
        return nullptr;
    }

    Node *u = t->right;

    if (u == nullptr)
    {
        return t;
    }

    t->right = u->left;
    u->left = t;
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(u->right), t->height) + 1;

    return u;
}

Node *TermsTree::rotateRight(Node *t) //rotates right
{
    if (t == nullptr || t->left == nullptr)
    {
        return t;
    }

    Node *u = t->left;
    t->left = u->right;
    u->right = t;

    // Update heights if they are stored in the nodes
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(u->left), height(u->right)) + 1;

    return u;
}

Node *TermsTree::rotateLeftTwice(Node *t) //rotates left twice
{
    t->right = rotateRight(t->right);
    return rotateLeft(t);
}

Node *TermsTree::rotateRightTwice(Node *t) //rotates right twice
{
    t->left = rotateLeft(t->left);
    return rotateRight(t);
}

void TermsTree::deleteTree(Node *&node) // deletes tree
{
    if (node == nullptr)
    {
        return;
    }
    node->indexes.clear();
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
    node = nullptr;
}

int TermsTree::height(Node *node) // returns height
{
    if (node == nullptr)
    {
        return -1;
    }
    else
    {
        return node->height;
    }
}

void TermsTree::print() // prints tree
{ 
    print("", root, false, true);
}
void TermsTree::print(const std::string &prefix, Node *parent, bool isLeft, bool isRoot)
{
    if (parent == nullptr)
        return;

    if (isRoot)
    {
        std::cout << "─────";
    }
    else
    {
        std::cout << prefix << (isLeft ? "L├────" : "R└───");
    }
    std::cout << parent->key << std::endl;

    print(prefix + (isLeft ? " │   " : "    "),
          parent->left, true, false);
    print(prefix + (isLeft ? " │   " : "    "),
          parent->right, false, false);
}
void TermsTree::load(std::string filename) // loads tree
{
    std::fstream file;
    std::string temp = filename;
    file.open(temp, std::ios::in);

    if (!file.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string temp;
        unsigned long key;
        std::vector<std::pair<unsigned long, int>> indexes;

        // Parse the key and indexes from the line
        std::getline(iss, temp, '{');
        key = std::stoul(temp);
        std::string indexesStr;
        std::getline(iss, indexesStr, '}');

        std::istringstream issIndexes(indexesStr);
        std::string index;
        while (std::getline(issIndexes, index, ':'))
        {
            std::istringstream issIndex(index);
            std::string indexPair;
            std::getline(issIndex, indexPair, ',');
            unsigned long index1 = std::stoi(indexPair);
            std::getline(issIndex, indexPair, ',');
            int index2 = std::stoi(indexPair);
            indexes.push_back(std::make_pair(index1, index2));
        }

        // Insert the key and indexes into the tree
        insert(key, indexes);
    }

    file.close();
}

void TermsTree::levelOrderTraversal(Node *root, std::fstream &file) // traverses tree
{
    if (root == nullptr)
    {
        return;
    }

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        // Print the key and its indexes
        file << current->key << "{";
        for (const auto &index : current->indexes)
        {
            file << index.first << "," << index.second << ":";
        }
        file << "}\n";

        // Enqueue the left and right child of the current node
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
    }
}
void TermsTree::store(std::string filename) // stores tree
{
    std::string line = filename;
    std::cout << "Storing to " << line << std::endl;
    printToFile(line);
}
void TermsTree::printToFile(const std::string &filename) // prints to file
{ 
    std::fstream file(filename, std::ios::out);
    std::cout << "Printing to " << filename << std::endl;
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    levelOrderTraversal(root, file);

    file.close();
}
