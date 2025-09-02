/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:27:43 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/02 17:09:19 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_clear_len(char *str);

/**
 * @brief clears a string.
 * @param mini t_minishell struct to exit in case of error.
 * @param str pointer to a not cleared string, must be freed before returning.
 * @return the new cleared string.
 * @details a cleared string is a string without "" or '' used just to ignore
 * 			metacharacters, for example "'" is not a cleared string
 * 			(result is: ').
 */
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

/**
 * @brief calculates the length of the cleared string.
 * @param str string to calculate its new length.
 * @return length of the cleared string.
 */
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
