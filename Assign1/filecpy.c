//Name: Aaron Brunette
//Assignment 1
//CS 433

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Purpose: To copy the contents of the first command line
// argument to the second command line argument
int main(int argc, char *argv[])
{
	//initialize buffer
	char buf[20];
	//initialize counter for loop
	int counter = 1;

	//two arguments
	if(argc == 3)
	{
		printf("The arguments are %s and %s\n", argv[1], argv[2]);
	}
	//more than 2 arguments
	else if(argc > 3)
	{
		printf("Too many arguments provided.");
		exit(1);
	}
	//less than 2 arguments
	else
	{
		printf("Too few arguments provided.");
		exit(1);
	}

	//open first argument as file to be copied
	int file1 = open(argv[1], O_RDONLY, 0600);

	//checks if file could be opened
	if(file1 == -1)
	{
		printf("File 1 could not be opened or changed");
		exit(1);
	}
	
	//open second argument as file to be copied too
	int file2 = open(argv[2], O_CREAT | O_WRONLY);

	//checks if file could be opened
	if(file2 == -1)
	{
		printf("File 2 could not be opened or changed.");
		exit(1);
	}

	//while there is nothing to read from the buffer, keep writing to file
	while(counter != 0)
	{
		counter = read(file1, buf, 20);
		write(file2, buf, counter);
	}
	//insert terminating character at the end of the file
	buf[sizeof(buf)] = '\0';

	//close both files
	close(file1);
	close(file2);

	return 0;
}
