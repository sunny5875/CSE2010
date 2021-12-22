#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//false 0 ,true 1
typedef struct threaded_tree * threaded_ptr;

struct threaded_tree{
    short int left_thread;
    threaded_ptr left_child;
    char data;
    threaded_ptr right_child;
    short int right_thread;
};


void InsertNode(threaded_ptr t, threaded_ptr temp, int a);
void insertRight(threaded_ptr parent, threaded_ptr insert);
void insertLeft(threaded_ptr parent, threaded_ptr insert);
void tinorder(threaded_ptr tree,FILE* fp_out);



int main() {
    FILE* fp=fopen("input.txt","r");
    FILE * fp_out=fopen("output.txt","wt");

    int cmd;
    fscanf(fp,"%d",&cmd);
    fgetc(fp);

    if(cmd>100)
    {
        printf("Maximum number of node is 100\n");
        return 1;
    }

    threaded_ptr t[cmd];
    threaded_ptr tree=malloc(sizeof(struct threaded_tree));
    tree->data=0;
    tree->left_thread=1;
    tree->right_thread=0;
    tree->left_child=tree;
    tree->right_child=tree;

//포인터 배열만들기
    for(int i=1;i<=cmd;i++){
        t[i]= malloc(sizeof(struct threaded_tree));
        t[i]->data=fgetc(fp);
        t[i]->right_child=NULL;
        t[i]->left_child=NULL;
        t[i]->right_thread=1;
        t[i]->left_thread=1;
        fgetc(fp);
    }

    //노드끼리의 연결
    for(int j=1;j<=cmd;j++){

        if(j==1){
            InsertNode(tree,t[j],-1);
        }
        //오른쪽에 들어가는 경우
        else if(j%2==1){
            InsertNode(t[(int)floor(j/2.0)], t[j], 1);
        }
            //왼쪽에 들어가는 경우
        else if(j%2==0){
           InsertNode(t[(int)floor(j/2.0)], t[j], 0);
        }
    }

    //inorder traversal로 출력
    tinorder(tree,fp_out);

    for(int i=1;i<=cmd;i++)
        free(t[i]);

    free(tree);
    fclose(fp);
    fclose(fp_out);
    return 0;
}


threaded_ptr insucc(threaded_ptr tree) {

    threaded_ptr temp;
    temp = tree->right_child;
    if (!tree->right_thread)
         while (!temp->left_thread)
            temp = temp->left_child;

    return temp;
}

void insertRight(threaded_ptr parent, threaded_ptr insert){
    threaded_ptr temp;
    insert->right_child=parent->right_child;
    insert->right_thread=parent->right_thread;
    insert->left_child= parent;
    insert->left_thread=1;
    parent->right_child=insert;
    parent->right_thread= 0;

    if(!insert->right_thread){
        temp=insucc(insert);
        temp->left_child=insert;
    }

}

void insertLeft(threaded_ptr parent, threaded_ptr insert) {
    threaded_ptr temp;
    insert->left_child= parent->left_child;
    insert->left_thread= parent->left_thread;
    insert->right_child=parent;
    insert->right_thread= 1;
    parent->left_child=insert;
    parent->left_thread=0;

    if(!insert->left_thread){
        temp=insucc(insert);
        temp->right_child=insert;
    }


}

//노드 연
void InsertNode(threaded_ptr tree, threaded_ptr temp,int a) {

        switch(a) {
        case -1:
            tree->left_thread=0;
                tree->left_child=temp;
                temp->left_child=tree;
                temp->left_thread=1;
                temp->right_child=tree;
                break;

            //왼쪽
            case 0:

                insertLeft(tree, temp);
                break;
                //오른쪽
            case 1:
                insertRight(tree, temp);
                break;

        }
}

//노드출력
void tinorder(threaded_ptr tree,FILE* fp_out){
    threaded_ptr temp=tree;
   for(;;){
        temp=insucc(temp);
        if(temp==tree) {
            break;
        }

        fprintf(fp_out,"%3c",temp->data);
    }

}

