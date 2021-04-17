#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<syslog.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<wait.h>

//caesar cipher
int cc()
{
	char message[100], ch;
	int i, key;
	
	printf("Enter a message to encrypt: ");
	gets(message);
	printf("Enter key: ");
	scanf("%d", &key);
	
	for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			message[i] = ch;
		}
	}
	
	printf("Encrypted message: %s", message);
	
	return 0;
}

int main(){
	int status;
	while(1){
		char counttime[100];
		pid_t child, child2, child3, child4, child5;
		
		time_t now = time(NULL);
		struct tm *t = localtime(&now);
		strftime (counttime, sizeof(counttime)-1, "%Y-%m-%d_%H:%M:%S", t);
		
		child1 = fork();
		if(child1 < 0) exit(EXIT_FAILURE);
		if(child1 == 0){
			if(fork() == 0){
				char* arg[] = {"mkdir", "-p", buff, NULL};
				execv("/bin/mkdir", arg);
			}
		}	
		child2 = fork();
		if (child2<fork) exit(EXIT_FAILURE);
		if(child2 == 0){
			chdir(counttime)
		}
		
		while(wait(&status) > 0);
		
		
		time_t first = time(0), second ;
		while (difftime(second, first) != 40) {
	   	second = time(0) ;
		}		
}
