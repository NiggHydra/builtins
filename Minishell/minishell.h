#ifndef MINISHELL_H
#define MINISHELL_H
//#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"
#include <sys/wait.h>
#include <signal.h>
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
void	ft_swap_chr(char **a, char **b);
char 	*get_env(char *s, t_list *data);
void	handle_signal(int	sig);
void my_signal(void);
int	check_pipe(char **s);
int	cmd(char **str, t_list *data);
int	ft_echo(char **s);
int	ft_env(t_list *data);
int ft_pwd(void);
int	update_pwd(char *old_pwd, t_list *data);
int	ft_cd(char **s, t_list *data);
int	add_export(t_list *data, char *s);
int	ft_export(t_list *data, char **s);
char **delete_env(t_list *data, char *s);
int	ft_unset(t_list *data, char **s);
int	cmd_excve(char  **s, t_list *data);
int	search_path(t_list *data);
int test_path(t_list *data, char *s);










#endif