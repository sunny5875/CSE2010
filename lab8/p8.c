#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};
typedef struct HeapStruct* PriorityQueue;


int Find(ElementType X, PriorityQueue H){
    int i=0;
    for(i=1;i<=H->Size;i++){
        if(H->Elements[i]==X) {
            return 1;
        }
    }
    if(i==H->Size+1)
        return 0;
}

void Insert(ElementType X, PriorityQueue H,FILE* fp_out) {
    int i;

    if (H->Size == H->Capacity) {
        fprintf(fp_out, "Heap is full\n");
        return;
    }
    if (Find(X, H) == 1) {
        fprintf(fp_out, "%d is already in the tree.\n", X);
        return;
    }

    for (i = ++H->Size; H->Elements[i / 2] < X; i /= 2)
        H->Elements[i] = H->Elements[i/2];

    H->Elements[i] = X;
    fprintf(fp_out, "Insert %d\n", H->Elements[i]);
}

void Print(PriorityQueue H, FILE* fp_out){
    int i=0;
    for(i=1;i<=H->Size;i++)
        fprintf(fp_out,"%d ",H->Elements[i]);
    fprintf(fp_out,"\n");
}


int main() {
    FILE * fp= fopen("input.txt","r");
    FILE* fp_out= fopen("output.txt","wt");
    int element, capacity;
    char cmd;
    fscanf(fp,"%d",&capacity);
    PriorityQueue heap=(PriorityQueue)malloc(sizeof(struct HeapStruct));

    heap->Capacity=capacity+1;
    heap->Size=0;
    heap->Elements=(ElementType*)malloc(sizeof(ElementType)*heap->Capacity);
    heap->Elements[0]=1000000;

    while(fscanf(fp,"%c",&cmd)!=EOF){

        if(cmd=='i'){
            fscanf(fp,"%d",&element);
            Insert(element,heap,fp_out);
        }
        else if (cmd=='f'){
            fscanf(fp,"%d",&element);
            if(Find(element,heap)==1)
                fprintf(fp_out, "%d is in the heap.\n", element);
            else
                fprintf(fp_out, "%d is not in the heap.\n", element);
        }
        else if(cmd=='p'){
           Print(heap,fp_out);
        }
    }







    return 0;
}
