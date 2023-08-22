//#include "stdio.h"
//#include "string.h"
//#include "locale.h"
//#include "math.h"
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    int n;
//    printf("¬ведите число:");
//    scanf("%d", &n);
//    char a[100];
//    int it = 0;
//    while (n != 0) {
//        int digit = n % 10;
//        char letter = '0' + digit;
//        a[it] = letter;
//        n /= 10;
//        it += 1;
//    }
//    for (int i = it-1; i >= 0; i--) {
//        printf("%c", a[i]);
//    }
//
//    double start;
//    int months;
//    double per;
//    printf("\n¬ведите начальную сумму:");
//    scanf("%lf", &start);
//    printf("¬ведите количество мес€цев:");
//    scanf("%d", &months);
//    printf("¬ведите процент:");
//    scanf("%lf", &per);
//
//    per = 1.0 + (per/100.0);
//    double itog = start;
//    for (int i = 1; i <= months; i++) {
//        itog *= per;
//    }
//    printf("%lf", itog);
//
//    return 0;
//}