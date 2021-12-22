#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS -1;
typedef struct StackRecord * Stack;
typedef int ElementType;

struct StackRecord{
    int Capacity;
    int TopOfStack;
    ElementType* Array;

};
void push(Stack s, FILE* fp_out,ElementType x);
void pop(Stack s, FILE* fp_out);



int main() {
    FILE* fp=fopen("input.txt","r");
    FILE * fp_out=fopen("output.txt","wt");

    Stack s;
    s=malloc(sizeof(struct StackRecord));
    if(s==NULL)
        fprintf(fp_out,"Out of space!!!\n");

    s->Array=malloc(sizeof(ElementType)*100);
    if(s->Array==NULL)
        fprintf(fp_out,"Out of space!!!\n");
    s->Capacity=100;
    s->TopOfStack=EmptyTOS;

    int count=fgetc(fp)-'0';


    for(int i=0;i<count;i++){
        char cmd[5];
        fscanf(fp,"%s",cmd);

        if(!strcmp(cmd,"push")){
          int x;
          fscanf(fp,"%d",&x);
          push(s,fp_out,x);

        }
        else if(!strcmp(cmd,"pop")){
          pop(s,fp_out);

        }

    }


    fclose(fp);
    fclose(fp_out);
    free(s->Array);
    free(s);

    return 0;
}



void push(Stack s,FILE* fp_out,ElementType x){
    if(s->Capacity==s->TopOfStack)
        fprintf(fp_out,"Full\n");
    else{
        s->Array[++(s->TopOfStack)]=x;
    }
}


void pop(Stack s, FILE* fp_out){
    if(s->TopOfStack==-1)
        fprintf(fp_out,"Empty\n");
    else{
        fprintf(fp_out,"%d\n",s->Array[s->TopOfStack]);
        (s->TopOfStack)--;
    }
}
