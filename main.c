/*
Name :- Pratik Satsure
Batch id :- 25026_079
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include "minishell.h"

char old_command_Str[100] = "minishell";
char new_command_Str[100];

int main()
{
    system("clear");
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    
    char ext_cmd[500][100]; // why global because it is a global data for session
    int count = extract_external_cmd(ext_cmd, 500);

    while(1)
    { 
        //printf("%s$:",old_command_Str);
        //printf("\033[1;33m🐚 %s\033[0m\033[1;34m $:\033[0m ", old_command_Str); // just to change the colour
        printf("\n\033[1;33m🐚 %s\033[0m\033[1;34m $:\033[0m ", old_command_Str);
        fflush(stdout);
        

        fgets(new_command_Str, sizeof(new_command_Str), stdin);
        new_command_Str[strcspn(new_command_Str, "\n")] = '\0';
        //new_command_Str[strcspn(new_command_Str, "\r")] = '\0';

        
        int len = strlen(new_command_Str);

        
        char *found = strstr(new_command_Str, "PS1=");
        

        if(found)
        {
            int flag = 0;

            for(int i = 0; i < len; i++)
            {
                if(new_command_Str[i] == ' ')
                {
                    flag = 1;
                    break;
                }
            }
            
            if(flag)
            {
                printf("Command Not Found\n");
            }
            else
            {
                strcpy(old_command_Str, new_command_Str + 4);

                //printf("%s$:",old_command_Str);

            }
        }
        else
        {
            char *args[50];

            int i = 0;

            args[i] = strtok(new_command_Str, " ");

            while(args[i] != NULL)
            {
                i++;

                args[i] = strtok(NULL, " ");
            }

            args[i] = NULL;
            
            check_command_type(args, ext_cmd, count);
            
        }
    }
}