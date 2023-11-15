#include <stdio.h>
#include <string.h>

struct Word{
    char name[50];
    char phienam[50];
    char nghia[50];
    int stt;
};

struct Node{
    Word data;
    Node *left,*right;
};

typedef Node* Tree;

void init(Tree &t){
    t=NULL;
}

Node* createnode(Word data){
    Node* newnode = new Node;
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

int compareFirstChar(char str1[] , char str2[]){
	if (str1[0] > str2[0]) {
        return 1;  
    } else if (str1[0] <= str2[0]) {
        return -1; 
    }
}

void add(Tree &t,Word data){
    if(t == NULL){
        t = createnode(data);
    }
    else{
        if(compareFirstChar(t->data.name,data.name) == -1 ){
            add(t->right,data);
        }
        else{
            if(compareFirstChar(t->data.name,data.name) == 1){
                add(t->left,data);
            }
        }
    }
}

void printaword(Word data){
    printf("\n%2s%2d%5s%15s%10s%15s%5s%15s%10s","|",data.stt,"|",data.name,"|",data.phienam,"|",data.nghia,"|");
}

void printAll(Tree t,int &count){
    if(t!=NULL){
        printAll(t->left,count);
        count++;
        t->data.stt = count;
        printaword(t->data);
        printAll(t->right,count);
    }
}

char chuyenchuhoathanhthuong(char str[]){
    for(int i=0;i<strlen(str);i++){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] +=32;
        }
    }
}

int findSubString(Word w,char b[]){
    char *str;
    char temp[50];
    strcpy(temp,w.name);
    chuyenchuhoathanhthuong(temp);
    chuyenchuhoathanhthuong(b);
    str=strstr(temp,b);
    if(str) return 1;
    else return -1;
}


void timKiem(Tree t,char w[]){
    if(t!=NULL){
        timKiem(t->left,w);
        if(findSubString(t->data,w) == 1){
            printaword(t->data);
        }
        timKiem(t->right,w);
    }
}

void NodeTheMang(Tree &X, Tree &Y) 
{
    if (Y->left != NULL)
    {
        NodeTheMang(X, Y->left);
    }
    else 
    {
        X->data = Y->data; 
        X = Y; 
        Y = Y->right; 
    }
}

//Xoa cac Node trong cay
void xoa(Tree &t,int stt){
    if(t == NULL){
        return ;
    }
    else{
        if(t->data.stt > stt){
            xoa(t->left,stt);
        }else{
            if(t->data.stt < stt){
                xoa(t->right,stt);
            }else{
                Node *p = t;
                if(t->left == NULL){
                    t=t->right;
                }else{
                    if(t->right == NULL){
                        t=t->left;
                    }
                    else {
                    	NodeTheMang(p,t->right);
					}
                }
                    delete p;
            }
        }
    }
}

//Chuyen du lieu cay sang mang nhung thang nao duoc tim thay
void chuyenDuLieu(Tree t , int &count,Word w[],char str[]){
    if(t!=NULL){
        if(findSubString(t->data,str) == 1){
            w[count] = t->data;
            count++;
        }
        chuyenDuLieu(t->left,count,w,str);
        chuyenDuLieu(t->right,count,w,str);
    }
}


void edit(Tree t,int stt,int chon,char str[]){
    if(t!=NULL){
        edit(t->left,stt,chon,str);
        if(t->data.stt == stt){
            if(chon == 1){
                strcpy(t->data.name,str);
            }else{
                if(chon == 2){
                    strcpy(t->data.phienam,str);
                }else{
                    if(chon == 3){
                        strcpy(t->data.nghia,str);
                    }
                }
            }
        }
        edit(t->right,stt,chon,str);
    }
}
