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
#include <signal.h>

int mysignal = 1 ;

void custom_signal_x(int signum) {
    mysignal = 0 ;
}

void make_program(char b[]) {
    FILE* src = fopen("killer.sh", "w") ;
    fputs(b, src) ;
    fclose(src) ;
}

void print_usage() {
    printf("Usage : ./soal3 [Options]\n") ;
    printf("Options :\n") ;
    printf("\t-z : Mode Immediately Kill\n") ;
    printf("\t-x : Mode Wait Till the end of process, then kill\n") ;
}

int main(int argc, char** argv) {
    if (argc > 2) {
        print_usage() ;
        return 0 ;
    }
    else if (argc == 2) {
        char b[80] ;
        if (!strcmp(argv[1], "-z")) {
            strcpy(b, "#!/bin/bash\nkillall -9 ./soal3\nrm $0\n") ;
            make_program(b) ;
        }
        else if (!strcmp(argv[1], "-x")) {
            strcpy(b, "#!/bin/bash\nkillall -15 ./soal3\nrm $0\n") ;
            make_program(b) ;
            signal(SIGTERM, custom_signal_x) ;
        }
        else {
            print_usage() ;
            return 0 ;
        }
    }
    else {
        print_usage() ;
        return 0 ;
    }

    time_t now ;
    struct tm t ;
    char buff[80] ;

    while(mysignal) {
        pid_t child_id ;
        now = time(0) ;
        t = *localtime(&now) ;
        strftime(buff, sizeof(buff), "%Y-%m-%d_%X", &t) ;

        child_id = fork() ;

        if (child_id < 0) {
            exit(EXIT_FAILURE) ;
        }

        if (child_id == 0) {
            // int status ;
            if (fork() == 0) {
                char* arg[] = {"mkdir", "-p", buff, NULL} ;
                execv("/bin/mkdir", arg) ;
            }
        }
        else {
            sleep(1) ;
            int i ;
            for (i = 0 ; i < 10 ; i++, sleep(5)) {

                if (fork() == 0) {
                    continue ;
                }

                time_t new_now = time(0) ;
                struct tm new_tstruct = *localtime(&new_now) ;
                char new_buff[80] ;
                strftime(new_buff, sizeof(new_buff), "%Y-%m-%d_%X", &new_tstruct) ;
                
                char path[80] ;
                strcpy(path, buff) ;
                strcat(path, "/") ;
                strcat(path, new_buff) ;
                
                char link[80] = "https://picsum.photos/" ;
                int picsize = (((long)mktime(&t)) % 1000) + 50 ;
                char num[10] ;
                sprintf(num, "%d", picsize) ;
                strcat(link, num) ;

                char* arg[] = {"wget", "-q", "-O", path, link, NULL} ;
                execv("/bin/wget", arg) ;
            }
            
            char str[30] = "Download Success", p[30] ;
            int j ;
            for (j = 0 ; j < strlen(str) ; j++) {
                if (str[j] == ' ') continue ;
                if ((str[j] >= 'a' && str[j] <= 'z' && str[j] + 5 > 'z') || (str[j] >= 'A' && str[j] <= 'Z' && str[j] + 5 > 'Z'))
                    str[j] -= 26 ;
                str[j] += 5 ;
            }
            strcpy(p, buff) ;
            strcat(p, "/") ;
            strcat(p, "status.txt") ;
            FILE* txt = fopen(p, "w") ;
            fputs(str, txt) ;
            fclose(txt) ;
            
            strcpy(p, buff) ;
            strcat(p, ".zip") ;
            char* argz[] = {"zip", p, "-q", "-m", "-r", buff, NULL} ;
            execv("/bin/zip", argz) ;
        }
        time_t first = time(0), second ;
        while (difftime(second, first) != 40) {
            second = time(0) ;
        }
    }
}
