/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:47:31 by musisman          #+#    #+#             */
/*   Updated: 2025/03/19 11:45:54 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	void	file_control(int *fd_infile, int *fd_outfile, int ac, char **av)
{
	*fd_infile = open(av[1], O_RDONLY);
	if (*fd_infile == -1 && ft_strncmp(av[1], "here_doc", 8))
		error(ERR_RFILE);
	if (!ft_strncmp(av[1], "here_doc", 8))
		*fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		*fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (*fd_outfile == -1)
		error(ERR_WFILE);
}

static void	child(char *av, char **env)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		error(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		error(ERR_PRC);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		do_execve(env, av);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], 0);
		waitpid(pid, NULL, 0);
	}
}

static void	read_strin(char *limiter, int fds[])
{
	char	*line;
	int		ln_limit;
	int		ln_line;

	ln_limit = ft_strlen(limiter);
	close(fds[0]);
	while (1)
	{
		line = get_next_line(0);
		ln_line = ft_strlen(line);
		if (!ft_strncmp(line, limiter, ln_limit) && ln_line == ln_limit + 1)
		{
			get_next_line(1);
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, fds[1]);
		free(line);
	}
}

void	here_doc(char *limiter)
{
	pid_t	pid;
	int		fds[2];

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
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	int	input_fd;
	int	output_fd;
	int	i;

	if (ac < 5)
		error(ERR_ARG);
	file_control(&input_fd, &output_fd, ac, av);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			error(ERR_ARG);
		i = 3;
		here_doc(av[2]);
	}
	else
	{
		i = 2;
		dup2(input_fd, 0);
	}
	while (i < ac - 2)
		child(av[i++], env);
	dup2(output_fd, 1);
	do_execve(env, av[ac - 2]);
	return (0);
}
