#include <stdio.h>
#include <string.h>
#include<direct.h>
#include <stdlib.h>
#include <sys/stat.h>


#define max 10000
#define rootLocation "C:\\Users\\ASUS\\CLionProjects\\untitled\\cmake-build-debug\\root"

char clipBoard[max];


int main();

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
            if(fopen(folder,"r")!=NULL){
                printf("\nYour file is already existing!\n");
            }
            else{
                fopen(folder,"w");
                printf("\nYour file created successfully!\n");
            }
        }
    }
    chdir(rootLocation);
}


void cat(){

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
            chdir(folder);
            memset(folder,'\0',sizeof (folder));
        }
        if(i== strlen(address)-1){

            if(fopen(folder,"r")==NULL){
                printf("\nYour file is NOT existing!\n");
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
                    printf("%c", c);
                }
                printf("\n");
            }
        }
    }
    chdir(rootLocation);
}


void removeStr(){

}


int main() {
    char function[max];
    while(1) {
        scanf("%s", &function);
        if (strcmp(function, "createfile") == 0) createFile();
        if (strcmp(function, "cat") == 0) cat();
        if (strcmp(function, "exit") == 0) return 0;
    }

}
