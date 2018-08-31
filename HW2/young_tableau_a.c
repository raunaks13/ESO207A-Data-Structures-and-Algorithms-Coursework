#include <stdio.h>

struct smallest
{
    int first;
    int second;
};

struct smallest search(int m, int n, int a[][n])
{
    int e = 8;
    int i = 0, j = 0;
    struct smallest pair;

    for(i = 0; i < m ; i++)
    {
        if(e < a[i][0])
        {
            printf("            %d          ", i);
            break;
        }
        else if(e == a[i][0])
        {
            pair.first = i;
            pair.second = j;
            return pair;
        }
    }

    i--;

    if(i >= 0)
    {
        for(j = 0 ; j < n ; j++)
        {
            if(e < a[i][j])
                break;
            else if(e == a[i][j])
            {
                pair.first = i;
                pair.second = j;
                printf("\n%d %d\n", pair.first, pair.second);

                return pair;
            }
        }
    }
}

int main()
{
    int a[3][4] = {
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12}
            };
    
    int m = 3, n = 4;

    int min = a[0][0];
    a[0][0] = 10000;

    int i = 0, j = 0;
    struct smallest smallest;

    while(i != m-1 || j != n-1)
    {
        smallest.first = i;
        smallest.second = j;

        if(j < n-1 && a[i][j+1] < a[i][j])
        {
            smallest.first = i;
            smallest.second = j+1;
        }
        if(i < m-1 && a[i+1][j] < a[smallest.first][smallest.second])
        {
            smallest.first = i+1;
            smallest.second = j;
        }
        if(smallest.first != i || smallest.second != j)
        {
            int temp = a[i][j];
            a[i][j] = a[smallest.first][smallest.second];
            a[smallest.first][smallest.second] = temp;
            i = smallest.first;
            j = smallest.second;
        }
        else break;
    }

    for(int i = 0;i < m; i++)
    {
        for(int j = 0;j < n;j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    struct smallest pair = search(m, n, a);
    printf("\n%d %d\n", pair.first, pair.second);
}