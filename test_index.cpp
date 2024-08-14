#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "UserInterface.h"
#include "handler.h"
#include "TermsTreeV2.h"
#include "OrganizationTree.h"
#include "WriterTree.h"

TEST_CASE("Testing Indexer", "[indexer]"){
    handler *handle = new handler();
    handle->jParse("sample_data");
    TermsTree *t = new TermsTree();
    OrganizationTree *o = new OrganizationTree();
    WriterTree *w = new WriterTree();
    t->insert("test", 1, 1);
    std::map<unsigned long, int> m = t->search("test");
    REQUIRE(m.size() == 1);
    o->insert("test", 1);
    std::map<unsigned long, int> m2 = o->search("test");
    REQUIRE(m2.size() == 1);
    w->insert("test", 1);
    std::map<unsigned long, int> m3 = w->search("test");
    REQUIRE(m3.size() == 1);
    handle->store("sample_data");
    REQUIRE(std::filesystem::exists("sample_data"));
    handle->load("sample_data");
    std::map<unsigned long, int> m4  = handle->getTermsTree().search("solvay");
    REQUIRE(m4.size() == 1);
    std::map<unsigned long, int> m5  = handle->getOrgsTree().search("solvay");
    REQUIRE(m5.size() == 1);



    delete t;
    delete o;
    delete w;

}