#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct _human {
    int ost;
    char* name;
} Human;

typedef struct _Stack {
    Human* data;
    struct _Stack* next;
} Stack;

Stack* push2Stack(Stack* root, char* aname, int aost)
{
    if (root == NULL)
    {
        root = (Stack*) malloc(sizeof(Stack));
        root->data = NULL;
        root->data = (Human*) malloc(sizeof(Human));
        root->data->name = (char*) malloc(256 * sizeof(char));
        strcpy(root->data->name, aname);
        root->data->ost = aost;
        root->next = NULL;
        return root;
    }
    Stack* temp = root;
    root = NULL;
    root = push2Stack(root, aname, aost);
    root->next = temp;
    return root;
}

Human* popFromStack(Stack** root)
{
    if (*root == NULL) return NULL;
    Stack* temp = (*root)->next;
    Human* res = (*root)->data;
    (*root)->data = NULL;
    (*root)->next = NULL;
    free(*root);
    *root = temp;
    return res;
}

int main() {
    FILE *input, *output;
    int n, svoya = 0, konechnaya = 0;
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        return 1;
    }
    output = fopen("output.txt", "w");
    fscanf(input, "%d ", &n);
    int read_ost = -1;
    char* str = (char*) malloc(256 * sizeof(char));

    Stack* root = NULL;
    Human* first = NULL;
    for(int i = 0; i < n; i++) {
        while((first = popFromStack(&root))){
            if (first->ost <= i) {
                if (first->ost == i) svoya++;
                if (i == n - 1) konechnaya++;
                fprintf(output, "%s\n", first->name);
                free(first->name);
                free(first);
            }
            else
            {
                root = push2Stack(root, first->name, first->ost);
                free(first->name);
                break;
            }
        }
        int num;
        fscanf(input, "%d", &num);
        for(int j = 0; j < num; j++) {
            fscanf(input, "%s", str);
            fscanf(input, "%d", &read_ost);
            root = push2Stack(root, str, read_ost);
        }
    }
    fprintf(output, "%d %d", svoya, konechnaya);

    fclose(input);
    fclose(output);
    return 0;
}