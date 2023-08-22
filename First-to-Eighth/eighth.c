//#include "stdio.h"
//#include "string.h"
//#include "locale.h"
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//    char str1[10];
//    char str2[10];
//    gets(str1);
//    gets(str2);
//
//    char conct[20];
//    strcpy(conct, str1);
//    strcat(conct, str2);
//    printf("Конкатенация: %s\n", conct);
//
//    int comp = strcmp(str1, str2);
//    printf("Сравнение: %s\n", (comp == 0) ? ("Строки равны") : ("Строки не равны"));
//    printf("Сравнение: %d\n", comp);
//
//    char symbol;
//    printf("Введите символ, первое вхождение которого нужно искать:");
//    scanf("%c", &symbol);
//    char *frstsmb1 = strchr(str1, symbol);
//    char *frstsmb2 = strchr(str2, symbol);
//    printf("Первое вхождение символа %c в строку 1 равно: %lld\n", symbol, (frstsmb1 == NULL) ? (-1) : (frstsmb1 - str1 + 1));
//    printf("Первое вхождение символа %c в строку 2 равно: %lld\n", symbol, (frstsmb2 == NULL) ? (-1) : (frstsmb2 - str2 + 1));
//
//    char *frstsmb3 = strpbrk(str1, str2);
//    printf("Первое вхождение любого символа строки 2 в строку 1 равно: %lld\n", (frstsmb3 == NULL) ? (-1) : (frstsmb3 - str1 + 1));
//
//    int ans = 0;
//    char *p = str1;
//    char *n = p + strlen(str1);
//    while (p < n) {
//        int cnt = strcspn(p, str2);
//        ans += cnt;
//        p += cnt + 1;
//    }
//    printf("Длина отрезка 1 строки, не содержащего символы строки 2: %d", ans);
//
//    return 0;
//}