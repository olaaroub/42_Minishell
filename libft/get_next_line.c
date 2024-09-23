/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:11:50 by hes-safi          #+#    #+#             */
/*   Updated: 2024/09/03 10:05:42 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*toreturn;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	toreturn = malloc(s1len + s2len + 1);
	while (s1[i])
		toreturn[j++] = s1[i++];
	i = 0;
	while (s2[i])
		toreturn[j++] = s2[i++];
	toreturn[j] = '\0';
	free(s1);
	return (toreturn);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * 2);
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	line[1] = '\0';
	while (read(fd, buffer, 1))
	{
		buffer[1] = '\0';
		line = ft_strjoin_gnl(line, buffer);
	}
	if (!ft_strlen_gnl(line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("Infile.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
