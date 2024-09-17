#include "parser.h"
#include "globals.h"
#include "BFS.h"
#include "dijkstra.h"
#include "PageRank.h"
#include <iostream>


#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

std::vector <priority_queue<psd, vector<psd>, greater<psd>>> routes;
std::vector<std::pair<long double, long double>> airports;
std::vector<int> airport_ids;
std::map<int, int> indices;
std::map<int, std::string> airport_names;
ofstream outputBFS, outputD, outputP;


//checks if a string is a number, if so return it, if not return -1
int isNumber(string s)
{
    for (size_t i = 0; i < s.length(); i++){
        if (isdigit(s[i]) == false)
            return -1;
      }
    return stoi(s);
}

//creates the directed adjacency matrix used for pagerank, a 1 in row i col j denotes a flight from airport j to airport i
std::vector<std::vector<double>> createAdjMatrix(std::vector <priority_queue<psd, vector<psd>, greater<psd>>>* routes, std::vector<std::pair<long double, long double>>* airports) {
  std::vector<std::vector<double>> matrix = std::vector<std::vector<double>>(airports->size(), std::vector<double>(airports->size()));
  for (int i=0;i<routes->size();i++) {
    std::priority_queue<psd, std::vector<psd>, std::greater<psd>> queue = (*routes)[i];
    while (!queue.empty()) {
      psd p = queue.top();
      queue.pop();

      matrix[p.second][i] = (double) p.first;
    }
  }
  return matrix;
}

//used for interfacing with the user when running using real data.
bool realcases() {
  std::cout << "---------Real Cases---------" << std::endl;
  std::cout << "Parsing data..." << std::endl;
  Parser p;
  p.runParse("airports.dat", "routes.dat", 1);
  routes = p.getRoutes();
  airports = p.getAirports();
  airport_ids = p.getAirportIds();
  indices = p.get_indices();
  airport_names = p.getNames();
  std::cout << "Parsing done." << std::endl;//parsing stuff
  std::cout << "Input 1 for BFS, 2 for Dijkstra's, and 3 for Pagerank." << std::endl;
  std::string uinput;
  cin >> uinput;
  while (uinput!="1"&&uinput!="2"&&uinput!="3") {
    std::cout << "Please try again." << std::endl;
    cin >> uinput;
  }
  if (uinput=="1") {
    std::cout << "---------BFS---------" << std::endl;//BFS stuff: get start and end from user, run.
    std::string startid, endid;
    std::cout << "Select start airport id (look in the airports.dat file)" << std::endl;
    std::cout << "Note: selecting an invalid id will default to selecting the first airport" << std::endl;
    cin >> startid;
    while (isNumber(startid)==-1) {
      std::cout << "Please try again" << std::endl;
      cin >> startid;
    }
    std::cout << "Select ending airport id" << std::endl;
    std::cout << "Note: selecting an invalid id will default to selecting the first airport" << std::endl;
    cin >> endid;
    while (isNumber(endid)==-1) {
      std::cout << "Please try again" << std::endl;
      cin >> endid;
    }
    BFS bfs(indices[isNumber(startid)], indices[isNumber(endid)], routes.size(), &routes);
    std::vector<int> path = bfs.run();
    std::cout << "Printing path:" << std::endl;
    if (path[0]==-1) std::cout << "A path could not be found from " << startid << " to " << endid << std::endl;
    else for (int q=0;q<path.size();q++) {
      if (q==path.size()-1) {
        std::cout << airport_names[airport_ids[path[q]]] << std::endl;
        outputBFS << airport_names[airport_ids[path[q]]] << std::endl;
      } else {
        std::cout << airport_names[airport_ids[path[q]]] << "->";
        outputBFS << airport_names[airport_ids[path[q]]] << "->";
      }
    }
    std::cout << "BFS done. ";
    std::cout << "Restart? (y/n)" << std::endl;
    std::string res;
    cin >> res;
    while (res!="y"&&res!="n") {
      std::cout << "Try again" << std::endl;
      cin >> res;
    }
    if (res == "y") return 1;
    else return 0;
  } else if (uinput=="2") {
    std::cout << "---------Dijkstra's---------" << std::endl;//Dijkstra's stuff: get start and end from user, run
    std::string startid, endid;
    std::cout << "Select start airport id (look in the airports.dat file)" << std::endl;
    std::cout << "Note: selecting an invalid id will default to selecting the first airport" << std::endl;
    cin >> startid;
    while (isNumber(startid)==-1) {
      std::cout << "Please try again" << std::endl;
      cin >> startid;
    }
    std::cout << "Select ending airport id" << std::endl;
    std::cout << "Note: selecting an invalid id will default to selecting the first airport" << std::endl;
    cin >> endid;
    while (isNumber(endid)==-1) {
      std::cout << "Please try again" << std::endl;
      cin >> endid;
    }
    Dijkstra dijkstra(indices[isNumber(startid)], indices[isNumber(endid)], routes.size(), routes);
    std::cout << "Running Dijkstra's..." << std::endl;
    std::vector<int> pat = dijkstra.run();
    std::cout << "Printing path:" << std::endl;
    if (pat[0]==-1) std::cout << "A path could not be found from " << startid << " to " << endid << std::endl;
    else for (int q=pat.size()-1;q>=0;q--) {
      if (q==0) {
        std::cout << airport_names[airport_ids[pat[q]]] << std::endl;
        outputD << airport_names[airport_ids[pat[q]]] << std::endl;
      }
      else {
        std::cout << airport_names[airport_ids[pat[q]]] << "->";
        outputD << airport_names[airport_ids[pat[q]]] << "->";
      }
    }
    std::cout << "Dijkstra's done. Restart? (y/n)" << std::endl;
    std::string res;
    cin >> res;
    while (res!="y"&&res!="n") {
      std::cout << "Try again" << std::endl;
      cin >> res;
    }
    if (res == "y") return 1;
    else return 0;

  } else if (uinput=="3") {
    std::cout << "---------PageRank---------" << std::endl;//Pagerank stuff: run pagerank, ask user for top airport number
    std::cout << "Creating adjacency matrix..." << std::endl;
    std::vector<std::vector<double>> adj = createAdjMatrix(&routes, &airports);
    PageRank pagerank(adj);
    pagerank.matrix(adj.size(), 0.85);
    vector<double> ranks;
    std::string iters;
    std::cout << "How many iterations? Keep in mind each iteration takes around half a second to compute. A good number is around 50." << std::endl;
    cin >> iters;
    while(isNumber(iters)==-1) {
      std::cout << "Try again" << std::endl;
      cin >> iters;
    }
    std::cout << "Running PageRank..." << std::endl;
    vector<double> re = pagerank.rank(ranks, isNumber(iters));
    priority_queue<psd> pqueue;
    
    for (int i=0;i<re.size();i++) {
      pqueue.push({re[i], i});
    }
    std::cout << "Ranks generated." << std::endl;
    std::cout << "Input the number of ranked airports you would like to see." << std::endl;
    std::string qnum;
    cin >> qnum;
    while (isNumber(qnum)==-1) {
      std::cout << "Try again" << std::endl;
      cin >> qnum;
    }
    int cou = 0;
    while (!pqueue.empty() && cou < isNumber(qnum)) {
      psd p = pqueue.top();
      pqueue.pop();
      outputP << cou+1 << ". Airport: " << airport_names[airport_ids[p.second]] << ", Rank: " << p.first << std::endl;
      std::cout << cou+1 << ". Airport: " << airport_names[airport_ids[p.second]] << ", Rank: " << p.first << std::endl;
      cou++;
    }
    std::cout << "PageRank done. Restart? (y/n)" << std::endl;
    std::string res;
    cin >> res;
    while (res!="y"&&res!="n") {
      std::cout << "Try again" << std::endl;
      cin >> res;
    }
    if (res == "y") return 1;
    else return 0;
  }
  return 0;
}


//used for showcasing small test cases.
bool smallcases() {
  std::string trash;
  std::cout << "You have chosen to run small test cases." << std::endl;
  std::cout << "Rather than asking for user input, the program will run predefined inputs that show the algorithms are working." << std::endl;
  std::cout << "Each case will have a description of what it demonstrates." << std::endl;
  std::cout << std::endl << "!IMPORTANT!: It is strongly recommended you reference the provided pngs in the data folder when corroborating test cases." << std::endl;
  std::cout << "Medium Graph.png is used for test cases 1-3. Small Graph.png is used for test cases 4-5." << std::endl << std::endl;
  std::cout << "Input any key when you are ready. Input q if you want to quit." << std::endl;
  cin >> trash;
  if (trash=="q") return 0;
  std::cout << "Parsing data..." << std::endl;
  Parser p;
  p.runParse("airportsmed.dat", "routesmed.dat", 0);
  routes = p.getRoutes();
  airports = p.getAirports();
  airport_ids = p.getAirportIds();
  indices = p.get_indices();
  airport_names = p.getNames();
  std::cout << "Parsing done." << std::endl;

  std::cout << "---------CASE 1---------" << std::endl;
  std::cout << "BFS returns path from 3 to 6 with least nodes visited" << std::endl;
  BFS bfs(indices[3], indices[6], routes.size(), &routes);
  std::vector<int> path = bfs.run();
  std::cout << "Printing path:" << std::endl;
  for (int q=0;q<path.size();q++) {
    if (q==path.size()-1) std::cout << airport_ids[path[q]] << std::endl;
    else std::cout << airport_ids[path[q]] << "->";
  }
  std::cout << "As seen, BFS finds the appropriate path with only 3 nodes visited, which is the least possible." << std::endl;
  std::cout << "Input any key to continue. Input q if you want to quit." << std::endl;
  cin >> trash;
  if (trash=="q") return 0;

  std::cout << "---------CASE 2---------" << std::endl;
  std::cout << "Dijkstra's finds the path from 3 to 6 with the shortest distance traveled" << std::endl;
  Dijkstra dijkstra(indices[3], indices[6], routes.size(), routes);
  std::vector<int> pat = dijkstra.run();
  std::cout << "Printing path:" << std::endl;
  for (int q=pat.size()-1;q>=0;q--) {
    if (q==0) std::cout << airport_ids[pat[q]] << std::endl;
    else std::cout << airport_ids[pat[q]] << "->";
  }
  std::cout << "As seen, Dijkstra's finds the least distance, with more airports visited than BFS." << std::endl;
  std::cout << "Input any key to continue. Input q if you want to quit." << std::endl;
  cin >> trash;
  if (trash=="q") return 0;

  std::cout << "---------CASE 3---------" << std::endl;
  std::cout << "BFS/Dijkstra's cannot find a path from 1 to 7" << std::endl;
  BFS bfs1(indices[1], indices[7], routes.size(), &routes);
  std::vector<int> path1 = bfs1.run();
  std::cout << "BFS Printing path:" << std::endl;
  if (path1[0]==-1) std::cout << "A path could not be found from 1 to 7" << std::endl;
  else for (int q=0;q<path1.size();q++) {
    if (q==path1.size()-1) std::cout << airport_ids[path1[q]] << std::endl;
    else std::cout << airport_ids[path1[q]] << "->";
  }

  Dijkstra dijkstra1(indices[1], indices[7], routes.size(), routes);
  std::vector<int> pat1 = dijkstra1.run();
  std::cout << "Dijkstra's Printing path:" << std::endl;
  if (pat1[0]==-1) std::cout << "A path could not be found from 1 to 7" << std::endl;
  else for (int q=pat1.size()-1;q>=0;q--) {
    if (q==0) std::cout << airport_ids[pat1[q]] << std::endl;
    else std::cout << airport_ids[pat1[q]] << "->";
  }
  std::cout << "As seen, BFS and Dijkstra's cannot find the path as it does not exist." << std::endl;
  std::cout << "Input any key to continue. Input q if you want to quit." << std::endl;
  cin >> trash;
  if (trash=="q") return 0;
  std::cout << "For pagerank testing, we use a smaller graph with 4 airports." << std::endl;
  std::cout << "Parsing data..." << std::endl;
  Parser p1;
  p1.runParse("airportssmall.dat", "routessmall.dat", 0);
  routes = p1.getRoutes();
  airports = p1.getAirports();
  airport_ids = p1.getAirportIds();
  indices = p1.get_indices();
  airport_names = p1.getNames();
  std::cout << "Parsing done." << std::endl;
  std::cout << "---------CASE 4---------" << std::endl;
  std::cout << "PageRank gives airport 3 the highest rank, and other airports sensible ranks" << std::endl;
  std::vector<std::vector<double>> adj = createAdjMatrix(&routes, &airports);
  PageRank pagerank(adj);
  pagerank.matrix(adj.size(), 0.85);
  vector<double> ranks;
  vector<double> re = pagerank.rank(ranks, 50);
  priority_queue<psd> pqueue;
    
  for (int i=0;i<re.size();i++) {
    pqueue.push({re[i], i});
  }
  int cou=0;
  while (!pqueue.empty()) {
    cou++;
    psd p = pqueue.top();
    pqueue.pop();
    std::cout << cou << ". Airport: " << airport_ids[p.second] << ", Rank: " << p.first << std::endl;
  }
  std::cout << "As seen, airport 3 has highest rank which is expected. Airport 4 has lowest rank which is also expected." << std::endl;
  std::cout << "Input any key to continue. Input q if you want to quit." << std::endl;
  cin >> trash;
  if (trash=="q") return 0;
 
  std::cout << "---------CASE 5---------" << std::endl;
  std::cout << "Pagerank with damping factor 0 gives all airports equal rank" << std::endl;
  std::vector<std::vector<double>> adj1 = createAdjMatrix(&routes, &airports);
  PageRank pagerank1(adj1);
  pagerank1.matrix(adj1.size(), 0);
  vector<double> ranks1;
  vector<double> re1 = pagerank1.rank(ranks, 50);
  priority_queue<psd> pqueue1;
    
  for (int i=0;i<re1.size();i++) {
    pqueue1.push({re1[i], i});
  }
  int cou1=0;
  while (!pqueue1.empty()) {
    cou1++;
    psd p = pqueue1.top();
    pqueue1.pop();
    std::cout << cou1 << ". Airport: " << airport_ids[p.second] << ", Rank: " << p.first << std::endl;
  }
  std::cout << "A damping factor of 0 means noone will ever go between airports. Thus they all have the same rank." << std::endl;

  std::cout << "Test cases done. Restart? (y/n)" << std::endl;
  cin >> trash;
  while (trash!="y"&&trash!="n") {
    std::cout << "Try again" << std::endl;
    cin >> trash;
  }
  if (trash=="y") return 1;
  return 0;
}


//where it all starts.
int main() {
  outputBFS.open("Outputs/outBFS.txt");
  outputD.open("Outputs/outDijkstras.txt");
  outputP.open("Outputs/outPageRank.txt");
  std::string userinput;
  std::cout << "Welcome to our CS 225 Final Project!" << std::endl;
  std::cout << "Input 1 for small test cases, input 2 for data from OpenFlights" << std::endl;

  cin >> userinput;

  while (userinput!="1"&&userinput!="2") {
    std::cout << "Please try again" << std::endl;
    cin >> userinput;
  }
  
  if (userinput == "1") {
    bool cont = 1;
    while (cont) {
      cont = smallcases();//run small test cases
    }
  }
  else if (userinput == "2") {
    bool cont = 1;
    while (cont) {
      cont = realcases();//run with real data
    }
  }

  std::cout << "Thanks for using our app. Goodbye" << std::endl;
  outputBFS.close();
  outputD.close();
  outputP.close();
}