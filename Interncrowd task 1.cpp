#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
using namespace std;
void isValidDate(const char *dateString,int &isValid)
{
int dd,mm,yy;
int sepIndex1,sepIndex2,i,r;
char mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
char sep;
isValid=0;
if(dateString==NULL) return;
int x=strlen(dateString);
if(x<8 || x>10) return;
if(!(dateString[1]=='/' || dateString[2]=='/' )) return;
if(dateString[1]=='/' ) sepIndex1=1;
else sepIndex1=2;
sep=dateString[sepIndex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(sepIndex1==2 && (dateString[1]<48 || dateString[1]>57)) return;
if(sepIndex1==1)
{
dd=dateString[0]-48;
if(dd==0) return;
}
else 
{
dd=((dateString[0]-48)*10)+(dateString[1]-48);
if(dd==0) return;
}
i=sepIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep)) return;
if(dateString[i+1]==sep) sepIndex2=i+1;
else sepIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return;
if(sepIndex2==i+2 && (dateString[i+1]<48 || dateString[i+1]>57)) return;
if(sepIndex2==i+1)
{
mm=dateString[i]-48;
}
else
{
mm=((dateString[i]-48)*10)+(dateString[i+1]-48);
}
if(mm<1 || mm>12) return;
i=sepIndex2+1;
yy=0;
r=0;
while(r<=3)
{
if(dateString[i+r]<48 || dateString[i+r]>57) return;
yy=(yy*10)+(dateString[i+r]-48);
r++;
}
if(yy<1901) return;
if(yy%400==0) mth[1]=29;
else if(yy%100==0) mth[1]=28;
else if(yy%4==0) mth[1]=29;
else mth[1]=28;
if(dd<1 || dd>mth[mm-1]) return;
isValid=1;
}

// programming about the task is starting form here.
// above code is for handling date related programming.

struct Birthday
{
char name[56];
char date[12];
char email[101];
};
void printLine(char g,int size)
{
int i;
for(i=1;i<=size;i++) printf("%c",g);
printf("\n");
}
void addBirthday()
{
FILE *f;
struct Birthday t,g;
char name[56];
char email[101];
char date[12];
printf("Enter name :  ");
fgets(name,56,stdin);
name[strlen(name)-1]='\0';
fflush(stdin);
printf("Enter date :  ");
fgets(date,12,stdin);
date[strlen(date)-1]='\0';
fflush(stdin);
int isValid;
isValidDate(date,isValid);
if(isValid==0)
{
printf("Invalid format of date : %s Usage x/x/xxxx or xx/xx/xxxx\n",date);
return ;
}
char m;
printf("Enter email : ");
fgets(email,101,stdin);
email[strlen(email)-1]='\0';
fflush(stdin);
printf("Save(Y/N)");
m=getchar();
fflush(stdin);
if(m!='y' && m!='Y')
{
printf("Birthday not added\n");
return ;
}
strcpy(g.name,name);
strcpy(g.date,date);
strcpy(g.email,email);
f=fopen("birthday.dat","ab");
fwrite(&g,sizeof(struct Birthday),1,f);
fclose(f);
printf("Birthday added , press enter to continue...............\n");
getchar();
fflush(stdin);
}
void showListByName()
{
FILE *f;
struct Birthday t;
char name[56];
char email[101];
char date[12];
printf("Birthday (search by name module)\n");
printf("Enter name :  ");
fgets(name,56,stdin);
name[strlen(name)-1]='\0';
fflush(stdin);
f=fopen("birthday.dat","rb");
if(f==NULL)
{
printf("Invalid detail\n");
return;
}
int found=0;
char m;
while(1)
{
fread(&t,sizeof(struct Birthday),1,f);
if(feof(f)) break;
if(strcasecmp(t.name,name)==0)		
{
printf("Name : %s\nDate : %s\nEmail : %s\n",t.name,t.date,t.email);
found=1;
}
}
fclose(f);
if(found==0)
{
printf("Invalid name \n");
return ;
}
printf("Press enter to continue....................");
getchar();
fflush(stdin);
}
void showListByDate()
{
FILE *f;
struct Birthday t;
char name[56];
char email[101];
char date[12];
printf("Birthday (search by date module)\n");
printf("Enter date :  ");
fgets(date,56,stdin);
date[strlen(date)-1]='\0';
fflush(stdin);
f=fopen("birthday.dat","rb");
if(f==NULL)
{
printf("Invalid detail\n");
return;
}
int found=0;
char m;
while(1)
{
fread(&t,sizeof(struct Birthday),1,f);
if(feof(f)) break;
if(strcmp(t.date,date)==0)		
{
printf("Name : %s\nDate : %s\nEmail : %s\n",t.name,t.date,t.email);
found=1;
}
}
fclose(f);
if(found==0)
{
printf("Invalid date : Usage date x/x/xxxx oy xx/xx/xxxx\n");
return ;
}
printf("Press enter to continue....................");
getchar();
fflush(stdin);
}

void showFullList()
{
FILE *f;
int newPage,pageSize;
int sNo;
struct Birthday t;
f=fopen("birthday.dat","rb");
if(f==NULL)
{
printf("Birthday(List Module)\n");
printLine('-',110);
printf("%10s  %-35s  %-10s  %-35s\n","S.No.","Name","Date","Email");
printLine('-',110);
printf("No student added\n");
printLine('-',110);
printf("Press enter to continue....................\n");
getchar();
fflush(stdin);
return ;
}
newPage=1;
pageSize=5;
sNo=0;
while(1)
{
if(newPage==1)
{
printf("Birthday(List Module)\n");
printLine('-',110);
printf("%10s  %-35s  %-10s  %-35s\n","S.No.","Name","Date","Email");
printLine('-',110);
newPage=0;
}

fread(&t,sizeof(struct Birthday),1,f);
if(feof(f)) break;
sNo++;
printf("%10d  %-35s  %-10s  %-35s\n",sNo,t.name,t.date,t.email);
if(sNo%pageSize==0)
{
printLine('-',110);
printf("Press enter to continue...................\n");
getchar();
fflush(stdin);
newPage=1;
}
}
if(sNo==0)
{
printf("No student added\n");
printLine('-',80);
printf("Press enter to continue...................\n");
getchar();
fflush(stdin);
}
if(sNo%pageSize!=0)
{
printLine('-',110);
printf("Press enter to continue...................\n");
getchar();
fflush(stdin);
}
fclose(f);
}
void showListByDay()
{
FILE *f;
struct Birthday t;
char name[56];
char email[101];
char date[12];
int day;
printf("Birthday (search by day module)\n");
printf("Enter day :  ");
scanf("%d",&day);
fflush(stdin);
f=fopen("birthday.dat","rb");
if(f==NULL)
{
printf("Invalid detail\n");
return;
}
int found=0;
char m;
char x[11];
int fDay;
char y[3];
int e=0;
while(1)
{
fread(&t,sizeof(struct Birthday),1,f);
if(feof(f)) break;
strcpy(x,t.date);
e=0;
while(x[e]!='/')
{
y[e]=x[e];
e++;
}
fDay=atoi(y);
if(fDay==day)		
{
printf("Name : %s\nDate : %s\nEmail : %s\n",t.name,t.date,t.email);
found=1;
}
}
fclose(f);
if(found==0)
{
printf("Invalid date \n");
return ;
}
printf("Press enter to continue....................");
getchar();
fflush(stdin);
}
void showListByMonth()
{
FILE *f;
struct Birthday t;
char name[56];
char email[101];
char date[12];
int month;
printf("Birthday (search by month module)\n");
printf("Enter month :  ");
scanf("%d",&month);
fflush(stdin);
f=fopen("birthday.dat","rb");
if(f==NULL)
{
printf("Invalid detail\n");
return;
}
int found=0;
char m;
char x[11];
int fMonth;
int fDay;
char y[3];
int e=0;
int g;
while(1)
{
fread(&t,sizeof(struct Birthday),1,f);
if(feof(f)) break;
strcpy(x,t.date);
e=0;
while(x[e]!='/') e++;
e++;
g=0;
while(x[e]!='/')
{
y[g]=x[e];
e++;
g++;
}
fMonth=atoi(y);
if(fMonth==month)		
{
printf("Name : %s\nDate : %s\nEmail : %s\n",t.name,t.date,t.email);
found=1;
}
}
fclose(f);
if(found==0)
{
printf("Invalid date \n");
return ;
}
printf("Press enter to continue....................");
getchar();
fflush(stdin);
}
int main()
{
int ch;
while(1)
{
printf("1. Add birthday\n");
printf("2. Get birthday date list by name\n");
printf("3. Get birthday date list by date\n");
printf("4. Show list of birtday date\n");
printf("5. Get birthday date list by day\n");
printf("6. Get birthday date list by month\n");
printf("7. Exit\n");
printf("Enter your choice : ");
scanf("%d",&ch);
fflush(stdin);
if(ch==1)
{
addBirthday();
}else if(ch==2)
{
showListByName();
}else if(ch==3)
{
showListByDate();
}else if(ch==4)
{
showFullList();
}else if(ch==5)
{
showListByDay();
}else if(ch==6)
{
showListByMonth();
}
else if(ch==7)
{
break;
}else 
{
printf("Invalid choice \n");
return 0;
}
}
return 0;
}
