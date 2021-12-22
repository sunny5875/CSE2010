#include <stdio.h>
#include <string.h>


typedef int element;

typedef struct{
    element array[100];
    int rear;
    int front;
}queue;

void enQ(queue* q, FILE* fp_out, element x);
void deQ(queue* q,FILE* fp_out);

int main() {
  queue* q;
  q->rear=-1;
  q->front=0;

    FILE* fp=fopen("input.txt","r");
    FILE * fp_out=fopen("output.txt","wt");

    int count=fgetc(fp)-'0';


    for(int i=0;i<count;i++){
        char cmd[5];
        fscanf(fp,"%s",cmd);

        if(!strcmp(cmd,"enQ")){
            element x;
            fscanf(fp,"%d",&x);
            enQ(q,fp_out,x);

        }
        else if(!strcmp(cmd,"deQ")){
           deQ(q,fp_out);

        }

    }

    fclose(fp);
    fclose(fp_out);

    return 0;
}

void enQ(queue* q, FILE* fp_out, element x){
    if(q->rear==99){
        fprintf(fp_out, "Full\n");
    }
    else{
        ++q->rear;
        q->array[q->rear] = x;
    }

}
void deQ( queue* q,FILE* fp_out){
    if(q->front>q->rear)
        fprintf(fp_out,"Empty\n");
    else {
        fprintf(fp_out, "%d\n", q->array[(q->front)++]);
    }

}

