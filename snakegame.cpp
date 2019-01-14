#include <iostream>
#include <stdlib.h>
#include <ctime>
#include<cstring>
#include<fstream>
using namespace std;
int row=26,col=26,f1=0,sc=0;
struct food{
	int x,y;
	char value;
};
struct snake
{
	int x,y;
	char svalue;
	snake *next;
};
//print snake
void printmat(char ar[100][100])
{
	system("CLS");
for(int i=0;i<=row+1;i++)
{
	cout<<". ";
}
cout<<"\n";
for(int i=0;i<row;i++)
{
	cout<<".";
	for(int j=0;j<col;j++)
	{
		cout<<ar[i][j]<<" ";
	}
	cout<<".";
	cout<<endl;
}
for(int i=0;i<=row+1;i++)
{
	cout<<". ";
}
cout<<"\n";
cout<<"score--"<<sc<<endl;
}
//print snake in mat
void printsn(struct snake *head,char ar[100][100])
{
	struct snake *temp=head->next;
	int x=head->x;
	int y=head->y;
		ar[head->x][head->y]=head->svalue;
		head=head->next;
	while(head!=NULL)
	{
if(x==head->x && head->y==y && head!=temp)
{
f1=1;
break;
}
ar[head->x][head->y]=head->svalue;
head=head->next;
}
if(f1==0)
printmat(ar);
}
void insert(struct snake** head,struct snake** tail,int x,int y)
{
	struct snake *n,*ptr;
	char ch;
		n= new snake;
	    n->x=x;
	    n->y=y;
	    n->next=NULL;
	    if((*head)==NULL)
	    {
	    	n->svalue='#';
		    (*head)=n;
		    (*tail)=n;
	    }
	    else
	    {
	    	n->svalue='&';
	    	(*tail)->next=n;
	    	(*tail)=(*tail)->next;
		}
}
//snake bite
void sbite(struct snake **head,struct food node)
{
struct snake *newnode=new snake;
newnode->x=node.x;
newnode->y=node.y;
newnode->svalue='#';
(*head)->svalue='&';
newnode->next=(*head);
(*head)=newnode;
}
void remove(struct snake **head,char ar[100][100])
{
	 struct snake *list=*head,*temp=list;
  if (list->next==NULL)
  {
f1=1;
delete(head);
delete(list->next);
}
else{
while(list->next!=NULL)
{
  temp=list;
  list=list->next;
}
ar[list->x][list->y]=' ';
temp->next=NULL;
delete(list);
}
}
void sstart(struct snake **head,struct snake **tail,char ar[100][100],int x,int y)
{
	if((*head)==NULL){
struct snake *newnode=new snake;
struct snake *newnode1=new snake;
newnode->x=x;
newnode->y=y;
newnode->svalue='#';
(*head)=newnode;
newnode1->x=x;
newnode1->y=y-1;
newnode1->svalue='&';
(*tail)=newnode1;
(*head)->next=(*tail);
(*tail)->next=NULL;
}
}
void saveFile(struct snake* head,struct food f,struct food s,char *file)
{
	ofstream fout;
	char str[10];
	fout.open(file);
	int i=0,temp,len,m;
	while(head!=NULL)
	{
		fout<<"snake,";
		itoa(head->x,str,10);
	    fout<<str;
     	fout<<',';
	    itoa(head->y,str,10);
    	fout<<str;
    	fout<<'\n';	
		head=head->next;
	}
	fout<<"food,";
	itoa(f.x,str,10);
	fout<<str;
	fout<<',';
	itoa(f.y,str,10);
	fout<<str;
	fout<<'\n';
	fout<<"poison,";
	itoa(s.x,str,10);
	fout<<str;
	fout<<',';
	itoa(s.y,str,10);
	fout<<str;
	fout<<'\n';
	fout<<"score,";
	itoa(sc,str,10);
	fout<<str;
	fout<<',';
	fout<<'0';
	fout<<'\n';
}

int xtract(char str[],int *i)
{
	int k=0,res;
	char num[10];
	while(str[*i]!=','&&str[*i]!='\0')
	{
		num[k]=str[*i];
		
		(*i)++;
		k++;
	}
	num[k]='\0';
	res=atoi(num);
	return res;
}

void loadFromFile(struct snake** head,struct snake** tail,char *file,char board[100][100])
{
	char str[20],num[10];
	int i=0,x,y,k,m=0;
	ifstream fin;
	fin.open(file);
	while(fin)
	{
		fin>>str;
		i=0;
		k=0;
		while(str[i]!=',')
		{
			num[k]=str[i];
			k++;
			i++;
		}
		num[k]='\0';
		cout<<num;
		//break;
		i++;
		x=xtract(str,&i);
		i++;
		y=xtract(str,&i);
		if(!(strcmp(num,"snake")))
		{
			insert(&(*head),&(*tail),x,y);
		}
		else if((!strcmp(num,"food")))
		{
			board[x][y]='O';
		}
		else if((!strcmp(num,"poison")))
		{
			board[x][y]='@';
		}
		else if((!strcmp(num,"score")))
		{
			sc=x;
		}
		
		
	}
	
}
struct food sposn(char ar[100][100],struct snake *head)
{
	
	struct food s;
int flag=1;
while(flag){
s.x=(rand()%24);
s.y=(rand()%24);
s.value='@';
while(head!=NULL){
if((head)->x==s.x && (head)->y==s.y)
{
	flag=1;
	break;
}
else
{
	flag=0;
}
head=head->next;
}}
ar[s.x][s.y]=s.value;
return s;
}
struct food sfood(char ar[100][100],struct snake *head)
{
	struct food f;
int flag=1;
while(flag){
f.x=(rand()%24);
f.y=(rand()%24);
f.value='O';
while(head!=NULL){
if((head)->x==f.x && (head)->y==f.y)
{
	flag=1;
	break;
}
else
{
	flag=0;
}
head=head->next;
}}
ar[f.x][f.y]=f.value;
return f;
}

//change positiion
void change(struct snake *head,int x,int y,char ar[100][100])
{
	int a,b;
while((head)!=NULL)
{
a=(head)->x;
b=(head)->y;
if(head->next==NULL){
ar[a][b]=' ';
}
(head)->x=x;
(head)->y=y;
x=a;
y=b;
(head)=(head)->next;
}
}
//move snake
void snakemove(struct snake **head,struct snake **tail,char ar[100][100])
{
	int x,y,fq=0;
	struct food s;
	struct food f;
	char file[10]="snake.txt";
char ch;
cout<<"Do you want to resume (y/n)\n";
cin>>ch;
if(ch=='y')
{
	loadFromFile(&(*head),&(*tail),file,ar);
}
else
{
int x,y;
cout<<"enter the pos\n";
cin>>x>>y;
sstart(&(*head),&(*tail),ar,x,y);
	struct snake *list=(*head);
	f=sfood(ar,*head);
	s=sposn(ar,*head);
}
	
	printsn(*head,ar);
	while(1)
	{
	if(f1==0)
	{
	char ch1;
cout<<"PRESS: l(left) ,r(right) ,d(down) ,t(top) ,q(quit)\n  "<<endl;
cin>>ch1;
switch(ch1)
{
case 'l':
x=(*head)->x;
 y=((*head)->y)-1;
 if(y!=((*head)->next->y))
 {
 if(y==0){
 y=col+1;
 }
 if(x==f.x && y==f.y)
 {
	 sbite(&(*head),f);
	  f=sfood(ar,*head);
	  sc++;
 }
 if((x==s.x && y==s.y))
 {
 	remove(&(*head),ar);
 	s=sposn(ar,*head);
 	sc--;
 }
 else
 change(*head,x,y,ar);
}
else
cout<<"invalid\n";
	break;
case 'r':
x=(*head)->x;
y=((*head)->y)+1;
if(y!=((*head)->next->y))
{
if(y==col+1)
 y=0;	
 if(x==f.x && y==f.y)
 {
	 sbite(&(*head),f);
	  f=sfood(ar,*head);
  sc++;
 }
 
 if((x==s.x && y==s.y))
 {
 	remove(&(*head),ar);
 	s=sposn(ar,*head);
 	sc--;
 }
 else
 change(*head,x,y,ar);
}
else
cout<<"Invalid\n";
	break;	
case 'd':
x=(*head)->x+1;
y=((*head)->y);
if(x!=(*head)->next->x)
{
if(x==row+1)
 x=0;
   if(x==f.x && y==f.y)
 {
	 sbite(&(*head),f);
	  f=sfood(ar,*head);
  sc++;
 }
 
 if((x==s.x && y==s.y))
 {
 	remove(&(*head),ar);
 	s=sposn(ar,*head);
 	sc--;
 }
 else
 change(*head,x,y,ar);
}
else
cout<<"Invalid\n";
	break;
	case 't':
x=(*head)->x-1;
y=((*head)->y);
if(x!=(*head)->next->x)
{
 if(x==0)
 x=row+1;
 if(x==f.x  && y==f.y)
 {
	 sbite(&(*head),f);
	  f=sfood(ar,*head);
  sc++;
 }
 
 if((x==s.x && y==s.y))
 {
 	remove(&(*head),ar);
s=sposn(ar,*head);
 	sc--;
 }
else
change(*head,x,y,ar);
}
else
cout<<"Invalid\n";
		break;
case 'q':
	f1=1;
	saveFile(*head,f,s,file);
  break;
default:cout<<"INVALID INPUT\n";
}  
		printsn(*head,ar);
	}
else
{
cout<<">>>>>>>>>>GAMEOVER>>>>>>>>>>>>>>>>>\n";
break;	
}
}
}
 
int main()
{
	char ar[100][100];

	srand(time(0));
struct snake *head=NULL,*tail=NULL;
for(int i=0;i<row;i++)
{
	for(int j=0;j<col;j++)
	{
		ar[i][j]=' ';
	}
}
snakemove(&head,&tail,ar);
}
