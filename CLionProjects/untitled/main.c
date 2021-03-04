#include <stdio.h>
#define N 255

int main()
{
    int a, b;
    int arr[N][N];
    int chararr[N];
    scanf ("%d %d", &a, &b);
    for(int i = 0; i < a; ++i)
    {
        chararr[i] = 0;
    }
    for (int i=0; i<b; i++)
    {
        for (int j = 0; j < a; j++)
        {
            int temp;
            scanf("%d", &temp);
            arr[i][j] = temp;
            if (temp < 0 && temp & 1) chararr[j] += temp;
        }
    }
    for(int k = 0; k < a - 1; ++k)
    {
        for(int i = 0; i < a - k; ++i)
        {
            if (chararr[i] > chararr[i + 1]) {
                for (int j = 0; j < b; ++j) {
                    int el = arr[j][i];
                    arr[j][i] = arr[j][i + 1];
                    arr[j][i + 1] = el;
                }
                int temp = chararr[i];
                chararr[i] = chararr[i + 1];
                chararr[i + 1] = temp;
            }
        }
    }
    for (int i=0; i<b; i++)
    {
        for (int j = 0; j < a; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("%d %d", chararr[0], chararr[a - 1]);


    return 0;
}