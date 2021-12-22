#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS -1;

typedef struct StackRecord * Stack;
typedef char ElementType;

struct StackRecord{
    int Capacity;
    int TopOfStack;
    ElementType* Array;

};

void push(Stack s, FILE* fp_out,ElementType x);
ElementType pop(Stack s, FILE* fp_out);

void push_(Stack s_, FILE* fp_out,int x);
int pop_(Stack s_, FILE* fp_out);




int main() {
    FILE *fp = fopen("input.txt", "r");
    FILE *fp_out = fopen("output.txt", "wt");


    char temp[100];
    fscanf(fp,"%s",temp);
    char* infix=(char*)malloc(strlen(temp)+1);
    strcpy(infix,temp);
    strtok(infix,"#");
    fprintf(fp_out,"Infix Form : %s\n",infix);
    rewind(fp);


    Stack s;
    s = malloc(sizeof(struct StackRecord));
    if (s == NULL)
        fprintf(fp_out, "Out of space!!!\n");

    s->Array = malloc(sizeof(ElementType) * 100);

    if (s->Array == NULL)
        fprintf(fp_out, "Out of space!!!\n");

    s->Capacity = 100;
    s->TopOfStack = EmptyTOS;


    Stack s_;
    s_ = malloc(sizeof(struct StackRecord));
    if (s_ == NULL)
        fprintf(fp_out, "Out of space!!!\n");

    s_->Array = malloc(sizeof(int) * 100);

    if (s_->Array == NULL)
        fprintf(fp_out, "Out of space!!!\n");

    s_->Capacity = 100;
    s_->TopOfStack = EmptyTOS;


    fprintf(fp_out,"Postfix Form : ");
    char ch;
    ch=fgetc(fp);

    char p_temp[100];
    for(int j=0;j<100;j++)
        p_temp[j]= (char) NULL;
    int i=0;
    //infix->postix
    while (ch!= '#') {

        if ('0' <= ch && ch <= '9') {
        p_temp[i]=ch;
        i++;

        }

        else {
            if(s->TopOfStack==-1) {
                push(s, fp_out, ch);
            }

            else if (ch == ')') {
                while (s->Array[s->TopOfStack] != '(') {
                    p_temp[i]=pop(s, fp_out);
                    i++;
                }
                pop(s,fp_out);
            }

            else if (s->Array[s->TopOfStack] == '(') {
                push(s, fp_out, ch);
            }

            else if (s->Array[s->TopOfStack] == '+' || s->Array[s->TopOfStack] == '-') {
                if (ch == '+' || ch == '-') {
                    p_temp[i]=pop(s,fp_out);
                    i++;
                }
                push(s, fp_out, ch);
            }

            else if (s->Array[s->TopOfStack] == '*' || s->Array[s->TopOfStack] == '/' || s->Array[s->TopOfStack] == '%') {
                if(ch=='(')
                    push(s,fp_out,ch);
                else {
                    p_temp[i]=pop(s, fp_out);
                    i++;
                    push(s, fp_out, ch);
                }
            }

        }

        ch = fgetc(fp);

    }
    while(s->TopOfStack!=-1){
       p_temp[i]=pop(s,fp_out);
       i++;
    }


    char* postfix=(char*)malloc(strlen(p_temp)+1);
    strcpy(postfix,p_temp);
    fprintf(fp_out,"%s\n",postfix);

        //postix 계산
        for(int k=0;k<strlen(postfix);k++){

            ch=postfix[k];

            if ('0'<= ch && ch <= '9') {
               int ch_=ch-'0';
                push_(s_, fp_out, ch_);

            }
            else {
                int a = pop_(s_, fp_out);
                int b = pop_(s_, fp_out);
                int temp;

                switch (ch) {
                    case '+':
                        temp=b+a;
                        push_(s_, fp_out, temp);
                        break;
                    case '-':
                        temp=b-a;
                        push_(s_, fp_out, temp);
                        break;
                    case '*':
                        temp=b*a;
                        push_(s_, fp_out, temp);
                        break;
                    case '/':
                        temp=b/a;
                        push_(s_, fp_out, temp);
                        break;
                    case '%':
                        temp=b%a;
                        push_(s_, fp_out, temp);
                        break;

                }
            }
        }

        fprintf(fp_out,"Evaluation Result : %d\n",pop(s_,fp_out));


        fclose(fp);
        fclose(fp_out);
        free(s->Array);
        free(s);
        free(s_->Array);
        free(s_);
        free(infix);
        free(postfix);

        return 0;
    }



void push(Stack s,FILE* fp_out,ElementType x){
    if(s->Capacity==s->TopOfStack)
        fprintf(fp_out,"Full\n");
    else{
        s->Array[++(s->TopOfStack)]=x;
    }
}


ElementType pop(Stack s, FILE* fp_out){
    if(s->TopOfStack==-1) {
        fprintf(fp_out, "Empty\n");
        return (ElementType) NULL;
    }
    else{
        return s->Array[s->TopOfStack--];
    }
}



void push_(Stack s_,FILE* fp_out,int x){
    if(s_->Capacity==s_->TopOfStack)
        fprintf(fp_out,"Full\n");
    else{
        s_->Array[++(s_->TopOfStack)]=x;
    }
}


int pop_(Stack s_, FILE* fp_out){
    if(s_->TopOfStack==-1) {
        fprintf(fp_out, "");
        return (int)NULL;
    }
    else{
        return s_->Array[s_->TopOfStack--];
    }
}




