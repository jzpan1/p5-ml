#include "Map.hpp"
#include "unit_test_framework.hpp"


TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(simple_test) {
    Map<std::string, double> myMap;

    ASSERT_TRUE(myMap.empty());
    ASSERT_EQUAL(myMap.size(), 0);

    myMap["Alice"] = 30.5;
    myMap["Bob"] = 40.2;
    myMap["Charlie"] = 25.8;

    ASSERT_FALSE(myMap.empty());
    ASSERT_EQUAL(myMap.size(), 3);

    Map<std::string, double>::Iterator iterAlice = myMap.find("Alice");
    Map<std::string, double>::Iterator iterUnknown = myMap.find("Unknown");

    ASSERT_EQUAL(iterAlice->second, 30.5);
    ASSERT_TRUE(iterUnknown == myMap.end());

    std::pair<Map<std::string, double>::Iterator, bool> result = myMap.insert(std::make_pair("David", 35.7));
    ASSERT_TRUE(result.second); 
    ASSERT_EQUAL(result.first->second, 35.7);  

    double& eveScore = myMap["Eve"];

    ASSERT_EQUAL(eveScore, 0.0); 

    Map<std::string, double>::Iterator beginit = myMap.begin();

    ASSERT_EQUAL(beginit->first, "Alice");
}

TEST_MAIN()
