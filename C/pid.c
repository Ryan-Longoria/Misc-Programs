#include <stdio.h>
#include <errno.h> //for errexit
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void printConcurrent(); //prints pid ppid cmd
void getPid(); //gets the Pid
int getJr(); //gets child
void getDad(); //gets parent and leads to child
void letsWait(); //wait process

int main (int argc, char *argv[])
{
    int i = 1;
    int j = 1;
    int length = argc;
    int length2 = 0;

    //i is 1 and not 0 for first argument
    for(i = 1; i < length; i++)
    {
        //max of 6 characters
        if(i <= 6)
        {
            //if not before colon in command line argument, skip and iterate to next
            if (strcmp(argv[i], ":") != 0)
                continue;
            //if before colon, execute to get parent and child 
            else
            {
                //to get the length of cla
                length2 = i - j + 1;
                //sends to get parent and then child. basically the rest of the program
                getDad(argv, i, j, length, length2);
                //iterate to next j
                j = i + 1;
            }
        }
        //if after 6 characters, break for loop
        else
            break;
    }
    
    //same as in the for loop, but once more.
    length2 = length - j + 1;
    getDad(argv, j, length, length + 1, length2);
    //we have to wait for the child process
    //send to letsWait to do this
    letsWait();

    return 0;
} //end of main

void getDad(char *argv[], int x, int y, int length, int length2)
{
    int i;
    char *execArgv[length2];
    
    //original length bigger than length2
    if (length2 < length)
    {
        //copy argv into execargv modified
        for(i = 0; i < length2 - 1; i++)
        {
            execArgv[i] = argv[i + y];
        }
    }
    //last element of array must be NULL for execvp
    execArgv[length2 - 1] = NULL;
    long lWaitPid;
    //creates a child
    long lForkPid = fork();



    
/*  int iExitStatus = 0;
    switch(fork())
    {
        case -1:
            break;
            //continue;
            //errExit("fork failed: %s", strerror(errno));
        case 0:
            printConcurrent(argv, y);
            execvp(argv[y], execArgv);
        default:
            lWaitPid = wait(&iExitStatus);
    }
*/    



    //send fork() to getJr function
    //If fork is case <0<, we don't want to print anything and we exit to main
    if (getJr(lForkPid) == 0)
        return;

    //send to print function if fork() is case 0
    printConcurrent(argv, y);
    
    //executes argv[y] using execArgv
    //int execvp(char *argv[y], char *execArgv);
    execvp(argv[y], execArgv);
} //end of getDad

void letsWait()
{
    //wait(NULL) blocks parent process for a child to finish
    //child process will turn into zombie until its parent waits on it
    while(wait(NULL) > 0);

    return;
} //end of letsWait

int getJr(long lForkPid)
{
    //Creates a child by using fork() 
    //return 0 is case <0<
    if (lForkPid != 0)
        return 0;
    else 
        return 1;
} //end of getJr

void printConcurrent(char *argv[], int num)
{
    //print pid ppid and they have to be type long
    //print cmd by making it a certain number in cla
    long lPid = getpid();
    long lPPid = getppid();
    char* cmd = argv[num];
    printf("PID: %ld, PPID: %ld, CMD %s\n", lPid, lPPid, cmd);
} //end of printConcurrent
