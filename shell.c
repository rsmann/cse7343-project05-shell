// Your Name
// Description.


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void copy(char *filename1, char *filename2);
void displayError(char* command);
bool isCopy(char* command);
bool isDelete(char* command);
bool isExecute(char* command);
bool isExit(char* command);
bool isType(char* command);
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

		if(isExit(command))
		{
			printf("Exiting... Thanks for using SMUSh - Scott's Shell.\n");
			break;
		}
		else if (isCopy(command))
		{

		}
		else if (isDelete(command))
		{

		}
		else if (isType(command))
		{

		}
		else
		{
			if (isExecute(command))
			{

			}
			else
			{
				displayError(command);
			}
		}

		// If command is type,
		// type(command)

		// If command is copy
		// copy(file1, file2)
	}

	return 0;
}

void copy(char *filename1, char *filename2)
{

}

void displayError(char* command)
{
	printf("Command not found: %s\n", command);
}

bool isCopy(char* command)
{
	return false;
}

bool isDelete(char* command)
{
	return false;
}

bool isExecute(char* command)
{
	return false;
}

bool isExit(char* command)
{
	return !strcmp(command, "exit");
}

bool isType(char* command)
{
	return false;
}

void type(char *command)
{
	// open the file
	char contents[1000];

	// Read the file
	// Output the file
}
