#include <cstdio>
#include <cstdlib>
#include <ctime>

void bubble_sort(int *arr, int p, int q)
{
    for (int i = p + 1; i <= q; i++)
    {
        int temp = arr[i], j = i - 1;
        while (j >= p)
        {
            if (arr[j] > temp)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            else
                break;
        }
        arr[j + 1] = temp;
    }
}

int Partition(int *arr, int p, int q, int mid)
{
    int i = p, j = q;
    while (i <= q && j >= p)
    {
        while (arr[i] < mid)
        {
            i++;
        }
        while (arr[j] > mid)
        {
            j--;
        }
        if (i >= j)
            break;
        else
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            ++i;
            --j;
        }
    }
    return j;
}

int Select(int *arr, int p, int q, int k)
{
    if (q - p < 75)
    {
        bubble_sort(arr, p, q);
        return arr[p + k - 1];
    }
    for (int i = 0; i <= (q - p - 4) / 5; i++)
    {
        bubble_sort(arr, p + 5 * i, p + 5 * i + 4);
        int temp = arr[p + 5 * i + 2];
        arr[p + 5 * i + 2] = arr[p + i];
        arr[p + i] = temp;
    }
    int mid = Select(arr, p, p + (q - p - 4) / 5, ((q - p - 4) / 5 + 1) / 2);
    int mid_id = Partition(arr, p, q, mid);
    int mid_rank = mid_id - p + 1;
    if (k == mid_rank)
    {
        return arr[mid_id];
    }
    else if (k < mid_rank)
    {
        return Select(arr, p, mid_id, k);
    }
    else
    {
        return Select(arr, mid_id + 1, q, k - mid_rank);
    }
}

int main()
{
    int num;
START:
    printf("please set the number of array\n>>");
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
    int k;
SELECT:
    printf("please input the i of the i-th smaller number you want\n>>");
    scanf("%d", &k);
    if (k > num)
    {
        printf("cannot find a number that over the index of array\n");
        system("pause");
        goto SELECT;
    }
    clock_t start = clock();
    int res = Select(arr, 0, num, k + 1);
    clock_t end = clock();
    printf("the %d-th smaller number is %d\n", k, res);
    printf("runtime: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    goto RETURN;
RETURN:
    // free(arr);
    return 0;
}
