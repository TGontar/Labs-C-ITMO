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
//    printf("������������: %s\n", conct);
//
//    int comp = strcmp(str1, str2);
//    printf("���������: %s\n", (comp == 0) ? ("������ �����") : ("������ �� �����"));
//    printf("���������: %d\n", comp);
//
//    char symbol;
//    printf("������� ������, ������ ��������� �������� ����� ������:");
//    scanf("%c", &symbol);
//    char *frstsmb1 = strchr(str1, symbol);
//    char *frstsmb2 = strchr(str2, symbol);
//    printf("������ ��������� ������� %c � ������ 1 �����: %lld\n", symbol, (frstsmb1 == NULL) ? (-1) : (frstsmb1 - str1 + 1));
//    printf("������ ��������� ������� %c � ������ 2 �����: %lld\n", symbol, (frstsmb2 == NULL) ? (-1) : (frstsmb2 - str2 + 1));
//
//    char *frstsmb3 = strpbrk(str1, str2);
//    printf("������ ��������� ������ ������� ������ 2 � ������ 1 �����: %lld\n", (frstsmb3 == NULL) ? (-1) : (frstsmb3 - str1 + 1));
//
//    int ans = 0;
//    char *p = str1;
//    char *n = p + strlen(str1);
//    while (p < n) {
//        int cnt = strcspn(p, str2);
//        ans += cnt;
//        p += cnt + 1;
//    }
//    printf("����� ������� 1 ������, �� ����������� ������� ������ 2: %d", ans);
//
//    return 0;
//}