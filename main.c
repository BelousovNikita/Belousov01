#include <stdio.h>

#define N 255

void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

int main() {
    int a, b;
    int arr[N][N];
    int char_arr[N] = {0};
    int ind[N] = {0};
    scanf("%d %d", &a, &b);
    for (int i = 0; i < a; i++)
        ind[i] = i;
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < a; j++) {
            scanf("%d", &arr[i][j]);
            if (arr[i][j] < 0 && arr[i][j] % 2 != 0)
                char_arr[j] += arr[i][j];
        }
    }
    int ans[N][N];
    for (int i = 0; i < a; i++) {
        int x = ind[i];
        for (int j = 0; j < b; j++) {
            ans[j][i] = arr[j][x];
        }
    }
    for (int t = 0; t < a; t++) {
        for (int i = 0; i < a - 1; i++) {
            if (char_arr[i + 1] < char_arr[i]) {
                swap(&char_arr[i], &char_arr[i + 1]);
                swap(&ind[i], &ind[i + 1]);
            }
        }
    }
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < a; j++) {
            printf("%d ", ans[i][ind[j]]);
        }
        printf("\n");
    }
    printf("%d %d", char_arr[0], char_arr[a - 1]);
    return 0;
}