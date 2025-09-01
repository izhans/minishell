/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:45:21 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/01 19:04:45 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_clear_len(char *str);

char	*ft_clear_var(t_minishell *mini, char **str)
{
	char	*new;
	char	comma;
	int		i;
	int		j;

	new = ft_calloc(ft_clear_len(*str) + 1, sizeof(char));
	if (new == NULL)
		ft_minishell_exit(mini);
	comma = 0;
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		ft_comma_check(&comma, (*str)[i]);
		if ((comma != 0 && (*str)[i] != comma)
				|| ((*str)[i] != SIMPLE_COMMA && (*str)[i] != DOUBLE_COMMA))
		{
			new[j] = (*str)[i];
			j++;
		}
		i++;
	}
	free(*str);
	return (new);
}

static int	ft_clear_len(char *str)
{
	int		len;
	char	comma;
	int		i;

	len = 0;
	i = 0;
	comma = 0;
	while (str[i])
	{
		ft_comma_check(&comma, str[i]);
		if ((comma != 0 && str[i] != comma)
			|| (str[i] != SIMPLE_COMMA && str[i] != DOUBLE_COMMA))
			len++;
		i++;
	}
	return (len);
}
