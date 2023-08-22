#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"


#pragma pack(push, 1)

//union for header flags
union HeaderFlags {
    char space;
    struct {
        unsigned char nulls:4;
        unsigned char footer:1;
        unsigned char experiment:1;
        unsigned char extheader:1;
        unsigned char unsync:1;
    };
};

//struct to store 10 bytes of the metadata header
struct ID3Header {
    unsigned char name[3];
    unsigned char version[2];
    union HeaderFlags flags;
    unsigned char size[4];
};

//struct to store (6 + size) bytes of extended header
struct ExtendedHeader {
    unsigned char size[4];
    unsigned char flags;
    unsigned char extflags;
};


//struct of frame
struct Frame {
    unsigned char id[4];
    unsigned char size[4];
    unsigned char flags[2];
    unsigned char *data;
};

//struct of whole file
struct WholeMP3 {
    struct ID3Header *header;
    struct ExtendedHeader *extheader;
    struct Frame* frames[100];
    FILE *allrest;
};

// footer is the same as header
//struct Footer {
//    char name[3];
//    char version[2];
//    union HeaderFlags flags;
//    int size;
//};


//func to turn 4 chars into int
int safe_synch_int(unsigned char k[4], int padd) {
    int ans = 0;
    for (int i = 3; i >= 0; i--) {
        unsigned char bytec = k[i];
        int byte = bytec;
        ans += byte * pow(2, padd*(3-i));
    }
    return ans;
}

//func to turn int into 4 chars
void safe_synch_int_reverse(int k, unsigned char res[4], int padd) {
    for (int i = 0; i < 4; i++) {
        int sizech = pow(2, padd);
        unsigned char ch = k % sizech;
        k /= sizech;
        res[3-i] = ch;
    }
}

//compare tags func, instead of strcmp
int string_comp(unsigned char *a, unsigned char *b, int len) {
    int flag = 0;
    for (int i =0; i <len; i++) {
        if (a[i] != b[i]) {
            flag = 1;
        }
    }
    return flag;
}

//func to open mp3 file and put all into structure
struct WholeMP3 *process_mp3file(char *filepath) {
    FILE *f1;
    f1 = fopen(filepath, "r+b");
    if (f1 == NULL) {
        printf("Error while opening file\n");
        return NULL;
    }
    if (fgetc(f1) != 'I') {
        printf("Incorrect format of file\n");
        return NULL;
    } else {
        rewind(f1);
    }

    //work with header
    struct ID3Header *header1 = malloc(sizeof (struct ID3Header));
    fread(header1, 1, sizeof (struct ID3Header), f1);
    int size_all = safe_synch_int(header1->size, 7);
    int count = 0;

    //work with extended header
    struct ExtendedHeader *extheader1 = NULL;
    if (header1->flags.extheader != 0) {
        extheader1 = malloc(sizeof (struct ExtendedHeader));
        fread(extheader1, 1, sizeof (struct ExtendedHeader), f1);
        int extsize = safe_synch_int(extheader1->size, 7);
        count += sizeof (struct ExtendedHeader) + extsize;
        fseek(f1, extsize, SEEK_CUR);
    }

    //work with frames
    struct Frame* frames[100];
    int ind = 0;

    while (count < size_all) {
        struct Frame *frame = malloc(sizeof(struct Frame) - 8);
        fread(frame, 1, sizeof(struct Frame) - 8, f1);
        int framesize = safe_synch_int(frame->size, 8);
        if (framesize == 0) {
            break;
        }
        char *frdata = malloc(framesize * sizeof(char));
        fread(frdata, 1, framesize, f1);
        frame->data = frdata;
        count += sizeof (struct Frame ) - 8 + framesize;
        frames[ind] = frame;
        ind += 1;
    }
    if (ind < 100) {
        while (ind < 100) {
            frames[ind] = NULL;
            ind += 1;
        }
    }
    //the rest of the file
    FILE *curs = f1;

    //declaring the structure to work with
    struct WholeMP3 *allFile = malloc(sizeof (struct WholeMP3));
    allFile->header = header1;
    allFile->extheader = extheader1;
    for (int i = 0; i < 100; i++) {
        allFile->frames[i] = frames[i];
    }
    allFile->allrest = f1;

    fclose(f1);

    return allFile;
}


//fun to show all metadata
void show(struct WholeMP3 *mp3f) {
    struct ID3Header *h = mp3f->header;
    struct ExtendedHeader *eh = mp3f->extheader;
    struct Frame** frms = mp3f->frames;
    printf("Version: %c%c%c\n", h->name[0], h->name[1], h->name[2]);

    printf("Subversion: %d.%d\n", h->version[0], h->version[1]);

    printf("Flags:\n");
    printf("usync: %d\n", h->flags.unsync);
    printf("extheader: %d\n", h->flags.extheader);
    printf("experiment: %d\n", h->flags.experiment);
    printf("footer: %d\n", h->flags.footer);

    printf("Size of metainfo: %d\n", safe_synch_int(h->size, 7));

    if (eh != NULL) {
        printf("Size of extended header: %d\n", safe_synch_int(eh->size, 7));
        printf("Flags: %c\n", eh->flags);
        printf("Extended flags: %c\n", eh->extflags);
    }
    int it = 0;
    while (frms[it] != NULL && frms[it]->id[0] >= 65 && frms[it]->id[0] <= 90) {
        struct Frame *fr = frms[it];
        printf("%s: ", fr->id);
        int sizefr = safe_synch_int(fr->size, 8);
        int i = 0;
        if (fr->data[0] == '\001') {
            if (fr->id[0] == 'C') {
                i += 1;
            } else {
                i += 3;
            }
        }
        if (fr->id[0] == 'A') {
            printf("picture is attached");
        } else {
            while (i < sizefr) {
                printf("%c", fr->data[i]);
                i += 1;
            }
        }
        printf("\n");
        it += 1;
    }
}

//funс to get particular tag
void get(struct WholeMP3 *mp3f, unsigned char *tag) {
    struct Frame **frms = mp3f->frames;
    int it = 0;
    int flag = 0;
    while (frms[it] != NULL && frms[it]->id[0] >= 65 && frms[it]->id[0] <= 90) {
        unsigned char *tagid = frms[it]->id;
        if (string_comp(tagid, tag, 4) == 0) {
            flag = 1;
            break;
        }
        it += 1;
    }
    if (flag == 1) {
        printf("%s: ", tag);

        if (frms[it]->id[0] == 'A') {
            printf("Picture is attached)");
            return;
        }

        int len = safe_synch_int(frms[it]->size, 8);
        int i = 0;
        if (frms[it]->data[0] == '\001') {
            if (frms[it]->id[0] == 'C') {
                i += 1;
            } else {
                i += 3;
            }
        }
        for (i; i < len; i++) {
            printf("%c", frms[it]->data[i]);
        }
    } else {
        printf("The tag %s doesn't exist in this file", tag);
    }

}


//set func
void set(struct WholeMP3 *mp3f, char *filepath, unsigned char *tag, unsigned char *value) {
    //finding the tag needed to change
    struct Frame **frms = mp3f->frames;
    int it = 0;
    while (frms[it] != NULL && frms[it]->id[0] >= 65 && frms[it]->id[0] <= 90) {
        unsigned char *tagid = frms[it]->id;
        if (string_comp(tagid, tag, 4) == 0) {
            break;
        }
        it += 1;
    }
    if (frms[it] == NULL || frms[it]->id[0] < 65 || frms[it]->id[0] > 90) { //there's no tag with name "tag"
        //Work with structures

        //make new field in structure
        struct Frame *q = malloc(sizeof(struct Frame));
        strcpy(q->id, tag);
        unsigned char temparr[4] = {0, 0, 0, 0};
        safe_synch_int_reverse(strlen(value), temparr, 8);
        for (int i = 0; i < 4; i++) {
            q->size[i] = temparr[i];
        }
        q->flags[0] = 0;
        q->flags[1] = 0;
        q->data = value;
        frms[it] = q;
        mp3f->frames[it] = q;


        //change the header size
        int prevsize = safe_synch_int(mp3f->header->size, 7);
        prevsize += sizeof(*frms[it]) - 8 + safe_synch_int(frms[it]->size, 8);
        unsigned char buffer[4] = {0, 0, 0, 0};
        safe_synch_int_reverse(prevsize, buffer, 7);
        for (int i = 0; i < 4; i++) {
            mp3f->header->size[i] = buffer[i];
        }


        //Work with files
        //rewriting everyting in tmp file until last tag
        FILE *f = fopen(filepath, "r+b");
        unsigned char *tagisk = frms[it - 1]->id;
        FILE *ftemp;
        rewind(f);
        ftemp = fopen("tmp.txt", "w+b");

        //write the header first
        fwrite(mp3f->header, sizeof (*(mp3f->header)), 1, ftemp);
        fseek(f, sizeof(*(mp3f->header)), SEEK_CUR);

        //write between header and last tag
        while (1) {
            unsigned char ch1 = fgetc(f);
            unsigned char ch2 = fgetc(f);
            unsigned char ch3 = fgetc(f);
            unsigned char ch4 = fgetc(f);
            unsigned char tmp[4] = {ch1, ch2, ch3, ch4};
            unsigned char *temp = tmp;

            if (string_comp(temp, tagisk, 4) == 0) {
                fseek(f, -4, SEEK_CUR);
                break;
            } else {
                fputc(ch1, ftemp);
                fseek(f, -3, SEEK_CUR);
            }
        }
        //writing last tag and new tag in tmp file
        fwrite(frms[it - 1], sizeof(*frms[it - 1]) - 8, 1, ftemp);
        for (int i = 0; i < safe_synch_int(frms[it - 1]->size, 8); i++) {
            char ch = frms[it - 1]->data[i];
            fputc(ch, ftemp);
        }
        fwrite(frms[it], sizeof(*frms[it]) - 8, 1, ftemp);
        for (int i = 0; i < safe_synch_int(frms[it]->size, 8); i++) {
            char ch = frms[it]->data[i];
            fputc(ch, ftemp);
        }
        fseek(f, 10 + safe_synch_int(frms[it - 1]->size, 8) + 10 + safe_synch_int(frms[it]->size, 8), SEEK_CUR);

        //write all rest
        while (!feof(f)) {
            char ch = fgetc(f);
            fputc(ch, ftemp);
        }

        //rewrite  everyting into original file
        fclose(f);
        FILE *fnew = fopen(filepath, "wb");
        rewind(ftemp);
        while (!feof(ftemp)) {
            char ch = fgetc(ftemp);
            fputc(ch, fnew);
        }
        fclose(fnew);
        fclose(ftemp);

    } else { ////tag with the name "tag" already exists
        //Work with structure

        //change field in structure
        int prevsize = safe_synch_int(mp3f->frames[it]->size, 8);
        int newleng = strlen(value);
        unsigned char buffer[4] = {0, 0, 0, 0};
        safe_synch_int_reverse(newleng, buffer, 8);
        for (int i = 0; i < 4; i++) {
            mp3f->frames[it]->size[i] = buffer[i];
        }
        mp3f->frames[it]->data = value;

        //change the header size
        unsigned char newbuffer[4] = {0, 0, 0, 0};
        if (prevsize > newleng) {
            int res = safe_synch_int(mp3f->header->size, 7) - prevsize + newleng;
            safe_synch_int_reverse(res, newbuffer, 7);
        } else {
            int res = safe_synch_int(mp3f->header->size, 7) + newleng - prevsize;
            safe_synch_int_reverse(res, newbuffer, 7);
        }
        for (int i = 0; i < 4; i++) {
            mp3f->header->size[i] = newbuffer[i];
        }

        //Work with files
        //rewrite everything until needed tag in tmp file
        FILE *f = fopen(filepath, "r+b");
        unsigned char *tagisk = frms[it]->id;

        FILE *ftemp;
        rewind(f);
        ftemp = fopen("tmp.txt", "w+b");

        //write header first
        fwrite(mp3f->header, sizeof (*(mp3f->header)), 1, ftemp);
        fseek(f, sizeof (*(mp3f->header)), SEEK_CUR);

        //write between header and needed tag
        while (1) {
            unsigned char ch1 = fgetc(f);
            unsigned char ch2 = fgetc(f);
            unsigned char ch3 = fgetc(f);
            unsigned char ch4 = fgetc(f);
            unsigned char tmp[4] = {ch1, ch2, ch3, ch4};
            unsigned char *temp = tmp;

            if (string_comp(temp, tagisk, 4) == 0) {
                fseek(f, -4, SEEK_CUR);
                break;
            } else {
                fputc(ch1, ftemp);
                fseek(f, -3, SEEK_CUR);
            }
        }

        //write the tag itself in tmp file
        fwrite(frms[it], sizeof(*frms[it]) - 8, 1, ftemp);
        for (int i = 0; i < safe_synch_int(frms[it]->size, 8); i++) {
            char ch = frms[it]->data[i];
            fputc(ch, ftemp);
        }
        fseek(f,  sizeof(*frms[it]) - 8 + prevsize, SEEK_CUR);

        //write all rest
        while (!feof(f)) {
            char ch = fgetc(f);
            fputc(ch, ftemp);
        }

        //rewrite everything into original file
        fclose(f);
        FILE *fnew = fopen(filepath, "wb");
        fclose(ftemp);
        ftemp = fopen("tmp.txt", "r+b");
        rewind(ftemp);
        while (!feof(ftemp)) {
            char ch = fgetc(ftemp);
            fputc(ch, fnew);
        }
        fclose(fnew);
        fclose(ftemp);
    }

    //remove tmp file
//    FILE *torm = fopen("tmp.txt", "w");
//    fclose(torm);
//    remove("tmp.txt");
}



char *getargvalue(char *inp, char *arg, int arglen) {
    if (strlen(inp) > arglen) {
        char *chk = malloc(arglen *sizeof (char));
        for (int i = 0; i < arglen; i++) {
            chk[i] = inp[i];
        }
        if (memcmp(chk, arg, arglen) == 0) {
            char *ans = strchr(inp, '=') + 1;
            return ans;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

int check_ifargcorrect(char *inp, char *arg, int arglen) {
    if (strlen(inp) == arglen) {
        if (strcmp(inp, arg) == 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


int main(int argc, char *argv[]) {
    char *filepath = NULL;
    char *tag = NULL;
    char *value = NULL;
    int command = 0;
    if (argc == 1 || argc == 2) {
        printf("Put --filepath of file and operation to do");
        return 0;
    } else if (argc == 3 || argc == 4) {
        for (int i = 1; i < argc; i++) {
            if (strlen(argv[i]) > 3 && argv[i][2] == 'f') {
                if (filepath == NULL) {
                    filepath = getargvalue(argv[i], "--filepath=", 11);
                    if (filepath == NULL) {
                        printf("Incorrect data format");
                        return 0;
                    }
                } else {
                    printf("Incorrect data format");
                    return 0;
                }
            } else if (strlen(argv[i]) > 3 && argv[i][2] == 's' && argv[i][3] == 'h') {
                if (check_ifargcorrect(argv[i], "--show", 6) == 1) {
                    if (command != 0) {
                        printf("Incorrect data format");
                        return 0;
                    }
                    command = 1;
                }
            } else if (strlen(argv[i]) > 3 && argv[i][2] == 'g') {
                if (tag == NULL) {
                    tag = getargvalue(argv[i], "--get=", 6);
                    if (tag == NULL) {
                        printf("Incorrect data format");
                        return 0;
                    }
                    if (command != 0) {
                        printf("Incorrect data format");
                        return 0;
                    }
                    command = 2;
                } else {
                    printf("Incorrect data format");
                }
            } else if (strlen(argv[i]) > 3 && argv[i][2] == 's' && strlen(argv[i]) > 1 && argv[i][3] == 'e') {
                if (tag == NULL) {
                    tag = getargvalue(argv[i], "--set=", 6);
                    if (tag == NULL) {
                        printf("Incorrect data format");
                        return 0;
                    }
                    if (command != 0) {
                        printf("Incorrect data format");
                        return 0;
                    }
                    command = 3;
                } else {
                    printf("Incorrect data format");
                    return 0;
                }
            } else if (strlen(argv[i]) > 3 && argv[i][2] == 'v') {
                if (value == NULL) {
                    value = getargvalue(argv[i], "--value=", 8);
                    if (value == NULL) {
                        printf("Incorrect data format");
                        return 0;
                    }
                } else {
                    printf("Incorrect data format");
                    return 0;
                }
            }
        }
    } else {
        printf("Incorrect data format");
        return 0;
    }

    //do operations
    struct WholeMP3 *allFile = process_mp3file(filepath);
    if (allFile == NULL) {
        printf("Incorrect data format");
        return 0;
    }

    if (command == 0) {
        printf("Incorrect data format");
        return 0;
    } else if (command == 1) {
        show(allFile);
    } else if (command == 2) {
        if (tag == NULL) {
            printf("Incorrect data format");
            return 0;
        }
        get(allFile, tag);
    } else if (command == 3) {
        if (tag == NULL || value == NULL) {
            printf("Incorrect data format");
            return 0;
        }
        set(allFile, filepath, tag, value);
    }



    return 0;
}

#pragma pack(pop)