#include <iostream>
#include "PageRank.h"
#include <vector>
#include <numeric>
#include <math.h>
 using namespace std;


PageRank::PageRank(std::vector<std::vector<double>> adj) : adj(adj) {
    num = adj.size();
}


//size>size of the matrix
//make adjacent matrix to transition matrix

void PageRank::matrix(int size, double damping) {
    this->num = size;

    for(int x = 0; x < num; x++){
        double sum = 0;
        for(int y = 0; y < num; y++){

            sum += adj[y][x];
        } 
        //if adjacent matrix is 1, two vertexs are connected
        //damping factor is usually tested around 0.85
        //damping factor is subtracted by 1 and divided by the number of documents
        if(sum > 0){
            for(int y = 0; y < num; y++){
                double prProability=(adj[y][x]/sum)*damping;
                adj[y][x] = ((1-damping)/num)+prProability;
            }             
        } else {          
            //pages with no outbound links are assumed to link 
            //out to all other pages in the collection  
            for(int y = 0; y < num; y++){
                adj[y][x] = 1/(double)num;
            } 
        }
    }
}


//staring-starting vector
//set the time of iteration
vector<double> PageRank::rank(vector<double> starting, int time) {

    //using random walk method
    //we start from a random node and walking 
    //through the whole graph
    starting.resize(this->num);
    for(int i = 0; i < this->num; i++){
        starting[i] = rand();
    }

    //starting = normalize(starting);

    vector<double> temp = starting;
    vector<double> temp2 = starting;

    bool state=false;
    for(int t = 0; t < time; t++){
        for(int i = 0; i < num; i++){
           temp2[i] = 0;
            //pagerank algorithm operation 
            for(int j = 0; j < num; j++){
                temp2[i] += adj[i][j] * temp[j];
                if (state)
                {
                 normalize(temp2);
                }

            }     
        }
        temp = temp2;
    }
    //result is stored in the pagerank result
    result = temp;
    return temp;
}

//helper function for pagerank algorithm
vector<double> PageRank::normalize( vector<double> output) {
    std::cout << "norm" << std::endl;
    double sum = 0.0;
    //normalization operation
    for(auto it = output.begin(); it != output.end(); ++it){
        sum += (*it)*(*it);
    }
    double normalize_final = sqrt(sum);
    if(normalize_final==0){
        throw std::logic_error("the input vector is a zero vector");
    }
    for(int n = 0; n < num; n++){
        output[n] = output[n] / normalize_final;
    }
    return output;
}
