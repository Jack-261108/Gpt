#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 12;
const int score[10][10] =
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 6, 6, 6, 6, 6, 6, 6, 6, 6},
     {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
     {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
     {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
     {0, 6, 7, 8, 9, 10, 9, 8, 7, 6},
     {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
     {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
     {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
     {0, 6, 6, 6, 6, 6, 6, 6, 6, 6}};
int a[N][N];
int x[N][N], y[N][N], z[N][N];
bool flag;
int maxi;

int sum()
{
    int temp = 0;
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            temp += a[i][j] * score[i][j];
    // cout<<temp<<endl;
    return temp;
}

void dfs(int i, int j)
{
    if (i == 0)
    {

        flag = true;
        maxi = max(maxi, sum());
        return;
    }
    if (j == 0)
        dfs(i - 1, 9);
    if (a[i][j] == 0)
    {
        for (int m = 1; m <= 9; m++)
        {
            int h = ((i - 1) / 3) * 3 + ((j - 1) / 3);
            if (x[i][m] == 0 && y[j][m] == 0 && z[h][m] == 0)
            {
                a[i][j] = m;
                x[i][m] = 1;
                y[j][m] = 1;
                z[h][m] = 1;
                dfs(i, j - 1);
                a[i][j] = 0;
                x[i][m] = 0;
                y[j][m] = 0;
                z[h][m] = 0;
            }
        }
    }
    else
    {
        dfs(i, j - 1);
    }
}

int main()
{
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
        {
            cin >> a[i][j];
            if (a[i][j] != 0)
            {
                x[i][a[i][j]] = 1;
                y[j][a[i][j]] = 1;
                int h = ((i - 1) / 3) * 3 + ((j - 1) / 3);
                z[h][a[i][j]] = 1;
            }
        }
    // cout<<a[9][9];
    dfs(9, 9);
    if (flag)
        cout << maxi;
    else
        cout << -1;
    return 0;
}