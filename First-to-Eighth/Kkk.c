//#include <stdio.h>
//#include "string.h"
//#include "locale.h"
//
//int main() {
//        setlocale(LC_ALL, "Russian");
//
//    char str1[20];
//    char str2[20];
//    gets(str1);
//    gets(str2);
//    strcat(str1, str2);
//    printf("%s\n", str1);
//
//    char str3[20];
//    char str4[20];
//    printf("¬ведите 2 строки дл€ сравнени€ первых n символов: ");
//    gets(str3);
//    gets(str4);
//    printf("¬ведите n - количество символов дл€ сравнени€: ");
//    int n;
//    scanf("%d", &n);
//
//    if (strncmp(str3, str4, n) == 0){
//        printf("ѕервые %d символов одинаковы\n", n);
//    }
//    else {
//        printf("ѕервые %d символов различны\n", n);
//    }
//
//    char str5[20];
//    char str6[20];
//    printf("¬ведите первую строку дл€ копировани€ в неЄ второй строки: ");
//    gets(str5);
//    printf("\n¬ведите вторую строку: ");
//    gets(str6);
//    strcpy(str5, str6);
//    printf("%s", str5);
//    return 0;
//}