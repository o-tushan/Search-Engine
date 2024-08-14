#define CATCH_CONFIG_MAIN
#include "jsonReader.h"
#include "catch2/catch.hpp"

TEST_CASE("Test Case 1", "[jsonReader]"){
    std::cout<< "PLEASE MOVE THE json_test_case FOLDER TO THE BUILD FOLDER BEFORE RUNNING" << std::endl;
    jsonReader *JR = new jsonReader();
    JR->jsonFileSystem("json_test_case");
    std::map<int, std::vector<std::string>> names = JR->getNames();
    std::map<int, std::vector<std::string>> orgs = JR->getOrgs();
    std::map<int, std::string> articleName = JR->getArticleNames();
    std::map<int, std::map<std::string, int>> terms = JR->getTerms();
    REQUIRE(names[999999][0] == "obama");
    REQUIRE(orgs[999999][0] == "usgov");
    REQUIRE(terms[999999]["obama"] == 1);
    REQUIRE(terms[999999]["is"] == 2);
    REQUIRE(terms[999999]["run"] == 1);
    REQUIRE(terms[999999]["for"] == 1);
    REQUIRE(articleName[999999] == "Test");
    
    JR->readJson("json_test_case/test.json", 999999);
    REQUIRE(names[999999][0] == "obama");
    REQUIRE(orgs[999999][0] == "usgov");
    REQUIRE(terms[999999]["obama"] == 1);
    REQUIRE(terms[999999]["is"] == 2);
    REQUIRE(terms[999999]["run"] == 1);
    REQUIRE(terms[999999]["for"] == 1);
    REQUIRE(articleName[999999] == "Test");

    delete JR;

    
}