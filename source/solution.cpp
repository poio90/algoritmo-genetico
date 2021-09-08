#include "../include/solution.hpp"

Solution::Solution(int _size){
    size = _size;
    chromosome = new int[size];
}

Solution::Solution(){}

Solution::~Solution(){
   delete chromosome;
}