// Scott Mann - CSE 7343 - 10/20/2013
// A simple Unix shell.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

	char *command = NULL;
	char *param1 = NULL;
	char *param2 = NULL;
	char sep[] = " ";
	char *result = NULL;
	char command_argv[3][255] = {0};
	char input[256] = {0};

	while(true)
	{
		int i = 0;
		input[0] = '\0';
		command_argv[0][0] = '\0';
		command_argv[1][0] = '\0';
		command_argv[2][0] = '\0';
		
		// Capture command
		printf("ssmannshell> ");
		scanf("%255[^\n]%*c", input);
		//printf("%s\n", input);

		//parse the command line to commandName, sourceFileName, targetFileName 3 arguments

		result = strtok(input, sep);
		//printf("%s", result);

		while( result != NULL )
		{
			strcpy(command_argv[i],result);
			result = strtok( NULL, sep );
			//printf("%s", result);
			i++;
		}

		command = command_argv[0];
		param1 = command_argv[1];
		param2 = command_argv[2];

		if(isExit(command))
		{
			printf("Exiting... Thanks for using SMUSh - Scott's Shell.\n");
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

void delete(char* filename)
{
	printf("Deleting...\n");

	int result = remove(filename);

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

void displayError(char* command)
{
	printf("Command not found: %s\n", command);
}

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
	FILE* exists = fopen(command, "r");

	if (exists != NULL)
    {
        fclose(exists);
        return true;
    }
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
