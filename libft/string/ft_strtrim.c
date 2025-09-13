/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:55:22 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/10 22:32:32 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_char_is_in_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;

	if (!s1 || *s1 == '\0')
		return (ft_strdup(""));
	start = 0;
	len = ft_strlen(s1);
	while (s1[start] && ft_char_is_in_set(s1[start], set))
		start++;
	while (len >= 1 && ft_char_is_in_set(s1[len - 1], set))
		len--;
	len -= start;
	if (len <= 0)
		return (ft_strdup(""));
	return (ft_substr(s1, start, len));
}

static char	*ft_char_is_in_set(char c, char const *set)
{
	return (ft_strchr(set, c));
}
