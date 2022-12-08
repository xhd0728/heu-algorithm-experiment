#include <iostream>
#include <cstdio>
#include <string>
#include <set>
#include <ctime>

using namespace std;

int arr[201][201];
set<string> lcs_s;
int lcs_max(string s1, string s2)
{
    int m = s1.length();
    int n = s2.length();
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                arr[i][j] = arr[i - 1][j - 1] + 1;
            else
                arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
        }
    }
    return arr[m][n];
}
void lcs_print(string s1, string s2, int i, int j, string str)
{
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            i--;
            j--;
            str = s1[i] + str;
        }
        else
        {
            if (arr[i - 1][j] > arr[i][j - 1])
                i--;
            else if (arr[i - 1][j] < arr[i][j - 1])
                j--;
            else
            {
                lcs_print(s1, s2, i - 1, j, str);
                lcs_print(s1, s2, i, j - 1, str);
                return;
            }
        }
    }
    if (str.length())
        lcs_s.insert(str);
}
int main()
{
    string s1, s2;
    printf("please input 1-st string\n>>");
    cin >> s1;
    printf("please input 2-st string\n>>");
    cin >> s2;
    int m = s1.length();
    int n = s2.length();
    int len = lcs_max(s1, s2);
    string str;
    clock_t start = clock();
    lcs_print(s1, s2, m, n, str);
    clock_t end = clock();
    set<string>::iterator it = lcs_s.begin();
    if (lcs_s.empty())
    {
        printf("str1 and str2 has no common subsequence\n");
        goto RETURN;
    }
    printf("the max length of common subsequence is: %d\n", len);
    printf("the longest common subsequence is: ");
    while (it != lcs_s.end())
    {
        cout << *it << endl;
        it++;
    }
    printf("runtime: %lf\n", double(end - start) / CLOCKS_PER_SEC);
    goto RETURN;
RETURN:
    return 0;
}