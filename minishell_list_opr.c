#include"minishell.h"
#include <stdio.h>

int insert_at_first(mini_list **head, mini_list **tail, int data)
{
    mini_list *new = malloc(sizeof(mini_list));

    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;

    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new -> next = *head;
        (*head) -> prev = new;
        *head = new;
    }
    return 1;
}
int insert_at_last(mini_list **head, mini_list **tail, int data)
{
    mini_list *new = malloc(sizeof(mini_list));

    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;

    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        new -> prev = *tail;
        (*tail) -> next = new;
        *tail = new;
    }
    return 1;
}
int delete_first(mini_list **head, mini_list **tail)
{
    if(*head == NULL)
    {
        return 0;
    }

    mini_list *temp = *head;

    if(*head == *tail)
    {
        free(*head);
        *head = NULL;
        *tail = NULL;
        return 1;
    }
    *head = temp -> next;
    (*head) -> prev =NULL;
    free(temp);
    return 1;

}
void print_list(mini_list *head)
{
    if(head == NULL)
    {
        printf("INFO: List Does Not Contain Any Data\n");
    }
    else
    {
        printf("Head -> ");
        while(head)
        {
            printf("%d <-",head->data);

            head = head -> next;
            if(head)
            {
                printf("> ");
            }
        }
        printf(" Tail\n");
    }
}