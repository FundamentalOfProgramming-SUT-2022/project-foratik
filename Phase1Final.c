#include <stdio.h>
#include <string.h>
#include<direct.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fileapi.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>


#define max 10000
#define rootLocation "C:\\Users\\ASUS\\CLionProjects\\untitled\\cmake-build-debug\\root"
//#define rootLocation "D:\\root"

char clipBoard[max];
char treeOutput[max];
char ArmanOutput[max];


int main();

void backup(char filename[]){

    char file2[max];

    memset(file2,'\0',sizeof (file2));
    file2[0]='.';

    if((int)filename[strlen(filename)-1]==32) filename[strlen(filename)-1]='\0';

    strcat(file2,filename);
    file2[strlen(file2)]='t';

    FILE *fptr1, *fptr2;
    fptr1 = fopen(filename, "r");
    //printf("error: %s\n", strerror(errno));
    if(access(file2, F_OK) == 0)    SetFileAttributes(file2, FILE_ATTRIBUTE_NORMAL);
    fptr2 = fopen(file2, "w+");
    //printf("error: %s\n", strerror(errno));
    char c;
    c = fgetc(fptr1);
    while (c != EOF)
    {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }
    fclose(fptr1);
    fclose(fptr2);
    SetFileAttributes(file2, FILE_ATTRIBUTE_HIDDEN);


}

void createFile(){
    chdir(rootLocation);
    char trash[max];
    char address[max];
    char folder[max];

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^\n]s",&address);



    memset(folder,'\0',sizeof (folder));

    int j=0;


    for(int i=0;i< strlen(address);i++){
        if(address[i]!='/'){
            folder[j]=address[i];
            j++;
        }
        else{
            j=0;
            mkdir(folder);
            chdir(folder);
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){
            if(folder[j-1]=='"') folder[j-1]='\0';

            if(access(folder, F_OK) == 0){
                printf("\nYour file is already existing!\n");
            }
            else{
                FILE *a;
                a=fopen(folder,"w");
                printf("\nYour file created successfully!\n");
                fclose(a);
            }
        }
    }
    chdir(rootLocation);
}

void insertstr2(char address[],char string[],int line,int charNum){


    char folder[max];
    memset(folder,'\0',sizeof (folder));
    for(int i=0;i<strlen(string)-1;i++){
        if((int)string[i]==92){
            if(((int)string[i-1]!=92)&&(string[i+1]=='n')){
                string[i]='\n';
                for(int m=i+1;m <strlen(string);m++){
                    string[m]=string[m+1];
                }
            }
            if(((int)string[i-1]==92)&&(string[i+1]=='n')){
                for(int m=i-1;m <strlen(string);m++){
                    string[m]=string[m+1];
                }
            }
        }
    }

    int j=0;

    for(int i=0;i< strlen(address);i++){
        if(address[i]!='/'){
            if(address[i]!='"') {
                folder[j] = address[i];
                j++;
            }
        }
        else{
            j=0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){

            if(access(folder, F_OK) != 0){
                printf("\nYour file is NOT existing!\n");
            }
            else{

                backup(folder);


                FILE *myFile;

                myFile=fopen(folder,"r");

                int lineNumber = 0;
                int c;
                int count=0;

                char edame[max];
                memset(edame,'\0',sizeof (edame));

                while(1) {

                    if( feof(myFile) ) {
                        break;
                    }

                    if(c=='\n'){
                        count++;
                        lineNumber++;
                    }

                    if(lineNumber==line-1){

                        for(int i=0;i<charNum;i++){
                            c = fgetc(myFile);
                        }
                        for(int i=0;1;i++){
                            if( feof(myFile) ) {
                                break;
                            }
                            edame[i]= fgetc(myFile);
                        }

                        break;
                    }
                    if(line!=1) {
                        c = fgetc(myFile);
                        count++;
                    }
                }
                fclose(myFile);

                myFile=fopen(folder,"r+");


                if((int)string[strlen(string)-1]==32) string[strlen(string)-1]='\0';
                if((int)string[strlen(string)-1]==34) string[strlen(string)-1]='\0';
                if((int)string[0]==34){

                    char newSTR[max];
                    for(int i=1;i<= strlen(string)+1;i++) newSTR[i-1]=string[i];
                    strcpy(string,newSTR);

                }


                strcat(string,edame);


                string[strlen(string)-1]='\0';
                if(lineNumber==line-1){
                    fseek(myFile,count+charNum,SEEK_SET);
                    fprintf(myFile,"%s",string);
                    printf("String added :)\n");
                }

                if(lineNumber<line-1){
                    for(int i=1;i<line-lineNumber;i++){
                        fseek(myFile,0,SEEK_END);
                        fprintf(myFile,"\n");
                    }
                    fseek(myFile,charNum,SEEK_END);
                    fprintf(myFile,"%s",string);
                    fprintf(myFile,"%c",string[strlen(string)-1]);
                    printf("String added :)\n");
                }
                fclose(myFile);

            }
        }
    }
    chdir(rootLocation);


}

void insertstr3(){

    chdir(rootLocation);
    char trash[max];
    char address[max];

    char string[max];
    int line;
    int charNum;

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s",&address);
    scanf("--pos %d:%d",&line,&charNum);

    insertstr2(address,ArmanOutput,line,charNum);

}

void insertstr(){

    chdir(rootLocation);
    char trash[max];
    char address[max];

    char string[max];
    int line;
    int charNum;

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s",&address);
    scanf("--str %[^-]s",&string);
    scanf("--pos %d:%d",&line,&charNum);

    insertstr2(address,string,line,charNum);

}




void cat2(int check){

    chdir(rootLocation);
    char trash[max];
    char address[max];
    char folder[max];

    int cnt=0;

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    if(check==0) scanf("/root/%[^\n]s",&address);
    if(check==1) scanf("/root/%[^=]s",&address);

    memset(folder,'\0',sizeof (folder));
    memset(ArmanOutput,'\0',sizeof (ArmanOutput));

    int j=0;

    for(int i=0;i< strlen(address);i++){
        if(address[i]!='/'){
            if(address[i]!='"') {
                folder[j] = address[i];
                j++;
            }
        }
        else{
            j=0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){

            if(access(folder, F_OK) != 0){
                printf("\nYour file is NOT existing!\n");
                printf("%s\n",folder);
                return;
            }
            else{

                FILE *myFile;

                myFile=fopen(folder,"r");

                int c;

                while(1) {
                    c = fgetc(myFile);
                    if( feof(myFile) ) {
                        break;
                    }

                    ArmanOutput[cnt++]=c;
                }
                fclose(myFile);
            }
        }
    }
    chdir(rootLocation);
}

void cat(){
    cat2(0);
    printf("%s\n",ArmanOutput);
}

void removeStr2(char address[],int line,int charNum,int size,char type){

    char folder[max];

    memset(folder, '\0', sizeof(folder));

    int j = 0;

    for (int i = 0; i < strlen(address); i++) {
        if (address[i] != '/') {
            if (address[i] != '"') {
                folder[j] = address[i];
                j++;
            }
        } else {
            j = 0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder, '\0', sizeof(folder));
        }
        if (i == strlen(address) - 1) {
            if ((int) folder[strlen(folder) - 1] == 32) folder[strlen(folder) - 1] = '\0';

            if (access(folder, F_OK) != 0) {
                printf("\nYour file is NOT existing!\n");
            } else {
                backup(folder);

                if(type=='b'){
                    FILE *myFile;

                    myFile = fopen(folder, "r");

                    int lineNumber = 0;
                    int c;
                    int count = 0;

                    char edame[max];
                    memset(edame, '\0', sizeof(edame));

                    while (1) {

                        if(line!=1) c = fgetc(myFile);

                        if (feof(myFile)) {
                            break;
                        }

                        if (c == '\n') lineNumber++;

                        if (lineNumber == line - 1) {

                            edame[count]='\n';
                            count++;

                            for (int i = 0; i < charNum; i++) {
                                c = fgetc(myFile);
                                edame[count] = c;
                                count++;
                            }
                            for (int i = 0; i < size; i++) {
                                edame[count-1]='\0';
                                count--;
                            }
                            for (int i = count; 1; i++) {
                                if (feof(myFile)) {
                                    break;
                                }
                                edame[i] = fgetc(myFile);
                                count++;
                            }

                            break;
                        }

                        edame[count] = c;
                        count++;
                    }
                    fclose(myFile);
                    myFile = fopen(folder, "w+");
                    edame[strlen(edame) - 1] = '\0';
                    if (lineNumber == line - 1) {
                        fseek(myFile, 0, SEEK_SET);
                        fprintf(myFile,"%s", edame);
                        printf("String removed :)\n");
                    }
                    fclose(myFile);
                }

                if (type == 'f') {

                    FILE *myFile;

                    myFile = fopen(folder, "r");

                    int lineNumber = 0;
                    int c;
                    int count = 0;

                    char edame[max];
                    memset(edame, '\0', sizeof(edame));

                    while (1) {
                        if(line!=1)
                            c = fgetc(myFile);
                        if (feof(myFile)) {
                            break;
                        }
                        if (c == '\n') lineNumber++;

                        if (lineNumber == line - 1) {

                            if(line!=1){
                                edame[count]='\n';
                                count++;
                            }

                            for (int i = 0; i < charNum; i++) {
                                c = fgetc(myFile);
                                edame[count] = c;
                                count++;
                            }
                            for (int i = 0; i < size; i++) {
                                c = fgetc(myFile);
                            }
                            for (int i = count; 1; i++) {
                                if (feof(myFile)) {
                                    break;
                                }
                                edame[i] = fgetc(myFile);
                                count++;
                            }

                            break;
                        }
                        edame[count] = c;
                        count++;


                    }
                    fclose(myFile);
                    myFile = fopen(folder, "w+");
                    edame[strlen(edame) - 1] = '\0';
                    if (lineNumber == line - 1) {
                        fseek(myFile, 0, SEEK_SET);
                        fprintf(myFile,"%s", edame);
                        printf("String removed :)\n");
                    }
                    fclose(myFile);
                }
            }

        }
    }

}

void removeStr() {

    chdir(rootLocation);
    char trash[max];
    char address[max];

    int line, charNum, size;
    char type;

    scanf("%[^/]s", &trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s", &address);
    scanf("--pos %d:%d -size %d -%c", &line, &charNum, &size, &type);

    removeStr2(address,line,charNum,size,type);


}


void copyStr2(char address[],int line,int charNum,int size,char type){

    char folder[max];
    memset(folder, '\0', sizeof(folder));
    memset(clipBoard,'\0',sizeof (clipBoard));

    int j = 0;

    for (int i = 0; i < strlen(address); i++) {
        if (address[i] != '/') {
            if (address[i] != '"') {
                folder[j] = address[i];
                j++;
            }
        } else {
            j = 0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder, '\0', sizeof(folder));
        }
        if (i == strlen(address) - 1) {
            if ((int) folder[strlen(folder) - 1] == 32) folder[strlen(folder) - 1] = '\0';

            if (fopen(folder, "r") == NULL) {
                printf("\nYour file is NOT existing!\n");
            } else {
                //backup(folder);
                if(type=='b'){
                    FILE *myFile;

                    myFile = fopen(folder, "r");

                    int lineNumber = 0;
                    int c;
                    int count = 0;

                    char edame[max];
                    memset(edame, '\0', sizeof(edame));

                    while (1) {

                        if(line!=1) c = fgetc(myFile);

                        if (feof(myFile)) {
                            break;
                        }

                        if (c == '\n') lineNumber++;

                        if (lineNumber == line - 1) {

                            edame[count]='\n';
                            count++;

                            for (int i = 0; i < charNum; i++) {
                                c = fgetc(myFile);
                                edame[count] = c;
                                count++;
                            }
                            //printf("edame:%s",edame);
                            for (int i = size-1; i >=0 ; i--) {
                                clipBoard[i]=edame[count-1];
                                //printf("%c\n\n",edame[count-1]);
                                //edame[count-1]='\0';
                                --count;
                            }
                            for (int i = count; 1; i++) {
                                if (feof(myFile)) {
                                    break;
                                }
                                edame[i] = fgetc(myFile);
                                count++;
                            }

                            break;
                        }
                        edame[count] = c;
                        count++;

                    }
                    fclose(myFile);
                }

                if (type == 'f') {

                    FILE *myFile;

                    myFile = fopen(folder, "r");

                    int lineNumber = 0;
                    int c;
                    int count = 0;

                    char edame[max];
                    memset(edame, '\0', sizeof(edame));

                    while (1) {
                        if(line!=1)
                            c = fgetc(myFile);
                        if (feof(myFile)) {
                            break;
                        }
                        if (c == '\n') lineNumber++;

                        if (lineNumber == line - 1) {

                            if(line!=1){
                                edame[count]='\n';
                                count++;
                            }

                            for (int i = 0; i < charNum; i++) {
                                c = fgetc(myFile);
                                edame[count] = c;
                                count++;
                            }
                            for (int i = 0; i < size; i++) {
                                c = fgetc(myFile);
                                clipBoard[i]=c;
                            }
                            for (int i = count; 1; i++) {
                                if (feof(myFile)) {
                                    break;
                                }
                                edame[i] = fgetc(myFile);
                                count++;
                            }

                            break;
                        }
                        edame[count] = c;
                        count++;


                    }
                    fclose(myFile);
                }
                printf("The string \"%s\" copied to clipboard !\n" ,clipBoard);
            }

        }
    }
}


void copyStr(){

    chdir(rootLocation);
    char trash[max];
    char address[max];

    int line, charNum, size;
    char type;

    scanf("%[^/]s", &trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s", &address);
    scanf("--pos %d:%d -size %d -%c", &line, &charNum, &size, &type);

    copyStr2(address,line,charNum,size,type);


}


void cutstr(){
    chdir(rootLocation);
    char trash[max];
    char address[max];

    int line, charNum, size;
    char type;

    scanf("%[^/]s", &trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s", &address);
    scanf("--pos %d:%d -size %d -%c", &line, &charNum, &size, &type);

    copyStr2(address,line,charNum,size,type);
    removeStr2(address,line,charNum,size,type);
}

void pastestr(){

    chdir(rootLocation);
    char trash[max];
    char address[max];

    char string[max];
    int line;
    int charNum;

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s",&address);
    scanf("--pos %d:%d",&line,&charNum);

    insertstr2(address,clipBoard,line,charNum);

}


void autoIndent(){

        chdir(rootLocation);
        char trash[max];
        char address[max];
        char folder[max];
        char data[max];

        scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
        scanf("/root/%[^\n]s",&address);

        memset(folder,'\0',sizeof (folder));
        memset(data,'\0',sizeof (data));

        int j=0;

        int counter=0;

        for(int i=0;i< strlen(address);i++){
            if(address[i]!='/'){
                if(address[i]!='"') {
                    folder[j] = address[i];
                    j++;
                }
            }
            else{
                j=0;
                if (chdir(folder)!=NULL) {
                    printf("Folder doesn't exist.\n");
                    return ;
                }
                memset(folder,'\0',sizeof (folder));
            }
            if(i== strlen(address)-1){

                if(access(folder, F_OK) != 0){
                    printf("\nYour file is NOT existing!\n");
                }
                else{

                    backup(folder);

                    FILE *myFile;

                    myFile=fopen(folder,"r");

                    int c;

                    int open=0;

                    while(1) {
                        c = fgetc(myFile);
                        if( feof(myFile) ) {
                            break;
                        }
                        if(c==123){
                            open++;
                            if((data[counter-1]!=32)&&(data[counter-1]!=9)){
                                if(counter!=0)
                                data[counter++]=32;
                            }
                            else{
                                for(int i=counter-1;data[i]==32;i--){
                                    counter=i;
                                }
                                if(data[counter-1]!=9)  data[counter++]=32;
                            }
                            data[counter++]=c;
                            data[counter++]=10;
                            for(int i=0;i<open;i++){
                                data[counter++]=9;
                            }
                        }
                        else if(c==125){

                            data[counter++]=10;
                            for(int i=0;i<open;i++){
                                data[counter++]=9;
                            }
                            data[counter++]=c;
                            data[counter++]=10;
                            open--;
                        }
                        else{
                            data[counter++]=c;
                            if(c==10){
                                for(int i=0;i<open;i++){
                                    data[counter++]=9;
                                }
                            }
                        }

                    }
                    fclose(myFile);
                    //backup(folder);

                    myFile=fopen(folder,"w+");

                    fprintf(myFile,"%s",data);

                    fclose(myFile);
                    printf("Auto indent done successfully.\n");


                }
            }
        }
        chdir(rootLocation);
}

char grepString[max];

void grep(int mode,char string[]){

    chdir(rootLocation);
    char trash[max];
    char address[max];
    char folder[max];
    //char string[max];
    char line[max];
    int count=0;
    int cnt=0;

    getchar();getchar();
    char type=getchar();
    if(mode!=2)
    {
        if(type=='-'){
            scanf("str %[^-]s", string);
        } else if(type=='c'){
            getchar();
            scanf("--str %[^-]s", string);
        } else if(type=='l'){
            getchar();
            scanf("--str %[^-]s", string);
        }
    }

    {
        if(string[strlen(string)-1]==32) string[strlen(string)-1]='\0';

        memset(ArmanOutput,'\0',sizeof (ArmanOutput));

        scanf("%[^/]s", &trash);
        while(1) {

            memset(address,'\0',sizeof (address));
            memset(folder,'\0',sizeof (folder));

            scanf("/root/%[^|]s", &address);
            if(address[strlen(address)-1]==32)  address[strlen(address)-1]='\0';

            chdir(rootLocation);
            int j=0;
            for(int i=0;i< strlen(address);i++){
                if(address[i]!='/'){
                    if(address[i]!='"') {
                        folder[j] = address[i];
                        j++;
                    }
                }
                else{
                    j=0;
                    if (chdir(folder)!=NULL) {
                        printf("Folder doesn't exist.\n");
                        return ;
                    }
                    memset(folder,'\0',sizeof (folder));
                }
                if(i== strlen(address)-1){

                    if(access(folder, F_OK) != 0){
                        if(mode==0) printf("\nYour file is NOT existing!\n");
                        strcat(ArmanOutput,"\nYour file is NOT existing!\n");
                    }
                    else{

                        FILE *myFile;

                        myFile=fopen(folder,"r");

                        int c;

                        memset(line,'\0',sizeof (line));

                        int w=0;

                        while(1) {
                            c = fgetc(myFile);
                            if( feof(myFile) ) {
                                break;
                            }
                            //printf("%c", c);

                            if(c!=10){
                                line[w++]=c;
                            } else{
                                if(strstr(line,string)!=NULL){
                                    count++;
                                    if(type=='-') {
                                        strcat(ArmanOutput, line);
                                        strcat(ArmanOutput, "\n");
                                        if (mode == 0) printf("%s\n", line);
                                    }
                                    if(type=='l'){
                                        strcat(ArmanOutput,folder);
                                        strcat(ArmanOutput, "\n");
                                        if(mode==0) printf("%s\n",folder);
                                        break;
                                    }
                                }
                                w=0;
                                memset(line,'\0',sizeof (line));
                            }
                        }
                        //printf("\n");
                        fclose(myFile);
                    }
                }
            }
            chdir(rootLocation);

            //printf("%s\n",address);
            getchar();
            int end=getchar();
            if(end==10) break;

        }
    }
    if(type=='c') printf("String found %d times.\n",count);

}


void compare(){

    chdir(rootLocation);
    char trash[max];
    char address[max];
    char address2[max];
    char folder[max],folder2[max];
    char line1[max],line2[max];
    char data1[max],data2[max];
    int l1=1,l2=1;

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^|]s",&address);
    scanf("| /root/%[^\n]s",&address2);



    memset(folder,'\0',sizeof (folder));
    memset(folder2,'\0',sizeof (folder2));

    int j=0;

    for(int i=0;i< strlen(address);i++){
        if(address[i]!='/'){
            if(address[i]!='"') {
                folder[j] = address[i];
                j++;
            }
        }
        else{
            j=0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){

            if(access(folder, F_OK) != 0){
                printf("\nYour first file is NOT existing!\n");
            }
            else{

                int j=0;

                for(int i=0;i< strlen(address2);i++){
                    if(address2[i]!='/'){
                        if(address2[i]!='"') {
                            folder2[j] = address2[i];
                            j++;
                        }
                    }
                    else{
                        j=0;
                        chdir(folder2);
                        memset(folder2,'\0',sizeof (folder2));
                    }
                    if(i== strlen(address2)-1){

                        if(access(folder2, F_OK) != 0){
                            printf("\nYour Second file is NOT existing!\n");
                        }
                        else{

                            FILE *myFile;
                            FILE *myFile2;

                            myFile=fopen(folder,"r");
                            myFile2=fopen(folder2,"r");

                            fscanf(myFile,"%[^EOF]s",&data1);
                            fscanf(myFile2,"%[^EOF]s",&data2);

                            for(int i=0;i< strlen(data1);i++){
                                if(data1[i]=='\n') l1++;
                            }
                            for(int i=0;i< strlen(data2);i++){
                                if(data2[i]=='\n') l2++;
                            }

                            fclose(myFile);
                            fclose(myFile2);

                            myFile=fopen(folder,"r");
                            myFile2=fopen(folder2,"r");


                            for(int i=1;i<=min(l1,l2);i++){
                                fgets(line1,sizeof (line1),myFile);
                                fgets(line2,sizeof (line2),myFile2);

                                if(strcmp(line1,line2)!=0){
                                    printf("\n============ #%d ============\n",i);
                                    printf("\nLine from file 1 : %s",line1);
                                    printf("\nLine from file 2 : %s",line2);
                                }
                            }
                            if(l1!=l2){
                                int mx=l2;
                                if(l1>l2) mx=l1;
                                printf("\n>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",min(l1,l2)+1,mx);
                                if(l1>l2){
                                    for(int i=min(l1,l2)+1;i<=mx;i++){
                                        fgets(line1,sizeof (line1),myFile);
                                        printf("Line from file 1 : %s",line1);
                                    }
                                }else{
                                    for(int i=min(l1,l2)+1;i<=mx;i++){
                                        fgets(line2,sizeof (line2),myFile2);
                                        printf("Line from file 2 : %s",line2);
                                    }
                                }
                            }
                            /*

                            //fscanf(myFile,"%[^EOF]s",&data1);
                            //fscanf(myFile2,"%[^EOF]s",&data2);

                            for(int i=0;i< strlen(data1);i++){
                                if(data1[i]=='\n') l1++;
                            }
                            for(int i=0;i< strlen(data2);i++){
                                if(data2[i]=='\n') l2++;
                            }

                            fgets(line1,sizeof (line1),myFile);
                            fgets(line2,sizeof (line2),myFile2);

                            printf("%s\n%s\n",line1,line2);

                            fgets(line1,sizeof (line1),myFile);
                            fgets(line2,sizeof (line2),myFile2);

                            printf("%s\n%s\n",line1,line2);
*/


                            fclose(myFile);
                            fclose(myFile2);

                        }
                    }
                }
            }
        }
    }
    chdir(rootLocation);

}

void undo(){

    chdir(rootLocation);
    char trash[max];
    char address[max];
    char folder[max];

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^\n]s",&address);


    memset(folder,'\0',sizeof (folder));

    int j=0;

    for(int i=0;i< strlen(address);i++){
        if(address[i]!='/'){
            if(address[i]!='"') {
                folder[j] = address[i];
                j++;
            }
        }
        else{
            j=0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){


            if(access(folder, F_OK) != 0){
                printf("\nYour file is NOT existing!\n");
            }
            else{

                char temp[max];
                memset(temp,'\0',sizeof (temp));
                temp[0]='.';
                strcat(temp,folder);
                //printf("%s\n%s\n\n",temp,folder);
                temp[strlen(temp)]='t';
                SetFileAttributes(temp, FILE_ATTRIBUTE_NORMAL);
                if(access(temp, F_OK) != 0){
                    printf("%s\n",temp);
                    printf("\nPrevious version is not existing!\n");
                    return;
                }


                rename(temp,"temp name");
                //printf("error: %s\n", strerror(errno));
                rename(folder,temp);
                //printf("error: %s\n", strerror(errno));
                rename("temp name",folder);
                //printf("error: %s\n", strerror(errno));
                SetFileAttributes(temp, FILE_ATTRIBUTE_HIDDEN);
                printf("File changed to previous version\n");

            }
        }
    }
    chdir(rootLocation);
}

void find2(char address[],char string[],char type,int m){

    char folder[max];
    char data[max];
    int count=0;


    if((int)string[strlen(string)-1]==32) string[strlen(string)-1]='\0';


    memset(folder,'\0',sizeof (folder));
    memset(data,'\0',sizeof (data));

    int j=0;

    for(int i=0;i< strlen(address);i++){
        if(address[i]!='/'){
            if(address[i]!='"') {
                folder[j] = address[i];
                j++;
            }
        }
        else{
            j=0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){

            if(access(folder, F_OK) != 0){
                printf("\nYour file is NOT existing!\n");
            }
            else{

                FILE *myFile;

                myFile=fopen(folder,"r");

                int c;
                int w=0;

                while(1) {
                    c = fgetc(myFile);
                    if( feof(myFile) ) {
                        break;
                    }
                    data[w++]=c;
                }
                fclose(myFile);

                int tmp=0;
                for(int i=0;i< strlen(string);i++){
                    if(string[i]=='*'){
                        if(i==0){
                            tmp=1;
                            break;
                        }
                        if(string[i-1]!='\\') {
                            tmp = 1;
                            break;
                        }else{
                            memmove(&string[i-1], &string[i], strlen(string) - i+1);
                        }
                    }
                }

                if(tmp==0) { // without wildcard
                    if(strstr(data,string)==NULL){
                        printf("Your string is not existing in the file.\n");
                        return;
                    } else {
                        for (int i = 0; i < strlen(data); i++) {
                            if(data[i]== string[0]){
                                if(strlen(string)==1){
                                    count++;
                                    if(type=='n'){
                                        printf("%d\n",i);
                                        return;
                                    }
                                }
                                for(int k=1;k< strlen(string);k++){
                                    if(data[i+k]!= string[k]) break;
                                    if(k== strlen(string)-1){
                                        count++;
                                        if(type=='n'){
                                            printf("%d\n",i);
                                            return;
                                        }
                                        else if(type=='b'){
                                            int space=1;
                                            for(int h=0;h<i;h++){
                                                if((int)data[h]==32) space++;
                                                if((int)data[h]==10) space++;
                                            }
                                            printf("%d\n",space);
                                            return;
                                        }
                                        else if(type=='k'){
                                            int space=1;
                                            for(int h=0;h<i;h++){
                                                if((int)data[h]==32) space++;
                                                if((int)data[h]==32) space++;
                                            }
                                            printf("%d\n",space);
                                        } else if(type=='t'){
                                            if(count==m){
                                                printf("%d\n",i);
                                                return;
                                            }
                                        } else if(type=='a'){
                                            printf("%d\n",i);
                                        } else if(type=='w'){
                                            if(count==m){
                                                int space=1;
                                                for(int h=0;h<i;h++){
                                                    if((int)data[h]==32) space++;
                                                    if((int)data[h]==32) space++;
                                                }
                                                printf("%d\n",space);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(type=='c') printf("%d\n",count);
                    }
                }

                if(tmp==1){//with wildcard
                    int start;
                    int q=0;
                    int star=0;
                    int last=-1;
                    for(int i=0;i< strlen(data);i++){

                        if((int)string[q]==42){
                            if(q==0) start=i;
                            star=1;
                            q++;
                        }
                        if((string[q]=='\0')&&(star==1)){
                            if(((int)data[i]!=32)&&((int)data[i]!=10)){
                                if((int)string[q-1]==42) last=i;
                                if(data[i-1]== string[q-1]) {
                                    last = i-1;
                                }
                            }else{ //found
                               // printf("%d %d\n",start,last);
                                count++;
                                if(type=='n'){
                                    printf("%d\n",start);
                                    return;
                                }
                                else if(type=='b'){
                                    int space=1;
                                    for(int h=0;h<i;h++){
                                        if((int)data[h]==32) space++;
                                        if((int)data[h]==10) space++;
                                    }
                                    printf("%d\n",space);
                                    return;
                                }
                                else if(type=='k'){
                                    int space=1;
                                    for(int h=0;h<start;h++){
                                        if((int)data[h]==32) space++;
                                        if((int)data[h]==32) space++;
                                    }
                                    printf("%d\n",space);
                                } else if(type=='t'){
                                    if(count==m){
                                        printf("%d\n",start);
                                        return;
                                    }
                                } else if(type=='a'){
                                    printf("%d\n",start);
                                } else if(type=='w'){
                                    if(count==m){
                                        int space=1;
                                        for(int h=0;h<start;h++){
                                            if((int)data[h]==32) space++;
                                            if((int)data[h]==32) space++;
                                        }
                                        printf("%d\n",space);
                                    }
                                }


                                star=0;
                                q=0;

                            }
                        }
                        if(((int)data[i]==32)||((int)data[i]==10)){
                            if((int)string[q]!=32){
                                q=0;
                            }
                        }
                        if(data[i]==string[q]){
                            if(q==0) start=i;
                            last=i;
                            q++;
                        }


                    }
                    if(last==-1) {
                        printf("Your string is not existing in the file.\n");
                        return;
                    }
                    if(type=='c') printf("%d\n",count);
                }

            }
        }
    }
    chdir(rootLocation);
}

void find(){
    chdir(rootLocation);
    char trash[max];
    char address[max];
    char string[max];
    char type = 'n';//n=none , c=count , t=at , b=byword , k=all byword ,a=all , w=at byword

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s",&address);
    scanf("--str %[^-]s",&string);
    scanf("-%c",&type);
    int m=-1;

    if(type=='t'){
        scanf("%d",&m);
    }

    find2(address,string,type,m);
}

void find3(){
    chdir(rootLocation);
    char trash[max];
    char address[max];
    char type = 'n';//n=none , c=count , t=at , b=byword , k=all byword ,a=all , w=at byword

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s",&address);
    scanf("-%c",&type);
    int m=-1;

    if(type=='t'){
        scanf("%d",&m);
    }

    find2(address,ArmanOutput,type,m);
}

void Replace(int start,int end,char string[],char data[]){

    char tmp[max];

    memset(tmp,'\0',sizeof (tmp));
    for(int i=end+1;i< strlen(data);i++){
        tmp[i-end-1]=data[i];
    }
    for(int i=start;i< strlen(data);i++){
        data[i]='\0';
    }
    strcat(data,string);
    strcat(data,tmp);

}

void replace(){

    chdir(rootLocation);
    char trash[max];
    char address[max];
    char folder[max];
    char string[max],data[max],newString[max],result[max][2];
    int count=0,resultCounter=0;
    char type = 'n';//n=none , c=count , t=at , b=byword , k=all byword ,a=all , w=at byword
    int m;

    scanf("%[^/]s",&trash);//Scans untill "/" and move to trash
    scanf("/root/%[^-]s",&address);
    scanf("--str1 %[^-]s",&string);
    scanf("--str2 %[^-]s",&newString);
    scanf("-a%c",&type);
    if(type=='t'){
        scanf("%d",&m);
    } else if (type!='l'){
        printf("Your input is invalid.\n");
        return;
    }

    if((int)string[strlen(string)-1]==32) string[strlen(string)-1]='\0';
    if((int)newString[strlen(newString)-1]==32) newString[strlen(newString)-1]='\0';

    //int deltaSize= strlen(newString)- strlen(string); //not working properly for wildcard.

    memset(folder,'\0',sizeof (folder));
    memset(data,'\0',sizeof (data));

    int j=0;

    for(int i=0;i< strlen(address);i++){
        if(address[i]!='/'){
            if(address[i]!='"') {
                folder[j] = address[i];
                j++;
            }
        }
        else{
            j=0;
            if (chdir(folder)!=NULL) {
                printf("Folder doesn't exist.\n");
                return ;
            }
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){

            if(access(folder, F_OK) != 0){
                printf("\nYour file is NOT existing!\n");
            }
            else{

                backup(folder);

                FILE *myFile;

                myFile=fopen(folder,"r");

                int c;
                int w=0;

                while(1) {
                    c = fgetc(myFile);
                    if( feof(myFile) ) {
                        break;
                    }
                    data[w++]=c;
                }
                fclose(myFile);

                int tmp=0;
                for(int i=0;i< strlen(string);i++){
                    if(string[i]=='*'){
                        if(i==0){
                            tmp=1;
                            break;
                        }
                        if(string[i-1]!='\\') {
                            tmp = 1;
                            break;
                        }else{
                            memmove(&string[i-1], &string[i], strlen(string) - i+1);
                        }
                    }
                }

                if(tmp==0) { // without wildcard
                    int last=-1;
                    if(strstr(data,string)==NULL){
                        printf("Your string is not existing in the file.\n");
                        return;
                    } else {
                        for (int i = 0; i < strlen(data); i++) {
                            if(data[i]== string[0]){
                                if(strlen(string)==1){
                                    count++;
                                    last=i;
                                    result[resultCounter][0]=i;
                                    result[resultCounter++][1]=last;

                                }
                                for(int k=1;k< strlen(string);k++){
                                    if(data[i+k]!= string[k]) break;
                                    if(k== strlen(string)-1){
                                        count++;
                                        last=i+ strlen(string)-1;
                                        result[resultCounter][0]=i;
                                        result[resultCounter++][1]=last;
                                    }
                                }
                            }
                        }
                    }
                }

                if(tmp==1){//with wildcard
                    int start;
                    int q=0;
                    int star=0;
                    int last=-1;
                    for(int i=0;i< strlen(data);i++){

                        if((int)string[q]==42){
                            if(q==0) start=i;
                            star=1;
                            q++;
                        }
                        if((string[q]=='\0')&&(star==1)){
                            if(((int)data[i]!=32)&&((int)data[i]!=10)){
                                if((int)string[q-1]==42) last=i;
                                if(data[i-1]== string[q-1]) {
                                    last = i-1;
                                }
                            }else{ //found
                                //printf("%d %d\n",start,last);

                                result[resultCounter][0]=start;
                                result[resultCounter++][1]=last;

                                star=0;
                                q=0;

                            }
                        }
                        if(((int)data[i]==32)||((int)data[i]==10)){
                            if((int)string[q]!=32){
                                q=0;
                            }
                        }
                        if(data[i]==string[q]){
                            if(q==0) start=i;
                            last=i;
                            q++;
                        }


                    }
                    if(last==-1) {
                        printf("Your string is not existing in the file.\n");
                        return;
                    }
                }

            }
        }
    }


    int deltaSize= strlen(newString)- (result[0][1]-result[0][0]+1);
    //printf("delta : %d\n",deltaSize);

    if(type=='t'){
        if(m>=resultCounter){
            printf("Invalid number !\n");
            return;
        }
        Replace(result[m-1][0],result[m-1][1],newString,data);

    } else if(type=='l'){
        for(int i=0;i<resultCounter;i++){
            //printf("%d %d\n",result[i][0]+deltaSize*i,result[i][1]+deltaSize*i);
            Replace(result[i][0]+deltaSize*i,result[i][1]+deltaSize*i,newString,data);
        }

    }
    //printf("%s\n",data);

    FILE *new;
    new= fopen(folder,"w+");
    fprintf(new,"%s",data);
    fclose(new);
    printf("Replace done successfully.\n");


    chdir(rootLocation);

}

void RecursiveTree (char *basePath, const int root,int depth)
{


    if(root==2+2*depth){
        return;
    }

    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++)
            {
                if (i%2 == 0 || i == 0)
                    strcat(treeOutput,"|");
                else
                    strcat(treeOutput," ");
            }


            if(dp->d_name[0]!='.') {
                strcat(treeOutput, "|-");
                strcat(treeOutput, "-");
                strcat(treeOutput, dp->d_name);
                strcat(treeOutput, "\n");
            }


            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            RecursiveTree(path, root + 2,depth);
        }
    }

    closedir(dir);
}


void tree2(){

    int depth;
    scanf("%d",&depth);

    if(depth<0){
        printf("Invalid depth.\n");
        return;
    }

    memset(treeOutput,'\0',sizeof (treeOutput));
    treeOutput[0]='\n';
    RecursiveTree(rootLocation,0,depth);
}


void tree(){

    int depth;
    scanf("%d",&depth);
    if(depth<0){
        printf("Invalid depth.\n");
        return;
    }

    memset(treeOutput,'\0',sizeof (treeOutput));
    treeOutput[0]='\n';
    RecursiveTree(rootLocation,0,depth);
    printf("%s\n",treeOutput);
}



void arman2(char func[]){
    if (strcmp(func, "insertstr") == 0){
        insertstr3();
    } else  if (strcmp(func, "find") == 0){
        find3();
    } else if (strcmp(func,"grep")==0){
        grep(2,ArmanOutput);
    }
}

void arman(){

    char func[max];
    memset(func,'\0',sizeof (max));
    scanf("%s",func);
    if (strcmp(func, "cat") == 0) {
        cat2(1);

    } else if (strcmp(func, "tree") == 0){
        tree2();
        memset(ArmanOutput,'\0',sizeof (ArmanOutput));
        strcpy(ArmanOutput,treeOutput);

    } else if (strcmp(func, "grep") == 0){
        grep(1,grepString);
    } else {
        printf("Invalid command\n");
        return;
    }
    char trash[max];
    memset(func,'\0',sizeof (func));
    scanf("%s %s",trash,func);
    arman2(func);
}


int main() {
    char function[max];

    chdir(rootLocation);


    while(1) {
        memset(grepString,'\0',sizeof (grepString));
        scanf("%s", &function);
        if (strcmp(function, "createfile") == 0) createFile();
        else if (strcmp(function, "insertstr") == 0) insertstr();
        else if (strcmp(function, "cat") == 0) cat();
        else if (strcmp(function, "removestr") == 0) removeStr();
        else if (strcmp(function, "copystr") == 0) copyStr();
        else if (strcmp(function, "cutstr") == 0) cutstr();
        else if (strcmp(function, "pastestr") == 0) pastestr();
        else if (strcmp(function, "auto-indent") == 0) autoIndent();
        else if (strcmp(function, "compare") == 0) compare();
        else if (strcmp(function, "grep") == 0) grep(0,grepString);
        else if (strcmp(function, "undo") == 0) undo();
        else if (strcmp(function, "find") == 0) find();
        else if (strcmp(function, "replace") == 0) replace();
        else if (strcmp(function, "tree") == 0) tree();
        else if (strcmp(function, "arman") == 0) arman();
        else if (strcmp(function, "exit") == 0) return 0;
    }

}
