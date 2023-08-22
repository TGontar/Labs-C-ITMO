//#include "stdio.h"
//#include "locale.h"
//#include "stdlib.h"
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    int arr[8] = {77, 12, 74, 34, 56, 78, 234, 678};
//
//    for (int i = 0; i < 8; i++) {
//        printf("%d: %d \n", i, arr[i]);
//    }
//
//
//    int m1[2][2] = {{2, 1},
//                    {1, 3}};
//    int m2[2][2] = {{1, 2},
//                    {3, 1}};
//
//    int ans[2][2];
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            ans[i][j] = 0;
//            for (int k = 0; k < 2; k++) {
//                ans[i][j] += m1[i][k]*m2[k][j];
//            }
//        }
//    }
//
//    printf("Матрица 1 * Матрица 2 = \n");
//    for(int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            printf("| %d row %d col: %d |", i, j, ans[i][j]);
//        }
//        printf("\n");
//    }
//
//    return 0;
//}