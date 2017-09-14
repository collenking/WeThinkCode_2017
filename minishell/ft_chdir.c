/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 10:48:57 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/14 14:54:01 by cnkosi           ###   ########.fr       */
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
	char		**token;

	if (ft_strcmp(path, "cd") == 0)
		chdir_home();
	else
	{
		token = ft_strsplit(path, ' ');
		if (ft_strcmp(token[0], "cd") == 0)
			chdir(token[1]);
		else
			ft_putendl("cd failed");
		free(token[0]);
		free(token[1]);
	}
}
