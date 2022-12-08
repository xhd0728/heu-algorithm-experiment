#include <cstdio>
#include <ctime>

using namespace std;

int bestv = 0;
int v[10000];
int w[10000];
int x[10000];
int bestx[10000];

void Backtrack(int num, int weight, int i, int cv, int cw)
{
    int j;
    if (i > num)
    {
        if (cv > bestv)
        {
            bestv = cv;
            for (i = 0; i <= num; i++)
                bestx[i] = x[i];
        }
    }
    else
        for (j = 0; j <= 1; j++)
        {
            x[i] = j;
            if (cw + x[i] * w[i] <= weight)
            {
                cw += w[i] * x[i];
                cv += v[i] * x[i];
                Backtrack(num, weight, i + 1, cv, cw);
                cw -= w[i] * x[i];
                cv -= v[i] * x[i];
            }
        }
}

int main()
{
    int num, weight;
START:
    printf("please input the number of items\n>>");
    scanf("%d", &num);
    if (num <= 0)
    {
        printf("please input a correct number\n");
        goto START;
    }
    printf("please input the max weight of the bag\n>>");
    scanf("%d", &weight);
    if (weight <= 0)
    {
        printf("please input a correct number\n");
        goto START;
    }
    int i;
    bestv = 0;
    printf("please input the weight and value of every item, once in a line\n");
    for (int i = 1; i <= num; ++i)
    {
        printf(">>");
        scanf("%d%d", &w[i], &v[i]);
    }
    clock_t start = clock();
    Backtrack(num, weight, 1, 0, 0);
    clock_t end = clock();
    printf("the max value is:\n%d\n", bestv);
    printf("selected items:\n");
    for (i = 1; i <= num; i++)
    {
        bestx[i] == 1 ? printf("%d ", i) : 1;
    }
    printf("%d ", bestx[i]);
    printf("\nruntime: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    return 0;
}
