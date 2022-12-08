#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>

using namespace std;
struct action
{
    int s;
    int f;
    int index;
} a[1000];

bool cmp(const action &a, const action &b)
{
    return a.f <= b.f;
}

int main()
{
    int n;
    bool b[1000];
    memset(b, 0, sizeof(b));
    printf("please input the number of activities:\n>>");
    scanf("%d", &n);
    printf("please input start time and finish time for every activity\n");
    printf("and split them by blank\n");
    for (int i = 1; i <= n; i++)
    {
        printf(">>");
        scanf("%d%d", &a[i].s, &a[i].f);
    }
    clock_t start = clock();
    sort(a, a + n + 1, cmp);
    b[1] = true;
    int preEnd = 1;
    for (int i = 2; i <= n; i++)
    {
        if (a[i].s >= a[preEnd].f)
        {
            b[i] = true;
            preEnd = i;
        }
    }
    clock_t end = clock();
    printf("selected activities:\n");
    for (int i = 1; i <= n; i++)
    {
        b[i] ? printf("%d ", i) : 1;
    }
    printf("\nruntime: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    return 0;
}
