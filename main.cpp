#include "DisjSet.h"
#include "MinCutter.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int Mincut(vector<vector<int>> G);
pair<double, int> MinimumCutPhase(vector<vector<int>> &w,
                                  vector<int> &G,
                                  DisjSet &dSet);

int main()
{
    // # of vertices
    int n;
    // # of edges
    int e;
    // Adjacency matrix
    vector<vector<double>> G;
    cin >> n;
    cin >> e;

    G = vector<vector<double>>(n, vector<double>(n, 0));

    int x, y;
    double w;
    for (int i = 0; i < e; i++)
    {
        cin >> x >> y >> w;
        G[x - 1][y - 1] = w;
        G[y - 1][x - 1] = w;
    }


    MinCutter m(G);
    cout<<m<<endl;
    cout.flush();
    return 0;
}
