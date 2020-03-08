#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    int Pipe1[2];
    int Pipe2[2];
    int ch1pid = -1, ch2pid = -1, numread, numwrite, d = 0;
    char buf;
    pipe(Pipe1);
    ch1pid = fork();

    if (ch1pid == 0)
    { /* child 1 */
        dup2(Pipe1[1], STDOUT_FILENO);
        close(Pipe1[0]);
        close(Pipe1[1]);
        execl(argv[1], ".", NULL);
    }

    pipe(Pipe2);
    ch2pid = fork();
    if (ch2pid == 0)
    { /* child 1 */
        dup2(Pipe2[0], STDIN_FILENO);
        close(Pipe2[0]);
        close(Pipe2[1]);
        execl(argv[2], "", NULL);
    }
    dup2(Pipe1[0], STDIN_FILENO);
    dup2(Pipe2[1], STDOUT_FILENO);
    close(Pipe1[0]);
    close(Pipe1[1]);
    close(Pipe2[0]);
    close(Pipe2[1]);
    buf=read(STDIN_FILENO, &buf, 1);
    write(STDOUT_FILENO, &buf, 1);
    close(STDOUT_FILENO);
}