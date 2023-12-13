#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node{
    int st;
    struct node* link;
};

int buffer[100],set[100];
char symbols[20];
struct node* transitions[100][100] = {NULL};
int e_closure[100][100] = {0};
int nosymbols,nostates,notrans, currInd;

int findSymbol(char c){
    for(int i=0;i<nosymbols;i++){
        if(symbols[i]==c) return i;
    }
    return 999;
}
void insert_trans(int s, char c, int e){
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    int j = findSymbol(c);
    if(j==999){
        printf("\nError");
        return;
    }
    temp->st = e;
    temp->link = transitions[s][j];
    transitions[s][j] = temp;
}
void findClosure(int curr, int og){
    struct node* temp;
    e_closure[og][currInd++] = curr;
    if(buffer[curr]==1){
        return;
    }
    buffer[curr] = 1;
    if(symbols[nosymbols-1]=='e' && transitions[curr][nosymbols-1]!=NULL){
        temp = transitions[curr][nosymbols-1];
        while(temp!=NULL){
            findClosure(temp->st,og);
            temp = temp->link;
        }
    }
}
int main(){
    printf("Enter the number of alphabets: if epsilon is present, enter it the last:");
    scanf("%d",&nosymbols);
    printf("\n Enter the symbols:");
    getchar();
    for(int i=0;i<nosymbols;i++){
        symbols[i] = getchar();
        getchar();
    }
    printf("\n Enter the number of states:");
    scanf("%d",&nostates);
    printf("\n Enter the number of transitions:");
    scanf("%d",&notrans);
    printf("\n Enter the transitions");
    for(int i=0;i<notrans;i++){
        int s1,s2;
        char c;
        scanf("%d%c%d",&s1,&c,&s2);
        insert_trans(s1,c,s2);
    }
    printf("\n Epsilon transitions are");
    for(int i=1;i<=nostates;i++){
        currInd = 0;
        findClosure(i,i);
        printf("\n q%d - {",i);
        for(int j=0;e_closure[i][j]!=0;j++){
            printf("q%d, ",e_closure[i][j]);
        }
        printf("}\n");
    }
    return 0;
}