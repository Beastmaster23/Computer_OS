#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    int Pipe1[2];
    int Pipe2[2];
    int ch1pid, ch2pid, numread, numwrite;
    char buf;

    if (ch1pid == 0)
    { /* child 1 */
        execl(argv[1], "prog1", NULL);
    }
    if (ch2pid == 0)
    { /* child 2 */
        execl(argv[2], "prog2", NULL);
    }
}