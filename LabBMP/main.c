#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#pragma pack(push, 1)

//struct for file header
struct BitMapFileHeader {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offsetbits;
};

//struct for info header
struct BitMapInfoHeader {
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitcount;
    unsigned int compression;
    unsigned int sizeimage;
    unsigned int xpmeter;
    unsigned int ypmeter;
    unsigned int colorsused;
    unsigned int colors;

};

//struct of all BMP file
struct AllFile {
    struct BitMapFileHeader *fileheader;
    struct BitMapInfoHeader *infoheader;
    unsigned int *palette;
    unsigned char **Pixels;
};

//func to open file and write it into structure
struct AllFile *openfile(char *filepath) {
    //open file
    FILE *f1;
    f1 = fopen(filepath, "r+b");
    if (f1 == NULL) {
        printf("Error while opening file");
        exit(1);
    } else if (fgetc(f1) != 'B') {
        printf("Incorrect file format");
        exit(1);
    } else {
        rewind(f1);
    }

    //declare objects to work with
    struct BitMapFileHeader *fileHeader = malloc(sizeof(struct BitMapFileHeader));
    struct BitMapInfoHeader *infoHeader = malloc(sizeof(struct BitMapInfoHeader));
    unsigned int *palette = NULL;
    unsigned char **Pixels = NULL;

    //read headers from file
    fread(fileHeader, sizeof(struct BitMapFileHeader), 1, f1);
    fread(infoHeader, sizeof(struct BitMapInfoHeader), 1, f1);

    //read palette from file
    palette = calloc(infoHeader->colors, sizeof(unsigned int));
    fread(palette, sizeof(unsigned int) * 2, 1, f1);

    //read pixels from file
    unsigned int fwidth = infoHeader->width;
    unsigned int fheight = infoHeader->height;
    Pixels = calloc(fheight, sizeof(unsigned char *));
    for (int i = 0; i < fheight; i++) {
        Pixels[i] = calloc(fwidth, sizeof(unsigned char));
    }

    int padd = 4 - fwidth % 4;
    for (int i = 0; i < fheight; i++) {
        fread(Pixels[i], sizeof(unsigned char) * fwidth, 1, f1);
        fseek(f1, padd, SEEK_CUR);
    }

    //make all file
    struct AllFile *bmpf = malloc(sizeof(struct AllFile));
    bmpf->fileheader = fileHeader;
    bmpf->infoheader = infoHeader;
    bmpf->palette = palette;
    bmpf->Pixels = Pixels;

    fclose(f1);
    return bmpf;
}

//func to set alive or dead value into new array
void setval(unsigned char **origin, unsigned char **dist, int i, int j, int cnt) {
    if (origin[i][j] == 0) {
        if (cnt == 3) {
            dist[i][j] = 1;
        } else {
            dist[i][j] = 0;
        }
    } else {
        if (cnt == 2 || cnt == 3) {
            dist[i][j] = 1;
        } else {
            dist[i][j] = 0;
        }
    }
}

//file to make life cycle
void gamelife(struct AllFile *bmpf, char *filepath) {

    //check if it's possible to play life
    if (bmpf->infoheader->bitcount != 8 || bmpf->fileheader->offsetbits - 54 > 8) {
        printf("Unable to play the game of life - incorrect color encoding");
        exit(1);
    }

    //make new array for generation
    unsigned char **pxl = bmpf->Pixels;
    unsigned int w = bmpf->infoheader->width;
    unsigned int h = bmpf->infoheader->height;
    unsigned char **newpixels = calloc(h, sizeof(unsigned char *));
    for (int i = 0; i < h; i++) {
        newpixels[i] = calloc(w, sizeof(unsigned char));
    }

    //do the life
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (j == 0) {
                if (i == 0) {
                    int cnt = pxl[i + 1][j] + pxl[i][j + 1] + pxl[i + 1][j + 1];
                    setval(pxl, newpixels, i, j, cnt);
                } else if (i == h - 1) {
                    int cnt = pxl[i - 1][j] + pxl[i][j + 1] + pxl[i - 1][j + 1];
                    setval(pxl, newpixels, i, j, cnt);
                } else {
                    int cnt = pxl[i + 1][j] + pxl[i + 1][j + 1] + pxl[i][j + 1] + pxl[i - 1][j + 1] + pxl[i - 1][j];
                    setval(pxl, newpixels, i, j, cnt);
                }
            } else if (j == w - 1) {
                if (i == 0) {
                    int cnt = pxl[i + 1][j] + pxl[i][j - 1] + pxl[i + 1][j - 1];
                    setval(pxl, newpixels, i, j, cnt);
                } else if (i == h - 1) {
                    int cnt = pxl[i - 1][j] + pxl[i][j - 1] + pxl[i - 1][j - 1];
                    setval(pxl, newpixels, i, j, cnt);
                } else {
                    int cnt = pxl[i + 1][j] + pxl[i + 1][j - 1] + pxl[i][j - 1] + pxl[i - 1][j - 1] + pxl[i - 1][j];
                    setval(pxl, newpixels, i, j, cnt);
                }
            } else {
                if (i == 0) {
                    int cnt = pxl[i][j - 1] + pxl[i + 1][j - 1] + pxl[i + 1][j] + pxl[i + 1][j + 1] + pxl[i][j + 1];
                    setval(pxl, newpixels, i, j, cnt);
                } else if (i == h - 1) {
                    int cnt = pxl[i][j - 1] + pxl[i - 1][j - 1] + pxl[i - 1][j] + pxl[i - 1][j + 1] + pxl[i][j + 1];
                    setval(pxl, newpixels, i, j, cnt);
                } else {
                    int cnt =
                            pxl[i - 1][j - 1] + pxl[i][j - 1] + pxl[i + 1][j - 1] + pxl[i + 1][j] + pxl[i + 1][j + 1] +
                            pxl[i][j + 1] + pxl[i - 1][j + 1] + pxl[i - 1][j];
                    setval(pxl, newpixels, i, j, cnt);
                }
            }
        }
    }

    //update field in structure
    bmpf->Pixels = newpixels;
////    debug prints
//    for (int i = h - 1; i >= 0; i--) {
//        for (int j = 0; j < w; j++) {
//            printf("%d ", pxl[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\n");
//
//    for (int i = h - 1; i >= 0; i--) {
//        for (int j = 0; j < w; j++) {
//            printf("%d ", newpixels[i][j]);
//        }
//        printf("\n");
//    }

    //rewrite into original file
    FILE *f1;
    f1 = fopen(filepath, "wb");

    //write headers and palette first
    fwrite(bmpf->fileheader, sizeof(struct BitMapFileHeader), 1, f1);
    fwrite(bmpf->infoheader, sizeof(struct BitMapInfoHeader), 1, f1);
    fwrite(bmpf->palette, sizeof(unsigned int) * 2, 1, f1);

    //write pixels
    int padd = 4 - w % 4;

    for (int i = 0; i < h; i++) {
        fwrite(newpixels[i], w, 1, f1);
        fwrite("0", sizeof(unsigned char), padd, f1);
    }

    fclose(f1);

}

//func to copy one file to another
void copy_file(char *from, char *to) {
    FILE *f1;
    FILE *f2;
    f1 = fopen(from, "r+b");
    f2 = fopen(to, "w+b");
    if (f1 == NULL || f2 == NULL) {
        printf("Error with opening files");
        exit(1);
    }
    while (!feof(f1)) {
        unsigned char ch = fgetc(f1);
        fputc(ch, f2);
    }
    fclose(f1);
    fclose(f2);
}

char *int_to_char(int k) {
    char *ans = malloc(10);
    sprintf(ans, "%d", k);
    return ans;
}

int main(int argc, char *argv[]) {
    char *input = NULL;
    char *output = NULL;
    int max_iter = 228;
    int dump_freq = 1;

    if (argc < 3) {
        printf("Use --input and --output to specify file paths");
        return 1;
    } else if (argc < 10) {
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "--input") == 0) {
                if (i < argc - 1) {
                    input = argv[i + 1];
                } else {
                    printf("Incorrect data format");
                    return 1;
                }
            } else if (strcmp(argv[i], "--output") == 0) {
                if (i < argc - 1) {
                    output = argv[i + 1];
                } else {
                    printf("Incorrect data format");
                    return 1;
                }
            } else if (strcmp(argv[i], "--max_iter") == 0) {
                if (i < argc - 1) {
                    max_iter = atoi(argv[i + 1]);
                } else {
                    printf("Incorrect data format");
                    return 1;
                }
            } else if (strcmp(argv[i], "--dump_freq") == 0) {
                if (i < argc - 1) {
                    dump_freq = atoi(argv[i + 1]);
                } else {
                    printf("Incorrect data format");
                    return 1;
                }
            }
        }
    } else {
        printf("Too much args");
        return 1;
    }

    //check if the args are correct
    if (input == NULL || output == NULL) {
        printf("Incorrect data format");
        return 1;
    }

    //check if we can open the file
    struct AllFile *allfile = openfile(input);
    if (allfile == NULL) {
        printf("Incorrect data format");
        return 1;
    }

    //do the generations
//    strcat(output, "tmp.bmp");
    int cnt = 0;
    for (int i = 0; i < max_iter; i++) {
        cnt += 1;
        gamelife(allfile, input);
        if (cnt == dump_freq) {
            char *aaa = int_to_char(i);
            char *aaaaa = malloc(strlen(output));
            strcpy(aaaaa, output);
            strcat(aaaaa, aaa);
            strcat(aaaaa, ".bmp");
            copy_file(input, aaaaa);
            cnt = 0;
        }
    }


    return 0;
}

#pragma pack(pop)
