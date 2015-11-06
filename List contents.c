/* 
Author: Erick Musembi
Description: Lists all the files & other directories in the directory passed through argv.
*/

/* 
	Importing the required headers. 
	Dirent.h for the dirent struct.
	Stdio.h  for printf.
*/

#include <dirent.h>
#include <stdio.h>

int main (int argc, char *argv[]) 
{
	// Checking that the user has given the correct number of arguments.
	if (argc != 3) {
		printf("Usage: %s, directory, logFile \nEG: %s C:\\Program Files, C:\\Log\1.txt", argv[0], argv[0] );
		getch();
		return 4;
	}
	else {
		//  dir (pointer) -  used for keeping track of the current directory name.
		DIR *dir;
		
		// If the directory exists.
		if ((dir = opendir(argv[1])) != NULL) {
			struct dirent *ent;
			
			/* Prepearing the File pointer for use in the while loop.
				Pointer needed for file access and output. */
			FILE *fp;
			fp = fopen(argv[2], "w+");
			
			// While we are in a directory and there are other directories present.
			while ((ent = readdir (dir)) != NULL) {
				// Prints all of the data to the console.
				printf("%s\n", ent->d_name);	
				// Writes all of the data to the file stated in argv[2].
				
				fprintf(fp, "%s\n", ent->d_name);	
			} 
			// Closes file ponter & directory pointer, free's the data and shows where the log was saved to.
			fclose(fp);
			closedir(dir);
			printf("Saved to: %s", argv[2]);
			return 0;	
		}
		// If the directory does not exist.
		else if (dir == NULL) {
			printf("You either typed the path incorrectly or the directory does not exist.");
			closedir(dir);
			return 1;	
		}
	// I assume that they are trying to access a restricted directory.
	else {
		printf("Could not open directory, try running your command line with administrative privilidges.");
		closedir(dir);
		return 2;
		}
	}
	
}
