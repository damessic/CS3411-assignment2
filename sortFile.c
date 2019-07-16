/* David Messick	  	   */
/* June 3, 2019		  	   */
/* CS3411		 	  	   */
/* Assignment 2	sortFiles  */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*A wrapper for write()*/
void printWrapper(char buf[2048]) {
	write(1, buf, strlen(buf));
}


int main(int argc, char **argv) {
	char buf[1024];
	char output[1024];
	
	if (argc < 1) {
        sprintf(buf, "Not enough arguments.\n");
        printWrapper(buf);
        return 1;
    }
	
	strcpy(output, "SORTED/");
	strcat(output, argv[1]);
	execl("/bin/sort", "/bin/sort", "-o", output, argv[1], (char *)NULL);
	
	return 0;
}