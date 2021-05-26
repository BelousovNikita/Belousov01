#include <stdio.h>
#include <malloc.h>

#define N 100

int inverse(int num) {
    return num == 1 ? 2 : 1;
}

int dfs(int v, int color[], int *(Adjacency_Matrix[]), int size) {
    for (int i = 0; i < size; i++) {
        if (Adjacency_Matrix[v][i]) {
            if (color[i] == 0) {
                color[i] = inverse(color[v]);
            }
            if (color[i] == color[v])
                return 0;
            if (!dfs(i, color, Adjacency_Matrix, size))
                return 0;
        }
    }
    return 1;
}

int main() {
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("File not found");
        return 1;
    }
//    int Adjacency_Ma/trix[N][N] = {0};
    int v, r;
    int Red = 0, Blue = 0;
    fscanf(input, "%d %d", &v, &r);
    int **Adjacency_Matrix = (int**) malloc(sizeof(int*)*v);
    for (int i=0; i<v; i++) {
        Adjacency_Matrix[i]=(int*) calloc (r,sizeof(int));
    }
    int *color = (int *) malloc(sizeof(int) * v);
    for (int i = 0; i < r; i++) {
        int from, to;
        fscanf(input, "%d %d", &from, &to);
        Adjacency_Matrix[from][to] = 1;
    }
    for (int i = 0; i < v; ++i)
        color[i] = 0; // 0 - не покрашена, 1 - красный, 2 - синий
    color[0] = 1;
    output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("File not found");
        return 1;
    }
    fprintf(output, "%d\n", dfs(0, color, Adjacency_Matrix, v));
    if (dfs(0, color, Adjacency_Matrix, v) == 1) {
        for (int i = 0; i < v; i++) {
            if (color[i] == 1)
                Red++;
            if (color[i] == 2)
                Blue++;
        }
        if (Red >= Blue)
            fprintf(output, "%d", v - Red);
        if (Blue > Red)
            fprintf(output, "%d", v - Blue);
    }
    free(color);
    fclose(input);
    fclose(output);
    return 0;
}


