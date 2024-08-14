#define CATCH_CONFIG_MAIN
#include "Node.h"
#include "catch2/catch.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "TermsTreeV2.h"
#include "OrganizationTree.h"
#include "WriterTree.h"
#include <climits>

TEST_CASE("Check Balancing","[TermsTreeV2]"){
TermsTree tree;
tree.insert("a", 1, 1);
tree.insert("b", 1, 1);
tree.insert("c", 1, 1);
tree.insert("d", 1, 1);
tree.insert("e", 1, 1);
tree.insert("f", 1, 1);
tree.insert("a", 2, 1);
tree.insert("a", 3, 2);
REQUIRE(tree.search("a").size() == 3);
REQUIRE(tree.search("b").size() == 1);
REQUIRE(tree.search("c").size() == 1);
tree.store("treeTest");
tree.~TermsTree();
REQUIRE(tree.isEmpty()==true);
}
TEST_CASE("Check Balancing - Writers","[WriterTree]"){
WriterTree tree;
tree.insert("a", 1);
tree.insert("b", 1);
tree.insert("c", 1);
tree.insert("d", 1);
tree.insert("e", 1);
tree.insert("f", 1);
tree.insert("a", 2);
tree.insert("a", 3);
REQUIRE(tree.search("a").size() == 3);
REQUIRE(tree.search("b").size() == 1);
REQUIRE(tree.search("c").size() == 1);
tree.store("treeTest");
tree.~WriterTree();
REQUIRE(tree.isEmpty()==true);
}
TEST_CASE("Check Balancing - Organizations","[OrganizationTree]"){
OrganizationTree tree;
tree.insert("a", 1);
tree.insert("b", 1);
tree.insert("c", 1);
tree.insert("d", 1);
tree.insert("e", 1);
tree.insert("f", 1);
tree.insert("a", 2);
tree.insert("a", 3);
REQUIRE(tree.search("a").size() == 3);
REQUIRE(tree.search("b").size() == 1);
REQUIRE(tree.search("c").size() == 1);
tree.store("treeTest");
tree.~OrganizationTree();
REQUIRE(tree.isEmpty()==true);
}
TEST_CASE("Check Storing"){
TermsTree tree;
tree.load("treeTest");
REQUIRE(tree.search("a").size() == 3);
REQUIRE(tree.search("b").size() == 1);
REQUIRE(tree.search("c").size() == 1);
tree.~TermsTree();
REQUIRE(tree.isEmpty()==true);
}
TEST_CASE("Check Storing - Writers"){
WriterTree tree;
tree.load("treeTest");
REQUIRE(tree.search("a").size() == 3);
REQUIRE(tree.search("b").size() == 1);
REQUIRE(tree.search("c").size() == 1);
tree.~WriterTree();
REQUIRE(tree.isEmpty()==true);
}
TEST_CASE("Check Storing - Organizations"){
OrganizationTree tree;
tree.load("treeTest");
REQUIRE(tree.search("a").size() == 3);
REQUIRE(tree.search("b").size() == 1);
REQUIRE(tree.search("c").size() == 1);
tree.~OrganizationTree();
REQUIRE(tree.isEmpty()==true);
}
