#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

int binary_search(int *arr, int start, int end, int key)
{
    int ret = -1;
    int mid;
    while (start <= end)
    {
        mid = start + ((end - start) >> 1);
        if (arr[mid] < key)
            start = mid + 1;
        else if (arr[mid] > key)
            end = mid - 1;
        else
        {
            ret = mid;
            break;
        }
    }
    return ret;
}

int main()
{
    int num;
START:
    printf("please set the length of array\n>>");
    scanf("%d", &num);
    if (num <= 0)
    {
        printf("please input correct number\n");
        system("pause");
        goto START;
    }
    int *arr = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; ++i)
    {
        arr[i] = (int)rand();
    }
    sort(arr, arr + num);
    printf("ordered!(from small to large)\n");
    for (int i = 0; i < num; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\nplease input a number to search\n>>");
    int k;
    scanf("%d", &k);
    clock_t start = clock();
    int res = binary_search(arr, 0, num - 1, k);
    clock_t end = clock();
    if (k == -1)
    {
        printf("number not found");
        goto RETURN;
    }
    printf("index: %d(start from 0)\n", res);
    printf("runtime: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    goto RETURN;
RETURN:
    free(arr);
    return 0;
}