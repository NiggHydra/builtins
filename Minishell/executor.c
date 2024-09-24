#include "minishell.h"

t_list	*last_lst(t_list *lst, int index)
{
	t_list	*list;
	int		i;

	if (!lst)
		return (NULL);
	list = lst;
	i = 0;
	while (i != index)
	{
		i++;
		list = list->next;
	}
	return (list);
}

char	*add_data_i(t_list *list, int index)
{
	int		i;
	t_list	*tmp;

	i = 0;

	if (list == NULL)
		return (0);
	tmp = list;
	while (i != index)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	return (tmp->content);
}

void	add_content(int index, t_list *lst)
{
	char	*content;
	char	*tmp;

	int i = 0;
	int j = 0;
	tmp = malloc(1000);
	content = add_data_i(lst, index);
	while (content[i])
		tmp[j++] = content[i++];
	tmp[j] = '\0';
	last_lst(lst, index)->content = ft_strdup(tmp);
	//printf ("++lst %s", last_lst(lst, index)->content);
	free(tmp);
}

int	ft_echo(t_list *data)
{
	(void)data;
	printf("test\n");

	return 0;
}

int	executor(char *str, t_list *data)
{
	//printf ("executor %s | %d\n",str,strcmp(str,"echo"));
	if ((strcmp(str,"echo") == 0))
		ft_echo(data);
	 	//ft_echo(&data);
	return (0);
}
void	cut_str(char *s)
{
	int i;

	i = 0;
	while (((s[i] >= 9 && s[i] <= 13) || s[i] == 32) && s[i + 1] != '\0')
	{
		printf ("here\n");
		s++;
		printf("str >> %s \n",s);
	}
	if (((s[i] >= 9 && s[i] <= 13) || s[i] == 32) && s[i + 1] == '\0')
	{
		*s = '\0';
		return ;
	}	

}
int main (int ac, char **av)
{
	//t_list *data = NULL;
	//t_list	*copy = NULL;
	//char *tmp;
	char *str;
	char **word;

	
	(void)ac;
	(void)av;
	 str = NULL;
	
	//int i = 0;
	//int j = 0;
	while (1)
	{
		//str = get_next_line (0);
		str = readline("input : ");
		add_history(str);

		word = ft_split(str, ' ');
		//executor(tmp, data);

		//while (*str)
		//{
		//	cut_str(str);
		//	printf("ctr >> %s \n",str);
		//	if (data == NULL)
		//	{

		//	}
		//	j = 0;
		//	tmp = malloc (sizeof(t_list) * (word + 1));
		//	while (*str)
		//	{
		//		tmp[j] = *(str);
		//		str ++;
		//		j ++;
		//	}
		//	tmp[j] = '\0';
		//	lstadd_back(&data,lstnew(tmp));
		//}
		//i = 0;
		//copy = data;
		//while (copy != NULL)
		//{
		//	add_content(i, data);
		//	copy = copy->next;
		//	i ++;
		//}
		//free(str);

	}
	return 0;
}