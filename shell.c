// Scott Mann - CSE 7343 - 10/20/2013
// A simple Unix shell.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void copy(char *source, char *destination);
void delete(char* filename);
void displayError(char* command);
void execute(char* command);
bool isCopy(char* command);
bool isDelete(char* command);
bool isExecutable(char* command);
bool isExit(char* command);
bool isType(char* command);
void type(char* filename);


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

		// The command wasn't exit, go ahead and parse the arguments once
		// for future use.
		int count = 0;
		char input[100] = {0};
		char result[100][32];
		strcpy(input, command);
		count = split2(input, result);

		int i = 0;
		for (i=0; i<count; i++) {
			printf("%s+", result[i]);
		}

		if (isCopy(result[0]))
		{
			copy(result[1], result[2]);
		}
		else if (isDelete(result[0]))
		{
			delete(result[1]);
		}
		else if (isType(result[0]))
		{
			type(result[1]);
		}
		else if (isExecutable(command))
		{
			execute(command);
		}
		else
		{
			displayError(command);
		}
	}

	return 0;
}

int split2(char* str, char results[256][32])
{
	//const char line[] = "2004/12/03 12:01:59;info1;info2;info3";
	const char *ptr = str; //line
	char field [ 32 ];
	int n;
	int i = 0;
	while ( sscanf(ptr, "%31[^ ]%n", field, &n) == 1 )
	{
		printf("field = \"%s\"\n", field);
		strcpy(results[i++], field);
		ptr += n; /* advance the pointer by the number of characters read */
		if ( *ptr != ' ' )
		{
			break; /* didn't find an expected delimiter, done? */
		}
		++ptr; /* skip the delimiter */
	}
	return i;
}

void copy(char *source, char *destination)
{
	printf("Copying...\n");
}

void delete(char* filename)
{
	printf("Deleting...\n");
}

void displayError(char* command)
{
	printf("Command not found: %s\n", command);
}

void execute(char* command)
{
	printf("Executing...\n");
}

bool isCopy(char* command)
{
	return !strcmp(command, "copy");
}

bool isDelete(char* command)
{
	return !strcmp(command, "delete");
}

bool isExecutable(char* command)
{
	return false;
}

bool isExit(char* command)
{
	return !strcmp(command, "exit");
}

bool isType(char* command)
{
	return !strcmp(command, "type");
}

void type(char *filename)
{
	printf("Opening %s for output...", filename);

	char currentChar = 0;
	FILE *handle;

	// Open the file
	handle = fopen(filename, "r");

	// If we didn't get a valid handle back, an error occurred
	if(handle == NULL)
	{
		perror("Error while opening the file.\n");
		return;
	}

	// Read every character and print it to the screen
	while((currentChar = fgetc(handle)) != EOF)
	{
		printf("%c", currentChar);
	}

	// Close the file cleanly
	fclose(handle);
}
