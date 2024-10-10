/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:08:25 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/10/10 11:28:58 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int	sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd ("\n", 1);
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay ();
		//rl_on_new_line();
		//rl_on_new_line();
	}
	return ;
}



void my_signal(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = SIG_IGN;
	signal( SIGINT ,handle_signal);
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}