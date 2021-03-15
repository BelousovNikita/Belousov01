#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define N 256

int main() {
    int d, beta, a = 1, sum = 0;
    char str[N] = {};
    scanf("%d", &beta);
    scanf("%s", str);
    d = strlen(str);
    if (str[0] == '-')
        a = -1;
    for (int i = d - 1; i >= 0; i--) {
        if ((beta < str[d - i - 1] - '0') && (isdigit(str[d - i - 1])) ||
            ((isalpha(str[d - i - 1]) && beta < str[d - i - 1] - '7')) || (str[d - i] == '-')) {
            printf("INCORRECT");
            return 0;
        }
        if (isdigit(str[i]))
            sum += ((str[i] - '0') * pow(beta, d - i - 1));
        else if (isalpha(str[i]))
            sum += ((str[i] - '7') * pow(beta, d - i - 1));
    }
    printf("%d", sum * a);
}
