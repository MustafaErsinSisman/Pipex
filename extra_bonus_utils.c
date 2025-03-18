/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:14:13 by musisman          #+#    #+#             */
/*   Updated: 2025/03/18 10:47:56 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void child(char *av, char **env, int *write_pipe, int *read_pipe, int is_last)
{
    if (read_pipe) 
    {
        dup2(read_pipe[0], 0);
        close(read_pipe[0]);
        close(read_pipe[1]);
    }
    if (!is_last) 
    {
        dup2(write_pipe[1], 1);
        close(write_pipe[0]);
        close(write_pipe[1]);
    }
    if (is_last) 
    {
        int temp_fd = dup(1);
        int output_fd = open("out", O_CREAT | O_WRONLY | O_APPEND, 0777);
        dup2(output_fd, 1);
        close(output_fd);
        do_execve(env, av);
        dup2(temp_fd, 1);
        close(temp_fd);
    } 
    else
        do_execve(env, av);

}

static int	creat_process(char *av, char **env, int *write_pipe, int *read_pipe, int is_last)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(ERR_PRC);
	if (pid == 0)
		child(av, env, write_pipe, read_pipe, is_last);
	return (pid);
}

void create_pipes_and_processes(int ac, char **av, char **env, int *pid, int *prev_pipe)
{
    int new_pipe[2];
    int i;

    i = -1;
    while (++i < ac - 4)
    {
        if (pipe(new_pipe) == -1)
            error(ERR_PIPE);
        pid[i] = creat_process(av[i + 2], env, new_pipe, prev_pipe, 0);
        if (prev_pipe[1] != -1)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
        prev_pipe[0] = new_pipe[0];
        prev_pipe[1] = new_pipe[1];
    }
}

void pipex_process(int ac, char **av, char **env, int *fds)
{
    int *pid;
    int prev_pipe[2];
    int i;
    int j;

    pid = malloc(sizeof(int) * (ac - 3));
    if (!pid)
        error(ERR_MEM);
    prev_pipe[0] = fds[0];
    prev_pipe[1] = -1;
    create_pipes_and_processes(ac, av, env, pid, prev_pipe);
    i = ac - 4;
    pid[i] = creat_process(av[ac - 2], env, NULL, prev_pipe, 1);
    close(prev_pipe[0]);
    close(prev_pipe[1]);
    j = -1;
    while (++j < ac - 3)
        waitpid(pid[j], NULL, 0);
    free(pid);
}


