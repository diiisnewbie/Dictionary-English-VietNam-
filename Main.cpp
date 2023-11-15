#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TextToSpeech.h"
#include "Menu.h"
#include "Tree.h"
#define filename "Words.txt"

void readfile(Tree &t,FILE *f);
void copy(Tree t,Word temp[],int &count);
void writefile(Word temp[],FILE *f,int count);
void docTu(Word data[],int count);
void drawBoard();


int main(){
	int choice=0;
	Tree t;
	init(t);
	FILE *f;
	readfile(t,f);
	do{
		menu();
		scanf("%d",&choice);
		switch(choice){
			case 1:{
				Word w;
				printf("\n\t*Them Tu");
				printf("\n\t  +Nhap ma so cua tu:");
				scanf("%d",&w.stt);
				printf("\n\t  +Nhap Tu:");
				fflush(stdin);
				gets(w.name);
				printf("\n\t  +Nhap Nghia:");
				fflush(stdin);
				gets(w.nghia);
				printf("\n\t  +Nhap Phien Am:");
				fflush(stdin);
				gets(w.phienam);
				add(t,w);
				break;
			}
			case 2:{
				printf("\n\t*Tim Kiem");
				printf("\n\t  +Nhap Tu Can Tim Kiem:");
				fflush(stdin);
				char temp[50];
				gets(temp);
				printf("\n\t\t\t*Nhung tu duoc goi y*\n");
				drawBoard();
				timKiem(t,temp);
				printf("\n%55s"," +----------------------------------------------------------------------------+");
				Word w[50];
				int count=0;
				chuyenDuLieu(t,count,w,temp);
				docTu(w,count);
				break;
			}
			case 3:{
					int stt;
					printf("\n\t*Xoa Tu*");
					printf("\n\t  +Nhap Ma So cua tu do de xoa:");
					scanf("%d",&stt);
					xoa(t,stt);
					printf("\n\t*Xoa Thanh Cong*");
					break;
			}
			case 4:{
				int stt;
				printf("\n\t*Sua Tu*");
				printf("\n\t  +Nhap Ma So cua tu do de sua:");
				scanf("%d",&stt);
				int chon=0;
				do{
					printf("\n\t   1.Sua ten.");
					printf("\n\t   2.Sua phien am.");
					printf("\n\t   3.Sua nghia.");
					printf("\n\t   0.Ket thuc.");
					printf("\n\t*Choc chuc nang can lam:");
					scanf("%d",&chon);
					switch(chon){
						case 1:{
							printf("\n\t*Nhap ten can sua:");
							char name[50];
							fflush(stdin);
							gets(name);
							edit(t,stt,chon,name);
							printf("\n\t*Cap Nhat Thanh Cong");
							break;
						}
						case 2:{
							printf("\n\t*Nhap phien am can sua:");
							char phienam[50];
							fflush(stdin);
							gets(phienam);
							edit(t,stt,chon,phienam);
							printf("\n\t*Cap Nhat Thanh Cong");
							break;
						}
						case 3:{
							printf("\n\t*Nhap nghia can sua:");
							char nghia[50];
							fflush(stdin);
							gets(nghia);
							edit(t,stt,chon,nghia);
							printf("\n\t*Cap nhat thanh cong");
							break;
						}
					}
				}while(chon > 0  && chon <= 3);
				break;
			}
			case 5:{
				int count=0;
				printf("\n\t*Xuat Danh Sach");
				drawBoard();
				printAll(t,count);
				printf("\n%55s"," +----------------------------------------------------------------------------+");
				break;
			}
			case 6:{
				Word w[100];
				int count=0;
				copy(t,w,count);
				writefile(w,f,count);
				break;
			}
		}
	}while(choice !=0);
}

//Doc File
void readfile(Tree &t,FILE *f){
	f = fopen(filename,"r");
	char *token;
	char line[100];
	Word w;
	while(fgets(line,100,f)!=NULL){

		token = strtok(line,"; \n");
		w.stt = atoi(token);

		token = strtok(NULL,"; \n");
		strcpy(w.name,token);

		token=strtok(NULL,"; \n");
		strcpy(w.phienam,token);

		token = strtok(NULL,"; \n");
		strcpy(w.nghia,token);

		add(t,w);
	}

	fclose(f);
}

//Chyuen du lieu tu tree sang Mang
void copy(Tree t,Word temp[],int &count){
	if(t!=NULL){
		temp[count] = t->data;
		count++;
		copy(t->left,temp,count);
		copy(t->right,temp,count);
	}
}

//Ghi du lieu vao file.txt
void writefile(Word temp[],FILE *f,int count){
	f=fopen (filename,"w");
	for(int i=0;i<count;i++){
		fprintf(f,"%d%s%s%s%s%s%s\n",temp[i].stt,";",temp[i].name,";",temp[i].phienam,";",temp[i].nghia);
	}
	fclose(f);
}

//Doc cac tu da tim kiem
void docTu(Word data[],int count){
	int maso=0;
	int i=0;
	do{
		printf("\n\t*Chon Tu(Theo Ma So) de may doc(Nhan 0 de ngung doc):");
		scanf("%d",&maso);
		for(int i =0 ; i<count ; i++){
			if(maso == data[i].stt){
				Text_to_Speech(data[i].name);
			}
		}
	}while(maso!=0);	
}

//Xuat ra khung bang
void drawBoard(){
	printf("\n%55s"," +---------------------------DICTIONARY DOUBLE DUY----------------------------+");
	printf("\n%2s%5s%2s%15s%10s%15s%5s%15s%10s","|","Ma So","|","Vocabulary","|","Spelling","|","Meaning","|");
	printf("\n%55s"," +----------------------------------------------------------------------------+");
}

