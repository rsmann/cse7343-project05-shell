// Scott Mann - CSE 7343 - 10/20/2013
// A simple Unix shell.

// Includes
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Function Prototypes
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

// Main processing loop for the shell
int main(int argc, char **argv) {
	printf("SMUsh Version 0.1.234\n");

	// Allocate outside of the loop for efficiency
	char *command = NULL;
	char *param1 = NULL;
	char *param2 = NULL;
	char sep[] = " ";
	char *result = NULL;
	char part[3][255] = {0};
	char input[256] = {0};

	// Begin the command processing loop
	while(true)
	{
		// Clear out the storage at the beginning of each loop
		int i = 0;
		input[0] = '\0';
		part[0][0] = '\0';
		part[1][0] = '\0';
		part[2][0] = '\0';
		
		// Capture command line input
		printf("SMUsh> ");
		scanf("%255[^\n]%*c", input);

		// parse the input into three separate arguments

		// Pull the first token from the input
		result = strtok(input, sep);

		// Loop through remaining tokens until there are none left
		while( result != NULL )
		{
			// Copy the result into the argument array
			strcpy(part[i],result);
			result = strtok( NULL, sep );
			i++;
		}

		// Transfer the parts into named storage
		command = part[0];
		param1 = part[1];
		param2 = part[2];

		// Evaluate the command types and pass the appropriate parameters
		if(isExit(command))
		{
			printf("Exiting... Thanks for using SMUsh - Scott's Shell.\n");
			break;
		}
		else if (isCopy(command))
		{
			copy(param1, param2);
		}
		else if (isDelete(command))
		{
			delete(param1);
		}
		else if (isType(command))
		{
			type(param1);
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

// Copies the source file to the destination file, byte by byte
void copy(char *source, char *destination)
{
	printf("Copying %s to %s...\n", source, destination);

	char currentChar = 0;
	FILE *sourceHandle;
	FILE *destinationHandle;

	// Open the file
	sourceHandle = fopen(source, "r");
	destinationHandle = fopen(destination, "a");

	// If we didn't get a valid handle back, an error occurred
	if(sourceHandle == NULL)
	{
		perror("Error while opening the input file.\n");
		return;
	}

	if(destinationHandle == NULL)
	{
		perror("Error while opening the output file.\n");
		fclose(sourceHandle);
		return;
	}

	// Read every character and print it to the screen
	while((currentChar = fgetc(sourceHandle)) != EOF)
	{
		fprintf(destinationHandle, "%c", currentChar);
	}

	// Close the file cleanly
	fclose(sourceHandle);
	fclose(destinationHandle);

	return;
}

// Deletes the file if it exists
void delete(char* filename)
{
	printf("Deleting...\n");

	// Attempt the removal
	int result = remove(filename);

	// If there was a problem, notify the user
	if(result != 0)
	{
		printf("Error deleting file: %s, result: %d\n", filename, result);
	}
	else
	{
		puts( "File successfully deleted" );
	}
	return;
}

// Display the erroneous command back to the user
void displayError(char* command)
{
	printf("Command not found: %s\n", command);
}

// Execute the command passed in
void execute(char* command)
{
	char args[1][1];
	args[0][0] = '\0';

	int pid = fork();

	if (pid == 0)
	{
		printf("Executing...\n");
		execvp(command, args);
	}
	else
	{
		wait(pid);
		return;
	}
}

// Is the command "copy"
bool isCopy(char* command)
{
	return !strcmp(command, "copy");
}

// Is the command "delete"
bool isDelete(char* command)
{
	return !strcmp(command, "delete");
}

// Is the command executable
bool isExecutable(char* command)
{
	// Trying to see if I could get ls to work
	if (!strcmp(command, "ls")) return true;

	FILE* exists = fopen(command, "r");

	if (exists != NULL)
    {
        fclose(exists);
        return true;
    }
	return false;
}

// Is the command "exit"
bool isExit(char* command)
{
	return !strcmp(command, "exit");
}

// Is the command "type"
bool isType(char* command)
{
	return !strcmp(command, "type");
}

// Output the file to the screen byte by byte
void type(char *filename)
{
	printf("Opening %s for reading...\n", filename);

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

	return;
}
