/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 03:27:32 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/11 18:05:18 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *path, char *cmd)
{
	char			**ret;
	char			buff[1000];
	char 			*r = buff;
	DIR				*d;
	struct	dirent	*dir;

	ret = ft_strsplit(path, ':');
	while (*ret)
	{
		*ret = ft_strjoin(*ret, "/");
		d = opendir(*ret);
		if (d == NULL) return (NULL);
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strcmp(dir->d_name, cmd) == 0)
			{
				*ret = ft_strcat(*ret, cmd);		
				r = *ret;
			}
		}
		closedir(d);
		ret++;
	}
	return (r);
}

void	ft_execve(char *line)
{
	extern char	**environ;
	char		**env;
	char		*path;
	char		**cmd;
	char		buff[1000];
	char		*p;

	p = buff;
	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
		{
			*env += 5;
			path = ft_strdup(*env);
		}
		env++;
	}
	cmd = ft_strsplit(line, ' ');
	p = ft_get_path(path, cmd[0]);
	ft_fork(line, p);
}

void	ft_fork(char *line, char *path)
{
	extern char	**environ;
	char		**args;
	//int			ret = 0;
	pid_t		pid;

	args = ft_strsplit(line, ' ');
	pid = fork();
	if (pid == 0)
		/*ret = */execve(path, args, environ);
	else if (pid < 0)
		ft_putendl("Failed to create a child process");
	wait(&pid);
}
