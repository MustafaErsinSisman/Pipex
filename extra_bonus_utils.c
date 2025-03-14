/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:48:06 by musisman          #+#    #+#             */
/*   Updated: 2025/03/14 12:48:06 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "pipex_bonus.h"

void	read_strin(char *limiter, int fds[])
{
	char	*line;

	line = get_next_line(0);
	close(fds[0]);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
                        get_next_line(1);
			free(line);
			exit(0);
		}
                ft_putstr_fd(line, fds[1]);
		free(line);
		line = get_next_line(0);
	}
}