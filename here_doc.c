/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:41:51 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/13 21:18:40 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_register_heredoc(t_minishell *mini, char **filename, bool expand);
bool	ft_must_expand(char *str);
static char	*ft_get_tmp_name(t_minishell *mini, int i);

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
