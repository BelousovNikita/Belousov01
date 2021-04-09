#include <stdio.h>
#define K 64
#define N 100

int det(int n, int arr[][K]) {
    if (n == 1)
        return arr[0][0];
    if (n == 2)
        return arr[0][0] * arr[1][1] - arr [0][1] * arr [1][0];
    else {
        int deter = 0;
        for (int i = 0; i < n; i++) {
            int minor[64][64] = {0};
            int j_m = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    for (int k = 1; k < n; k++) {
                        minor [k-1][j_m] = arr[k][j];
                    }
                    j_m++;
                }
            }
            deter+= (i % 2 == 0 ? 1 : -1) * arr[0][i] * det(n-1, minor);
        }
        return deter;
    }
}

int main() {
    int r, k, deter;
    scanf("%d", &r);
    int arr_det[N] = {0};
    for (int l = 0; l < r; l++) {
        scanf("%d", &k);
        int arr[K][K];
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                scanf("%d", &arr[i][j]);
            }
        }
        deter = det(k, arr);
        arr_det[l] = deter;
    }
    for (int i = 0; i < r; i++) {
        printf ("%d", arr_det[i]);
        printf("\n");
    }
}
