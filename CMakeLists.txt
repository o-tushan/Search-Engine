cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

set(CMAKE_CXX_STANDARD 17)
file(COPY sample_data/ DESTINATION sample_data/)
include(CTest)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)


add_executable(supersearch main.cpp queryHandler.h stemming.h parser.h english_stem.h common_lang_constants.h jsonReader.h WriterTree.cpp OrganizationTree.cpp TermsTreeV2.cpp handler.h) 

add_executable(QHTests QHtest.cpp queryHandler.h stemming.h parser.h english_stem.h common_lang_constants.h)
add_test(NAME TestQH COMMAND QHTests)

add_executable(testjsonReader testJSONReader.cpp jsonReader.h)
add_test(NAME TestjsonReader COMMAND testjsonReader)

add_executable(test_Trees TreeTests.cpp WriterTree.cpp OrganizationTree.cpp TermsTreeV2.cpp)
add_test(NAME TestTrees COMMAND test_Trees)

set(CMAKE_VERBOSE_MAKEFILE OFF)

include(CTest)
add_executable(indexTester test_index.cpp queryHandler.h stemming.h parser.h english_stem.h common_lang_constants.h jsonReader.h WriterTree.cpp OrganizationTree.cpp TermsTreeV2.cpp handler.h)
add_test(NAME indexTest COMMAND handlerTest)