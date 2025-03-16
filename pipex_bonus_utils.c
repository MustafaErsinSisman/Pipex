/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:48:20 by musisman          #+#    #+#             */
/*   Updated: 2025/03/16 10:29:51 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error(char *err)
{
	perror(err);
	exit(1);
}

static char	*ft_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0 && env[i + 1])
		i++;
	if (!env[i + 1])
		error(ERR_PATH);
	path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	return (path);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*arg;
	char	*str;
	char	*tmp;

	tmp = ft_path(env);
	path = ft_split(tmp, ':');
	free(tmp);
	i = -1;
	while (path[++i])
	{
		arg = ft_strjoin(path[i], "/");
		str = ft_strjoin(arg, cmd);
		free(arg);
		if (access(str, F_OK) == 0)
		{
			ft_free(path);
			return (str);
		}
		free(str);
	}
	ft_free(path);
	return (NULL);
}

void	do_execve(char **env, char *av)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd[0])
	{
		ft_free(cmd);
		error(ERR_CMD);
	}
	path = find_path(cmd[0], env);
	if (!path)
	{
		ft_free(cmd);
		error(ERR_CMD);
	}
	if (execve(path, cmd, env) == -1)
		error(ERR_PRC);
	free(path);
}

