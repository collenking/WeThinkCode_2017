/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 10:48:57 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/21 14:36:14 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*chdir_home()
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "HOME", 4) == 0)
		{
			return (&environ[i][5]);
			break ;
		}
		i++;
	}
	return (NULL);
}

void	ft_chdir(char *path)
{
	char	**token = NULL;
	int		len;

	len = ft_strlen(path);
	while (ft_isspace(path[len - 1]))
		len--;
	if (ft_strcmp(path, "cd") == 0 && len == 2)
		chdir(chdir_home());
	else
	{
		token = ft_strsplit(path, ' ');
		if (ft_strcmp(token[0], "cd") == 0)
		{
			if (chdir(token[1]) == -1)
			{
				ft_putstr("cd: no such file or directory: ");
				ft_putendl(token[1]);
			}
			free(token[0]);
			free(token[1]);
		}
		else
			ft_putendl("cd failed");
	}
	if (ft_wrd_cnt(path) > 2)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(token[1]);
	}
}
