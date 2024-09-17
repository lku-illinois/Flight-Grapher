#pragma once
#include <queue>
#include <string>
#include <map>
#include "globals.h"

class BFS {
    public:
        BFS(int start, int end, int size, std::vector<std::priority_queue<psd, std::vector<psd>, std::greater<psd>>>* routes);
        BFS(int size, std::vector<std::priority_queue<psd, std::vector<psd>, std::greater<psd>>>* routes);
        void clear();
        std::vector<int> run();
    private:
        std::queue<std::vector<int>> queue;
        int start;
        int end;
        int size;
        int dist;
        std::vector<int> visited;
        std::vector<std::priority_queue<psd, std::vector<psd>, std::greater<psd>>>* routes;
};