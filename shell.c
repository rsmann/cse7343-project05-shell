// Your Name
// Description.


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool commandIsExit(char* command);
void copy(char *filename1, char *filename2);
void displayError(char* command);
void type(char* command);

int main(int argc, char **argv) {
	// TODO
	printf("SMUSh Version 0.1.234\n");

	char command[100] = {0};

	while(true)
	{
		// Capture command
		printf("ssmannshell> ");
		scanf("%s", command);

		if(commandIsExit(command))
		{
			printf("Exiting... Thanks for using Scott's Shell.\n");
			break;
		}
		else
		{
			displayError(command);
		}

		// If command is type,
		// type(command)

		// If command is copy
		// copy(file1, file2)
	}

	return 0;
}


bool commandIsExit(char* command)
{
	return !strcmp(command, "exit");
}

void copy(char *filename1, char *filename2)
{

}

void displayError(char* command)
{
	printf("Command not found: %s\n", command);
}

void type(char *command)
{
	// open the file
	char contents[1000];

	// Read the file
	// Output the file
}

