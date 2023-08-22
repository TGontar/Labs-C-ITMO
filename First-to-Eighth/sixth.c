//#include "stdio.h"
//#include "stdlib.h"
//
//int main() {
//    int array[4];
//    int *arr = array;
//    for (int i = 0; i < 4; i++) {
//        arr[i] = 1000 + i;
//    }
//    int *p = arr;
//    for (int i = 0; i < 4; i++) {
//        printf("%d: %d \n", i, *p);
//        p++;
//    }
//
//    int *darr = calloc(4, sizeof(int));
//    for (int i = 0; i < 4; i++) {
//        darr[i] = 1000 + i;
//    }
//
//    printf("Dynamic array: \n");
//    for (int i = 0; i < 4; i++) {
//        printf("%d: %d \n", i, darr[i]);
//    }
//
//    free(darr);
//
//    return 0;
//}