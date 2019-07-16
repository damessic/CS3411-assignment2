/* David Messick	  */
/* June 3, 2019		  */
/* CS3411		 	  */
/* Assignment 2	asort */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*Wrapper to print more easily*/
void printWrap(char buf[1024]) {
	write(1, buf, strlen(buf));
}

/*Checks to see if directory exists*/
int directoryCheck(const char *directory) {
	struct stat st;
	
	stat(directory, &st);
	if (S_ISDIR(st.st_mode)) {
		return 1;
	}
	
	return 0;
}

/*Main*/
int main(int argc, char **argv) {
	const char directory[] = "SORTED";
	char buf[1024];
	char output[1024];
	int i;
    int status;
	pid_t pid;
	
	/*Checks for correct number of arguments*/
	if (argc < 2) {
		sprintf(buf, "Error. Not enough arguments.\n");
		printWrap(buf);
		return 1;
	}

	/*Directory exists*/
	if (directoryCheck(directory)) {
		sprintf(buf, "Directory %s exists!\n", directory);
		printWrap(buf);
	}
	/*Creates directory if one does not exist*/
	else {
		sprintf(buf, "Directory %s does NOT exist!\nCreating directory %s...\nDirectory %s created!\n", directory, directory, directory);
		printWrap(buf);
		mkdir(directory, 0755);
	}
		
	/*Iterates through arguments*/
	for (i = 1; i < argc; i++) {
		
		pid = fork();

		if(pid == 0) {
			/*Child*/
			getpid();
			
			/*Tests new file where to go by adding SORTED/ in front of its name*/
			strcpy(output, "SORTED/");
			strcat(output, argv[i]);
			
			/*Exec for sort*/
			execl("/bin/sort", "/bin/sort", "-o", output, argv[i], (char *)NULL);
			
			exit(0);
		}
		else if (pid > 0) {
			/*Parent*/
			
			/*Wait for child to terminate*/
			wait(&status);
			
			/*When exit*/
			if (WIFEXITED(status)) {
				/*If successful*/
				if ((WEXITSTATUS(status)) == 0) {
					sprintf(buf, "%s : success (%d)\n", argv[i], WEXITSTATUS(status));
					printWrap(buf);
				}
				/*If failure*/
				if ((WEXITSTATUS(status)) == 2) {
					sprintf(buf, "%s : fail (%d)\n", argv[i], WEXITSTATUS(status));
					printWrap(buf);
				}
			}
		}
		else {
			/*error: The return of fork() is negative*/
			perror("fork failed");
			_exit(2); /*exit failure, hard*/
		}
	}
	
	sprintf(buf, "All done.\n");
	printWrap(buf);
	
	return 0;
}