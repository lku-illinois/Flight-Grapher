#include <iostream>
using namespace std;
#include <queue>
#include <vector>
#include<map>
#include <float.h>
#include "globals.h"

#include "dijkstra.h"

//dijkstras constructor, no start and end
Dijkstra::Dijkstra(int airport_num, std::vector<std::priority_queue<psd, vector<psd>, std::greater<psd>>> routes) :
    airport_num(airport_num),
    visited(airport_num, false),
    distance(airport_num, DBL_MAX),
    parent(airport_num)
{
    this->routes = routes;
}

//dijkstras constructor with start and end
Dijkstra::Dijkstra(int start, int end, int airport_num, std::vector<std::priority_queue<psd, vector<psd>, std::greater<psd>>> routes) :
    start(start),
    end(end),
    airport_num(airport_num),
    visited(airport_num, false),
    distance(airport_num, DBL_MAX),
    parent(airport_num)
{
    this->routes = routes;
}

//clear stuff
void Dijkstra::reset() {
    visited = std::vector<bool>(airport_num, false);
    distance = std::vector<long double>(airport_num, DBL_MAX);
    parent = std::vector<int>(airport_num);
    candidate = std::priority_queue<psd, vector<psd>, greater<psd>>();
}

//run dijkstras with the start and end defined
std::vector<int> Dijkstra::run() {
    visited[start] = true;
    distance[start] = 0;
    parent[start] = -1;
    for (int i=0;i<airport_num;i++) {
        candidate.push({distance[i], i});
    }
    candidate.push({0, start});
    while (!candidate.empty()) {
        std::priority_queue<psd, vector<psd>, greater<psd>> tmp = candidate;
        int now = candidate.top().second;
        if (now == end) break;
        candidate.pop();
        visited[now] = true;
        while (!routes[now].empty()) {
            auto p = routes[now].top();
            if (!visited[p.second]) {
                long double alt = distance[now] + p.first;
                if (alt < distance[p.second]) {
                    distance[p.second] = alt;
                    parent[p.second] = now;
                    update(p.second, alt);
                }
            }
            routes[now].pop();
        }
    }
    if (distance[end] == DBL_MAX) {
        return {-1};
        cout << "cannot reach " << end <<" from " << start << endl;
    } else {
        std::vector<int> path;
        printf("Total distance: %Lg\n", distance[end]);
        while (parent[end] != -1) {
            path.push_back((int)end);
            end = parent[end];
        }
        path.push_back(start);
        return path;
    }
    return {-1};

}

//helper function to find and update the distance in the queue
void Dijkstra::update(int a, long double alt) {
    priority_queue<psd, vector<psd>, greater<psd>> tmp;
    while (!candidate.empty()) {
        psd q = candidate.top();
        candidate.pop();
        if (q.second == a) tmp.push({alt, a});
        else tmp.push(q);
    }
    
    candidate = tmp;
}