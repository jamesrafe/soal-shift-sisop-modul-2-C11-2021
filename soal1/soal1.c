#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

void main () {
	pid_t pid, sid;
	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}
	
	umask(0);

	sid = setsid();
	if (sid < 0) {
    	exit(EXIT_FAILURE);
	}

	// if ((chdir("/")) < 0) {
 //    	exit(EXIT_FAILURE);
	// }

	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// int temp = 0;
	while (1) {
		struct tm *Sys_T;
		time_t Tval = time(NULL);
		Sys_T = localtime(&Tval);
		pid_t child_id1, child_id2;
		int status;	
		
		if (Sys_T->tm_mday == 9 &&
			Sys_T->tm_mon+1 == 4 &&
			Sys_T->tm_hour == 16 &&
			Sys_T->tm_min == 22) {

			child_id1 = fork();
			if (child_id1 == 0) {
				child_id2 = fork();
				if (child_id2 == 0) {
					char *argv[] = {"/bin/sh", "-c", "mkdir Musyik && mkdir Pyoto && mkdir Fylm", NULL};
					execve(argv[0], &argv[0], NULL);
				} else {
					while(wait(&status) > 0);
					char *argv[][4] = {{"/bin/sh", "-c", "wget --no-check-certificate 'https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download' && mv 'uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download' 'MUSIK.zip' && unzip MUSIK.zip && mv MUSIK/* Musyik/ && rmdir MUSIK && rm MUSIK.zip", NULL}, 
					{"/bin/sh", "-c", "wget --no-check-certificate 'https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download' && mv 'uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download' 'FILM.zip' && unzip FILM.zip && mv FILM/* Fylm/ && rmdir FILM && rm FILM.zip", NULL}, 
					{"/bin/sh", "-c", "wget --no-check-certificate 'https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download' && mv 'uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download' 'FOTO.zip' && unzip FOTO.zip && mv FOTO/* Pyoto/ && rmdir FOTO && rm FOTO.zip", NULL}};
					int idx;
					for (idx = 0; idx < 3; idx++) {
						if (0 == fork()) continue;
						execve(argv[idx][0], &argv[idx][0], NULL);
					}
				}
			} 
		} else if (Sys_T->tm_mday == 9 &&
			Sys_T->tm_mon+1 == 4 &&
			Sys_T->tm_hour == 22 &&
			Sys_T->tm_min == 22) {
			char *argv[] = {"/bin/sh", "-c", "zip Lopyu_Stevany.zip Musyik/* Fylm/* Pyoto/* && rm -r Musyik && rm -r Fylm && rm -r Pyoto", NULL};
			execve(argv[0], &argv[0], NULL);
		}
		// temp++;
		sleep(60);
	}
}
