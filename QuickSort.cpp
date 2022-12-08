#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Range
{
    int start, end;
    Range(int s = 0, int e = 0) { start = s, end = e; }
};

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void quick_sort(int *arr, const int len)
{
    if (len <= 0)
        return;
    Range r[len];
    int p = 0;
    r[p++] = Range(0, len - 1);
    while (p)
    {
        Range range = r[--p];
        if (range.start >= range.end)
            continue;
        int mid = arr[range.end];
        int left = range.start, right = range.end - 1;
        while (left < right)
        {
            while (arr[left] < mid && left < right)
                left++;
            while (arr[right] >= mid && left < right)
                right--;
            swap(arr[left], arr[right]);
        }
        if (arr[left] >= arr[range.end])
            swap(arr[left], arr[range.end]);
        else
            left++;
        r[p++] = Range(range.start, left - 1);
        r[p++] = Range(left + 1, range.end);
    }
}

int main()
{
    int num;
START:
    printf("please input the number of array\n>>");
    scanf("%d", &num);
    if (num <= 0)
    {
        printf("please input correct number\n");
        system("pause");
        goto START;
    }
    int *arr = (int *)malloc(sizeof(int) * num);
    printf("please input %d numbers, and split them by space\n>>", num);
    for (int i = 0; i < num; ++i)
    {
        scanf("%d", &arr[i]);
    }
    clock_t start = clock();
    quick_sort(arr, num);
    clock_t end = clock();
    printf("array ordered by quick_sort func\n");
    for (int i = 0; i < num; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("runtime: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    goto RETURN;
RETURN:
    free(arr);
    return 0;
}