#pragma once

#include <vector>
using namespace std;

class PageRank
{
  public:
    PageRank(std::vector<std::vector<double>> adj);
    void matrix(int size, double damping);
    vector<double> rank(vector<double> initial, int time);
    vector<double> normalize( vector<double> output);
    vector<vector<double>> adj;
    vector<double> result; 
    int num;
};