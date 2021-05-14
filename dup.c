#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void)
{
    char* arg[2] = {"A", };       //string array
    char* env[2] = {"A", };       //environment
    int pid, pipefd[2];
 
    if(pipe(pipefd) < 0)
    {
        perror("pipe error");
        exit(-1);
    }
 
    pid = fork();
 
    if(pid == -1)                          //Error
    {
        perror("Failed to Create Process");
        exit(-1);
    }
    else if(pid == 0)                     //자식 프로세스(0인 경우)
    {
        printf("Thank you!\n");                                                        //Running Check2!
 
        dup2(pipefd[0], 0);
        close(pipefd[1]);
 
        execve("/usr/bin/ls", arg, env);
    }
    else                                 //부모 프로세스
    {
        printf("I will find you. I will look for you. I will send for you.\n");        //Running Check1!
 
        write(pipefd[1], "payload", 4);
 
        sleep(10);
    }
 
    return 0;
}
