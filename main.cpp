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
    vector<vector<int>> G;
    cin >> n;
    cin >> e;

    G = vector<vector<int>>(n, vector<int>(n, 0));

    int x, y, w;
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

// int Mincut(vector<vector<int>> w)
// {
//     int n = w.size();
//     vector<int> Smin;
//     vector<bool> seen(n);

//     // You need to find the value of the minimum cut
//     double current_min_cut = numeric_limits<double>::max();

//     // Create a vertex set
//     vector<int> V(n);
//     for (unsigned i = 0; i < V.size(); i++)
//         V[i] = i;

//     // Randomize the set of vertices
//     //random_shuffle(V.begin(), V.end());

//     // Use a disjoint set data structure to shrink G
//     DisjSet dSet(n);

//     // Compute the minimumCut while there is
//     // at least 2 vertices
//     while (V.size() > 1)
//     {
//         pair<double, int> result = MinimumCutPhase(w, V, dSet);
//         double cut_of_the_phase = result.first;
//         int last = result.second;

//         if (cut_of_the_phase < current_min_cut)
//         {
//             current_min_cut = cut_of_the_phase;

//             // Clear the partition set every time!
//             Smin.clear();
//             for (int i = 0; i < n; i++)
//                 if (dSet.find(last) == dSet.find(i))
//                     Smin.push_back(i);
//         }
//     }

//     return current_min_cut;
// }

// pair<double, int> MinimumCutPhase(vector<vector<int>> &w,
//                                   vector<int> &G, // Make a Copy!!
//                                   DisjSet &dSet)
// {

//     // A container to the vertices in this phase
//     vector<int> A;

//     // Store a copy of G
//     vector<int> V;

//     // Copying G by assign function
//     V.assign(G.begin(), G.end());

//     // Choose a vector from v=2 to insert in A
//     A.push_back(1);

//     // Remove the vertex inserted in A from G
//     // V.erase(V.begin() + 1);
//     V.erase(remove(V.begin(), V.end(), 1), V.end());

//     // Initialize with the minimum value, because you
//     // want to find the maximum cut value
//     double cut_of_the_phase;

//     // Use this auxiliary variable to help you to find
//     // the largest value in each phase
//     double cutWeight = 0.0;

//     //most tightly connected vertex
//     int mtcv;

//     // Store the initial size of G
//     int n = V.size() + A.size();

//     // You need to do until A is as large as the initial size of G
//     while (A.size() < n)
//     {
//         cut_of_the_phase = numeric_limits<double>::min();
//         // Find the most tightly connected vertex - mtcv
//         mtcv = V.front();
//         for (auto i : V)
//         {
//             cutWeight = 0.0;
//             for (auto j : A)
//                 cutWeight += w[i][j];
//             if (cutWeight > cut_of_the_phase)
//             {
//                 // Store the cut of the phase value
//                 cut_of_the_phase = cutWeight;
//                 // Store the most tightly connected vertex - mtcv
//                 mtcv = i;
//             }
//         }
//         // Add to A the most tightly connected vertex - mtcv
//         A.push_back(mtcv);
        
//         // Remove mtcv from V
//         V.erase(remove(V.begin(), V.end(), mtcv), V.end());
//     }

//     // Before last
//     int s = *(A.end() - 2);
//     // Last added
//     int t = A.back();

//     // Merge the two last vertex added last
//     dSet.Union(s, t);

//     // Shrink G
//     G.erase(remove(G.begin(), G.end(), t), G.end());
//     for (auto i : A){
//         w[i][s] += w[i][t];
//         w[s][i] = w[i][s];
//     }

//     return make_pair(cut_of_the_phase, t);
// }