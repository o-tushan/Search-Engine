# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members:
Davis Lynn
Christopher Cook
Owen Tushan

Used free extension: [ ] 24 hrs or [x] 48 hrs

[] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent by Davis    | Time spent by Chris    | Time spent by Owen
| ----------- | :-----------------:| :---------------: | :--------------------: | :--------------------: | :-------------------:
| UML diagram | Nov 3              | Nov 3             | 0.5 hrs                | 0.5 hrs                | 1 hr
| Query Handler| Nov 10            | Nov 7             | 0 hrs                  | 3 hrs                  | 2 hrs
| json Parser | Nov 10             | Nov 9             | 0 hrs                  | 3 hrs                  | 3 hrs
| trees       | Nov 13             | Nov 12            | 6 hrs                  | 0 hrs                  | 0 hrs
| parser+handler| Nov 20           | Nov 16            | 6 hrs                  | 6 hrs                  | 5 hrs
| tree algos  | Nov 30             | Nov 29            | 7 hrs                  | 0 hrs                  | 0 hrs
| UI and answers| Nov 30           | Nov 30            | 2 hrs                  | 2 hrs                  | 4 hrs
| bug fixing  | Nov 30             | Nov 30            | 3 hrs                  | 3 hrs                  | 1 hr



### High-level Design of Solution

![UML](Final UML.png)

### High Level Code Breakdown
----- Common_lang_constants -----

This is the stemming algorithm that we used for the project

----- english_stem -----

This is the stemming algorithm that we used for the project

----- Handler -----

    private variables
        std::map<> articles
            contains the document ID, article names, writer names, and organizations

handler()
    default constructor

handler(const handler &H)
    constructor that sets reader and query

 handler operator=(const handler &H)
    assignment operator

~handler()
    destructor

jParse(std::string directory)
    creates a bunch of maps that link the doc ID to the other article data. Inserts the data into the trees and the articles map

void store()
    stores the trees in a text file

void load()
    loads the trees in a text file

void Query(std::string input)
    grabs the query from the user and sends it to handler to parse

void search(std::vector<std::string> words, std::vector<std::string> orgs, std::vector<std::string> names, std::vector<std::string> excludeWords)
    searches the trees

 void output(std::map<int, std::pair<int, std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>>> searchResults, std::map<int, std::pair<int, std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>>> partialResults)
    returns the results from the trees based on what we searched with

----- jsonParser -----

    private variables
        string inParse
            the text from the article that needs parsed

    map<> outParse
        stores the name and relavency

    jsonParser()
        default constructor

    jsonParser(std::string *x)
        sets inParse

    jsonParser(const jsonParser &P)
        sets inParse and outParse

    jsonParser operator=(const jsonParser &P)
        assignment operator

    ~jsonParser()
        destructor

    void toLower()
        lowers the entirety of inParse

    void toAlpha()
        removes all non letters from inParse

    void parse()
        turns the text from the article into individual words

    void stopWords()
        goes through the words in the article and removes the stop words

    void stem()
        stems all of the words

----- jsonReader -----

    private variables
        Document doc 
            Document object from rapidjson

    jsonReader()
        default constructor

    void readJson(const std::string &fileName, int key)
        reads the article and gets all of the info 

    void jsonFileSystem(std::string path)
        creates the ID of each file and runs readJson on each article in a directory

    std::map<int, std::map<std::string, int>> getTerms()
        returns terms
    

    std::map<int, std::vector<std::string>> getNames()
        returns names
    

    std::map<int, std::vector<std::string>> getOrgs()
        returns orgs
    

    std::map<int, std::string> getArticleNames()
        returns articleName

----- main -----

    main()
        calls UserInterface

----- Node -----

    terms tree

----- Node2 -----

    does orgs and writer trees

----- OrganizationTree -----

    private variables
        Node root
            root node of node type 2

    OrganizationTree::OrganizationTree() : root(nullptr)
        default constructor

    OrganizationTree::~OrganizationTree()
        destructor

    OrganizationTree::OrganizationTree(const OrganizationTree &T)
        sets root

    OrganizationTree OrganizationTree::operator=(const OrganizationTree &T)
        assignment operator

    bool OrganizationTree::isEmpty()
        returns nullptr

    void OrganizationTree::insert(std::string organization, int docID)
        calls the insert below

    Node *OrganizationTree::insert(Node *node, std::string term, int docID)
        actually inserts and does all of the rotations and balancing for the orgs 

    void OrganizationTree::insert(unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
        calls the insert below

    Node *OrganizationTree::insert(Node *node, unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
        loads in the data from the txt file and does balancing 

    std::map<unsigned long, int> OrganizationTree::search(std::string term)
        traverses through the tree and searches for a hash

    Node *OrganizationTree::rotateLeft(Node *t)
        rotates a node left 

    Node *OrganizationTree::rotateRight(Node *t)
        rotates a node right

    Node *OrganizationTree::rotateLeftTwice(Node *t)
        rotates a node twice to the left 

    Node *OrganizationTree::rotateRightTwice(Node *t)
        rotates a node twice to the right 

    void OrganizationTree::deleteTree(Node *&node)
        deletes the tree 

    int OrganizationTree::height(Node *node)
        gets the tree height

    void OrganizationTree::print()
        calls the other print 

    void OrganizationTree::print(const std::string &prefix, Node *parent, bool isLeft, bool isRoot)
        prints out the tree for bug fixing

    void OrganizationTree::load(std::string filename)
        opens a file and parses the key and indexes and puts them into trees

    void OrganizationTree::store(std::string filename)
        calls printToFile

    void OrganizationTree::levelOrderTraversal(Node *root, std::fstream &file)
        prints to a file

    void OrganizationTree::printToFile(const std::string &filename)
        calls levelOrderTraversal

----- parser -----

    private variables
        string inParse
            the text that needs to be parsed for query

     parser()
        default constructor

    parser(std::string *x)
        sets inParse and outParse

    parser(const parser &P)
        sets inParse

    parser operator=(const parser &P)
        assignment operator

    ~parser()
        destructor
    
    void toLower()
        makes inParse lowercase

    void toAlpha()
        removes all non letters in inParse

    void parse()
        turns inParse into words

    void stem()
        does stemming on inParse

    void stopWords()
        removes all stop words from inParse

----- queryHandler -----

    private variables
        string input
            input from the user 

    queryHandler()
        default constructor

    queryHandler(std::string *input)
        assigns input and the maps 

    queryHandler operator=(const queryHandler &QH)
        assignment operator

    ~queryHandler()
        destructor

    void userInput()
        gets the user query

    void smartParse()
        gets the users search parameters such as the org and names  

    void wordParse()
        calls all of the parsing functions such as tolower and toalpha

----- stemming -----

Also the stemming algorithm that we used for the project

----- TermsTreeV2 -----

    private variables
        node root
            node root of type node 1

    TermsTree::TermsTree()
        sets root to nullptr

    TermsTree::~TermsTree()
        destructor

    TermsTree::TermsTree(const TermsTree &T)
        sets the node root

    TermsTree TermsTree::operator=(const TermsTree &T)
        assignment operator

    bool TermsTree::isEmpty()
        returns nullptr

    void TermsTree::insert(std::string organization, int docID, int relevancy)
        calls the insert below

    Node *TermsTree::insert(Node *node, std::string term, int docID, int relevancy)
        inserts all of the terms and does balancing

    void TermsTree::insert(unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
        calls the insert below

    Node *TermsTree::insert(Node *node, unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
        loads in the data from a txt file and does balancing

    std::map<unsigned long, int> TermsTree::search(std::string term)
        traverses the tree and searches for a hash

    Node rotateLeft(Node *t)
        rotates a node left 

    Node rotateRight(Node *t)
        rotates a node right

    Node rotateLeftTwice(Node *t)
        rotates a node twice to the left 

    Node rotateRightTwice(Node *t)
        rotates a node twice to the right 

    void deleteTree(Node *&node)
        deletes the tree 

    int height(Node *node)
        gets the tree height

    void print()
        calls the other print 

    void print(const std::string &prefix, Node *parent, bool isLeft, bool isRoot)
        prints out the tree for bug fixing

    void load(std::string filename)
        opens a file and parses the key and indexes and puts them into trees

    void store(std::string filename)
        calls printToFile

    void levelOrderTraversal(Node *root, std::fstream &file)
        prints to a file

    void printToFile(const std::string &filename)
        calls levelOrderTraversal

----- test -----

    tested the time that query handler took to run on a small scale 

----- testReader -----

    tested the time jsonReader took to run 

----- TreeTests -----

    tested the trees for insertion and searching 

----- TreeTests2 -----

    tested the trees for perpetuance

----- UserInterface -----

    UserInterface()
        default constructor

    help()
        provides a breakdown of commands for the user if needed

    index(string directory)

        indexes a directory and stores it in a file

    query(string terms)
        asks for which index that is needing to be used
        calls the query functionality of handler
    UI()
        generates a UI and allows you to interact with the search engine
        all functionality available with one command line prompt

----- WriterTree -----

    private variables
        Node root
            root node of node type 2

    WriterTree::WriterTree() : root(nullptr)
        default constructor

    WriterTree::~WriterTree()
        destructor

    WriterTree::WriterTree(const OrganizationTree &T)
        sets root

    WriterTree WriterTree::operator=(const WriterTree &T)
        assignment operator

    bool WriterTree::isEmpty()
        returns nullptr

    void insert(std::string organization, int docID)
        calls the insert below

    Node insert(Node *node, std::string term, int docID)
        actually inserts and does all of the rotations and balancing for the writers

    void insert(unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
        calls the insert below

    Node insert(Node *node, unsigned long key, std::vector<std::pair<unsigned long, int>> indexes)
        loads in the data from the txt file and does balancing 

    std::map<unsigned long, int> search(std::string term)
        traverses through the tree and searches for a hash

    Node rotateLeft(Node *t)
        rotates a node left 

    Node rotateRight(Node *t)
        rotates a node right

    Node rotateLeftTwice(Node *t)
        rotates a node twice to the left 

    Node rotateRightTwice(Node *t)
        rotates a node twice to the right 

    void deleteTree(Node *&node)
        deletes the tree 

    int height(Node *node)
        gets the tree height

    void print()
        calls the other print 

    void print(const std::string &prefix, Node *parent, bool isLeft, bool isRoot)
        prints out the tree for bug fixing

    void load(std::string filename)
        opens a file and parses the key and indexes and puts them into trees

    void store(std::string filename)
        calls printToFile

    void levelOrderTraversal(Node *root, std::fstream &file)
        prints to a file

    void printToFile(const std::string &filename)
        calls levelOrderTraversal

### Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.

    The backbone of the search engine is the tree data types that we used to store the data relating to the articles. Because trees are easily customizable and efficient to search through and insert, it makes trees a very viable option for a very complex program like this one. The efficiency of a tree at this scale makes it O(N*log(N)) complexity.

    When it comes to sorting the data regarding each of the articles, such as matching the ID to the authors, organizations, and names involved, we used a map for its automatic sorting and the ability to pair the ID to the article's other data. We also used maps to store all of the parsed words, as it's sorting made it really easy for us to search through and find words that we searched by. Since maps are automatically sorted, it has a complexity of O(log(N)).

    In order to transport data such as the list of organizations and names, we used vectors for their simplicity. Rather than take each name or org separately, vectors made it easy to keep everything together and have an easily accessible list of the data. The complexity of a vector is O(N) since you can really only go through it in a linear motion.

### User Documentation
- What are the features of your software?

    Our software is able to take directories of news articles and store the data contained within in an effecient manner. A user can search using words and phrases that they are interested in along with any associated people, authors, or organizations. Using this data, the search engine will then look through all of the articles and return the ones deemed most relavent to all of the user's information provided.

- Describe how to use the software.

    To use the software, a user simply types "supersearch", followed by the command they want to use. They can then search using any terms they want. Alongside this, they can search using any associated names or any associated organizations within the article. Words can also be excluded, so the user can avoid terms that they don't want the article to include if they choose.

- Some example queries with the results.

   ### Using the sample_data
Q germany british operations

Search Results: 
Title: German firms doing business in UK gloomy about Brexit - survey, DocID: 999998
Writer Names: eric schweitzer, carolyn julie fairbairn, joachim lang, schweitzer, 
Org Names: reuters, eu, confederation of british industry, bdi, dihk chambers of industry and commerce, 

### Using the Kaggle Database
q PER:Obama ORG:netflix obama
Search Results:
Title: David Letterman Interviews Barack Obama on Netflix: Highlights | Fortune, DocID: 968342
Writer Names: david letter, barack obama, don reisinger, david letterman, michelle, obama, letterman, michelle obama, oba,
Org Names: netflix,

Title: Letterman lands Obama as first guest on new Netflix show, DocID: 961881
Writer Names: obama, letterman, david letterman, barack obama, george clooney, howard stern, malala yousafzai, tina fey, jay-z,
Org Names: netflix, reuters staff, netflix inc, reuters,

Title: Letterman and Obama reunite in new Netflix show, DocID: 961770
Writer Names: obama, letterman, david letterman, barack obama, lisa bernhard    veteran, lisa bernhard,
Org Names: netflix,

Title: David Letterman lands Obama as first new talk show guest, DocID: 944369
Writer Names: obama, david letterman, barack obama, pope francis, donald trump, letterman, george clooney, howard stern, malala yousafzai, tina fey, jay-z,
Org Names: reuters, netflix,

Title: Barack Obama Is David Letterman's First Guest on New Netflix Show | Fortune, DocID: 949746
Writer Names: barack obama, david letterman, jonathan vanian, letterman, obama, george clooney, howard stern, malala yousafzai, tina fey, jay-z,
Org Names: netflix, cbs,

Query took 0.005807 seconds 

### Performance
Within the sample data provided, we were able to parse and sort all 6 files in about .02 of a second, inserting 436 words and keeping track of relevance through multiple documents. When dealing with the kaggle database, we were able to parse around 60,000 documents within 135 seconds. 

With the 60,000 documents, queries took .005 seconds with all filters, and less  than .001 seconds without filters

### Bonus Work
Did you attempt any bonuses? If so, please give a brief description of what you did.

   > Your answer