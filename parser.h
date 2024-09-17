

#include <map>
#include <vector>
#include <string>
#include <queue>

#include "globals.h"

class Parser {
    public:
        void runParse(std::string airport, std::string route, int distType);
        std::vector<std::priority_queue<psd, std::vector<psd>, std::greater<psd>>> getRoutes();
        std::vector<std::pair<long double, long double>> getAirports();
        std::vector<int> getAirportIds();
        std::map<int, int> get_indices();
        std::map<int, std::string> getNames();
    private:
        int isNumber(std::string s);
        long double toRadians(const long double degree);
        long double distance(long double lat1, long double long1, long double lat2, long double long2);
        long double distancePy(long double lat1, long double long1, long double lat2, long double long2);
        std::vector<std::priority_queue<psd, std::vector<psd>, std::greater<psd>>> routes;
        std::vector<std::pair<long double, long double>> airports;
        std::vector<int> airport_ids;
        std::map<int, int> id_to_index;
        std::map<int, std::string> airport_names;
};