/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:23:04 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/22 22:58:38 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env()
{
	int		i;
	extern char		**environ;

	i = 0;
	while (environ[i])
		ft_putendl(environ[i++]);
}

char	**add_env(char *name, char *value, t_vars *v)
{
	extern char	**environ;

	v->len = ft_strlen(name) + ft_strlen(value);
	v->i = 0;
	v->env = environ;
	while (v->env[v->i])
		v->i++;
	v->i--;
	v->env[v->i + 1] =
		(char*)malloc(sizeof(char) * ft_strlen(v->env[v->i]) + 1);
	ft_strcpy(v->env[v->i + 1], v->env[v->i]);
	v->env[v->i] = NULL;
	free(v->env[v->i]);
	v->env[v->i] = (char*)malloc(sizeof(char) * (v->len + 2));
	v->env[v->i] = ft_strcpy(v->env[v->i], name);
	v->env[v->i] = ft_strcat(v->env[v->i], "=");
	v->env[v->i] = ft_strcat(v->env[v->i], value);
	v->env[v->i] = ft_strcat(v->env[v->i], "\0");
	v->env[v->i + 2] = NULL;
	return (v->env);
}

void	ft_setenv(char *line, t_vars *v)
{
	extern char	**environ;

	v->i = 0;
	v->flag = 0;
	v->token = ft_strsplit(line, '=');
	v->len = ft_strlen(v->token[0]);
	v->env = environ;
	while (environ[v->i])
	{
		if (ft_strncmp(environ[v->i], v->token[0], v->len) == 0)
		{
			v->flag = 1;
			if (environ[v->i][v->len] == '=')
			{
				ft_strclr(environ[v->i]);
				environ[v->i] = v->token[0];
				ft_strcat(environ[v->i], "=");
				ft_strcat(environ[v->i], v->token[1]);
			}
			else
				environ[v->i] -= v->len;
		}
		v->i++;
	}
	(v->flag == 0) ? environ = add_env(v->token[0], v->token[1], v) : 0;
}

void	ft_unsetenv(char *line, t_vars *v)
{
	extern char	**environ;
	v->i = 0;

	v->len = ft_strlen(line);
	while (environ[v->i])
	{
		if (ft_strncmp(environ[v->i], line, v->len) == 0)
		{
			while (environ[v->i])
			{
				environ[v->i] = environ[v->i + 1];
				v->i++;
			}
		}
		v->i++;
	}
}
