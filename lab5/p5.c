#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode* treeptr;

typedef struct TreeNode{
    int value;
    treeptr left, right;
}TreeNode;

treeptr FindMax(treeptr tree);
treeptr InsertNode(int value, treeptr tree,FILE* fp_out);
treeptr DeleteNode(int value, treeptr tree,FILE* fp_out);
treeptr FindNode(int value, treeptr tree);
void PostFree(treeptr tree);
void PrintInorder(treeptr tree,FILE* fp_out);
void PrintPreorder(treeptr tree,FILE* fp_out);
void PrintPostorder(treeptr tree,FILE* fp_out);




int main() {
    FILE* fp=fopen("input.txt","r");
    FILE* fp_out= fopen("output.txt","wt");

    treeptr  tree=NULL;
    char cmd[100];
    int value;

    while(EOF!=fscanf(fp,"%s",cmd)){
        if(!strcmp(cmd,"i")){
            fscanf(fp,"%d",&value);
            if(FindNode(value,tree)==NULL)
                tree = InsertNode(value,tree,fp_out);
            else
                fprintf(fp_out,"%d already exists.\n",value);
        }

        else if(!strcmp(cmd,"d")){
            fscanf(fp,"%d",&value);
            if(FindNode(value,tree)!=NULL)
                tree = DeleteNode(value,tree,fp_out);
            else
                fprintf(fp_out,"Deletion failed. %d does not exist.\n",value);
        }

        else if(!strcmp(cmd,"f")){
            fscanf(fp,"%d",&value);
            if (FindNode(value,tree)==NULL)
                fprintf(fp_out,"%d is not in the tree.\n",value);
            else
                fprintf(fp_out,"%d is in the tree.\n",value);
        }

        else if(!strcmp(cmd,"pi")){
            fprintf(fp_out,"pi - ");
            PrintInorder(tree,fp_out);
            fprintf(fp_out,"\n");
        }
        else if(!strcmp(cmd,"pr")){
            fprintf(fp_out,"pr - ");
            PrintPreorder(tree,fp_out);
            fprintf(fp_out,"\n");
        }
        else if(!strcmp(cmd,"po")){
            fprintf(fp_out,"po - ");
            PrintPostorder(tree,fp_out);
            fprintf(fp_out,"\n");
        }
    }
    PostFree(tree);
    return 0;
}


treeptr FindNode(int value, treeptr tree){
    //없는 경우
    if(tree==NULL) {
        return NULL;
    }
        //작은 경우
    else if(value<tree->value)
        return FindNode(value, tree->left);
        //큰 경우
    else if (value>tree->value)
        return FindNode(value, tree->right);
        //찾은 경우
    else {
        return tree;
    }
}

treeptr InsertNode(int value, treeptr tree,FILE* fp_out){
    /*insert시 동일한 값이 나올 경우 에러메시지 출력해야 한다*/
    //leaf에 도달한 경우
    if (tree == NULL) {
        tree = (treeptr)malloc(sizeof(struct TreeNode));
        if(tree==NULL)
            fprintf(fp_out,"Out of space!!\n");
        //노드에 값 할당
        tree->value = value;
        tree->left = tree->right = NULL;
    }
        //값이 해당된 트리의 값보다 작은 경으
    else if (value < tree->value)
        tree->left = InsertNode(value, tree->left,fp_out);
        //값이 해당된 트리의 값보다 큰 경우
    else if (value > tree->value)
        tree->right = InsertNode(value, tree->right,fp_out);


    return tree;
}



treeptr  FindMax(treeptr t){
    //에러 메세지
    if(t==NULL)
        return NULL;
    else {
        while (t->right != NULL)
            t = t->right;
    }
    return t;
}

treeptr DeleteNode(int value, treeptr tree,FILE * fp_out){
    treeptr tmpcell;
    if(tree==NULL) {
        fprintf(fp_out, "Element not found\n");
        return tree;
    }
        //지워야하는게 인쪽에 있는 경
    if (value < tree->value)
        tree->left = DeleteNode(value, tree->left,fp_out);
        //지워야하는게 오른쪽에 있는 경우
    else if (value > tree->value)
        tree->right = DeleteNode(value, tree->right,fp_out);
        //two child인 경우
    else if (tree->left && tree->right) {
        tmpcell = FindMax(tree->left);
        tree->value = tmpcell->value;
        tree->left = DeleteNode(tree->value, tree->left,fp_out);
    }
        //1 or 0 child인 경
    else {
        tmpcell = tree;
        if (tree->left == NULL)
            tree = tree->right;
        else if (tree->right == NULL)
            tree = tree->left;
        free(tmpcell);
    }
    return tree;
}

void PrintInorder(treeptr tree,FILE* fp_out){
    if(tree==NULL)
        return ;
    if(tree){
        PrintInorder(tree->left,fp_out);
        fprintf(fp_out,"%d ", tree->value);
        PrintInorder(tree->right,fp_out);
    }
}
void PrintPreorder(treeptr tree,FILE* fp_out){
    if(tree==NULL)
        return ;
    if(tree) {
        fprintf(fp_out, "%d ", tree->value);
        PrintPreorder(tree->left, fp_out);
        PrintPreorder(tree->right, fp_out);
    }
}
void PrintPostorder(treeptr tree,FILE*fp_out){
    if(tree==NULL)
        return ;
    if(tree) {
        PrintPostorder(tree->left, fp_out);
        PrintPostorder(tree->right, fp_out);
        fprintf(fp_out, "%d ", tree->value);
    }
}


void PostFree(treeptr tree){
    if(tree==NULL)
        return ;
    if(tree) {
        PostFree(tree->left);
        PostFree(tree->right);
        free(tree);
    }
}