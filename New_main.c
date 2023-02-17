#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void  print(char *str)
{
  printf("%s\n", str);
}

void  ex()
{
  printf("%s\n", "je suis une erreur\n");
  exit(0);
}

void    exec(char *env[])
{
    int pid;
    int pipefd[2];
    int fd_in;
    int i;
    int nb_pipe; // a compter dans le parser || nb_pipe = nb_command - 1;
    char  cmd[] = "/usr/bin/ls";
    char  *arvec[] = {"ls", "-l", NULL};
    char  *envec[] = {NULL};

    nb_pipe = 2;
    i = 0;
    fd_in = dup(STDIN_FILENO);
    while (i < nb_pipe)
    {
      pipe(pipefd);
      pid = fork();
      pipefd[1] = dup2(fd_in, STDIN_FILENO);
      if (pid == 0) // pid == 0 -> dans l'enfant
      {
        if (i != 0)
          dup2(fd_in, STDIN_FILENO);
        if (i + 1 != nb_pipe)
          dup2(pipefd[1], STDOUT_FILENO);
        close(fd_in);
        close(pipefd[0]);
        close(pipefd[1]);
        if (i < nb_pipe)
        {
          execve(cmd, arvec, envec);
        }
      }
      dup2(pipefd[0], fd_in);
      close(pipefd[0]);
      close(pipefd[1]);
      i++;
    }
    close(fd_in);
    
}

int main(int argc, char *argv[], char *env[])
{
    //if (argc < 2)
      //  exit(0);
    exec(env);
    return (0);
}