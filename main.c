#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <dir.h>
#include <strings.h>
#include <conio.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFFER_SIZE 100

FILE *fp;

char dir[20]="default/";

int setDB()
{
	char *token;
	char inp[20];
	DIR *dr;
	printf("Enter Database Name:");
	scanf("%s",&inp);
	dr=opendir(inp);
	char pw[20];
	if(dr==NULL){
		printf("Database does not exist, using default Database");
		strcpy(dir,"default/");
	}
	else {
	FILE *fp1;
	char word[50];
	fp1 = fopen("password.txt","r");
	if (fp1 == NULL) {
    	printf("Error Password File Not Found!\n");
	} 
	else 
	{
    while(!feof(fp1)) {
        fgets(word,50,fp1);
        word[strcspn(word,"\n")] = 0;
        if(strcmp(strtok(word," "),inp)==0)
        	{
        		//fgets(word,30,fp1);
				token = strtok(NULL," ");
				printf("Enter Database Password: ");
				scanf("%s", pw);
				if(strcmp(token,pw)==0)
					goto OUT;
				else
				{
					printf("Invalid Password, Exiting...\n");
					strcpy(dir,"default/");
					printf("Using default database...");
					return -1;
				}
			}
    	}
	}
	OUT:
	fclose(fp1);
	system("cls");
	printf("Using Database: %s",inp);
	strcpy(dir,inp);strcat(dir,"/");
	}
	closedir(dr);
	return 0;
}

int createDB()
{
	char* token;
	FILE *fp1;
	char d[20],p[20];
	int a=0;
	printf("Enter Database Name:");
	scanf("%s",d);
	a=mkdir(d);
	if(a==0)
	{
		//fp1 = fopen("password.txt","a+");
		//strcat(dr,"password.txt");
		if (access("password.txt",F_OK) == -1)
        {printf("file doesn't exist");return 1;}
    	else
        {
		fp1=fopen("password.txt","a+");
		printf("Enter Database Password: ");
		scanf("%s",&p);
		if (p != NULL) {
			fputs(d,fp1);
			fputc(' ',fp1);
			fputs(p,fp1);
	    }
		fputc('\n',fp1);
		fclose(fp1);
		system("cls");
		printf("Database Successfully Created\n\n");
		return 0;}
	}
	else
	{
		printf("Database Already Exists\n\n");
		return -1;
	}
}

int createTB()
{
	char tb[50];
	char* token;
	char dr[20];
	printf("Enter Table Name:");
	scanf("%s",&tb);
	strcat(tb,".txt");
	strcpy(dr,dir);
	strcat(dr,tb);
	if (access(dr,F_OK) != -1)
        {printf("Table already exists");return 1;}
    else
        fp=fopen(dr,"w");
    printf("Enter 'col data_type' separated by commas:");
	scanf("%s",&tb);
	token= strtok(tb,",");
	while (token != NULL) {
		fputs(token,fp);
	    token = strtok(NULL,",");
	    if(token!=NULL) fputc(',',fp);
	}
	fputs(";",fp);
	printf("Table created successfully");
	fclose(fp);
	return 0;
}

/*int dropRow()
{
	FILE *fp1;
	char tb[50],word[50],c[100];;
	char* token;
	char col[50];
	int count=0,bit=0,counter=0,flag,choice,i;
	printf("Enter Table Name:");
	scanf("%s",&tb);
	strcat(tb,".txt");
	strcpy(dr,dir);
	strcat(dr,tb);
	if (access(dr,F_OK) != -1)
        fp=fopen(dr,"a+");
    else
        {printf("Table does not exist");return;}
    printf("Enter the Primary Column Value:");
    scanf("%s",&col);
     while(!feof(fp1)) {
        fgets(word,50,fp1);
        word[strcspn(word,"\n")] = 0;
        if(strcmp(strtok(word,","),col)==0)
        	{
        		//fgets(word,30,fp1);
				token = strtok(NULL," ");
				if(strcmp(token,pw)==0)
					goto OUT;
				else
				{
					printf("Invalid Password, Exiting...\n");
					strcpy(dir,"default/");
					printf("Using default database...");
					return -1;
				}
				#define MAXCHAR 1000
				while (fgets(str, MAXCHAR, fp) != NULL)
        		printf("%s", str);
			}
    	}
    
}*/

int show()
{
    DIR *d;
    struct dirent *dr;
    d = opendir(dir);
    if (d)
    {
        while ((dr = readdir(d)) != NULL)
        {
            printf("%s\n", dr->d_name);
        }
        closedir(d);
    }
    return(0);
}

void selectCOL(int count){
	char *buffer = NULL;
	buffer = (char *) malloc(sizeof(char) * 50);
	char* token,word;
	int flag, bit,counter=1,i=0,status=0;
	if(count==0) return;
/*	fseek(fp, 0, SEEK_SET);
	fgets(buffer,50,fp);
	token=strtok(buffer,";");
	strcpy(buffer,token);
	token=strtok(buffer,",");
	while(token!=NULL)
	{
		if(strcmp(token,inp)==0)
		{		
			printf("\nColumn number is %d\n",count);
			status=1;
			break;
		}
		else count++;
		token=strtok(NULL,",");
		token=strtok(NULL,",");
	}
	if(status==0) {printf("\nColumn not found");return;}*/
	flag=1;
	bit=16;
	while(bit>=0){
		if(flag==1) {
		printf("\n");flag=0;bit--;}
		printf("=");bit--;}
	printf("=\n");
	fseek(fp,0,SEEK_SET);
	int row=1;
	int wrd=1;
	
	while(fgets(buffer,50,fp)!= NULL)
	{	
		buffer[strcspn(buffer,"\n")] = 0;
		if(row==2) {
			bit=15;
			while(bit>=0){
				printf("=");bit--;}
			printf("=\n");
		}
		token=strtok(buffer,",");
		while(token!=NULL)
		{
			if(counter%2==0 && i==0) {counter++;token=strtok(NULL,","); continue;}
			else
			{
			if(wrd==count) {printf("|%s",token);if(strlen(token)<=6) printf("\t\t|\n");else printf("\t|\n");wrd=1;row++;break;}
			else
				{token=strtok(NULL,",");wrd++;}
			counter++;
			}
		}
		i=1;
	}
	bit=15;
	while(bit>=0){
		printf("=");bit--;}
	printf("=\n");
	printf("\nDisplayed Successfully");
	fclose(fp);
}

void select_by_row_value(char* in,int count)
{
	char *buffer = NULL;
	char *buffer1 = NULL;
	buffer = (char *) malloc(sizeof(char) * 50);
	buffer1 = (char *) malloc(sizeof(char) * 50);
	char tb[50];
	char inp[30],inp1[30];
	char* token,word;
	char* token1;
	char dr[20];
	strcpy(inp1,in);
	int row=1;
	int wrd=1;
	fseek(fp,0,SEEK_SET);
	while(fgets(buffer,50,fp)!= NULL)
	{	
//		printf("old buffer is %s",buffer);
		buffer[strcspn(buffer, "\n")] = 0;
		strcpy(buffer1,buffer);
		int a = 0;
		if(row==1){row++;continue;}
		token=strtok(buffer,",");
//		printf("new buffer is %s",buffer1);
		while(token!=NULL)
		{
			if(strcmp(inp1,token)==0) 
			{
				a=1;
				break;
			}
			else
				{token=strtok(NULL,",");}
		}
		if(a==1)
			{
//				printf("new buffer is %s",buffer);
				token1 = strtok(buffer1,",");
				while(token1!=NULL)
				{
					printf("|%s",token1);if(strlen(token1)<=7) printf("\t\t|");else printf("\t|");
					token1=strtok(NULL,",");
				}
				printf("\n");
			}
		row++;
	}
	fclose(fp);
	return;
}

int COL()
{
	static char tt[50],dr[50];
	char* token;
	char *buffer = NULL;
	buffer = (char *) malloc(sizeof(char) * 50);
	int count = 1,status=0;
	printf("Enter columns to print: \n");
    fseek(fp,0,SEEK_SET);
	fgets(dr,50,fp);
    token=strtok(dr,",");
    int i=1;
    printf("(");
	while(token!=NULL)
	{
		if(i%2!=0) 
		{
			printf("%s",token);
			token=strtok(NULL,",");
			if(token!=NULL) printf(",");
		}
		else token=strtok(NULL,",");
		i++;
	}
	printf("\b");
	printf(")\n");
    scanf("%s",&tt);
	fseek(fp, 0, SEEK_SET);
	fgets(buffer,50,fp);
	token=strtok(buffer,";");
	strcpy(buffer,token);
	token=strtok(buffer,",");
	while(token!=NULL)
	{
		if(strcmp(token,tt)==0)
		{		
			printf("\nColumn number is %d\n",count);
			status=1;
			break;
		}
		else count++;
		token=strtok(NULL,",");
		token=strtok(NULL,",");
	}
	if(status==0) {printf("\nColumn not found");return 0;}
	return count;
}

void Format(int col)
{
	printf("Rows matched: \n");
	char c[100];
	char* token;
	int i=0,flag, bit,counter=1;
	flag=1;
	bit=16*col;
	while(bit>=0){
		if(flag==1) {
		printf("\n");flag=0;bit--;}
		printf("=");bit--;}
	printf("=\n");
	fseek(fp,0,SEEK_SET);
	while(fgets(c,100,fp)!= NULL&&i==0)
	{	
		c[strcspn(c, "\n")] = 0;
		token=strtok(c,",");
		while(token!=NULL)
		{
			if(counter%2==0 && i==0) {counter++;token=strtok(NULL,","); continue;}
			else
			{ 
				printf("|%s",token);
				if(strlen(token)<=7) printf("\t\t|");
				else printf("\t|");
				token=strtok(NULL,",");
				counter++;
			}
		}
		if(i==0){
		flag=1;
		bit=16*col;
		while(bit>=0){
			if(flag==1) {
			printf("\n");flag=0;bit--;}
			printf("=");bit--;}
		printf("=");
		}
		if(feof(fp)==0)printf("\n");
		i=1;
	}
}

void ROW(int count,int col)
{
	char kin[30];
	int bit;
	printf("Enter the value to display\n");	
	scanf("%s",&kin);
	printf("Rows matched: \n");
	Format(col);
	select_by_row_value(kin,count);
	bit=16*col;
	while(bit>=0){
		printf("=");bit--;} 
	return;
}

void ROW2(int count,int col)
{
	char kin1[30],kin2[30];
	int bit;
	printf("Enter the values to display\n");	
	scanf("%s%s",&kin1,&kin2);
	printf("Rows matched: \n");
	Format(col);
	select_by_row_value(kin1,count);
	select_by_row_value(kin2,count);
	bit=16*col;
	while(bit>=0){
		printf("=");bit--;}
	return ;
}

void select()
{
	char tb[50],tt[50],c[100];;
	char* token,word;
	char dr[50];
	int count=0,bit=0,counter=0,flag,choice,i;
	printf("Enter Table Name:");
	scanf("%s",&tb);
	strcat(tb,".txt");
	strcpy(dr,dir);
	strcat(dr,tb);
	if (access(dr,F_OK) != -1)
        fp=fopen(dr,"a+");
    else
        {printf("Table does not exist");return;}
    /*printf("Enter columns to print: \n");
    fgets(dr,50,fp);
    token=strtok(dr,",");
    int i=1;
    printf("(");
	while(token!=NULL)
	{
		if(i%2!=0) 
		{
			printf("%s",token);
			token=strtok(NULL,",");
			if(token!=NULL) printf(",");
		}
		else token=strtok(NULL,",");
		i++;
	}
	printf("\b");
	printf(")\n");
    scanf("%s",&tt);*/
    fseek(fp,0,SEEK_SET);
    fgets(tb,50,fp);
    fgets(tb,50,fp);
    token=strtok(tb,",");
	while(token!=NULL)
	{
		token=strtok(NULL,",");
		count++;
	}
	printf("\nSelect your query:\n\n1 - Select * from table\n2 - Select ___ from table\n3 - Select * from table where ___\n\nEnter Your Choice: ");
	scanf("%d",&choice);
    switch(choice)
	{
	case 1: goto Normal;
			break;
	case 2: selectCOL(COL());
			return;
			break;
	case 3: ROW(COL(),count);
			printf("\n\nDisplayed Successfully");
			return;
			break;
	case 4: ROW2(COL(),count);
			printf("\n\nDisplayed Successfully");
			return;
			break;
	default:printf("\nInvalid Query");
			return;
			break;
	}
	
Normal:
	flag=1;
	bit=16*count;
	while(bit>=0){
		if(flag==1) {
		printf("\n");flag=0;bit--;}
		printf("=");bit--;}
	printf("=\n");
	fseek(fp,0,SEEK_SET);
	while(fgets(c,100,fp)!= NULL)
	{	
		c[strcspn(c, "\n")] = 0;
		token=strtok(c,",");
		while(token!=NULL)
		{
			if(counter%2!=0 && i==0) {counter++;token=strtok(NULL,","); continue;}
			else
			{ 
				printf("|%s",token);
				if(strlen(token)<=6) printf("\t\t|");
				else printf("\t|");
				token=strtok(NULL,",");
				counter++;
			}
		}
		if(i==0){
		flag=1;
		bit=16*count;
		while(bit>=0){
			if(flag==1) {
			printf("\n");flag=0;bit--;}
			printf("=");bit--;}
		printf("=");
		}
		if(feof(fp)==0)printf("\n");
		i=1;
	}
	flag=1;
	bit=16*count;
	while(bit>=0){
		if(flag==1) {
		printf("\n");flag=0;bit--;}
		printf("=");bit--;}
	printf("=");
	printf("\n\nDisplayed Successfully");
	fclose(fp);
}

void drop()
{
	int status;
	char file_name[25],dr[25];
	printf("Enter table name:");
	scanf("%s",&file_name);
	strcpy(dr,dir);
	strcat(dr,file_name);
	strcat(dr,".txt");
	status=remove(dr);
	if (status == 0)
    	printf("%s table dropped successfully.\n", file_name);
	else
    	printf("Table does not exist\n");
}

void dropDB(){
	int status,i=0;
	char dname[25],drt[25],dt[25];
	printf("Enter database name:");
	scanf("%s",&dname);
	DIR *d;
    struct dirent *dr;
    d = opendir(dname);
    strcpy(drt,dname);
    strcat(drt,"/");
    strcpy(dt,drt);
    if (d)
    {
        while ((dr = readdir(d)) != NULL)
        {
			if(i>=2){remove(strcat(drt,dr->d_name));strcpy(drt,dt);}
			i++;
        }
        closedir(d);
    }
	status=rmdir(dname);
	if (status == 0)
    {
		printf("%s database dropped successfully\n", dname);
		if(strcmp(dir,dt)==0) {printf("Database changed to default");
		strcpy(dir,"default/");
		}
	}
	else
    	printf("Database does not exist\n");
}

void insert(){
	char tb[50];
	char inp[BUFFER_SIZE];
	char* token;
	char* word;
	char dr[20];
	FILE *fp1;
	printf("Enter Table Name:");
	scanf("%s",&tb);
	strcat(tb,".txt");
	strcpy(dr,dir);
	strcat(dr,tb);
	if (access(dr,F_OK) != -1)
        {fp=fopen(dr,"a");fp1=fopen(dr,"r");}
    else{
		printf("Table does not exist");return;}
    printf("Enter row: \n");
	char c[30];
    fgets(c,30,fp1);
    word=strtok(c,";");
    token=word;
    word=strtok(token,",");
    int i=1;
    printf("(");
	while(word!=NULL){
		if(i%2==0) 
		{
			printf("%s",word);
			word=strtok(NULL,",");
			if(word!=NULL) printf(",");
		}
		else word=strtok(NULL,",");
		i++;
	}
	printf(")");
	printf("\n");
    scanf("%s",&inp);
    //fgets(inp,BUFFER_SIZE,stdin);
    printf("\n");
    int status;
	//token= strtok(inp,"+");
	fputc('\n',fp);
	fputs(inp,fp);/*
	while (token != NULL) {
		printf("%s",token);
		status=fputs(token,fp);
	    token = strtok(NULL,"+");
	    if(token!=NULL) fputc(',',fp);
	}*/
	//fputc("\n",fp);
	//status=fputs(inp,fp);
	if(status>0) printf("\nRow Successfully Inserted");
	else {printf("\nRow Insertion Failed");fclose(fp);return;}
	fclose(fp);
}

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        //if (entry->d_type == DT_DIR) 
		{
            //char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            //snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            if(strcspn(entry->d_name, ".")==strlen(entry->d_name))
				printf("%*s[%s]\n", indent, "", entry->d_name);
            //listdir(path, indent + 2);
        } //else 
		{
            //printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) 
{
	mkdir("default");
	int choice=0;
	char str[50];
	char* string;
	while(1){
		printf("Minor DB\nCurrent DB: %s",dir);
	memset(str, 0, 50);
   printf("\nEnter Query:");
   fflush(stdin);
   scanf("%99[^\n]",&str);
   //fflush(stdin);
   //printf("%s",str);
   string=str;
   system("cls");
   if (strcmp(string, "use") == 0) 
        {
            setDB();
            
        } 
    else if (strcmp(string, "create new database") == 0)
        {
            createDB();
            
        }
    else if (strcmp(string, "create new table") == 0)
        {
            createTB();
            
        }
    else if (strcmp(string, "insert into table") == 0)
        {
            insert();
            
        }
    else if (strcmp(string, "display table") == 0)
        {
            select();
            
        }
    else if (strcmp(string, "drop table") == 0)
        {
            drop();
            
        }
    else if (strcmp(string, "drop database") == 0)
        {
            dropDB();
            
        }
    else if (strcmp(string, "show tables") == 0)
        {
            show();
            
        }
    else if (strcmp(string, "show databases") == 0)
        {
            listdir(".",0);
            
        }
    else if (strcmp(string, "exit") == 0)
        {
            printf("Goodbye!");
            exit(0);
        }
    else /* default: */
        {
            printf("\n\nInvalid Query\n\n");
            
        }
    printf("\n\n");

   }
   return 0; 
}
