/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:47:31 by musisman          #+#    #+#             */
/*   Updated: 2025/03/16 16:40:30 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	void	file_control(int *fd_infile, int *fd_outfile, int ac, char **av)
{
	*fd_infile = open(av[1], O_RDONLY);
	if (*fd_infile == -1 && ft_strncmp(av[1], "here_doc", 8))
		error(ERR_RFILE);
	if (!ft_strncmp(av[1], "here_doc", 8))
		*fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY, 0777);
	else
		*fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (*fd_outfile == -1)
		error(ERR_WFILE);
}

static void	read_strin(char *limiter, int fds[])
{
	char	*line;
	size_t len;

	len = ft_strlen(limiter);
	close(fds[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			get_next_line(1);
			free(line);
			exit(0);
		}
		if (ft_strncmp(line, limiter, len) == 0 && len == ft_strlen(line))
		{
			get_next_line(1);
			free(line);
			close(fds[1]);
			return ;
		}
		ft_putstr_fd(line, fds[1]);
		free(line);
		line = get_next_line(0);
	}
}

void	here_doc(char *limiter, int ac, char **av, int *i)
{
	pid_t	pid;
	int		fds[2];

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			error(ERR_ARG);
		*i = 3;
		if (pipe(fds) == -1)
			error(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			error(ERR_PRC);
		if (pid == 0)
			read_strin(limiter, fds);
		else
		{
			close(fds[1]);
			dup2(fds[0], 0);
			close(fds[0]);
			wait(NULL);
		}
	}
	else
		*i = 2;
}

int	main(int ac, char **av, char **env)
{
	int	input_fd;
	int	output_fd;
	int	i;
	int	fds[2];

	if (env == NULL)
		error(ERR_ENV);
	if (ac < 5)
		error(ERR_ARG);
	file_control(&input_fd, &output_fd, ac, av);
	here_doc(av[2], ac, av, &i);
	if (i == 2)
		dup2(input_fd, 0);
	if (pipe(fds) == -1)
		error(ERR_PIPE);
	process_tree(ac, av, env, fds);
	close(fds[0]);
	close(fds[1]);
	dup2(output_fd, 1);
	close(output_fd);
	do_execve(env, av[ac - 2]);
}
