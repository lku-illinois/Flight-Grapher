#include <queue>
#include <vector>
#include <map>
#include "globals.h"

using namespace std;

class Dijkstra {
    public:
        Dijkstra();
        Dijkstra(int airport_num, std::vector<std::priority_queue<psd , std::vector<psd>, std::greater<psd>>> routes);
        Dijkstra(int start, int end, int airport_num, std::vector<std::priority_queue<psd , std::vector<psd>, std::greater<psd>>> routes);
        std::vector<int> run();
        void reset();
    private:
        void update(int a, long double alt);

        int airport_num;
        std::vector<std::priority_queue<psd, std::vector<psd>, std::greater<psd>>> routes;
        std::vector<bool> visited;
        std::vector<long double> distance;
        std::vector<int> parent;
        std::priority_queue<psd, vector<psd>, std::greater<psd>> candidate;
        int start;
        int end;
};