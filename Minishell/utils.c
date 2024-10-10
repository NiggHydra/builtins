#include "minishell.h"

size_t	ft_count_word(char const *s, char c)
{
	size_t	word;
	size_t	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

char	*ft_strcmp2(const char *s1, const char *s2)
{
	size_t			i;
	size_t			j;
	size_t			k;
	char	*result;

	i = 0;
	k = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0' || s2[i] != '\0'))
		i ++;
	j = i;
	while(s2[i] != '\0')
	{	
		k ++;
		i ++;
	}
	result = malloc(sizeof(char *) * (k + 1));
	i = j;
	j = -1;
	while (s2[i] != '\0')
		result[++j] = s2[i++];
	result[j + 1] = '\0';
	return (result);
}

void ft_strcat(char *d, const char *s)
{
	size_t	index;
	size_t	i;

	index = 0;
	while (d[index])
		index++;
	i = 0;
	while (s[i])
	{
		d[index + i] = s[i];
		i++;
	}
	d[index + i + 1] = '\0';
}
void	ft_swap_chr(char **a, char **b)
{
	char *tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_env(t_list *data)
{
	int i = 0;
	int n;
	int j = 0;

	while (data->exprt[i] != NULL)
		i ++;
	n = i;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (strcmp(data->exprt[j], data->exprt[j + 1]) > 0)
				ft_swap_chr(&data->exprt[j], &data->exprt[j + 1]);
			j ++;	
		}
		i ++;
	}
}

void	current_dir(t_list *data)
{
	char pwd[1000];
	data->directory  = ft_strcmp2(getenv("HOME"), getcwd(pwd, sizeof(pwd)));
	data->directory  = ft_strjoin("~",data->directory);
	data->directory  = ft_strjoin(data->directory ,"$ ");
}

int strlen_tab(char **s)
{
	int i = 0;
	while(s[i] != NULL)
		i ++;
	return (i);
}
char	**re_fill_data(char **str, char *s, int n)
{
	int i;
	char **copy;

	if (s == NULL)
		return (NULL);
	copy = malloc(sizeof(char *) * (n + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		copy[i] = ft_strdup(str[i]);
		i ++;
	}
	copy[i] = ft_strdup(s);
	copy[i + 1] = NULL;
	return (copy);
}

char 	**realloc_tab(char **str, char *s, int concat)
{
	int i;
	int n;
	char *concatenation;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strncmp(str[i], s, strlen_nvar(s))  == 0 )
		{
			if (concat == 1)
			{
				concatenation = ft_strchr(s, '=');
				// concatenation;
				str[i] = ft_strjoin (str[i], concatenation + 1);
				return (str);
			}
			else if  (concat == 0)
			{
				free (str[i]);
				str[i] = ft_strdup (s);
				return (str);
			}
			
		}
		//free (concatenation);
		i ++;
	}
	n = strlen_tab (str) + 1;
	str = re_fill_data (str,s, n);
	return (str);
}

int	free_tab(char **s)
{
	int i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	return (0);
}

int	strlen_nvar (char *s)
{
	int i;

	i = 0;
	while ((s[i] != '=' && s[i] != '+') && s[i] != '\0')
		i ++;
	return (i);
}


int nt_valid_identifier(char *s)
{
	ft_putstr_fd("export : `", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("`: not a valid identifier\n", 1);
	return (0);
}

char 	*get_env(char *s, t_list *data)
{
	int i;
	char *env;

	i = 0;
	env = NULL;
	while (data->envrnmt[i] != NULL)
	{
		if (ft_strncmp(s, data->envrnmt[i], ft_strlen(s)) == 0)
		{
			env = ft_strjoin(s , "=");
			env = ft_strcmp2 (env, data->envrnmt[i]);
			printf ("your env >>>>>> %s\n", env);
			break;
		}
		i ++;
	}
	if (!env)
		return (NULL);
	return (env);
}

int	check_pipe(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
	{
		if (strcmp (s[i], "|") == 0)
			return (1);
		i ++;
	}
	return (0);
}

int	cmd(char **str, t_list *data)
{
	if ((strcmp(str[0],"echo") == 0))
		return(ft_echo(str));
	else if ((strcmp(str[0],"pwd") == 0))
		return (ft_pwd());
	else if ((strcmp(str[0],"cd") == 0))
		return (ft_cd(str, data));
	else if ((strcmp(str[0],"env") == 0))
		return (ft_env(data));
	else if ((strcmp(str[0],"export") == 0))
		return (ft_export(data, str));
	else if ((strcmp(str[0],"unset") == 0))
		return (ft_unset(data, str));
	else if ((strcmp(str[0], "get_env") == 0))
		get_env(str[1], data);
	else
		return (cmd_excve(str, data));
	return (0);
}
