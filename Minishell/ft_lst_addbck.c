#include "minishell.h"
t_list *lstnew(void  *content)
{
    t_list *new;

    new = malloc(sizeof(t_list));
    if (new == NULL)
        return NULL;
    new->content = ft_strdup(content);
    new->next = NULL;
    return new;
}

void lstadd_back(t_list **lst, t_list *new)
{
    t_list *temp;

    if (*lst == NULL)
        *lst = new;
    else
    {
        temp = *lst;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}
