/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 10:48:57 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/19 09:41:15 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir_home()
{
	extern char	**environ;
	char		**env;
	int			i;

	i = 0;
	env = environ;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME", 4) == 0)
		{
			env[i] += 5;
			chdir(env[i]);
			break;
		}
		i++;
	}
}

void	ft_chdir(char *path)
{
	char	**token = NULL;
	int		len;
	int		cd;

	cd = 0;
	len = ft_strlen(path);
	while (ft_isspace(path[len - 1]))
		len--;
	if (ft_strcmp(path, "cd") == 0 || len == 2)
		chdir_home();
	else
	{
		token = ft_strsplit(path, ' ');
		if (ft_strcmp(token[0], "cd") == 0)
			cd = chdir(token[1]);
		else
			ft_putendl("cd failed");
	}
	if (cd == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(token[1]);
	}
	if (ft_wrd_cnt(path) > 2)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(token[1]);
	}
	free(token[0]);
	free(token[1]);
}
