/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 03:27:32 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/22 22:58:35 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *paths, char *cmd)
{
	char **path;
	char *tmp;
	char *joinpath;

	if (!paths)
		return (NULL);
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

int		ft_fork(char *line, char *path)
{
	extern char	**environ;
	char		**args;
	pid_t		pid;

	args = ft_strsplit(line, ' ');
	pid = fork();
	if (pid == 0)
		return (execve(path, args, environ));
	else if (pid < 0)
		ft_putendl("Failed to create a child process");
	wait(&pid);
	ft_strdel(args);
	return (0);
}

void	ft_execve(char *line, char *path, t_vars *v)
{
	extern char	**environ;

	v->i = 0;
	v->cmd = ft_strsplit(line, ' ');
	v->path = ft_get_path(path, v->cmd[0]);
	v->fok = ft_fork(line, v->path);
	if (v->fok == -1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(line);
		return ;
	}
	else
	{
		while (environ[v->i])
		{
			if (ft_strncmp(environ[v->i], "PATH", 4) == 0)
				v->fullpath = ft_strdup(&environ[v->i][5]);
			v->i++;
		}
	}
}

void	ft_execve1(char *line, t_vars *v)
{
	extern char	**environ;

	v->i = 0;
	v->fullpath = NULL;
	while (environ[v->i])
	{
		if (ft_strncmp(environ[v->i], "PATH", 4) == 0)
			v->fullpath = ft_strdup(&environ[v->i][5]);
		v->i++;
	}
	v->cmd = ft_strsplit(line, ' ');
	if (!(v->path = ft_get_path(v->fullpath, v->cmd[0])))
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(line);
		return ;
	}
	v->fok = ft_fork(line, v->path);
	if (v->fok == -1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(line);
		return ;
	}
}
