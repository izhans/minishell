/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:24:39 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/26 14:33:13 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    signal_setup();

volatile sig_atomic_t sig_num = 0;

/**
 * @brief signal handler function point of entry.
 * @param signal number of signal.
 */
void    signal_handler(int signal)
{
    sig_num = signal;
    if (sig_num == SIGINT)
    {
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
    }
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_minishell *mini;
	char		*str;

	mini = ft_create_t_minishell(envp);
    signal_setup();
	while (true)
	{
        str = readline("minishell> ");
        if (str == NULL)
            break ;
		mini->line = ft_parser(mini, str);
        if (!ft_is_empty(mini->line->line) && ft_validate(mini, mini->line))
            ft_process(mini);
        if (mini->line->line[0] != 0)
            add_history(mini->line->line);
	    
        ft_free_t_minishell_execution(mini);
	}
    ft_free_t_minishell(mini);
}

/**
 * @brief sets up all signals to catch or ignore.
 */
void    signal_setup()
{
    if (isatty(0))
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
    }
}
