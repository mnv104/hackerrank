#include <cmath>
#include <set>
#include <stdint.h>
#include <limits.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <utility>
using namespace std;

class Edges {
public:
   vector<set<int>> edges;
   Edges(int numNodes) {
      edges.resize(numNodes);
   }
   Edges(const Edges &e) {
      edges = e.edges;
   }
   void addEdge(int node1, int node2) {
      edges[node1].insert(node2);
      edges[node2].insert(node1);
   }
   set<int> operator[](int node) const {
      return edges[node];
   }
};

ostream& operator<<(ostream &stream, const set<int>& s)
{
   for (auto f: s) {
      stream << f << " ";
   }
   stream << endl;
   return stream;
}

ostream& operator<<(ostream &stream, const Edges &e)
{
   vector<set<int>>::const_iterator it = e.edges.cbegin();
   string s;
   int count = 0;
   while (it != e.edges.cend()) {
      set<int> v = *it;
      set<int>::const_iterator it1 = v.cbegin();
      stringstream ss;
      ss << "Node " << count << ":";
      s += ss.str();
      ss.clear();
      ss.str("");
      while (it1 != v.cend()) {
         ss << *it1 << " ";
         it1++;
      }
      ss << endl;
      s += ss.str();
      it++;
      count++;
   }
   stream << s;
   return stream;
}



class Graph {
public:
    int id;
    int N;
    int M;
    Edges edges;
    int S;
   public:
    Graph(const int &_id, const int &_N, const int &_M, const Edges &_edges, const int &_S):
    id(_id), N(_N), M(_M), S(_S), edges(_edges) {
    }
};

void readInput(int &T, vector<Graph> &v)
{
    {
        string line;
        getline(cin, line);
        stringstream ss(line);
        ss >> T;
    }
    for (int i = 0; i < T; i++) {
         int N, M;
         string line;
         getline(cin, line);
         stringstream ss(line);
         ss >> N;
         ss >> M;
         Edges edges(N);
         for (int j = 0; j < M; j++) {
             getline(cin, line);
             stringstream ss1(line);
             int node1, node2;
             ss1 >> node1;
             ss1 >> node2;
             edges.addEdge(node1 - 1, node2 - 1);
         }

         getline(cin, line);
         ss.str("");
         ss.clear();
         ss << line;
         int S;
         ss >> S;
         v.push_back(Graph(i, N, M, edges, S-1));
    }
    return;
}

void displayGraphs(const vector<Graph> &graphs)
{
    for (auto g: graphs) {
       cout << "id: " << g.id << " N = " << g.N << " M = " << g.M << " " << endl;
       cout << "S: " << g.S << endl;
       cout << g.edges << endl;
    }
}

struct node {
   int nodeId;
   int distance;
   node(int n, int d): nodeId(n), distance(d) { }
};

void bfsInt(const Graph& g)
{
   vector<node> v;
   vector<int> distances;
   distances.resize(g.N);
   for (int i = 0; i < g.N; i++) {
      if (i == g.S) {
         distances[i] = 0;
      } else {
         distances[i] = INT_MAX;
      }
   }
   v.push_back(node(g.S, 0));
   int distance = 6;
   while (!v.empty()) {
      node n = v.front();
      set<int> edges = g.edges[n.nodeId];
      for (auto e: edges) {
         if (distances[e] == INT_MAX) {
            distances[e] = distance + n.distance;
            v.push_back(node(e, distance + n.distance));
         }
      }
      v.erase(v.begin());
   }
   for (int i = 0; i < g.N; i++) {
      if (i != g.S) {
         if (distances[i] == INT_MAX) {
            cout << -1 << " ";
         } else {
            cout << distances[i] << " ";
         }
      }
   }
   cout << endl;
   return;
}

void bfs(const vector<Graph> &graphs)
{
    for (auto g: graphs) {
       bfsInt(g);
    }
}

int main() {
    int T;
    vector<Graph> graphs;
    readInput(T, graphs);
    bfs(graphs);
    return 0;
}

