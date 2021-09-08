#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP
struct Solution{
    int* chromosome;
    int size;
};

struct Individual{
  Solution solution;
  double fitness;
  int updated;
};

struct Population{
    Individual *individual;
    int size;
};
#endif 