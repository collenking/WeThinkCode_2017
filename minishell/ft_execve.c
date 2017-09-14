/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 03:27:32 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/14 14:57:48 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *paths, char *cmd)
{
	char **path;
	char *tmp;
	char *joinpath;

	path = ft_strsplit(paths, ':');
	while (*path)
	{
		tmp = ft_strjoin(*path++, "/");
		joinpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(joinpath, F_OK) == 0)
			return (joinpath);
	}
	return (NULL);
}

void	ft_fork(char *line, char *path)
{
	extern char	**environ;
	char		**args;
	pid_t		pid;

	args = ft_strsplit(line, ' ');
	pid = fork();
	if (pid == 0)
		execve(path, args, environ);
	else if (pid < 0)
		ft_putendl("Failed to create a child process");
	wait(&pid);
	ft_strdel(args);
}

void	ft_execve(char *line)
{
	extern char	**environ;
	char		**env;
	char		*path;
	char		**cmd;
	char		*p;
	int			i;

	i = 0;
	env = environ;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			path = ft_strdup(&env[i][5]);
		i++;
	}

	cmd = ft_strsplit(line, ' ');
	p = ft_get_path(path, cmd[0]);
	ft_fork(line, p);
}
