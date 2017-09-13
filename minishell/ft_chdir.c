/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 10:48:57 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/11 18:10:20 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir_home()
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, "HOME", 4) == 0)
		{
			*env += 5;
			chdir(*env);
			break;
		}
		env++;
	}
}

void	ft_chdir(char *path)
{
	char		cwd[1024];
	char		**token;

	if (ft_strcmp(path, "cd") == 0)
		chdir_home();
	else
	{
		token = ft_strsplit(path, ' ');
		if (ft_strcmp(token[0], "cd") == 0)
			chdir(token[1]);
		else if (ft_strcmp(token[0], "pwd") == 0 || 
				ft_strcmp(token[0], "/bin/pwd") == 0)
		{
			getcwd(cwd, sizeof(cwd));
			ft_putendl(cwd);
		}
	}
}
