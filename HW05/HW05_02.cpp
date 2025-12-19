#include <iostream>
#include <vector>
using namespace std;

using Edge = pair<int, int>;
using FarthestNodeInfo = pair<int, long long>;

void FindFarthestDfs(int u, int p, long long CurrentDist, FarthestNodeInfo& Info, const vector<vector<Edge>>& Adj) {
    if (CurrentDist > Info.second)
    {
        Info = {u, CurrentDist};
    }
    
    for (const auto& edge : Adj[u])
    {
        int v = edge.first;
        int w = edge.second;
        if (v != p)
        {
            FindFarthestDfs(v, u, CurrentDist + w, Info, Adj);
        }
    }
}

bool FindPathDfs(int u, int p, int Target, vector<int>& Path, const vector<vector<Edge>>& Adj)
{
    Path.push_back(u);
    if (u == Target)
    {
        return true;
    }
    
    for (const auto& edge : Adj[u])
    {
        int v = edge.first;
        if (v != p)
        {
            if (FindPathDfs(v, u, Target, Path, Adj))
            {
                return true;
            }
        }
    }
    
    Path.pop_back();
    return false;
}


void Solve()
{
    int N, K;
    cin >> N >> K;

    vector<vector<Edge>> Adj(N + 1);
    for (int i = 0; i < N - 1; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        Adj[u].push_back({v, w});
        Adj[v].push_back({u, w});
    }
    
    FarthestNodeInfo InfoA = {0, -1};
    FindFarthestDfs(1, 0, 0, InfoA, Adj);
    int A = InfoA.first;

    FarthestNodeInfo InfoB = {0, -1};
    FindFarthestDfs(A, 0, 0, InfoB, Adj);
    int B = InfoB.first;
    long long DiameterLen = InfoB.second;

    if (K == 1)
    {
        cout << DiameterLen << "\n";
        return;
    }

    vector<int> DiameterPath;
    FindPathDfs(A, 0, B, DiameterPath, Adj);

    vector<bool> OnDiameter(N + 1, false);
    for (int node : DiameterPath)
    {
        OnDiameter[node] = true;
    }
    
    vector<long long> DistFromA(N + 1, 0);
    vector<long long> MaxBranchDist(N + 1, 0);
    
    long long AccumulatedDist = 0;
    for (size_t i = 0; i < DiameterPath.size(); ++i)
    {
        int u = DiameterPath[i];
        DistFromA[u] = AccumulatedDist;

        if (i + 1 < DiameterPath.size())
        {
            int v = DiameterPath[i + 1];
            for (const auto& edge : Adj[u])
            {
                if (edge.first == v)
                {
                    AccumulatedDist += edge.second;
                    break;
                }
            }
        }
    }
    
    for (int u : DiameterPath)
    {
        long long current_max_branch_for_u = 0;
        for (const auto& edge : Adj[u])
        {
            int v = edge.first;
            if (!OnDiameter[v])
            {
                FarthestNodeInfo BranchInfo = {v, edge.second};
                FindFarthestDfs(v, u, edge.second, BranchInfo, Adj);
                current_max_branch_for_u = max(current_max_branch_for_u, BranchInfo.second);
            }
        }
        MaxBranchDist[u] = current_max_branch_for_u;
    }
    
    int m = DiameterPath.size();
    vector<long long> PrefixMax(m), SuffixMax(m);
    
    PrefixMax[0] = MaxBranchDist[DiameterPath[0]];
    for (int i = 1; i < m; ++i)
    {
        int u = DiameterPath[i];
        PrefixMax[i] = max(PrefixMax[i-1], DistFromA[u] + MaxBranchDist[u]);
    }

    SuffixMax[m-1] = MaxBranchDist[DiameterPath[m-1]];
    for (int i = m - 2; i >= 0; --i)
    {
        int u = DiameterPath[i];
        long long DistFromB = DiameterLen - DistFromA[u];
        SuffixMax[i] = max(SuffixMax[i+1], DistFromB + MaxBranchDist[u]);
    }
    
    long long MinMaxDiameter = -1;
    
    for (int i = 0; i < m - 1; ++i)
    {
        long long DiamASide = PrefixMax[i];
        long long DiamBSide = SuffixMax[i+1];
        long long CurrentMax = max(DiamASide, DiamBSide);

        if (MinMaxDiameter == -1 || CurrentMax < MinMaxDiameter)
        {
            MinMaxDiameter = CurrentMax;
        }
    }
    
    cout << MinMaxDiameter << "\n";
}

int main(void) {
    
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Solve();

    return 0;
}
