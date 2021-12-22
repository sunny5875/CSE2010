#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode
{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Height(Position P){
    if(P==NULL)
        return -1;
    else
        return P->Height;

}


int Max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}


Position SingleRotateWithLeft( Position k2){
    Position k1;
    k1=k2->Left;
    k2->Left=k1->Right;
    k1->Right=k2;

    k2->Height=Max(Height(k2->Left),Height(k2->Right))+1;
    k1->Height=Max(Height(k1->Left),Height(k1->Right))+1;
    return k1;
}

Position SingleRotateWithRight( Position k2){
    Position k1;
    k1=k2->Right;
    k2->Right=k1->Left;
    k1->Left=k2;

    k2->Height=Max(Height(k2->Left),Height(k2->Right))+1;
    k1->Height=Max(Height(k1->Left),Height(k1->Right))+1;

    return k1;
}


static Position DoubleRotateWithLeft( Position k3){
    k3->Left=SingleRotateWithRight(k3->Left);
    return  SingleRotateWithLeft(k3);
}
static Position DoubleRotateWithRight( Position k3){
    k3->Right=SingleRotateWithLeft(k3->Right);
    return SingleRotateWithRight(k3);
}


AVLTree Insert( ElementType X, AVLTree T ,FILE* fp_out,int* check){
    //자리를 찾은 경우
    if(T==NULL){
        T= malloc(sizeof( struct AVLNode));
        if(T==NULL) {
            fprintf(fp_out, "Out of Space!!\n");
            return NULL;
        }
        else{
            T->Element=X;
            T->Height=0;
            T->Right=T->Left=NULL;
        }
    }
    else if(X<T->Element){
        T->Left=Insert(X,T->Left,fp_out,check);
        if(Height(T->Left)-Height(T->Right)==2) {
            if(X<T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
            T = DoubleRotateWithLeft(T);
        }
    }
    else if(X>T->Element){
        T->Right=Insert(X,T->Right,fp_out,check);
        if(Height(T->Right)-Height(T->Left)==2){
            if(X>T->Right->Element)
                T=SingleRotateWithRight(T);
            else
                T=DoubleRotateWithRight(T);
        }
    }
    else{
        fprintf(fp_out,"%d already in the tree!\n",X);
        *check=1;
    }
    T->Height=Max(Height(T->Left),Height(T->Right))+1;
    return T;
}



void show_avlT(AVLTree tree,FILE* fp_out){
    if(tree==NULL)
        return ;
    if(tree){
        show_avlT(tree->Left,fp_out);
        fprintf(fp_out,"%d(%d) ", tree->Element,tree->Height);
        show_avlT(tree->Right,fp_out);
    }

}

void FreeAvl_T(AVLTree tree){
    if(tree==NULL)
        return ;
    if(tree) {
        FreeAvl_T(tree->Left);
        FreeAvl_T(tree->Right);
        free(tree);
    }
}

int main() {
    FILE* fp=fopen("input.txt","r");
    FILE* fp_out=fopen("output.txt","wt");
    ElementType cmd=0;
    AVLTree avl_T=NULL;
    int check=0;
    int *check_ = &check;

    while(fscanf(fp,"%d",&cmd)!=EOF){
        avl_T=Insert(cmd,avl_T,fp_out,check_);
        if(*check_==0) {
            show_avlT(avl_T, fp_out);
            fprintf(fp_out, "\n");
        }
        else
            *check_=0;
    }

   FreeAvl_T(avl_T);
    fclose(fp);
    fclose(fp_out);
    return 0;
}
