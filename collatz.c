//Name: Aaron Brunette
//Assignment 2
//CS 433

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

//Purpose: To implement the fork function in order to create a child
// process that will run the Collatz conjecture for any value given
// as an argument in the command line.

//Algorithm: Uses the fork() function to create a child process which
// runs a different operation on the seed value depending on whether
// it is odd or even. When the seed value reaches 1 the operations
// are complete and the child process will end. While the child
// process runs the parent process waits until the child is finished.
int main(int argc, char *argv[])
{
	//error checking if there is only one argument
	if(argc <= 1)
	{
		printf("Please enter a number to test.\n");
		exit(1);
	}

	//error checking if there is more than two arguments
	if(argc >= 3)
	{
		printf("You have entered too many arguments.\n");
		exit(1);
	}

	//initialize int from second argument
	int seed = strtol(argv[1], NULL, 10);

	//fork process
	pid_t childPid = fork();

	//failed to fork
	if(childPid < 0)
	{
		printf("fork failed errno = 0x%x, (5s) \n", __FILE__, errno, strerror(errno));
		exit(-1);
	}

	//parent process
	else if(childPid != 0)
	{
		printf("I'm the parent %d, my child is %d\n\n", getpid(), childPid);
		wait(NULL);	//wait for child process
	}

	//child process created
	else
	{
		printf("I'm the child %d, my parent is %d\n\n", getpid(), childPid);

		while(seed != 1)
		{
			//seed is even
			if((seed % 2) == 0)
			{
				printf("seed is even, dividing by 2.");
				seed = seed / 2;
				printf("seed is now %d\n\n", seed);
			}
			//seed is odd
			else
			{
				printf("seed is odd, multiplying by 3 then adding 1.");
				seed = (3 * seed) + 1;
				printf("seed is now %d\n\n", seed);
			}
		}
	}

	return 0;
}
