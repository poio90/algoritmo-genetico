/* 
 * File:   Mutator.cpp
 * Author: braian
 *
 * Created on 9 de octubre de 2020, 07:41 PM
 */

#include "../include/mutator.hpp"

/*
 * Simple C++ Test Suite
 */


class MutatorTest : public Mutator {
public:

    MutatorTest() : Mutator(0) {
        this->test1();
    }

    void test1() {
        std::cout << "Mutator test 1 Scramble" << std::endl;


        int array[7] = {1, 2, 3, 4, 5, 6, 7};

        int* pa = &array[1];
        int* pb = &array[4];

        this->scramble(pa, pb);

        cout << "Resultado: ";

        for (int x : array) {
            cout << x;

        }


    }

};



