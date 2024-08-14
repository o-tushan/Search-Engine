#include "WriterTree.h"
WriterTree::WriterTree() //constructor
{
    root = nullptr;
}

WriterTree::~WriterTree() //destructor
{
    deleteTree(root);
}
WriterTree::WriterTree(const WriterTree &T) //copy constructor
{
    root = T.root;
}
WriterTree WriterTree::operator=(const WriterTree &T) //assignment operator
{
    root = T.root;
    return *this;
}

bool WriterTree::isEmpty() //checks if tree is empty 
{
    return (root == nullptr);
}

void WriterTree::insert(std::string organization, int docID) //inserts into tree
{
    root = insert(root, organization, docID);
}

Node *WriterTree::insert(Node *node, std::string term, int docID)
{
    // Standard BST insertion
    if (node == nullptr)
    {
        // Create a new node with the provided information
        return new Node(hasher(term), docID);
    }

    if (hasher(term) < node->key)
    {
        // Recursive call to insert into the left subtree
        node->left = insert(node->left, term, docID);
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
        node->right = insert(node->right, term, docID);
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
        // Duplicate terms are not allowed in this example
        node->indexes.insert(std::make_pair(docID, hasher(term)));
        return node;
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    return node;
}
void WriterTree::insert(unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
{
    root = insert(root, key, indexes);
}
Node *WriterTree::insert(Node *node, unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
{
    // Standard BST insertion
    if (node == nullptr)
    {
        // Create a new node with the provided information
        return new Node(key, indexes);
    }

    if (key < node->key)
    {
        // Recursive call to insert into the left subtree
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
        // Recursive call to insert into the right subtree
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
        // Duplicate terms are not allowed in this example
        for (const auto &index : indexes)
        {
            node->indexes.insert(std::make_pair(index.first, index.second));
        }
        return node;
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    return node;
}
std::map<unsigned long, int> WriterTree::search(std::string term)
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

Node *WriterTree::rotateLeft(Node *t)
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

Node *WriterTree::rotateRight(Node *t)
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

Node *WriterTree::rotateLeftTwice(Node *t) //double rotation
{
    t->right = rotateRight(t->right);
    return rotateLeft(t);
}

Node *WriterTree::rotateRightTwice(Node *t) //double rotation
{
    t->left = rotateLeft(t->left);
    return rotateRight(t);
}

void WriterTree::deleteTree(Node *&node) //deletes tree
{
    if (node == nullptr)
    {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
    node = nullptr;
}

int WriterTree::height(Node *node) //returns height of tree
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

void WriterTree::print() //prints tree
{
    print("", root, false, true);
}
void WriterTree::print(const std::string &prefix, Node *parent, bool isLeft, bool isRoot) //prints tree
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
void WriterTree::load(std::string filename) //loads tree
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
void WriterTree::store(std::string filename) //stores tree
{
    std::string line = filename;
    printToFile(line);
}
void WriterTree::levelOrderTraversal(Node *root, std::fstream &file) //level order traversal
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
void WriterTree::printToFile(const std::string &filename)   //prints tree to file
{
    std::fstream file;
    file.open(filename, std::ios::out);
    if (!file.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        return;
    }
    levelOrderTraversal(root, file);
    file.close();
}