/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:24:39 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/09 17:50:07 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_setup(void);
bool	ft_minishell(t_minishell *mini);
bool	ft_check_valid_input(t_minishell *mini, char *str, char **temp2);

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

	(void)argc;
	(void)argv;
	mini = ft_create_t_minishell(envp);
	signal_setup();
	while (ft_minishell(mini))
		;
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

bool	ft_minishell(t_minishell *mini)
{
	char		*str;
	char		*temp2;

	str = ft_readline_mini(mini, PROMPT);
	if (str == NULL)
		return (false);
	if (ft_check_valid_input(mini, str, &temp2))
		return (free(str), free(temp2), true);
	str = ft_expand_var(mini, &str, false);
	mini->line = ft_parser(mini, str);
	if (ft_expand_clear(mini, &mini->line)
		&& !ft_is_empty(mini->line->line)
		&& ft_validate(mini, mini->line, temp2))
	{
		free(temp2);
		ft_process(mini);
	}
	ft_free_t_minishell_execution(mini);
	return (true);
}

bool	ft_check_valid_input(t_minishell *mini, char *str, char **temp2)
{
	char	*str2;
	char	*temp;
	bool	is_empty;

	temp = ft_strdup(str);
	if (temp == NULL)
	{
		perror(PERROR_OPEN);
		ft_minishell_exit(mini, EXIT_FAILURE);
	}
	*temp2 = ft_strdup(str);
	if (*temp2 == NULL)
	{
		if (temp)
			free(temp);
		perror(PERROR_OPEN);
		ft_minishell_exit(mini, EXIT_FAILURE);
	}
	if (temp[0] != 0 && isatty(STDIN_FILENO))
		add_history(temp);
	str2 = ft_expand_var(mini, &temp, false);
	is_empty = ft_is_empty(str2);
	free(str2);
	return (is_empty);
}
