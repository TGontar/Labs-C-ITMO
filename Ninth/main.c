#include "stdio.h"
#include "string.h"
#include "locale.h"
#include "math.h"

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    printf("¬ведите число:");
    scanf("%d", &n);
    char chisl[10][10] = {"ноль", "один", "два", "три", "четыре", "п€ть", "шесть", "семь", "восемь", "дев€ть"};
    printf("%s", chisl[n]);

    double start;
    int months;
    double per;
    printf("\n¬ведите начальную сумму:");
    scanf("%lf", &start);
    printf("¬ведите количество мес€цев:");
    scanf("%d", &months);
    printf("¬ведите процент:");
    scanf("%lf", &per);

    per = 1.0 + ((per/12)/100.0);
    double itog = start;
    for (int i = 1; i <= months; i++) {

        itog *= per;
        printf("%.2lf\n", itog);
    }


    return 0;
}