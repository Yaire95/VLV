#include <iostream>
#include <vector>
#include "VLVector.hpp"
#include <cassert>

using std::cout;
using std::endl;
using std::vector;

int main() {

    /////////////////////////////// GENERAL API TESTS /////////////////////////
    VLVector<int, 2> vec1;
    cout << "----------------GENERAL API TESTS----------------" << endl;
    cout << "**************0**************\n";
    cout << "TEST default constructor, PUSH_BACK(), at(), SIZE(), CAPACITY, and POP_BACK" << endl;
    assert(vec1.capacity() == 2);
    for (int i = 0; i < 20; i++) {
        vec1.push_back(i);
        assert(vec1.at(i) == i);
    }
    assert(vec1.capacity() == 30);
    assert(vec1.size() == 20);
    for (int i = 0; i < 15; i++) {
        vec1.pop_back();
    }
    assert(vec1.size() == 5);
    for (int i = 0; i < vec1.size(); i++) {
        assert(vec1.at(i) < 5);
    }
    cout << "TESTS PASSED!!\n" << endl;

    printf("**************1**************\n");
    cout << "TEST Copy Constructor" << endl;
    VLVector<int, 2> vec2 = vec1;
    for (int i = 0; i < vec1.size(); i++) {
        assert(vec2.at(i) == vec1.at(i));
    }
    assert(vec1.size() == vec2.size());
    cout << "TESTS PASSED!!\n" << endl;
    printf("**************2**************\n");
    cout << "TEST data, clear(), and iterating using the iterator" << endl;
    int counter = 0;
    for (const auto &num : vec2) {
        assert(num == vec2.at(counter));
        counter++;
    }
    vec2.clear();
    assert(vec2.size() == 0);
    int *data;
    data = vec2.data();
    for (int i = 0; i < vec2.size(); i++) {
        assert(data[i] == vec2.at(i));
    }
    cout << "TESTS PASSED!!\n" << endl;
    printf("**************3**************\n");
    cout << "TEST operators: [], ==, !=, = " << endl;
    VLVector<int, 2> vec3;
    for (int i = 0; i < 20; i++) {
        vec3.push_back(i);
        assert(vec3[i] == i);
    }
    VLVector<int, 2> vec4 = vec3;
    for (int i = 0; i < 20; i++) {
        assert(vec3.size() == vec4.size());
        assert(vec3[i] == vec4[i]);
    }
    auto myIter1 = vec3.begin();
    auto otherIter = vec4.begin();
    int c = *myIter1;
    int b = *otherIter;
    assert(vec3 == vec4);
    assert(vec3 != vec1);
    assert(vec3 != vec2);
    cout << "TESTS PASSED!!\n" << endl;


    ///////////////////////////////////ITERATOR TESTS/////////////////////////////////

    cout << "----------------GENERAL ITERATOR TESTS----------------" << endl;

    printf("**************4**************\n");
    cout << "TEST Standard Iterator Loop Functions" << endl;
    VLVector<int, 5> vec5;
    for (int i = 0; i < 10; i++) {
        vec5.push_back(i);
    }
    int count = 0;
    for (const auto &num : vec5) {
        assert(num == count);
        count++;
    }

    cout << "TESTS PASSED!!\n" << endl;
    printf("**************5**************\n");
    cout << "TEST Standard Iterator +/- Arithmetic" << endl;

    auto myIter = vec5.begin();
    myIter += 5;
    assert(*myIter == 5);
    ++myIter;
    assert(*myIter == 6);
    myIter -= 3;
    assert(*myIter == 3);
    --myIter;
    assert(*myIter == 2);

    cout << "TESTS PASSED!!\n" << endl;
    printf("**************6**************\n");
    cout << "TEST Standard Iterator == != Arithmetic" << endl;

    auto secondIter = vec5.begin();
    assert(!(myIter == secondIter));
    secondIter += 2;
    assert((myIter == secondIter));


    cout << "TESTS PASSED!!\n" << endl;
    printf("**************7**************\n");
    cout << "TEST Standard Iterator < > <= >= Arithmetic" << endl;

    assert(myIter <= secondIter && myIter >= secondIter);
    ++myIter;
    assert(!(myIter <= secondIter) && (myIter >= secondIter));
    assert((myIter > secondIter) && !(myIter < secondIter));
    secondIter += 3;
    assert(!(myIter > secondIter) && (myIter < secondIter));

    cout << "TESTS PASSED!!\n" << endl;
    std::cout << "Standard Iterator Tests Passed!!! \n" << endl;

    cout << "----------------API ITERATOR TESTS----------------" << endl;
    cout << "**************8**************\n";
    cout << "TEST Insert 1" << endl;

    myIter = vec5.begin();
    auto thirdIter = vec5.insert(secondIter, 20);
    assert(*thirdIter == 20);
    myIter += 5;
    assert(myIter == thirdIter);
    myIter = vec5.begin();
    for (int i = 0; i < 11; i++) {
        if (i < 5) {
            assert(*myIter == i);
        } else if (i == 5) {
            assert(*myIter == 20);
        } else {
            assert(*myIter == i - 1);
        }
        myIter++;
    }
    assert(vec5.capacity() == 15);

    std::cout << "TEST PASSED!\n";
    cout << "**************9**************\n";
    cout << "TEST Erase 1" << endl;
    thirdIter = vec5.erase(thirdIter);
    assert(*thirdIter == 5);
    for (int i : vec5) {
        assert(i != 20);
    }
    assert(vec5.capacity() == 15);
    assert(vec5.size() == 10);
    std::cout << "TEST PASSED!\n";
    cout << "**************10**************\n";
    cout << "TEST Insert 2 - small insert" << endl;

    myIter = vec5.begin();
    myIter += 8;
    VLVector<int, 5> vec6 = vec5;
    auto posIter = vec6.begin();
    posIter += 8;
    auto forthIter = vec6.insert(posIter, thirdIter, myIter);
    myIter = vec6.begin();
    for (int i = 0; i < 8; i++) {
        assert(*myIter == i);
        myIter++;
    }
    for (int i = 5; i < 10; i++) {
        assert(*myIter == i);
        myIter++;
    }

    cout << "**************11**************\n";
    cout << "TEST Insert 2 - big insert (moving from stack to heap to heap, ect..)" << endl;

    vec1.clear();
    vec6.clear();

    for(int i = 0; i < 200; i++)
    {
        if(i<3)
        {
            vec1.push_back(i);
        }
        vec6.push_back(i);
    }
    myIter1 = vec1.end() - 1;
    vec1.insert(myIter1, vec6.begin(), vec6.end());
    assert(vec1[0] == 0 && vec1[1] == 1);
    for(int i = 0; i < 200; i++)
    {
        assert(vec1[i+2] == i);
    }
    assert(vec1[202] == 2);
    assert(vec1.capacity() == 241);

    std::cout << "TEST PASSED! \n";
    cout << "**************12**************\n";
    cout << "TEST Erase 2 and moving from heap back to stack" << endl;

    auto fourthIter = vec5.begin();
    thirdIter++;
    fourthIter = vec5.erase(fourthIter, thirdIter);
    // changed to 6
    assert(*fourthIter == 6);
    for(int i : vec5)
    {
        assert(i != 0 && i != 1 && i != 2 && i != 3 && i != 4);
    }
    assert(vec5.size() == 4);
    assert(vec5.capacity() == 5);
    std::cout << "TEST PASSED!\n";

    cout << "**************13**************\n";
    cout << "TEST constructor(1) and moving from stack to heap" << endl;
    VLVector<int, 5> vec7;
    for(int i = 0; i < 20; i++)
    {
        vec7.push_back(i);
    }
    auto fifthIter = vec7.begin();
    auto sixthIter = fifthIter + 11;
    VLVector<int, 5> vec8(fifthIter, sixthIter);
    assert(vec8.size() == 11);
    for(int i = 0; i < 11; i++)
    {
        assert(vec8.at(i) == i);
    }
    cout << "TESTS PASSED!!\n" << endl;
    cout << "-------------ALL TESTS PASSED SUCCESSFULLY--------------" << endl;
    return 0;
}