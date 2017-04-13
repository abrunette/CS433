/*****************filename**************/
//Author: Aaron Brunette
//Github: abrunette
//Last updated: 2017/04/12
//Compiled with gcc
//Written on Vim
//Purpose: To use 32-bit virtual address translation.
/***************************************/

#include <stdio.h>      //C standard I/O library
#include <unistd.h>     //POSIX OS API
#include <errno.h>      //C error codes
#include <stdlib.h>     //C general library
#include <fcntl.h> 	//file control library

//Purpose: To find the page number and offset
//of a user defined variable with a file size
//of fileSize.
//User information: ./vmexp <positive integer>
//Input:  1 command line argument
//Output: Print statments
int main(int argc, char* argv[])
{
	unsigned int vaddress = 0;	//virtual address location
	unsigned int pageNum = 0;	//page number
	unsigned int offset = 0;		//offset
	unsigned int fileSize = 4096;	//file size

	if(argc < 2)	//too few arguments
	{
		printf("Too few arguments. One argument required.\n\n");
		exit(1);
	}

	if(argc > 2)	//too many arguments
	{
		printf("Too many arguments. One argument required.\n\n");
		exit(1);
	}

	vaddress = atoi(argv[1]);	//convert cmd line arg to int
	
	pageNum = vaddress / fileSize;	//find page number
	
	offset = vaddress % fileSize;	//find offset

	//print statements
	printf("The address %u contains:\n", vaddress);
	printf("Page number = %u\n", pageNum);
	printf("Offset = %u\n\n", offset);

	exit(0);
}
