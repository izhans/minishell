/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:39:53 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/02 19:28:43 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief calculates the length of the env name in str, a name follows this
 * 			$[A-Za-z_][A-Za-z0-9_] or $? (can also just be $).
 * @param mini t_minishell struct with attribute exit_status, to know its length
 * @param str string starting with the name.
 * @return returns the length of the env name in str.
*/
int	ft_word_name_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?')
		return (1);
	while (str[i] == '_' || ft_isalpha(str[i])
		|| (i != 0 && ft_isalnum(str[i])))
		i++;
	return (i);
}

/**
 * @brief returns a non-malloc string with the content of the expansion name
 * 			(not the name neither '='), doesnt work for status.
 * @param mini t_minishell struct, to loop the env attribute to find the word
 * @param str env variable name.
 * @return the content of the env variable.
*/
char	*ft_get_env_var_content(t_minishell *mini, char *str)
{
	int		word_len;
	char	*word_name;
	t_list	*env_node;
	char	*content;

	word_len = ft_word_name_len(str);
	env_node = mini->envp;
	while (env_node)
	{
		content = (char *)env_node->content;
		word_name = ft_substr(content, 0, ft_word_name_len(content));
		if (word_name == NULL)
			ft_minishell_exit(mini, EXIT_FAILURE);
		if (ft_strncmp(word_name, str,
				ft_max(ft_strlen(word_name), word_len)) == 0)
		{
			free(word_name);
			return (ft_strchr(content, '=') + 1);
		}
		free(word_name);
		env_node = env_node->next;
	}
	return (0);
}

/**
 * @brief calculates the length of the expansion (not name, neither '=')
 * 			, works for status.
 * @param mini t_minishell struct to loop over the env.
 * @param str name of the expansion.
 */
int	ft_word_len(t_minishell *mini, char *str)
{
	int		word_len;
	char	*word_name;
	t_list	*env_node;
	char	*content;

	word_len = ft_word_name_len(str);
	env_node = mini->envp;
	if (str[0] == '?')
		return (ft_number_len(mini->exit_status));
	else if (word_len == 0)
		return (1);
	while (env_node)
	{
		content = (char *)env_node->content;
		word_name = ft_substr(content, 0, ft_word_name_len(content));
		if (word_name == NULL)
			ft_minishell_exit(mini, EXIT_FAILURE);
		if (ft_strncmp(word_name, str,
				ft_max(ft_strlen(word_name), word_len)) == 0)
			return (free(word_name), ft_strlen(ft_strchr(content, '=') + 1));
		free(word_name);
		env_node = env_node->next;
	}
	return (0);
}
