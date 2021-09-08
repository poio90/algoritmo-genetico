#include "../include/generator.hpp"

void Generator::random(Solution s){
    Utils u;
    for(int i=0; i<s.size; i++){
        s.chromosome[i] = i;
    }
    u.permute(s);
}

void Generator::probabilistic(){}

void Generator::greedy(){}
