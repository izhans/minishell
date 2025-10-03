/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:35:38 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/04 01:45:51 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks whether a process has died due to a signal, restores SIGINT
 * 			handler for the parent.
 */
bool	signal_check(int status)
{
	signal(SIGINT, signal_handler);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (ft_putendl(""), false);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		if (__WCOREDUMP(status) == 0)
			ft_putendl("Quit (core dumped)");
		else
			ft_putendl("Quit");
		return (false);
	}
	return (true);
}

/**
 * @brief set up signals for childs.
 */
void	signal_setup_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
