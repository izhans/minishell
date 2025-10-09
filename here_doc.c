/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:41:51 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/09 17:08:28 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_get_tmp_name(t_minishell *mini, int i);
static void		ft_collect_heredoc_input(t_minishell *mini, char *delim,
					char *tmp_name, bool expand);

/**
 * @brief creates a child and registers a specific heredoc, handles Ctrl-C
 * 			killing the child.
 * @param mini to expand env variables and handle errors.
 * @param filename pointer to position where the temporary filename must be.
 * @param expand true if it must expand the input or not.
 * @return true if child was NOT killed, false otherwise.
 */
bool	ft_register_heredoc(t_minishell *mini, char **filename, bool expand)
{
	static int	i = 1;
	char		*name;
	pid_t		pid;
	int			status;

	*filename = ft_clear_var(mini, filename);
	name = ft_get_tmp_name(mini, i++);
	pid = fork();
	if (pid == FORK_ERROR)
		return (perror("fork"), false);
	else if (pid == FORK_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_collect_heredoc_input(mini, *filename, name, expand);
		free(name);
		ft_minishell_exit(mini, EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	free(*filename);
	*filename = name;
	if (!signal_check(status))
		return (unlink(name), false);
	return (true);
}

/**
 * @brief handles input collection for heredoc.
 * @param mini t_minishell struct to free and expand env variables.
 * @param delim delimiter of heredoc.
 * @param tmp_name temporary file name for heredoc.
 * @param expand true if it must expand, false otherwise.
 */
static void	ft_collect_heredoc_input(t_minishell *mini, char *delim,
			char *tmp_name, bool expand)
{
	char	*str;
	int		fd;

	fd = open(tmp_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		return (perror(PERROR_OPEN), ft_minishell_exit(mini, EXIT_FAILURE));
	}
	str = ft_readline_mini(mini, "> ");
	while (str != NULL && ft_strcmp(str, delim) != 0)
	{
		if (expand)
			str = ft_expand_var(mini, &str, true);
		ft_putendl_fd(str, fd);
		free(str);
		str = ft_readline_mini(mini, "> ");
	}
	if (str == NULL)
		ft_putendl_fd(WARNING_HD_EOF, STDERR_FILENO);
	else
		free(str);
	close(fd);
}

/**
 * @brief checks whether a filename str must be expanded or not, checking
 * 			if there is any double or simple quotes.
 * @param str string to check quotes.
 * @return false if there is any quote and it must not expand, true otherwise.
 */
bool	ft_must_expand(char *str)
{
	char	comma;
	int		i;

	i = 0;
	comma = 0;
	while (str[i])
	{
		ft_comma_check(&comma, str[i]);
		if (comma != 0)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief creates the name for the heredoc temporary file, adding the
 * 			corresponding number.
 * @param mini t_minishell struct to call exit in case of error.
 * @param i number of heredoc.
 * @returns malloc string with the name of the heredoc file.
 */
static char	*ft_get_tmp_name(t_minishell *mini, int i)
{
	char	*str;
	char	*itoa;

	itoa = ft_itoa(i);
	if (!itoa)
		ft_minishell_exit(mini, EXIT_FAILURE);
	str = ft_strjoin(TMP_FILE_PREFIX, itoa);
	free(itoa);
	if (!str)
		ft_minishell_exit(mini, EXIT_FAILURE);
	return (str);
}
