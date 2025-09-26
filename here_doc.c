/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:41:51 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/26 14:26:14 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_tmp_name(t_minishell *mini, int i);

/**
 * @brief registers a heredoc, creating a file and reading the input from
 * 			standard input and cleaning and expanding (expand only if
 * 			heredoc filename doesnt have any double or simple quote).
 * @param mini to call clear and expand functions.
 * @param filename  pointer to the string holding the filename
 * @param expand bool that shows wheter it must be expanded or not.
 */
void	ft_register_heredoc(t_minishell *mini, char **filename, bool expand)
{
	static int	i = 1;
	char		*str;
	char		*name;
	int			fd;

	*filename = ft_clear_var(mini, filename);
	name = ft_get_tmp_name(mini, i++);
	fd = open(name, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return ;
	str = readline("> ");
	while (str != NULL && ft_strcmp(str, *filename) != 0)
	{
		if (expand)
			str = ft_expand_var(mini, &str, true);
		ft_putendl_fd(str, fd);
		free(str);
		str = readline("> ");
	}
	if (str == NULL)
		printf(WARNING_HD_EOF, *filename);
	else
		free(str);
	free(*filename);
	*filename = name;
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
