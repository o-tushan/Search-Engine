#define CATCH_CONFIG_MAIN
#include "queryHandler.h"
#include "catch2/catch.hpp"

TEST_CASE("Check Balancing", "[QueryHandler]")
{
    std::string input = "PER:Obama ORG:netflix who is obama -biden";
    queryHandler *QH = new queryHandler(&input);
    QH->smartParse();
    QH->wordParse();
    bool test=true;
    REQUIRE(QH->getNames().size() == 1);
    REQUIRE(QH->getWords().size() == 1);
    REQUIRE(QH->getExcludeWords().size() == 1);
    REQUIRE(QH->getOrgs().size() == 1);
    REQUIRE(test==true);
    queryHandler *QH2 = new queryHandler();
    QH2 = QH;
    REQUIRE(QH2->getNames().size() == 1);
    REQUIRE(QH2->getWords().size() == 1);
    REQUIRE(QH2->getExcludeWords().size() == 1);
    REQUIRE(QH2->getOrgs().size() == 1);
    delete QH;
}