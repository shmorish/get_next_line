/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmorish <shmorish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:32:15 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/02 13:05:34 by shmorish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_before_newline(char *s)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (newline_pos(s) + 1));
	if (!ret)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		ret[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*get_after_newline(char *s)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) - newline_pos(s) + 1));
	if (!ret)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	i++;
	if (s[i] == '\0')
	{
		free(ret);
		free(s);
		return (NULL);
	}
	while (s[i])
		ret[j++] = s[i++];
	ret[j] = '\0';
	free(s);
	return (ret);
}

char	*output_utils(char **store, char *buf, int flag)
{
	char	*line;

	if (flag == 0)
	{
		line = get_before_newline(*store);
		*store = get_after_newline(*store);
		free(buf);
		return (line);
	}
	else
	{
		line = ft_strdup(*store);
		free(*store);
		*store = NULL;
		free(buf);
		return (line);
	}
}

char	*free_and_return_null(char *buf)
{
	free(buf);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	char		*buf;
	int			read_size;

	if (fd < 0 || OPEN_MAX <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if ((read_size == -1) || (read_size == 0 && store[fd] == NULL))
			return (free_and_return_null(buf));
		buf[read_size] = '\0';
		if (store[fd] == NULL)
			store[fd] = ft_strdup(buf);
		else
			store[fd] = ft_strjoin(store[fd], buf);
		if (!newline_ex(store[fd], '\n'))
			return (output_utils(&store[fd], buf, 0));
		if (read_size == 0)
			return (output_utils(&store[fd], buf, 1));
	}
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char	*test;
// 	int		fd1;
// 	int		fd2;
// 	int		i;

// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	i = 0;
// 	for(int i = 0; i < 10; i++)
// 	{
// 		test = get_next_line(fd1);
// 		printf("%d: %s\n", i, test);
// 		free(test);
// 		test = get_next_line(fd2);
// 		printf("%d: %s\n", i, test);
// 		free(test);
// 	}
// 	printf("\n");
// }

// __attribute__((destructor))
// static void	destructor(void){
// 	system("leaks -q a.out");
// }
