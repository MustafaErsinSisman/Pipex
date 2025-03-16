/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:08:41 by musisman          #+#    #+#             */
/*   Updated: 2025/03/16 15:51:01 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child(char *av, char **env, int *fds)
{
	dup2(fds[1], 1);
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	do_execve(env, av);
}

static int	creat_process(void (*func)(char *, char **, int *)
		, char **av, char **env, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(ERR_PRC);
	if (pid == 0)
		func(*av, env, fds);
	return (pid);
}

void process_tree(int ac, char **av, char **env, int *fds)
{
        pid_t *pid;
        int j;
        int i;
        
        i = 2;
        if (ft_strncmp(av[1], "here_doc", 8) == 0)
	        i = 3;
        pid = malloc((ac - 2 - i) * sizeof(pid_t));
        if (!pid)
		error(ERR_PRC);
        j = -1;
        while (++j < ac - 2 - i)
        {
	        pid[j] = creat_process(child, &av[j + i], env, fds);
	        close(fds[1]);
	        dup2(fds[0], 0);
	        close(fds[0]);
        }
        j = 0;
        i = 2;
        if (ft_strncmp(av[1], "here_doc", 8) == 0)
	        i = 3;
        while (j < ac - 2 - i)
	        waitpid(pid[j++], NULL, 0);
}
