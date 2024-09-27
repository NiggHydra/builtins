#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_list
{
	char *content;
	char *path;
	char *directory;
	char **all_path;
	char *str;
	char **envrnmt;
	char **exprt;
	//struct s_list *next;
} t_list;


t_list *lstnew(void *content);
void lstadd_back(t_list **lst, t_list *new);
size_t	ft_count_word(char const *s, char c);
int	verify_option(char *s);
char	*ft_strcmp2(const char *s1, const char *s2);
void ft_strcat(char *d, const char *s);
void	sort_env(t_list *data);
int	search_path(t_list *data);
int test_path(t_list *data, char *s);
void	current_dir(t_list *data);
char	**ft_fill_data(char **env);
int	ft_export(t_list *data, char **s);
int strlen_tab(char **s);
char	**re_fill_data(char **str, char *s, int n);
char 	**realloc_tab(char **str, char *s, int concat);
char  *assign_val(char *s);
int	strlen_nvar (char *s);
int nt_valid_identifier(char *s);
int	free_tab(char **s);







#endif