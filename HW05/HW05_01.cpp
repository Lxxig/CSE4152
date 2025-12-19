#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

int main(void) {
    
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> Adj(N + 1);
    for (int i = 0; i < M; ++i)
    {
        int u, v;
        cin >> u >> v;
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }

    vector<pair<int, int>> RedVertices;
    for (int i = 1; i <= N; ++i)
    {
        int d;
        cin >> d;
        if (d != -1)
        {
            RedVertices.push_back({i, d});
        }
    }
    
    vector<int> ResultVertices;

    if (RedVertices.empty())
    {
        ResultVertices.resize(N);
        iota(ResultVertices.begin(), ResultVertices.end(), 1);
    }
    else
    {
        int K = RedVertices.size();
        vector<vector<int>> Dist(N + 1, vector<int>(K, -1));
        queue<pair<int, int>> Q;
        vector<int> Count(N + 1, 0);

        for (int k = 0; k < K; ++k)
        {
            int StartNode = RedVertices[k].first;
            int RequiredDist = RedVertices[k].second;
            
            Dist[StartNode][k] = 0;
            Q.push({StartNode, k});

            if (RequiredDist == 0) {
                Count[StartNode]++;
            }
        }

        while (!Q.empty())
        {
            pair<int, int> Current = Q.front();
            Q.pop();
            int u = Current.first;
            int SourceK = Current.second;
            int RequiredDist = RedVertices[SourceK].second;

            if (Dist[u][SourceK] >= RequiredDist) continue;

            for (int v : Adj[u])
            {
                if (Dist[v][SourceK] == -1)
                {
                    Dist[v][SourceK] = Dist[u][SourceK] + 1;
                    Q.push({v, SourceK});
                    if (Dist[v][SourceK] == RequiredDist)
                    {
                        Count[v]++;
                    }
                }
            }
        }

        for (int i = 1; i <= N; ++i)
        {
            if (Count[i] == K)
            {
                ResultVertices.push_back(i);
            }
        }
    }
    
    cout << ResultVertices.size() << endl;
    if (!ResultVertices.empty())
    {
        sort(ResultVertices.begin(), ResultVertices.end());
        for (size_t i = 0; i < ResultVertices.size(); ++i)
        {
            cout << ResultVertices[i] << (i == ResultVertices.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}