#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define N 256

int main() {
    int d, beta, a = 1, sum = 0, b;
    char str[N] = {};
    scanf("%d", &beta);
    scanf("%s", str);
    d = strlen(str);
    if (str[0] == '-')
        a = -1;
    for (int i = d - 1; i >= 0; i--) {
        b = pow(beta, d - i - 1);
        if ((beta < str[d - i - 1] - '0') && (isdigit(str[d - i - 1])) ||
            ((isalpha(str[d - i - 1]) && beta < str[d - i - 1] - 'A' + 10)) || (str[d - i] == '-')) {
            printf("INCORRECT");
            return 0;
        }
        if (isdigit(str[i]))
            sum += ((str[i] - '0') * b);
        else if (isalpha(str[i]))
            sum += ((str[i] - 'A' + 10) * b);
    }
    printf("%d", sum * a);
    return 0;
}