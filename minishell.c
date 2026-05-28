#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include"minishell.h"
#include<errno.h>

char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "jobs", "fg", "bg", NULL};
    
int status = 0;
pid_t child_pid = -1;
mini_list *head = NULL;
mini_list *tail = NULL;

void signal_handler(int signum)
{
    if(signum == SIGINT)
    {
        if(child_pid > 0)
        {
            // child is runnning
            kill(child_pid, SIGINT);
            
        }
        else
        {
            // no child running 
            // againg print prompt str
            //printf("%s$:",old_command_Str);
            // just to change colour
            printf("\n\033[1;33m🐚 %s\033[0m\033[1;34m $:\033[0m ", old_command_Str);
            fflush(stdout);

        }
    }
    else if(signum == SIGTSTP)
    {
        if(child_pid > 0)
        {
            // afetr preessing ctrl + Z pause
            kill(child_pid, SIGTSTP);  // stop child

            insert_at_first(&head, &tail,child_pid);

            child_pid = -1; 
            
        }
    }
    
}

void check_command_type(char **args, char ext_cmd[][100], int count)
{
    if(args[0] == NULL) return;

    int i = 0;

    while(builtins[i] != NULL)
    {
        if(strcmp(args[0], builtins[i]) == 0)
        {
            execute_internal_command(args);
            return;
        }
        i++;
    }
    execute_external_command(args, ext_cmd, count);
}

void execute_internal_command(char **args)
{
    if(strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if(strcmp(args[0], "cd") == 0)
    {
        //char buff[50];
        //chdir(buff);
        //printf("%s\n", buff);

        if(args[1] == NULL)
        {
            chdir(getenv("HOME"));
        }
        else
        {
            if(chdir(args[1]) != 0)
            {
                printf("\033[1;31mcd: %s: No such file or directory\033[0m\n", args[1]); // red error
            }
        }
    }
    else if(strcmp(args[0], "pwd") == 0)
    {
        char buff[1000];
        getcwd(buff, sizeof(buff));
        //printf("%s\n",buff);
        printf("\033[1;36m%s\033[0m\n", buff);  // cyan
    }
    else if(strcmp(args[0], "echo") == 0 && args[1])
    {
        if(strcmp(args[1], "$$") == 0)
        {
            printf("%d\n",getpid());
        }
        else if(strcmp(args[1], "$SHELL") == 0)
        {
            char *shell = getenv("SHELL");
            printf("%s\n", shell);
        }
        else if(strcmp(args[1], "$?") == 0)
        {
            printf("%d\n", WEXITSTATUS(status));
        }
        else 
        {
            for(int i = 1; args[i] != NULL; i++)
            {
                //printf("%s ",args[i]);
                printf("\033[1;35m%s\033[0m ", args[i]);  // magenta
            }
            printf("\n");
        }
    }


    // special commands
    if(strcmp(args[0], "jobs") == 0)
    {
        print_list(head);
    }
    if(strcmp(args[0], "fg") == 0)
    {
        pid_t var = head->data;
        delete_first(&head, &tail);

        child_pid = var;

        kill(var, SIGCONT);

        waitpid(var, &status, WUNTRACED);
        child_pid = -1;
    }
    if(strcmp(args[0], "bg") == 0)
    {
        pid_t var = head->data;
        kill(var, SIGCONT);
        delete_first(&head, &tail);
    }


    
}

int extract_external_cmd(char ext_cmd[][100], int max_cmd)
{
    FILE *fp = fopen("extCommand.txt", "r");

    if(fp == NULL)
    {
        printf("ERROR: open file...\n");
        return -1;
    }

    //execute_external_command(args);
    
    //char ext_cmd[500][100];
    char buff[100];

    int i= 0;
    

    // storing in 2d array
    while(i < max_cmd && fgets(buff, sizeof(buff),fp) != NULL)
    {
        buff[strcspn(buff, "\r\n")] = '\0';
        strcpy(ext_cmd[i], buff);
        i++;
    }
    fclose(fp);

    return i; // Return number of commands loaded

}

void execute_external_command(char **args, char ext_cmd[][100], int count)
{
    int found = 0;
    for(int j = 0; j < count; j++)
    {
        if(strcmp(args[0],ext_cmd[j]) == 0)
        {
            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("%s : Command not found\n",args[0]);
        return;
    }

    child_pid = fork();

    if(child_pid < 0)
    {
        perror("fork");
        return;
    }
    if(child_pid == 0)
    {
        //printf("\033[1;32m");  // green output
        write(STDOUT_FILENO, "\033[1;32m", 7);  // use write instead of printf
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        execvp(args[0], args); // execute extrenal command
        exit(1);
    }
    else
    {
        //wait(&status);
        
        signal(SIGTSTP, signal_handler);

        waitpid(child_pid, &status, WUNTRACED);  
        write(STDOUT_FILENO, "\033[0m", 4);  // reset color after child finishes
        if(!WIFSTOPPED(status))
        {
            child_pid = -1;
        }
    }
}


