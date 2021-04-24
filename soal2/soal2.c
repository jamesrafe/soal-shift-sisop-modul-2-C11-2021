#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <glob.h>
#include <dirent.h>
#include <string.h>

int animalCount = 0, nameCount = 0, ageCount = 0;
char animals[55][20];
char names[55][20];
char ages[55][3];

int handleAnimal(char filename[], int j){
	int charCount=0;
	for(; j<strlen(filename)-4; j++){
  		if(filename[j] == ';'){
  			break;
  		}
  		animals[animalCount][charCount] = filename[j];
  		charCount++;
  	}
  	animalCount++;
  
 	return j;
}
int handleName(char filename[], int j){
	int charCount=0;
	for(j=j+1; j<strlen(filename)-4; j++){
  		if(filename[j] == ';'){
  			break;
  		}
  		names[nameCount][charCount] = filename[j];
  		charCount++;
  	}
  	nameCount++;
  	return j;
}
int handleAge(char filename[], int j){
	int charCount=0;
	for(j=j+1; j<strlen(filename)-4; j++){
  		if(filename[j] == '_'){
  			j++;
  			break;
  		}
  		ages[ageCount][charCount] = filename[j];
  		charCount++;
  	}
  	ageCount++;
  	return j;
}
int handleElse(char filename[], int j){
	j = handleAnimal(filename, j);
	j = handleName(filename, j);
	j = handleAge(filename, j);
	
	pid_t cid[10];
  	int stat[10];
  	char loc[100] = "modul2/petshop/";
  	char curloc[100] = "modul2/petshop/";
  	char animalName[50], animalName2[50], animalName3[50];
  	strcpy(animalName, animals[animalCount-1]);
  	strcpy(animalName2, animals[animalCount-1]);
  	strcpy(animalName3, animals[animalCount-1]);
  	strcat(loc, animalName);
  	strcat(curloc, filename); 	
  
  	cid[0] = fork();

  	if (cid[0] == 0) {
  		char *argv[4] = {"mkdir", "-p", loc, NULL};
		execv("/bin/mkdir", argv);
 	 }
  
 	 while ((wait(&stat[0])) > 0);
 	 
 	 char log[30]="";
 	 
 	 FILE *fp;
 	 strcat(log, "/home/solxius/modul2/petshop/");
 	 strcat(log, animalName2);
 	 strcat(log, "/keterangan.txt");
 	 
 	 fp = fopen (log, "a");
   	 fprintf(fp, "nama : %s\numur : %s\n\n", names[nameCount-1], ages[ageCount-1]);  
   	 fclose(fp);
   	 char loca[100] = "modul2/petshop/";
   	 strcat(loca, animalName3);
 	 strcat(loca, "/");
  	 strcat(loca, names[nameCount-1]);
  	 strcat(loca, ".jpg");
 	 
 	 if(j<strlen(filename)-4){
 	 	cid[1] = fork();

	  	if (cid[1] == 0) {
	  		char *argv[4] = {"cp", curloc, loca, NULL};
			execv("/bin/cp", argv);
	 	 }
	 	 while ((wait(&stat[1])) > 0);
  		handleElse(filename, j);
  	 }
 	 
 	 else{
 	 	cid[1] = fork();

	  	if (cid[1] == 0) {
	  		char *argv[4] = {"mv", curloc, loca, NULL};
			execv("/bin/mv", argv);
	 	 }
	 	 while ((wait(&stat[1])) > 0);
 	 	return j;
 	 }
}

int main() {
  pid_t child_id[10];
  int status[10];
  
  child_id[0] = fork();

  if (child_id[0] == 0) {
  	char *argv[] = {"mkdir", "-p", "modul2/petshop", NULL};
	execv("/bin/mkdir", argv);
  }
  
  while ((wait(&status[0])) > 0);
  child_id[1] = fork();
  if (child_id[1] == 0) {
  	char *argv[] = {"unzip", "/home/solxius/Downloads/pets.zip", "-d", "/home/solxius/modul2/petshop/", NULL};
	execv("/bin/unzip", argv);
  }  
  while ((wait(&status[1])) > 0);
  child_id[2] = fork();
  if (child_id[2] == 0) {
  	glob_t globbuf;
	int err = glob("/home/solxius/modul2/petshop/*/", 0, NULL, &globbuf);
	int numberofmatch = 3+(int) globbuf.gl_pathc;
	char *argv[100] = {"rm", "-r"};
	int count = 2;
        for (int i = 0; globbuf.gl_pathv[i]; i++) {
            argv[count] = globbuf.gl_pathv[i];
            count++;
        }
        
     	argv[count+1] = NULL;
	execv("/bin/rm", argv);
  }  
  while ((wait(&status[2])) > 0);
  printf("parent\n");
  
  struct dirent **namelist;
  int n = scandir("/home/solxius/modul2/petshop/", &namelist, NULL, alphasort);
  if (n == -1) {
      perror("scandir");
      exit(EXIT_FAILURE);
  }
  char filename[n][50];
  for(int i=0; i<n; i++) {
       strcpy(filename[i], namelist[i]->d_name);
       free(namelist[i]);
  }
  free(namelist);
  for(int i=2; i<n; i++){
  	int test = handleElse(filename[i], 0);
  }  
  return 0;
}
