#include "stdio.h"

int main(int argc, char *argv[]) {
    char *filename1 = argv[1];
    char *filename2 = argv[2];
    char *filename3 = argv[3];
    FILE *f1, *f2, *f3;
    f1 = fopen(filename1, "r");
    f3 = fopen(filename3, "w");

    while (!feof(f1)) {
        char str[100];
        fscanf(f1, "%s", str);
        fprintf(f3, "%s\n", str);
    }
    fclose(f1);
    f2 = fopen(filename2, "r");
    while (!feof(f2)) {
        char str[100];
        fscanf(f2, "%s", str);
        fprintf(f3, "%s\n", str);
    }
    fclose(f2);


    return 0;
}
