
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main (int ac, char **av, char **envp)
{
    int pid;
    
    pid = fork();
    if (pid == 0)
        execve("/bin/ls", av, envp);
     wait(NULL);
    printf("bonjour, pid = %d\n", pid);
    return (0);
}
