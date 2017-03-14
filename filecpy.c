//Name: Aaron Brunette
//Assignment 1
//CS 433
//Last updated: 2017/02/22
//STRACE INCLUDED BELOW

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


/*		STRACE BELOW		*/

/*

execve("./filecpy", ["./filecpy", "myfile.txt", "mycopy.txt"], [/* 39 vars */]) = 0
brk(0)                                  = 0x9fc0000
mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7fac000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686/sse2/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686/sse2", 0xbfb3a8ec) = -1 ENOENT (No such file or directory)
open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls/i686", 0xbfb3a8ec) = -1 ENOENT (No such file or directory)
open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/sse2/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls/sse2", 0xbfb3a8ec) = -1 ENOENT (No such file or directory)
open("/opt/rh/devtoolset-1.1/root/usr/lib/tls/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib/tls", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
open("/opt/rh/devtoolset-1.1/root/usr/lib/i686/sse2/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib/i686/sse2", 0xbfb3a8ec) = -1 ENOENT (No such file or directory)
open("/opt/rh/devtoolset-1.1/root/usr/lib/i686/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib/i686", 0xbfb3a8ec) = -1 ENOENT (No such file or directory)
open("/opt/rh/devtoolset-1.1/root/usr/lib/sse2/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib/sse2", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
open("/opt/rh/devtoolset-1.1/root/usr/lib/libc.so.6", O_RDONLY) = -1 ENOENT (No such file or directory)
stat64("/opt/rh/devtoolset-1.1/root/usr/lib", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
open("/etc/ld.so.cache", O_RDONLY)      = 3
fstat64(3, {st_mode=S_IFREG|0644, st_size=106412, ...}) = 0
mmap2(NULL, 106412, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb7f92000
close(3)                                = 0
open("/lib/libc.so.6", O_RDONLY)        = 3
read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0 \260[\0004\0\0\0"..., 512) = 512
fstat64(3, {st_mode=S_IFREG|0755, st_size=1706204, ...}) = 0
mmap2(0x5a5000, 1422788, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x5a5000
mmap2(0x6fb000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x156) = 0x6fb000
mmap2(0x6fe000, 9668, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x6fe000
close(3)                                = 0
mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7f91000
set_thread_area({entry_number:-1 -> 6, base_addr:0xb7f916c0, limit:1048575, seg_32bit:1, contents:0, read_exec_only:0, limit_in_pages:1, seg_not_present:0, useable:1}) = 0
mprotect(0x6fb000, 8192, PROT_READ)     = 0
mprotect(0x5a1000, 4096, PROT_READ)     = 0
munmap(0xb7f92000, 106412)              = 0
fstat64(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 21), ...}) = 0
mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7fab000
write(1, "The arguments are myfile.txt and"..., 44The arguments are myfile.txt and mycopy.txt
) = 44
open("myfile.txt", O_RDONLY)            = 3
open("mycopy.txt", O_WRONLY|O_CREAT, 0600) = 4
read(3, "This is some text th", 20)     = 20
write(4, "This is some text th", 20)    = 20
read(3, "at I need copied.\n", 20)      = 18
write(4, "at I need copied.\n", 18)     = 18
read(3, "", 20)                         = 0
write(4, "", 0)                         = 0
close(3)                                = 0
close(0)                                = 0
exit_group(0)                           = ?

*/
