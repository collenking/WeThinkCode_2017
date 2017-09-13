/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 14:23:04 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/08 09:14:25 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char *line, t_vars *v)
{
	extern char		**environ;

	v->env = environ;
	while (*(v->env) && !*line)
		ft_putendl(*(v->env)++);
}

/*void	ft_env_name(char *line, t_vars *v)
{
	extern char		**environ;
	int				len;

	len = ft_strlen(line);
	v->env = environ;
	while (*(v->env))
	{
		if (ft_strncmp(*(v->env), line, len) == 0)
		{
			ft_putendl(*(v->env));
			break ;
		}
		v->env++;
	}
}*/
void	add_env(char *name, char *value, t_vars *v)
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
}

void	ft_setenv(char *line, t_vars *v)
{
	extern char	**environ;

	v->flag = 0;
	v->token = ft_strsplit(line, ' ');
	v->len = ft_strlen(v->token[0]);
	v->env = environ;
	while (*(v->env))
	{
		if (ft_strncmp(*(v->env), v->token[0], v->len) == 0)
		{
			v->flag = 1;
			*(v->env) += v->len;
			if ((**(v->env)) == '=')
			{
				ft_strclr(*(v->env));
				*(v->env) = v->token[0];
				ft_strcat(*(v->env), "=");
				ft_strcat(*(v->env), v->token[1]);
			}
			else
				*(v->env) -= v->len;
		}
		v->env++;
	}
	(v->flag == 0) ? add_env(v->token[0], v->token[1], v) : 0;
}

void	ft_unsetenv(char *line, t_vars *v)
{
	extern char	**environ;
	v->i = 0;

	v->token = ft_strsplit(line, ' ');
	v->len = ft_strlen(v->token[0]);
	v->env = environ;
	while (v->env[v->i])
	{
		if (ft_strncmp(v->env[v->i], v->token[0], v->len) == 0)
		{
			while (v->env[v->i])
			{
				v->env[v->i] = v->env[v->i + 1];
				v->i++;
			}
		}
		v->i++;
	}

}
