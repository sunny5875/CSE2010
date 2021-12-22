#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Elt_type;
typedef  int Edge;
typedef int set_type;
typedef Elt_type Dis_j;



set_type find(Elt_type x, Dis_j* s){
   while(s[x]>0)
        x=s[x];
    return x;
 /*  if(s[x]<=0)
       return x;
   else
       return(s[x]=find(s[x],s));*/
}

void Union(Dis_j *s,set_type r1, set_type r2){
    if(s[r2]<s[r1])
        s[r1]=r2;
    else{
        if(s[r2]==s[r1])
            s[r1]--;
        s[r2]=r1;
    }

}

int main() {
    FILE* fp=fopen("input.txt","r");
    FILE* fp_out=fopen("output.txt","wt");

    int num;
    fscanf(fp,"%d",&num);

    if(num>=10) {
        fprintf(fp_out, "Number has to be less than 10\n");
        return 1;
    }

    int edge_num=(num-1)*num*2;
    int i,ran1,ran2,a,j,ran;
    int check_0,check_;
    set_type u,v;
// e: edge들의 집합 dis_set : 결과물
    Edge e[edge_num][2];
    Dis_j *dis_set=(Dis_j*)malloc(sizeof(Dis_j)*(num*num+1));
    char maze[num*2+1][num*2+1];
    
    srand((unsigned int)time(NULL));
    a=1;
    //edge set 만들기
    i=0;
   while(i<edge_num) {
       if(i==0){
           e[i][0] = a;
           e[i][1] = a + 1;
           e[i + 1][0] = a;
           e[i + 1][1] = a + num;
           a++;
           i+=2;
       }
        else if((a)%num==0){
            e[i][0]=a;
            e[i][1]=a+num;
            a++;
            i++;
        }
        else if((a>num*(num-1) &&a<=num*num)){

            e[i][0]=a;
            e[i][1]=a+1;
            a++;
            i++;
        }
        else {
            e[i][0] = a;
            e[i][1] = a + 1;
            e[i + 1][0] = a;
            e[i + 1][1] = a + num;
            a++;
            i+=2;
        }
    }
/*

    for (int k = 0; k < edge_num; ++k) {
        printf("%d %d \n",e[k][0],e[k][1]);
    }
*/

    //dis_set초기화
    for(i=1;i<=num*num;i++)
        dis_set[i]=0;

    for(i=0;i<num*2+1;i++){
        for(j=0;j<num*2+1;j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0)
                    maze[i][j] = '+';
                else
                    maze[i][j] = '-';
            }
            else {
                if (j % 2 == 0)
                    maze[i][j] = '|';
                else {
                    maze[i][j] = ' ';
                }
            }
        }
    }

    maze[1][0]=' ';
    maze[num*2-1][num*2]=' ';

    while(1){
        ran= rand()%(edge_num);
        ran1=e[ran][0];
        ran2=e[ran][1];
       while(ran1==0 && ran2==0){
            ran= rand()%(edge_num);
            ran1=e[ran][0];
            ran2=e[ran][1];
        }
       e[ran][0]=0;
       e[ran][1]=0;

        u=find(ran1,dis_set);
        v=find(ran2,dis_set);

        if(u!=v) {
            Union(dis_set, u, v);
            //가로
            if(ran2-ran1==num){
                maze[((ran1-1)/num)*2+2][((ran1-1)%num)*2+1]=' ';
            }
            else{
                maze[((ran1-1)/num)*2+1][((ran1-1)%num)*2+2]=' ';
            }

        }

        check_=0;
        check_0=0;
        for(i=1;i<=num*num;i++) {
            if (dis_set[i] < 0) {
                check_++;
            }
            else if(dis_set[i]==0){
                check_0++;
                }
        }


        if((check_0==0)&&(check_==1))
            break;

    }

   for(i=0;i<num*2+1;i++) {
        for (j = 0; j < num * 2 + 1; j++)
            fprintf(fp_out,"%c", maze[i][j]);
        fprintf(fp_out,"\n");
    }


        free(dis_set);
    return 0;
}