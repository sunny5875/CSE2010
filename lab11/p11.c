#include <stdio.h>
#include <stdlib.h>
#define INF 99999

typedef struct {
    int key;
    int weight;
}Node;
typedef struct {
    int capacity;
    int size;
    Node* element;
}Heap;

struct _Graph {
    int size;
    int* node;
    int** matrix;
};


typedef struct _Graph* Graph;
typedef Heap* minheap;
Graph graph;



void CreateGraph(int* nodes) {
    int i = 0;
    int j = 0;
    graph->matrix = (int**)malloc(sizeof(int*)*(graph->size + 1));
    for (i = 0; i < graph->size + 1; i++) {
        graph->matrix[i] = (int*)malloc(sizeof(int)*(graph->size + 1));
    }
}
void InsertEdge(Graph G, int a, int b, int count) {

    int i = 0;
    int in, out;
    for (i = 0; i < G->size; i++) {
        if (G->node[i] == a) {
            in = i;
        }
        if (G->node[i] == b) {
            out = i;
        }
    }
    G->matrix[in][out] = count;
}

Heap* createMinHeap(int heapSize) {
    minheap heap = (minheap)malloc(sizeof(Heap));
    heap->capacity = heapSize + 1;
    heap->size = 0;
    heap->element = (Node*)malloc(sizeof(Node)*(heap->capacity));


    return heap;
}

void insert(Heap* minHeap, int vertex, int distance,FILE* fp_out) {
    int i;
    if (minHeap->size == minHeap->capacity) {
        fprintf(fp_out, "Heap is full\n");
        return;
    }

    for (i = ++minHeap->size; minHeap->element[i / 2].weight > distance; i /= 2)
        minHeap->element[i] = minHeap->element[i / 2];


    minHeap->element[i].key = vertex;
    minHeap->element[i].weight = distance;

}

Node deleteMin(Heap* minHeap) {
    int i, child;
    Node MinElement, LastElement;
    MinElement = minHeap->element[1];
    LastElement = minHeap->element[(minHeap->size)--];
    for (i = 1; i * 2 <= minHeap->size; i = child) {
        child = 2 * i;
        if (child != minHeap->size&& minHeap->element[child + 1].weight < minHeap->element[child].weight)
            child++;

        if (LastElement.weight > minHeap->element[child].weight)
            minHeap->element[i] = minHeap->element[child];
        else
            break;
    }
    minHeap->element[i] = LastElement;

    return MinElement;
}


void printShortedsPath(int* pred, int end,FILE* fp_out,int count) {
    int tmp=end;
    int* path=(int*)malloc(sizeof(int)*count);
    int i=0;
    int j=0;
   /* if (pred[end] == INF) {
        fprintf(fp_out, "%d ", graph->node[end]);
        return;
    }
    printShortedsPath(pred, pred[end],fp_out);
    fprintf(fp_out, "%d ", graph->node[end]);*/

    path[i]=end;
    i++;
    tmp=pred[end];
   while(tmp!=INF){
       path[i]=tmp;
       i++;
       tmp=pred[tmp];

        if(i>count-1) {
            fprintf(fp_out, "No path\n");
            return ;
        }
   }

   for(j=i-1;j>=0;j--)
    fprintf(fp_out,"%d ",graph->node[path[j]]);

}


///key
void Decrease_Priority(Heap *minHeap, int key, int newweight) {
    int i,j;

    for (i = 1; i < minHeap->capacity; i++) {
        if (minHeap->element[i].key == key) {
            break;
        }
    }

    for (j = i; minHeap->element[j / 2].weight > newweight; j /= 2)
        minHeap->element[j] = minHeap->element[j / 2];


    minHeap->element[j].key = key;
    minHeap->element[j].weight = newweight;

}



int main() {
    FILE* fp = fopen("input.txt", "r");
    FILE* fp_out = fopen("output.txt", "wt");

    graph = (Graph)malloc(sizeof(struct _Graph));
    int vertexIn, vertexOut, vertexCount;
    int i, num;
    int vertex;
    num = 0;
    int start, end, start_index = 0;
    int u_index = 0;
    int node[100];
    char tmp,tmp1,tmp2;
    //첫번쨰줄
    while(1){
        fscanf(fp,"%d%c",&vertex,&tmp);
        if(tmp!='\n') {
            node[num]=vertex;
            num++;

        } else {
            node[num]=vertex;
            num++;
            break;
        }

    }
    graph->size = num;
    graph->node = (int*)malloc(sizeof(int)*num);
    CreateGraph(node);
    int* pred=(int*)malloc(sizeof(int)*num);
    int* d= (int*)malloc(sizeof(int)*num);
    Node u;

    for (i = 0; i < graph->size; i++)
    {
        graph->node[i] = node[i];
    }


    Heap* heap = createMinHeap(graph->size);


    for (int j = 0; j < graph->size; j++) {
        for (int k = 0; k < graph->size; k++) {
            graph->matrix[j][k] = INF;
        }
    }

    while (1) {
        if(fscanf(fp, "%d%c%d%c%d", &vertexIn, &tmp1, &vertexOut, &tmp2, &vertexCount) == 5){
        InsertEdge(graph, vertexIn, vertexOut, vertexCount);}
       else{
           start=vertexIn;
           end=vertexOut;
           break;
       }
    }


    for (i = 0; i < heap->capacity; i++) {
        pred[i] = 0;
        d[i] = INF;
    }

    for (i = 0; i < graph->size; i++) {
        if (graph->node[i] == start) {
            start_index = i;
            d[i] = 0;
            break;
        }
    }

    if(i==graph->size) {
        fprintf(fp_out, "no path\n");
        return 3;
    }

    pred[start_index] = INF;

    for (i = 0; i < graph->size; i++) {
        if (graph->matrix[start_index][i] != INF) {
            d[i] = graph->matrix[start_index][i];
            pred[i] = start_index;
        }
    }



    for (i = 0; i < graph->size; i++) {
        insert(heap, node[i], d[i],fp_out);
    }

    while (heap->size != 0) {

        //가장 짧은 길이를 가진 노드 뺴기
        u = deleteMin(heap);
        //방문표시
        for (i = 0; i < graph->size; i++) {
            if (u.key == graph->node[i]) {
                u_index = i;
                break;
            }
        }


        //u와 인접한 vertex중에서 값 업데이트하기
       for (i = 0; i < graph->size; i++) {
            if (graph->matrix[u_index][i] <INF) {;
                if (d[u_index] + graph->matrix[u_index][i] <d[i]) {
                    d[i] = d[u_index] + graph->matrix[u_index][i];
                    pred[i]=u_index;
                    Decrease_Priority(heap, node[i], d[i]);
                }
            }
        }

    }


    for (i = 0; i < graph->size; i++) {
        if (end == graph->node[i]) {
            end = i;
            break;
        }
    }
    if(i==graph->size)
        fprintf(fp_out,"no path\n");

else {
        printShortedsPath(pred, end, fp_out, graph->size);
    }

    fclose(fp);
    fclose(fp_out);
    return 0;
}