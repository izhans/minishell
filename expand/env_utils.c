/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:39:53 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/04 17:19:48 by ralba-ji         ###   ########.fr       */
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
	t_envp	*env_node;

	word_len = ft_word_name_len(str);
	env_node = mini->tenvp;
	while (env_node)
	{
		if (ft_strncmp(env_node->key, str,
				ft_max(ft_strlen(env_node->key), word_len)) == 0)
			return (env_node->value);
		env_node = env_node->next;
	}
	return (NULL);
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
	t_envp	*env_node;

	word_len = ft_word_name_len(str);
	env_node = mini->tenvp;
	if (str[0] == '?')
		return (ft_number_len(mini->exit_status));
	else if (word_len == 0)
		return (1);
	while (env_node)
	{
		if (ft_strncmp(env_node->key, str,
				ft_max(ft_strlen(env_node->key), word_len)) == 0)
			return (ft_strlen(env_node->value));
		env_node = env_node->next;
	}
	return (0);
}

/**
 * @brief calculates the size of an t_envp list.
 * @param list
 * @returns the size of the list.
 */
int ft_envp_lstsize(t_envp *list)
{
    int size;

    size = 0;
    while (list)
    {
        size++;
        list = list->next;
    }
    return (size);
}

/**
 * @brief transforms t_envp to char **
 * @param list t_envp list
 * @return the transformed list or NULL if malloc fails.
 */
char **ft_envp_list_to_str_array(t_envp *list)
{
    int size;
    char **array;
    int i;

    size = ft_envp_lstsize(list);
    array = ft_calloc(size + 1, sizeof(char *));
    if (!array)
        return (NULL);
    i = 0;
    while (list)
    {
        array[i] = ft_calloc(ft_strlen(list->key) + ft_strlen(list->value) + 2, 1);
        if (!array[i])
            return (ft_free_str_array(array), NULL);
        ft_strlcpy(array[i], list->key, ft_strlen(list->key) + 1);
        array[i][ft_strlen(list->key)] = '=';
		
        ft_strlcpy(&array[i][ft_strlen(list->key) + 1], list->value, ft_strlen(list->value) + 1);
		printf("%s\n", array[i]);
        list = list->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}