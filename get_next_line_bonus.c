/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:58:32 by mazaroua          #+#    #+#             */
/*   Updated: 2022/11/16 18:58:34 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}

char	*extract_line(char	*s)
{
	int		i;
	char	*line;

	if (*s == '\0')
		return (NULL);
	i = 0;
	line = malloc(ft_len(s) + 2);
	if (!line)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\n')
		{
			line[i] = '\n';
			i++;
			break ;
		}
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	check_no_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*skip(char *line, char *temp)
{
	int		i;
	int		t;
	int		l;
	char	*new_temp;

	i = 0;
	t = ft_strlen(temp);
	if (temp[ft_len(temp)] == '\0')
	{
		free(temp);
		return (NULL);
	}
	l = ft_strlen(line);
	new_temp = malloc(t - l + 1);
	if (!new_temp)
		return (NULL);
	while (temp[l])
		new_temp[i++] = temp[l++];
	new_temp[i] = '\0';
	free(temp);
	return (new_temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*temp[OPEN_MAX];
	char		*line;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	readed = 1;
	while (readed > 0 && check_no_new_line(temp[fd]) == 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (free(buffer), NULL);
		buffer[readed] = '\0';
		temp[fd] = ft_strjoin(temp[fd], buffer);
	}
	line = extract_line(temp[fd]);
	temp[fd] = skip(line, temp[fd]);
	free(buffer);
	return (line);
}
