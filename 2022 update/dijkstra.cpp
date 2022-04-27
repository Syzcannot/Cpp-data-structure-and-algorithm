#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> dijkstra(int source,vector<vector<pair<int,int>>> &ma){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
    vector<int> dis(n+1,0x3f3f3f);
    dis[source]=0;
    q.push(make_pair(0,source));
    while (!q.empty()){
        auto now=q.top(); q.pop(); int d=now.first; int x=now.second;
        if (dis[x]<d) continue;
        for (auto i:ma[x]){
            int newdis=d+i.second;
            if (newdis<dis[i.first]){
                dis[i.first]=newdis;
                q.emplace(make_pair(i.first,newdis));
            }
        }
    }
    return dis;
}
int main() {
    int s=1;
    n=2;
    vector<vector<pair<int,int>>> edges(n+1); //edges[i][j]表示i相连的第j条边是<b,w>，b是编号，w是权值，也就是i与b有一条w的边
    edges[1].push_back(make_pair(2,1));
    auto dist=dijkstra(s,edges);
    cout<<dist[2];
    return 0;
}
