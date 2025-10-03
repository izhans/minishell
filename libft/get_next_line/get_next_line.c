/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:53:28 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/03 13:30:44 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_gnl_populate_line(int fd, char **line);
static void	ft_gnl_concat_buffer_to_line(
				char *buffer, char **line, int buffer_len);
static char	*ft_gnl_get_line(char **line);
static void	ft_gnl_clean_line(char **line, int new_line_index);

/**
 * @brief returns the next line of the given fd
 * @param fd the fd from which to read
 * @returns the next line of the fd or NULL if the line couldn't be populated
 * uses a static var to preserve the read info in succesive calls
 * if the line is not initialized, is initalized with a null char
 * the line is populated with the info from the file
 * returns NULL or the next line
 */
char	*get_next_line(int fd)
{
	static char	*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > __FD_SETSIZE)
		return (NULL);
	if (!line)
	{
		line = malloc(1);
		if (line == NULL)
			return (NULL);
		line[0] = '\0';
	}
	ft_gnl_populate_line(fd, &line);
	if (line == NULL)
		return (NULL);
	return (ft_gnl_get_line(&line));
}

/**
 * @brief populates the line with the content from the file
 * @param fd the file descriptor to read from
 * @param line a pointer to the static var that contents the previous read chars
 * reads until a \n is found
 * if an error (-1) or EOF (0) is found, frees the buffer and the line^
 * 						^if is EOF and the line has chars, it is not freed
 * if not, it appends the read chars (buffer) to the line and frees the buffer
 */
static void	ft_gnl_populate_line(int fd, char **line)
{
	char	*buffer;
	int		read_chars;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (ft_gnl_free(line));
	buffer[0] = '\0';
	while (!ft_gnl_has_new_line(buffer))
	{
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars <= 0)
		{
			free(buffer);
			if (read_chars < 0 || ft_strlen(*line) == 0)
				ft_gnl_free(line);
			return ;
		}
		buffer[read_chars] = '\0';
		ft_gnl_concat_buffer_to_line(buffer, line, read_chars);
	}
	free(buffer);
}

/**
 * @brief appends the buffer to the line
 * @param buffer the read chars from the file
 * @param line where to concatenate the buffer
 * @param buffer_len the length of the buffer
 * allocates space for the concatenated line
 * copies line into concatenated line
 * copies buffer into concatenated line
 * null terminates concatenated line
 * frees previous line and replaces it with concatenated line
 */
static void	ft_gnl_concat_buffer_to_line(
	char *buffer, char **line, int buffer_len)
{
	int		line_len;
	char	*concatenated_line;
	int		i;
	int		j;

	line_len = ft_strlen(*line);
	concatenated_line = malloc(line_len + buffer_len + 1);
	if (concatenated_line == NULL)
		return (ft_gnl_free(line));
	i = 0;
	while ((*line)[i])
	{
		concatenated_line[i] = (*line)[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		concatenated_line[i + j] = buffer[j];
		j++;
	}
	concatenated_line[i + j] = '\0';
	free(*line);
	*line = concatenated_line;
}

/**
 * @brief extracts the next line
 * @param line the line from which to extract the next line
 * @returns the next line
 * if the line is empty, frees the line
 * finds the line ending index (\n or \0 in EOF case)
 * copies the line content until the line ending into the next line
 * null terminates the next line
 * cleans the copied info from the line
 * returns the next line
 */
static char	*ft_gnl_get_line(char **line)
{
	char	*next_line;
	int		new_line_index;
	int		i;

	if (ft_strlen(*line) == 0)
		return (ft_gnl_free(line), NULL);
	new_line_index = ft_gnl_where_is_new_line(*line);
	next_line = malloc(new_line_index + 1);
	if (next_line == NULL)
		return (ft_gnl_free(line), NULL);
	i = 0;
	while (i < new_line_index)
	{
		next_line[i] = (*line)[i];
		i++;
	}
	next_line[i] = '\0';
	ft_gnl_clean_line(line, new_line_index);
	return (next_line);
}

/**
 * @brief removes the extracted info from the line
 * @param line the line to clean
 * @param new_line_index the position where the info to preserve starts
 * if without the info to remove the line is empty, frees the line
 * copies the info to preserve into the temp line and null terminates it
 * frees the line
 * replaces the line with the temp line
 */
static void	ft_gnl_clean_line(char **line, int new_line_index)
{
	int		line_len;
	char	*tmp_line;
	int		i;

	line_len = ft_strlen(*line);
	if (line_len == new_line_index)
		return (ft_gnl_free(line));
	tmp_line = malloc(line_len - new_line_index + 1);
	if (tmp_line == NULL)
		return (ft_gnl_free(line));
	i = 0;
	while ((*line)[new_line_index])
	{
		tmp_line[i] = (*line)[new_line_index];
		i++;
		new_line_index++;
	}
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
}
