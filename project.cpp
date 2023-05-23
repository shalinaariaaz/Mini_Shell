#include <iostream>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include "custom.cpp"

#include <sys/types.h>
#include <sys/wait.h>

#define TOKENSIZE 100

using namespace std;
void StrTokenizer(char *line, char **argv);
void myExecvp(char **argv);
int GetEnv();
void handleCustomCommand(char **argv);

void StrTokenizer(char *line, char **argv);
void handleCustomCommand(char **argv);

int main(int argc, char *argv[])
{
    char input[250];
    char *argValues[TOKENSIZE];

    while (true)
    {
        cout << "SMMshell-> ";
        cin.getline(input, 250);
        addToHistory(input);

        StrTokenizer(input, argValues);

        if (strcmp(argValues[0], "exit") == 0)
        {
            break;
        }
        else if (strcmp(input, "\n") == 0)
        {
            continue;
        }
        else if (strcmp(argValues[0], "concat") == 0)
        {

            char *concatCommand;

            strcpy(concatCommand, argv[1]);
            strcat(concatCommand, " ");
            strcat(concatCommand, argv[2]);

            // Execute the concatenated command
            if (execvp(concatCommand, argv) == -1)
            {
                perror("execvp");
                return 1;
            }
        }
        else
        {
            handleCustomCommand(argValues);
        }
    }

    return 0;
}

void StrTokenizer(char *input, char **argv)
{
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL)
    {
        argv[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    argv[i] = NULL;
}
