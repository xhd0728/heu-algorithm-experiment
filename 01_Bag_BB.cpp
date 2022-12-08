#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct thing
{
    int w;
    int v;
    double k;

    thing()
    {
        w = 1;
        v = 0;
    }

    void getK()
    {
        k = (double)v / w;
    }

    bool operator<(const thing &s) const
    {
        return k > s.k;
    }
};

struct node
{
    int W;
    int V;
    int ub;
    int a[105];
    int index;

    node() : a{}
    {
        W = 0;
        V = 0;
        ub = 0;
        index = 0;
    }

    bool operator<(const node &s) const
    {
        return ub < s.ub;
    }

    void getUb(int C, vector<thing> things, int M)
    {
        int lb = 0;
        int _W = W;
        int i = index;
        while (_W + things[i].w <= C && i < M)
        {
            _W += things[i].w;
            lb += things[i].v;
            i++;
        }
        i++;
        int leave = (C - _W) * (things[i].k);
        ub = V + lb + leave;
    }
};

int main()
{
    int C = 0;
    int M = 0;
START:
    printf("please input the number of items\n>>");
    scanf("%d", &M);
    if (M <= 0)
    {
        printf("please input a correct number\n");
        goto START;
    }
    printf("please input the max weight of the bag\n>>");
    scanf("%d", &C);
    if (C <= 0)
    {
        printf("please input a correct number\n");
        goto START;
    }
    vector<thing> things;
    priority_queue<node> q;
    printf("please input the weight and value of every item, once in a line\n");
    for (int i = 0; i < M; i++)
    {
        thing t;
        printf(">>");
        scanf("%d%d", &t.w, &t.v);
        things.push_back(t);
        things[i].getK();
    }
    clock_t start = clock();
    sort(things.begin(), things.end());
    node t;
    t.getUb(C, things, M);
    q.push(t);
    int result = 0;
    while (q.empty() == false)
    {
        node f = q.top();
        q.pop();
        if (f.V >= f.ub)
        {
            result = f.V;
            break;
        }
        if (f.index < M)
        {
            node l = f;
            l.index = l.index + 1;
            l.getUb(C, things, M);
            q.push(l);
        }
        if (f.index < M && f.W + things[f.index].w <= C)
        {
            node r = f;
            r.W += things[r.index].w;
            r.V += things[r.index].v;
            r.a[r.index] = 1;
            r.index = r.index + 1;
            r.getUb(C, things, M);
            q.push(r);
        }
    }
    clock_t end = clock();
    printf("the max value is:\n%d\n", result);
    printf("\nruntime: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    return 0;
}
