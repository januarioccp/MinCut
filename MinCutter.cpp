#include "MinCutter.h"
#include "DisjSet.h"

ostream& operator<<(ostream& os, const MinCutter& m){
    os<<m.minCut<<endl;
    os<<"{";
    for(auto i:m.S1){
        os<<i;
        if(i!=m.S1.back())
            os<<",";
    }
    os<<"}{";
    for(auto i:m.S2){
        os<<i;
        if(i!=m.S2.back())
            os<<",";
    }
    os<<"}";
    return os;
}


MinCutter::MinCutter(const vector<vector<double> > &wf){
    this->w = wf;
    this->MINIMUMCUT();
}

MinCutter::MinCutter(const vector<vector<int> > &wf){
    this->w.resize(wf.size());
    for(int i = 0; i < wf.size(); i++){
        this->w[i].resize(wf[i].size());
        for(int j = 0; j < wf[i].size(); j++)
            this->w[i][j] = double(wf[i][j]);
    }
    #ifdef DEBUG
        cout<<__LINE__<<" : "<<w.size()<<endl;
    #endif
    this->MINIMUMCUT();
    #ifdef DEBUG
        cout<<__LINE__<<" : "<<w.size()<<endl;
    #endif
}

MinCutter::~MinCutter(){
    delete this->dSet;
}

void MinCutter::MINIMUMCUT()
{
    int n = this->w.size();
    #ifdef DEBUG
        cout<<__LINE__<<" : "<<w.size()<<endl;
    #endif
    // You need to find the value of the minimum cut
    this->minCut = numeric_limits<double>::max();

    // Create a vertex set
    G.resize(n);
    for (unsigned i = 0; i < G.size(); i++)
        G[i] = i;

    // TODO Randomize the set of vertices
    //random_shuffle(V.begin(), V.end());

    // Use a disjoint set data structure to shrink G later
    dSet = new DisjSet(n);

    // Compute the minimumCut while there is
    // at least 2 vertices
    while (G.size() > 1)
    {
        pair<double, int> result = MINIMUMCUTPHASE();
        double cut_of_the_phase = result.first;
        int last = result.second;

        if (cut_of_the_phase < this->minCut)
        {
            this->minCut = cut_of_the_phase;
            // Clear the partition set every time???
            S1.clear();
            S2.clear();
            for (int i = 0; i < n; i++)
                if (dSet->find(last) == dSet->find(i))
                    S1.push_back(i);
                else
                    S2.push_back(i);   
        }
        // Shrink G
        G.erase(remove(G.begin(), G.end(), last), G.end());
    }
}

pair<double, int> MinCutter::MINIMUMCUTPHASE(){
    // A container to the vertices in this phase
    vector<int> A;

    // Store a copy of G
    vector<int> V;

    // Copying G by assign function
    V.assign(G.begin(), G.end());

    // Choose a vector from v=2 to insert in A
    A.push_back(1);

    // Remove the vertex inserted in A from G
    // V.erase(V.begin() + 1);
    V.erase(remove(V.begin(), V.end(), 1), V.end());

    // Initialize with the minimum value, because you
    // want to find the maximum cut value
    double cut_of_the_phase;

    // Use this auxiliary variable to help you to find
    // the largest value in each phase
    double cutWeight = 0.0;

    //most tightly connected vertex
    int mtcv;

    // Store the initial size of G
    int n = V.size() + A.size();

    // You need to do until A is as large as the initial size of G
    while (A.size() < n)
    {
        cut_of_the_phase = numeric_limits<double>::min();
        // Find the most tightly connected vertex - mtcv
        mtcv = V.front();
        for (auto i : V)
        {
            cutWeight = 0.0;
            for (auto j : A)
                cutWeight += w[i][j];
            if (cutWeight > cut_of_the_phase)
            {
                // Store the cut of the phase value
                cut_of_the_phase = cutWeight;
                // Store the most tightly connected vertex - mtcv
                mtcv = i;
            }
        }
        // Add to A the most tightly connected vertex - mtcv
        A.push_back(mtcv);
        
        // Remove mtcv from V
        V.erase(remove(V.begin(), V.end(), mtcv), V.end());
    }

    // Before last
    int s = *(A.end() - 2);
    // Last added
    int t = A.back();

    #ifdef DEBUG
    cout<<cut_of_the_phase<<endl;
    for (int i = 0; i < w.size(); i++)
        if (dSet->find(t) == dSet->find(i))
            cout<<i<<" ";
    cout<<" - "
    for (int i = 0; i < w.size(); i++)
        if (dSet->find(t) != dSet->find(i))
            cout<<i<<" ";
        cout<<endl;
    #endif

    // Merge the two last vertex added last
    dSet->Union(s, t);

    for (auto i : A){
        w[i][s] += w[i][t];
        w[s][i] = w[i][s];
    }

    return make_pair(cut_of_the_phase, t);
}