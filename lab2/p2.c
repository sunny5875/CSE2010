#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

typedef struct {
    int studentID;
    char* studentName;
}ElementType;

struct Node{
    ElementType element;
    PtrToNode next;

};


void Insert(List l, ElementType x,FILE* fp_out);
void Delete(ElementType x, List l,FILE* fp_out);
Position Find(ElementType x, List l);
void PrintList(List l,FILE* fp_out);

int main() {
    List head=malloc(sizeof(struct Node));
    head->next=NULL;

    FILE *fp=fopen("input.txt","r");
    FILE *fp_out=fopen("output.txt","wt");
    char ch;

    while((ch=fgetc(fp))!=EOF) {
        //add student
        if (ch == 'i') {

            int tmp_id;
            fscanf(fp, "%d", &tmp_id);
            char tmp_fname[31],tmp_lname[31];
            fscanf(fp,"%s %s",tmp_fname,tmp_lname);

            ElementType x;
            x.studentID = tmp_id;
            x.studentName=(char*)malloc(strlen(tmp_fname)+strlen(tmp_lname)+1);
            strcpy(x.studentName,tmp_fname);
            strcat(x.studentName," ");
            strcat(x.studentName,tmp_lname);

            Insert(head,x,fp_out);
        }
            //delete student
        else if (ch == 'd') {
            int tmp_id;
            fscanf(fp, "%d", &tmp_id);

            ElementType x;
            x.studentID = tmp_id;
            Delete(x, head,fp_out);

        }
            //find
        else if (ch == 'f') {
            int tmp_id;
            fscanf(fp, "%d", &tmp_id);

            ElementType x;
            x.studentID = tmp_id;
            Position p = Find(x, head);
            if(p!=NULL) {
                fprintf(fp_out, "Find Success : %d %s\n", p->element.studentID,p->element.studentName);
            }
            else{
                fprintf(fp_out, "Find %d Failed. There is no student ID.\n", x.studentID);
            }
        }

        else if (ch == 'p'){
            PrintList(head,fp_out);
        }

    }

    struct Node* curr = head->next;      // 연결 리스트 순회용 포인터에 첫 번째 노드의 주소 저장
    while (curr != NULL)    // 포인터가 NULL이 아닐 때 계속 반복
    {
        struct Node *next = curr->next;    // 현재 노드의 다음 노드 주소를 임시로 저장
        free((void *) curr->element.studentName);
        free(curr);                        // 현재 노드 메모리 해제
        curr = next;                       // 포인터에 다음 노드의 주소 저장
    }

    free(head);

    fclose(fp);
    fclose(fp_out);

    return 0;
}

 void Insert(List l, ElementType x,FILE* fp_out)
 {

     struct Node* temp = malloc(sizeof(struct Node));
     temp->element.studentName =(char*)malloc(strlen(x.studentName)+1);
     temp->element.studentID = x.studentID;
     strcpy(temp->element.studentName, x.studentName);

     if(l->next==NULL){
         l->next = temp;
     }
     else{
         Position p;
         p = l;
         while(p->next!=NULL){
             if(p->next->element.studentID==x.studentID){
                 free(x.studentName);
                 fprintf(fp_out,"Insertion Failed. ID %d already exists.\n",x.studentID);
                 return;
             }
             else if(p->next->element.studentID>x.studentID){
                 break;
             }
             p= p->next;
         }
         temp->next = p->next;
         p->next = temp;
     }


     fprintf(fp_out, "Insertion Success : %d\n", x.studentID);
     fprintf(fp_out, "Current Success > ");
     struct Node *temp_ = l->next;
     while (temp_ != NULL) {
         fprintf(fp_out, "%d %s ", temp_->element.studentID, temp_->element.studentName);
         temp_ = temp_->next;
        if(temp_!=NULL)
            fprintf(fp_out,"- ");
     }
     fprintf(fp_out, "\n");


 }

 //sorting도 해야 함.

// Find에서 ID가 없는 경우

Position Find(ElementType x, List l){
    Position p=l->next;
    while(p!=NULL){
        if(p->element.studentID==x.studentID)
            return p;
        p=p->next;
    }
    return NULL;
}






// delete에서 ID가 없는 경우,

void Delete(ElementType x, List l,FILE* fp_out){
    Position p = l;

    while(p->next!=NULL) {
        if (p->next->element.studentID== x.studentID) {
            List temp = p->next;
            p->next = temp->next;

            free(temp->element.studentName);
            free(temp);

            fprintf(fp_out, "Deletion Success : %d\n", x.studentID);

            fprintf(fp_out, "Current List > ");
            struct Node *temp_ = l->next;
            while (temp_ != NULL) {
                fprintf(fp_out, "%d %s ", temp_->element.studentID, temp_->element.studentName);
                temp_ = temp_->next;
                if(temp_!=NULL)
                    fprintf(fp_out,"- ");

            }
            fprintf(fp_out, "\n");

            return;
        }
        p = p->next;
    }
            fprintf(fp_out,"Deletion Failed : Student ID %d is not in the list\n",x.studentID);

}

void PrintList(List l,FILE* fp_out){
    struct Node* header=l->next;
    struct Node* temp=l->next;

  //sorting
    fprintf(fp_out,"------LIST------\n");
    while(header!=NULL){
        fprintf(fp_out,"%d %s\n",header->element.studentID,header->element.studentName);
        header=header->next;
    }
    fprintf(fp_out,"-----------------\n");

}