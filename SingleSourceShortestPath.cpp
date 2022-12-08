#include <cstdio>
#include <queue>
#define P pair<long long, int>
#define maxn 500005
using namespace std;

const int INF = 1e7;

priority_queue<P, vector<P>, greater<P>> q;
int dis[maxn], vis[maxn], head[maxn];
int n, m, s;
int cnt;

struct Edge
{
    int u, v, w, next;
} e[maxn * 2];

void add(int u, int v, int w)
{
    e[++cnt].u = u;
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}
void dijkstra()
{
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (!vis[x])
        {
            vis[x] = 1;
            for (int i = head[x]; i; i = e[i].next)
            {
                int v = e[i].v;
                dis[v] = min(dis[v], dis[x] + e[i].w);
                q.push(make_pair(dis[v], v));
            }
        }
    }
}

int main()
{
    printf("please input the number of places:\n>>");
    scanf("%d", &n);
    printf("please input the number of edges:\n>>");
    scanf("%d", &m);
    printf("please input the id of start point:\n>>");
    scanf("%d", &s);
    for (int i = 1; i <= m; ++i)
    {
        dis[i] = INF;
    }
    dis[s] = 0;
    q.push(make_pair(0, s));
    printf("please input start point, finish point and distance for %d edges\n", m);
    int ui, vi, wi;
    for (int i = 1; i <= m; i++)
    {
        printf(">>");
        scanf("%d%d%d", &ui, &vi, &wi);
        add(ui, vi, wi);
    }
    dijkstra();
    printf("the distance from s to every point is:\n");
    for (int i = 1; i <= n; i++)
    {
        printf("dis s -> %d : %d\n", i, dis[i]);
    }
    return 0;
}