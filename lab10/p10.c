#include <stdio.h>
#include <stdlib.h>


struct _Graph{
    int size;
    int* node;
    int** matrix;
};
struct _Queue{
    int* key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

typedef struct _Graph* Graph;
typedef struct _Queue* Queue;
Graph graph;

FILE* fp_out;

Graph CreateGraph(int* nodes){
    int i=0;
    int j=0;
    graph->matrix=malloc(sizeof(int*)*(graph->size+1));
    for(i=0;i<graph->size+1;i++){
        graph->matrix[i]=malloc(sizeof(int)*(graph->size+1));
    }
    return graph;
}
void InsertEdge(Graph G, int a, int b){
    int i=0;
    int in,out;
    for(i=0;i<G->size;i++){

        if(G->node[i]==a){
            in=i;
        }
        if(G->node[i]==b){
            out=i;
        }
    }
    G->matrix[in][out]=1;

}

Queue MakeNewQueue(int X){
    Queue queue=(Queue)malloc(sizeof(struct _Queue));
    queue->rear=-1;
    queue->first=0;
    queue->max_queue_size=X;
    queue->qsize=0;
    queue->key=(int*)malloc(sizeof(int)*X);

    return queue;
}

void Enqueue(Queue Q, int X){
    if(Q->rear==Q->max_queue_size-1)
        return;
    Q->key[++Q->rear]=X;
    ++Q->qsize;

}
int Dequeue(Queue Q){
    if(Q->first>Q->rear)
        return -1;
    --Q->qsize;
    return Q->key[Q->first++];

}

int* CheckIndegree(int* indegree_,Graph G){
    int i=0;
    int j=0;
    int sum=0;
    for(i=0;i<G->size;i++){
        for(j=0;j<G->size;j++){
            if(G->matrix[j][i]==1)
                sum+=1;
        }
        indegree_[i]=sum;
        sum=0;
    }

   
    return indegree_;
}

void Topsort(Graph G){
    fprintf(fp_out,"TopSort Result : ");
    int* Indegree=malloc(sizeof(int)*G->size);
     int i=0;
    Queue q=MakeNewQueue(G->size);
    Indegree=CheckIndegree(Indegree,G);
    int v,w,temp,w_;

    for(i=0;i<G->size;i++) {
        if (Indegree[i] == 0) {
            Enqueue(q, G->node[i]);
        }
    }

    while(q->qsize!=0){
        //v는 key값
        v=Dequeue(q);
        fprintf(fp_out,"%d ",v);
//temp는 index
        for(i=0;i<G->size;i++){
            if(v==G->node[i])
                temp=i;
        }
        //w는 key
        for(i=0;i<G->size;i++) {
            if (G->matrix[temp][i]>0) {
               w_=i;
               w=G->node[i];
                if(--Indegree[w_]==0) {
                    Enqueue(q, w);
                }
            }
        }

    }

}



int main() {
    FILE* fp=fopen("input.txt","r");
    fp_out=fopen("output.txt","wt");

    graph=(Graph)malloc(sizeof(struct _Graph));


    int vertexIn,vertexOut;
    int c;
    int i,j,num;
    char node_[50];
    int node[10];
    num=0;
    //node배열 최대 9개 숫자 범위는 1~9

    fgets(node_,50,fp);
    for(i=0;i<50;i+=2){
        if('1'<=node_[i]&& node_[i]<='9'){
            node[num] = node_[i]-'0';
            num++;
        }
        else
            break;
    }
    graph->size=num;
    graph->node=(int*)malloc(sizeof(int)*num);

    for(i=0;i<num;i++) {
        graph->node[i] = node[i];
    }


    //num
    CreateGraph(graph->node);

    while(1){
        vertexIn=fgetc(fp)-'0';
        fgetc(fp);
        vertexOut=fgetc(fp)-'0';
        InsertEdge(graph,vertexIn,vertexOut);
        if(fgetc(fp)==EOF)
            break;

    }



    fprintf(fp_out,"Adjacency matrix\n  ");
    for(i=0;i<graph->size;i++){
    fprintf(fp_out,"%d ",graph->node[i]);
    }
    fprintf(fp_out,"\n");


    for(i=0;i<graph->size;i++){
        for(j=0;j<graph->size;j++){
        if(j==0){
            fprintf(fp_out,"%d ",graph->node[i]);
        }
            fprintf(fp_out,"%d ", graph->matrix[i][j]);
        }
        fprintf(fp_out,"\n");
    }

    fprintf(fp_out,"\n\n\n");
    Topsort(graph);


    fclose(fp);
    fclose(fp_out);
    return 0;
}
