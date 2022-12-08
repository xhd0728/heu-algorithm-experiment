#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#define MaxSize 1024

typedef struct wordcnt
{
    char ch;
    int cnt = 0;
} Count;

typedef struct NumCount
{
    Count count[MaxSize];
    int length = 0;
} NumCount;

typedef struct HTree
{
    char data;
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef struct HCode
{
    char data;
    char *str;
} *HuffmanCode;

void ReadData(char *source);
void WordCount(char *data, NumCount *paraCnt);
void Show(NumCount *paraCnt);
void CreateHuffmanTree(HuffmanTree &HT, int length, NumCount cntarray);
void select(HuffmanTree HT, int top, int *s1, int *s2);
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int length);
void Encode(char *data, HuffmanCode HC, int length);
void Decode(HuffmanTree HT, int length);

int main()
{
    char data[MaxSize];
    NumCount Cntarray;
    ReadData(data);
    WordCount(data, &Cntarray);
    Show(&Cntarray);
    HuffmanTree tree;
    CreateHuffmanTree(tree, Cntarray.length, Cntarray);
    HuffmanCode code;
    CreateHuffmanCode(tree, code, Cntarray.length);
    Encode(data, code, Cntarray.length);
    Decode(tree, Cntarray.length);
    printf("decoded file is saved as \"out.txt\"\n");
    return 0;
}

void ReadData(char *source)
{
    ifstream infile;
    infile.open("in.txt");
    printf("the context in \"in.txt\" is:\n\n");
    infile.getline(source, MaxSize);
    cout << source << "\n";
    infile.close();
    cout << "\n";
}

void WordCount(char *data, NumCount *paraCnt)
{
    int flag;
    int len = strlen(data);
    for (int i = 0; i < len; ++i)
    {
        flag = 0;
        for (int j = 0; j < paraCnt->length; ++j)
        {
            if (paraCnt->count[j].ch == data[i])
            {
                ++paraCnt->count[j].cnt;
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            paraCnt->count[paraCnt->length].ch = data[i];
            ++paraCnt->count[paraCnt->length].cnt;
            ++paraCnt->length;
        }
    }
}

void Show(NumCount *paraCnt)
{
    printf("total: %d ASCII characters\n\n", paraCnt->length);
    for (int i = 0; i < paraCnt->length; ++i)
    {
        printf("char \'%c'\' appears %d times\n", paraCnt->count[i].ch, paraCnt->count[i].cnt);
    }
    cout << "\n";
}

void CreateHuffmanTree(HuffmanTree &HT, int length, NumCount cntarray)
{
    if (length <= 1)
        printf("ERROR!!!\r\n");

    int s1, s2;
    int m = length * 2 - 1;
    HT = new HTNode[m + 1];
    for (int i = 1; i <= m; ++i)
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }

    for (int i = 1; i <= length; ++i)
    {
        HT[i].data = cntarray.count[i - 1].ch;
        HT[i].weight = cntarray.count[i - 1].cnt;
    }

    for (int i = length + 1; i <= m; ++i)
    {
        select(HT, i - 1, &s1, &s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void select(HuffmanTree HT, int top, int *s1, int *s2)
{
    int min = INT_MAX;
    for (int i = 1; i <= top; ++i)
    {
        if (HT[i].weight < min && HT[i].parent == 0)
        {
            min = HT[i].weight;
            *s1 = i;
        }
    }

    min = INT_MAX;
    for (int i = 1; i <= top; ++i)
    {
        if (HT[i].weight < min && i != *s1 && HT[i].parent == 0)
        {
            min = HT[i].weight;
            *s2 = i;
        }
    }
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int length)
{
    HC = new HCode[length + 1];
    char *cd = new char[length];
    cd[length - 1] = '\0';
    int c, f, start;
    for (int i = 1; i <= length; ++i)
    {
        start = length - 1;
        c = i;
        f = HT[c].parent;
        while (f != 0)
        {
            --start;
            if (HT[f].lchild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = f;
            f = HT[c].parent;
        }
        HC[i].str = new char[length - start];
        HC[i].data = HT[i].data;
        strcpy(HC[i].str, &cd[start]);
    }
    delete[] cd;
}

void Encode(char *data, HuffmanCode HC, int length)
{
    ofstream outfile;
    outfile.open("code.bin");
    for (int i = 0; i < int(strlen(data)); ++i)
    {
        for (int j = 1; j <= length; ++j)
        {
            if (data[i] == HC[j].data)
            {
                outfile << HC[j].str;
            }
        }
    }
    outfile.close();
    printf("encode file is saved as \"code.bin\"\n\n");
}

void Decode(HuffmanTree HT, int length)
{
    char codetxt[MaxSize * length];
    ifstream infile;
    infile.open("code.bin");
    infile.getline(codetxt, MaxSize * length);
    infile.close();

    ofstream outfile;
    outfile.open("out.txt");

    int root = 2 * length - 1;
    for (int i = 0; i < int(strlen(codetxt)); ++i)
    {
        if (codetxt[i] == '0')
            root = HT[root].lchild;
        else if (codetxt[i] == '1')
            root = HT[root].rchild;
        if (HT[root].lchild == 0 && HT[root].rchild == 0)
        {
            outfile << HT[root].data;
            root = 2 * length - 1;
        }
    }
    outfile.close();
    printf("decode file is saved as \"out.txt\"\n\n");
}
