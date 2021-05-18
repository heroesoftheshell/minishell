// cd, pwd

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <path name>\n", argv[0]);
        return 1;
    }
    char name[PATH_MAX];
    printf("Before Current Directory:%s\n",getcwd(name,PATH_MAX));
    if(chdir(argv[1])==-1) // 실패시 -1, 성공시 0
    {
        printf("failed, change directory\n");
    }
    else
    {
        printf("After Current Directory:%s\n",getcwd(name,PATH_MAX));
    }

    if(chdir(argv[1])==-1) // 실패시 -1, 성공시 0
    {
        printf("failed, change directory\n");
    }
    else
    {
        printf("After Current Directory:%s\n",getcwd(name,PATH_MAX));
    }

    return 0;
}
