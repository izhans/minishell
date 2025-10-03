/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:24:39 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/03 13:52:53 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_setup(void);

volatile sig_atomic_t	g_sig_num = 0;

/**
 * @brief signal handler function point of entry.
 * @param signal number of signal.
 */
void	signal_handler(int signal)
{
	g_sig_num = signal;
	if (g_sig_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*mini;
	char		*str;

	(void)argc;
	(void)argv;
	mini = ft_create_t_minishell(envp);
	signal_setup();
	while (true)
	{
		str = ft_readline_mini(mini, PROMPT);
		if (str == NULL)
			break ;
		mini->line = ft_parser(mini, str);
		if (ft_expand_clear(mini, &mini->line)
			&& !ft_is_empty(mini->line->line) && ft_validate(mini, mini->line))
			ft_process(mini);
		if (mini->line->line[0] != 0 && isatty(STDIN_FILENO))
			add_history(mini->line->line);
		ft_free_t_minishell_execution(mini);
	}
	rl_clear_history();
	ft_free_t_minishell(mini);
}

/**
 * @brief sets up all signals to catch or ignore.
 */
void	signal_setup(void)
{
	if (isatty(STDIN_FILENO))
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
