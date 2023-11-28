#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(basicOp){
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.empty());

    ASSERT_TRUE(bst.size() == 0);
    ASSERT_TRUE(bst.height() == 0);

    bst.insert(10);
    ASSERT_FALSE(bst.empty());
    ASSERT_TRUE(bst.size() == 1);
    ASSERT_TRUE(bst.height() == 1);
}

TEST(duplicationObject){
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.empty());

    ASSERT_TRUE(bst.size() == 0);
    ASSERT_TRUE(bst.height() == 0);

    BinarySearchTree<int>::Iterator it = bst.insert(10);
    ASSERT_FALSE(bst.empty());
    ASSERT_TRUE(bst.size() == 1);
    ASSERT_TRUE(bst.height() == 1);

    BinarySearchTree<int>::Iterator it1 = bst.insert(10);
    ASSERT_EQUAL(it, it1);
    ASSERT_TRUE(bst.size() == 1);
    ASSERT_TRUE(bst.height() == 1);
}

TEST(multObject){
    BinarySearchTree<int> bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);

    ASSERT_FALSE(bst.empty());
    ASSERT_TRUE(bst.size() == 5);
    ASSERT_TRUE(bst.height() == 3);
}

TEST(copyTree){
    BinarySearchTree<int> bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);

    ASSERT_FALSE(bst.empty());
    ASSERT_TRUE(bst.size() == 5);
    ASSERT_TRUE(bst.height() == 3);

    BinarySearchTree<int> bst1(bst);

    ASSERT_FALSE(bst1.empty());
    ASSERT_TRUE(bst1.size() == 5);
    ASSERT_TRUE(bst1.height() == 3);
}

TEST(find_object_in_tree){
    BinarySearchTree<int> bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);

    BinarySearchTree<int>::Iterator it = bst.find(5);

    *it = 10;

    BinarySearchTree<int>::Iterator it2 = bst.find(10);

    ASSERT_EQUAL(it, it2);
}

TEST(preOrder){
    BinarySearchTree<int> bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(6);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(7);

    std::ostringstream expected;
    expected << "4 2 1 3 6 5 7 ";
    std::ostringstream actual;
    bst.traverse_preorder(actual);
    ASSERT_EQUAL(expected.str(), actual.str());
}

TEST(inOrder){
    BinarySearchTree<int> bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(6);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(7);

    std::ostringstream expected;
    expected << "1 2 3 4 5 6 7 ";
    std::ostringstream actual;
    bst.traverse_inorder(actual);
    ASSERT_EQUAL(expected.str(), actual.str());
}

TEST(invariant){
    BinarySearchTree<int> bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(6);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(7);

    BinarySearchTree<int>::Iterator it = bst.begin();

    it++;

    ASSERT_EQUAL(6, *it);

    *it = 0;

    ASSERT_FALSE(bst.check_sorting_invariant());
}

TEST(plus_operator){
    BinarySearchTree<int> bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(6);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(7);

    BinarySearchTree<int>::Iterator it = bst.begin();

    it++;

    ASSERT_EQUAL(6, *it);

    BinarySearchTree<int>::Iterator it2 = bst.find(2);

    it2++;

    ASSERT_EQUAL(*it2, 3);

    it2++;

    ASSERT_EQUAL(*it2, 7);
}

TEST(single_node_tests){
    BinarySearchTree<int> bst;

    ASSERT_FALSE(bst.empty());
    ASSERT_TRUE(bst.size() == 1);
    ASSERT_TRUE(bst.height() == 1);

    BinarySearchTree<int>::Iterator it = bst.insert(1);

    *it = 2;

    BinarySearchTree<int>::Iterator it2 = bst.begin();

    ASSERT_EQUAL(it, it2);

    BinarySearchTree<int>::Iterator it3 = bst.find(2);

    ASSERT_EQUAL(it3, it);

    std::ostringstream expected;
    expected << "2 ";
    std::ostringstream actual;
    bst.traverse_preorder(actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    std::ostringstream expected1;
    expected1 << "2 ";
    std::ostringstream actual1;
    bst.traverse_inorder(actual1);
    ASSERT_EQUAL(expected1.str(), actual1.str());

    ASSERT_TRUE(bst.check_sorting_invariant());

}

TEST(min_max_element){
    BinarySearchTree<int> bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(6);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(7);

    BinarySearchTree<int>::Iterator it = bst.max_element();
    ASSERT_EQUAL(*it, 7);
    BinarySearchTree<int>::Iterator it1 = bst.min_element();
    ASSERT_EQUAL(*it1, 1);

    BinarySearchTree<int>::Iterator it2 = bst.min_greater_than(6);
    ASSERT_EQUAL(*it2, 7);

    BinarySearchTree<int>::Iterator it3 = bst.min_greater_than(1);
    ASSERT_EQUAL(*it3, 2);
}

TEST_MAIN()
