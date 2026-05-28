#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>

extern char old_command_Str[100];
extern char new_command_Str[100];

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}mini_list;

extern mini_list *head;
extern mini_list *tail;

int insert_at_first(mini_list **head, mini_list **tail, int data);
int insert_at_last(mini_list **head, mini_list **tail, int data);
int delete_first(mini_list **head, mini_list **tail);
void print_list(mini_list *head);

void check_command_type(char **args, char ext_cmd[][100],int count);

int extract_external_cmd(char ext_cmd[][100], int max_cmd);

void execute_internal_command(char **args);

void execute_external_command(char **args, char ext_cmd[][100],int count);

void signal_handler(int signum);
#endif