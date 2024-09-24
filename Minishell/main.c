#include "minishell.h"

int print_echo(char **s, int i)
{
	while (s[i] != NULL)
	{
		if (s[i + 1] == NULL)
			ft_putstr_fd(s[i], 1);
		else
		{
			ft_putstr_fd(s[i], 1);
			write(1," ",1);
		}
		i ++;
	}
	return (0);
}

int	verify_option(char *s)
{
	int i = 0;

	if (s[i] == '-' && s[i + 1] == 'n')
		i ++;
	while (s[i] != '\0')
	{
		if (s[i] == 'n')
			i ++;
		else
			return (0);
	}
	return (1);
}
int	ft_echo(char **s)
{
	int i;

	i = 1;
	if (s[i] == NULL)
		printf ("\n");
	while (s[i] != NULL && (verify_option(s[i]) == 1))
			i++;
	if (s[i] != NULL && verify_option(s[i]) == 0)
	{
		if (verify_option(s[i - 1]) == 1)
			print_echo(s, i);
		else
		{
			print_echo(s, i);
			write (1, "\n", 1);
		}
	}
	return (0);
}

int	ft_env(t_list *data)
{
	int i;
	i = 0;
	while (data->envrnmt[i] != NULL)
	{
		ft_putstr_fd(data->envrnmt[i], 1);
		write (1, "\n", 1);
		i ++;
	}
	return (0);
}

int ft_pwd(void)
{
	char pwd[1000];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n",pwd);
	return (0);
}
int	ft_cd(char **s, t_list *data)
{
	int i;
	
	i = 1;
	if (s[i] == NULL)
	{
		chdir (getenv("HOME"));
		data->directory = ft_strdup("~$ ");
		return (0);
	}
	else 
	{
		if ((strcmp (s[i], "HOME") == 0 
			|| strcmp (s[i], "~") == 0 || strcmp (s[i], "~/") == 0)
				&& chdir (getenv("HOME")) == 0)
			data->directory  = ft_strdup("~$ ");
		else if (chdir (s[i]) == -1)
			printf("bash: cd: %s: No such file or directory\n",s[i]);
		else
			current_dir(data);

	}
	return (0);
}

int	add_export(t_list *data, char *s)
{
	int i;
	int concat;

	concat = 0;

	i = 0;
	if (ft_isalpha (s[i]) == 0 || s[i] == '=' )
		return (nt_valid_identifier(s));
	while (s[i] != '\0')
	{
		if (ft_isalnum(s[i]) || s[i] == '_')
			i ++;
		else
		{
			if (s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
			{
				if (s[i] == '+' && s[i + 1] == '=')
					concat = 1;
				data->envrnmt = realloc_tab(data->envrnmt, s, concat);
				break;
			}
			return (nt_valid_identifier(s));
		}
	}
	data->exprt = realloc_tab(data->exprt, s ,concat);
	sort_env(data);
	return (0);
}

int	ft_export(t_list *data, char **s)
{
	int i;
	int j;
	int	equal;

	
	j = 0;
	i = 1;
	if (s[i] == NULL)
	{
		while (data->exprt[i] != NULL)
		{
			j = 0;
			equal = 0;
			ft_putstr_fd("declare -x ", 1);
			while (data->exprt[i][j] != '\0')
			{
				if (data->exprt[i][j] == '=' )
				{
					equal = 1;
					ft_putchar_fd(data->exprt[i][j], 1);
					ft_putchar_fd('"', 1);
				}
				else
					ft_putchar_fd(data->exprt[i][j], 1);
				j++;
			}
			if (equal == 1)
				ft_putchar_fd('"', 1);
			ft_putchar_fd('\n', 1);
			i ++;
		}
	}
	else
	{
		while (s[i] != NULL)
		{
			add_export(data, s[i]);
			i++;
		}
	}
	return (0);
}

int delete_env(t_list *data, char *s)
{
	int i;
	//char **copy;
	i = 0;
	char *pth1;
	printf ("here we go %s\n", s);
	while (data->exprt[i] != NULL)
	{
		pth1 = NULL;
		printf ("strlen name var >>> %d\n",strlen_nvar(data->exprt[i]));
		pth1 = strncpy(pth1, data->exprt[i], strlen_nvar(data->exprt[i]));
		//printf ("cmp >>> %s | %s = %d\n",pth1, s, strcmp(pth1, s));
		printf ("%s\n", pth1);
		//if (strcmp(pth1, s) == 0)
		//if ()
		free (pth1);
		i ++;
	}
	
	return (0);
}

int	ft_unset(t_list *data, char **s)
{
	int i;

	i = 1;
	if (s[i] == NULL)
		return (0);
	else
	{
		while (s[i] != NULL)
		{
			delete_env(data, s[i]);
			i++;
		}
	}
	return (0);
}
int	cmd_excve(char  **s, t_list *data)
{
	pid_t fork_t;

	fork_t  = fork ();
	if (fork_t < 0)
		printf ("creation process erreur\n");
	if (fork_t == 0)
	{
		search_path(data);
		if (test_path(data, s[0]) == 0)
			execve (data->path, s, data->envrnmt);
		else
		{
			ft_putstr_fd(s[0], 1);
			ft_putstr_fd(": Command not found\n", 1);
		}
			
	}
	else
		wait(&fork_t);
	return (0);
}
int	search_path(t_list *data)
{
	char *pth;
	int i = 0;
	while (data->envrnmt[i] != NULL)
	{
		if (ft_strncmp("PATH",data->envrnmt[i], 4) == 0)
			pth = ft_strdup (data->envrnmt[i]);
		i ++;
	}
	if (!pth)
		return (1);
	else
	{
		pth = ft_strcmp2("PATH=",pth);
		data->all_path = ft_split(pth, ':');
	}
	return (0);
}

int test_path(t_list *data, char *s)
{
	int i ;
	i = 0;

	char *pths;
	while (data->all_path[i] != NULL)
	{
		pths = ft_strjoin("/", s);
		pths = ft_strjoin( data->all_path[i], pths);
		if (access(pths, F_OK | X_OK) == 0)
		{
			data->path = ft_strdup (pths);
			free(pths);
			return (0);
		}
		free(pths);
		i ++;
	}
	return (1);
}

int	executor(char **str, t_list *data)
{
	if ((strcmp(str[0],"echo") == 0))
		ft_echo(str);
	else if ((strcmp(str[0],"pwd") == 0))
		ft_pwd();
	else if ((strcmp(str[0],"cd") == 0))
		ft_cd(str, data);
	else if ((strcmp(str[0],"env") == 0))
		ft_env(data);
	else if ((strcmp(str[0],"export") == 0))
		ft_export(data, str);
	else if ((strcmp(str[0],"unset") == 0))
		ft_unset(data, str);
	else
		cmd_excve(str, data);
		//printf ("here\n");
	return (0);
}

char	**ft_fill_data(char **env)
{
	int i;
	char **copy;

	i = 0;
	while (env[i] != NULL)
		i ++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);

	i = 0;
	while (env[i] != NULL)
	{
		copy[i] = ft_strdup(env[i]);
		i ++;
	}
	copy[i] = NULL;
	return (copy);
}
int main (int ac, char **av, char **env)
{

	char *str;
	char **word;
	t_list data;
	
	(void)ac;
	(void)av;
	str = NULL;
	data.envrnmt = ft_fill_data(env);
	data.exprt = ft_fill_data(env);
	sort_env(&data);
	current_dir(&data);
	while (1)
	{
		//str = get_next_line (0);
		str = readline(data.directory);
		add_history(str);

		word = ft_split(str, ' ');
		if (*word != NULL)
			executor(word , &data);
		//free (data.envrnmt);
		//free (data.exprt);
	}
	return 0;
}