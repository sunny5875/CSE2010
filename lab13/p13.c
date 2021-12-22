#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct ListNode {
    int Element;
};

typedef struct HashTbl {
    int TableSize;
    struct ListNode *theLists;
} HashTbl;

typedef HashTbl *HashTable;
HashTable h;


int Hash(int value, int Size, int i, int solution) {
    int a;
    switch (solution) {
        case 1:
            while ((h->theLists[(value) % Size + i]).Element != value && (h->theLists[(value) % Size + i]).Element != 0) {
                i++;
            }
            a= (value) % Size + i;
            break;
        case 2:
           while (h->theLists[(value) % Size + i * i].Element != 0&&h->theLists[(value) % Size + i * i].Element != value)
                i++;
            a=(value) % Size + i * i;
            break;
        case 3:
            while (h->theLists[((value) % Size + i * (7 - value % 7)) % Size].Element != 0&&h->theLists[((value) % Size + i * (7 - value % 7)) % Size].Element != value) {
                i++;
            }
            a=((value) % Size + i * (7 - value % 7)) % Size;
            break;
    }

    return a;
}

void Insert(HashTable H, int value, int solution) {
    int tmp;
    tmp= Hash(value, H->TableSize, 0, solution);
    (H->theLists[tmp]).Element = value;
}

void delete(HashTable H, int value, int solution) {
    int tmp = Hash(value, H->TableSize, 0, solution);
    H->theLists[tmp].Element = 0;
}

int find(HashTable H, int value, int solution) {
    int tmp = Hash(value, H->TableSize, 0, solution);
    if (h->theLists[tmp].Element==value)
        return 1;
    else
        return 0;

}

void print(HashTable H, FILE *fp_out) {
    for (int a = 0; a < H->TableSize; a++) {
        fprintf(fp_out, "%d ", H->theLists[a].Element);
    }
}

int main() {
    char cmd = 'A';
    int element = 0;
    int testcount;
    char type[10];
    int hashsize;
    int solution = 0;

    FILE *fp = fopen("input.txt", "r");
    FILE *fp_out = fopen("output.txt", "wt");


    fscanf(fp, "%d", &testcount);


    while (testcount > 0) {
        fscanf(fp, "%s", type);
        if (strcmp(type, "Linear") == 0) {
            fprintf(fp_out, "Linear\n");
            solution = 1;
        } else if (strcmp(type, "Quadratic") == 0) {
            fprintf(fp_out, "Quadratic\n");
            solution = 2;
        } else if (strcmp(type, "Double") == 0) {
            fprintf(fp_out, "Double\n");
            solution = 3;
        }


        fscanf(fp, "%d %c ", &hashsize, &cmd);
        h = (HashTable) malloc(sizeof(struct HashTbl));
        h->TableSize = hashsize;
        h->theLists = (struct ListNode *) malloc(sizeof(struct ListNode) * (h->TableSize));
        for (int i = 0; i < h->TableSize; i++)
            h->theLists[i].Element = 0;


        while (1) {
            if (cmd == 'i') {
                fscanf(fp, "%d", &element);
                if (find(h, element, solution) == 1)
                    fprintf(fp_out, "Already exists\n");
                else {
                    Insert(h, element, solution);
                    fprintf(fp_out, "Inserted %d\n", element);
                }


            } else if (cmd == 'd') {
                fscanf(fp, "%d", &element);
                if (find(h, element, solution) == 1) {
                    delete(h, element, solution);
                    fprintf(fp_out, "Deleted %d\n", element);
                } else
                    fprintf(fp_out, "%d not exists\n", element);

            } else if (cmd == 'f') {
                fscanf(fp, "%d", &element);
                if (find(h, element, solution) == 1)
                    fprintf(fp_out, "%d is exist.\n", element);
                else
                    fprintf(fp_out, "Not found\n");

            } else if (cmd == 'p') {
                print(h, fp_out);
                fprintf(fp_out, "\n");

            } else if (cmd == 'q') {
                testcount--;
                fprintf(fp_out, "\n");
                break;
            }
            fgetc(fp);
            fgetc(fp);
            fscanf(fp, "%c", &cmd);

        }

    }
    return 0;
}
