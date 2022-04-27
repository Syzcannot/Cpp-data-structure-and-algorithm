
#include <bits/stdc++.h>

#define INF 2147483647
#define MAXN 10000
#define MAXM 500000
using namespace std;

struct edge {
    int u, v;
    int w;
    int next;
};
edge e[MAXM];

int n, m, x, y, w, len;
int first[MAXN + 30], d[MAXN + 30];
bool vis[MAXN + 30];

void add_edge(int a, int b, int c) {
    len++;
    e[len].u = a;
    e[len].v = b;
    e[len].w = c;
    e[len].next = first[a];
    first[a] = len;
}

void spfa(int s) {
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        d[i] = INF;
    d[s] = 0;
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = first[x]; i != 0; i = e[i].next) {
            y = e[i].v;
            if (d[x] + e[i].w < d[y]) {
                d[y] = d[x] + e[i].w;
                if (vis[y] == false) {
                    q.push(y);
                    vis[y] = true;
                }
            }
        }
    }
}

int main() {
    int s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        add_edge(x, y, w);
    }
    spfa(s);
    for (int i = 1; i <= n; i++) {
        cout << d[i] << ' ';
    }
    return 0;
}
