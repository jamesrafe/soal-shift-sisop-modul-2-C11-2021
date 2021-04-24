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
#include <dirent.h>
#include <string.h>

void main () {
	pid_t pid, sid;
	pid = fork();
	int idx;

	char *link[] = {
		"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
		"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
		"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
	};
	char *output_file[] = {
		"uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
		"uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
		"uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
	};
	char *mkdir[][3] = {
		{"mkdir", "Musyik", NULL}, 
		{"mkdir", "Pyoto", NULL}, 
		{"mkdir", "Fylm", NULL}
	};
	char *wget[][4] = {
		{"wget", "-nc", link[0], NULL},
		{"wget", "-nc", link[1], NULL},
		{"wget", "-nc", link[2], NULL}
	};
	char *unzip[][3] = {
		{"unzip", output_file[0], NULL},
		{"unzip", output_file[1], NULL},
		{"unzip", output_file[2], NULL}
	};
	char *src_dir[3] = {
		"MUSIK",
		"FOTO",
		"FILM"
	};
	char *dest_dir[3] = {
		"Musyik",
		"Pyoto",
		"Fylm"
	};
	char *rm[][3] = {
		{"rm", output_file[0], NULL},
		{"rm", output_file[1], NULL},
		{"rm", output_file[2], NULL}
	};
	char *rmdir[][3] = {
		{"rmdir", "MUSIK", NULL},
		{"rmdir", "FOTO", NULL},
		{"rmdir", "FILM", NULL}
	};
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

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while (1) {
		struct tm *Sys_T;
		time_t Tval = time(NULL);
		Sys_T = localtime(&Tval);
		pid_t child_id;
		int status;	
		
		if (Sys_T->tm_mday == 9 &&
			Sys_T->tm_mon+1 == 4 &&
			Sys_T->tm_hour == 16 &&
			Sys_T->tm_min == 22) {
			child_id = fork();
			if (child_id == 0) {
				child_id = fork();
				if (child_id == 0) {
					for (idx = 0; idx < 3; idx++) {
						if (0 == fork()) continue;
						execv("/bin/mkdir", mkdir[idx]);
					}
				} else {
					while (wait(&status) > 0);
					child_id = fork();
					if (child_id == 0) {
						for (idx = 0; idx < 3; idx++) {
							if (0 == fork()) continue;
							execv("/usr/bin/wget", wget[idx]);
						}
					} else {
						while (wait(&status) > 0);
						sleep(5);
						child_id = fork();
						if (child_id == 0) {
							for (idx = 0; idx < 3; idx++) {
								if (0 == fork()) continue;
								execv("/usr/bin/unzip", unzip[idx]);
							}
						} else {
							while (wait(&status) > 0);
							sleep(5);
							child_id = fork();
							if (child_id == 0) {
								for (idx = 0; idx < 3; idx++) {
									if (0 == fork()) continue;
									DIR *dp;
							        struct dirent *ep;
							        char src[50];
							        char dest[50];
							        char path[100]; 

							        getcwd(path, sizeof(path));
	                                strcat(path,"/");
	                                strcpy(dest,"");
	                                strcpy(dest,path);
	                                strcat(dest,dest_dir[idx]);
	                                strcat(path,src_dir[idx]);
	                                dp = opendir(path);

	                                while ((ep = readdir (dp))) {
	                                    strcpy(src,"");
	                                    strcpy(src,path);
	                                    if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
	                                        if (0 == fork()) {
	                                            strcat(src,"/");
	                                            strcat(src,ep->d_name);
	                                            char *argv[] = {"mv", src, dest, NULL};
	                                            execv("/bin/mv", argv);      
	                                        } else {
	                                        	waitpid(child_id, &status, 0);
	                                        }
	                                    }
	                                }
								}
							} else {
								sleep(10);
								for (idx = 0; idx < 3; idx++) {
									if (0 == fork()) continue;
									execv("/bin/rm", rm[idx]);
								}
								for (idx = 0; idx < 3; idx++) {
									if (0 == fork()) continue;
									execv("/bin/rmdir", rmdir[idx]);
								}
							}
						}
					}
				}
			} 
		} else if (Sys_T->tm_mday == 9 &&
			Sys_T->tm_mon+1 == 4 &&
			Sys_T->tm_hour == 22 &&
			Sys_T->tm_min == 22) {
			child_id = fork();
			if (child_id == 0) {
				char *argv[] = {"zip", "-r", "Lopyu_Stevany", "Musyik", "Fylm", "Pyoto", NULL};
				execv("/usr/bin/zip", argv);
			} else {
				while (wait(&status) > 0);
				char *argv[] = {"rm", "-r", "Musyik", "Fylm", "Pyoto", NULL};
				execv("/bin/rm", argv);
			}
		}
		sleep(60);
	}
}
