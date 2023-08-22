#include "stdio.h"
#include "string.h"
#include "locale.h"
#include "math.h"

void split(int n, int arr[], int k, int it) {
    if (n == 0) {
        return;
    } else {
        int digit = n % 10;
        arr[k - it - 1] = digit;
        split(n / 10, arr, k, it + 1);
    }
}

void removeGaps(char *ps, const char *startstr, char result[], int count, int cnt1, int cnt2) {
    int flag = 0;
    if (*ps == '\0') {
        return;
    } else if (*ps == ' ') {
        if (*(ps - 1) == '\'' || *(ps - 1) == '\"' || *(ps - 1) == '(' || *(ps - 1) == '[' || *(ps - 1) == '{') {
            if (*(ps-1) == '\'') {
                if (cnt1 == 0) {
                    cnt1 = 1;
                    flag = 1;
                } else {
                    cnt1 = 0;
                }
            } else if (*(ps-1) == '\"') {
                if (cnt2 == 0) {
                    cnt2 = 1;
                    flag = 1;
                } else {
                    cnt2= 0;
                }
            } else {
                flag = 1;
            }
        } else if (*(ps - 1) == '.') {
            char *tmp = ps;
            while (*tmp == ' ') {
                tmp += 1;
            }
            if (*tmp == '\0') {
                flag = 1;
            }
        } else if (*(ps - 1) == ' ' && *(ps + 1) == ' ') {
            flag = 1;
        } else if (result[count-1] == '\'' || result[count-1] == '\"' || result[count-1] == '(' || result[count-1] == '[' || result[count-1] == '{') {
            flag = 1;
        }
    }
    if (flag == 0 || ps == startstr) {
        result[count] = *ps;
        count += 1;
    }
    removeGaps(ps + 1, startstr, result, count, cnt1, cnt2);
}


int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    printf("¬ведите число:");
    scanf("%d", &n);

    int k = 0;
    int tmp = n;
    while (tmp != 0) {
        tmp /= 10;
        k += 1;
    }

    int arr[k];

    split(n, arr, k, 0);

    for (int i = 0; i < k; i++) {
        printf("%d ", arr[i]);
    }


    char str[100];
    printf("\n¬ведите строку:");
    fflush(stdin);
    gets(str);

    char ans[100];
    for (int i = 0; i < 100; i++) {
        ans[i] = 0;
    }
    removeGaps(str, str, ans, 0, 0, 0);

    printf("%s", ans);

    return 0;
}