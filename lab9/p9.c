#include <stdio.h>
#include <stdlib.h>
#define order 3

typedef struct B_node* Btree;
struct B_node{
    int n_keys;
    struct B_node *child[order];
    int key[order-1];
};

Btree btree=NULL;
FILE* fp_out;

int searchPos(int key, int* arr, int n) {
    int pos=0;
    while(pos<n && key>arr[pos])
        pos++;
    return pos;
}

int ins(struct B_node* ptr, int key,int* upKey,struct B_node** newnode){
    int newKey,lastKey,splitPos;
    struct B_node* newPtr;
    struct B_node *lastPtr;
    int n,pos,value,i;

    if(ptr==NULL){
        *newnode=NULL;
        *upKey=key;
        return 1;
    }

    n=ptr->n_keys;
    pos=searchPos(key,ptr->key,n);

    if(pos<n && key==ptr->key[pos])
        return 0;

    value = ins(ptr->child[pos], key, &newKey, &newPtr);

   if(value !=1)
        return value;

//node split하지 않는 경우
    if(n<order-1){
        pos= searchPos(newKey,ptr->key,n);

        for(i =n;i>pos;i--){
            ptr->key[i]=ptr->key[i-1];
            ptr->child[i+1]=ptr->child[i];
        }
        ptr->key[pos]=newKey;
        ptr->child[pos+1]=newPtr;
        ++(ptr->n_keys);
        return 3;
    }

    if(pos==order-1){
        lastKey=newKey;
        lastPtr=newPtr;
    }

    
    else{
       lastKey=ptr->key[order-2];
       lastPtr=ptr->child[order-1];

       for(i=order-2;i>pos;i--){
           ptr->key[i]=ptr->key[i-1];
           ptr->child[i+1]=ptr->child[i];
       }
       ptr->key[pos]=newKey;
       ptr->child[pos+1]=newPtr;
    }

    splitPos=(order-1)/2;
    (*upKey)=ptr->key[splitPos];
    (*newnode)=(struct B_node*)malloc(sizeof(struct B_node));
    ptr->n_keys=splitPos;
    (*newnode)->n_keys= order-1-splitPos;

    for(i=0;i<(*newnode)->n_keys;i++){
        (*newnode)->child[i]=ptr->child[i+splitPos+1];
        if(i<(*newnode)->n_keys-1)
            (*newnode)->key[i]=ptr->key[i+splitPos+1];
        else
            (*newnode)->key[i]=lastKey;
    }
    
    (*newnode)->child[(*newnode)->n_keys]=lastPtr;

    return 1;
}



void insert(int key){
   struct B_node* newnode;
   int upKey;
   int status;

   status =ins(btree,key,&upKey,&newnode);

   if(status == 0)
       fprintf(fp_out,"Key %d already available\n",key);


  else if(status== 1){
       struct B_node* uproot=btree;
       btree=(struct B_node*)malloc(sizeof(struct B_node));
       btree->n_keys=1;
       btree->key[0]=upKey;
       btree->child[0]=uproot;
       btree->child[1]=newnode;
   }


}
void inorder(struct B_node *ptr) {
    if (ptr) {
        if (ptr->n_keys >= 1) {
            inorder(ptr->child[0]);
            fprintf(fp_out,"%d ", ptr->key[0]);
            inorder(ptr->child[1]);
            if (ptr->n_keys == 2) {
                fprintf(fp_out,"%d ", ptr->key[1]);
                inorder(ptr->child[2]);
            }
        }
    }
}


int main() {
    FILE* fp=fopen("input.txt","r");
    fp_out=fopen("output.txt","wt");
    char cmd;
    int value;

    while(fscanf(fp,"%c",&cmd)!=EOF){
        if(cmd=='i'){
            fscanf(fp,"%d",&value);
            insert(value);

        }
        else if(cmd=='p'){
            inorder(btree);
            fprintf(fp_out,"\n");
        }

    }



    return 0;
}
