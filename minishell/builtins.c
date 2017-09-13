/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:44:43 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/13 17:09:05 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_env(char *line)
{
	extern char	**environ;
	char		**env;
	int			len;

	len = ft_strlen(line);
	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, line, len) == 0)
		{
			*env += len + 1;
			ft_putendl(*env);
			break ;
		}
		env++;
	}
}

void	ft_echo(char *line, t_vars *v)
{
	v->i = 0;
	while (ft_isspace(line[v->i]))
		v->i++;
	line = line + v->i;
	v->len = ft_strlen(line) - 1;
	if ((line[v->i] == 34 || line[v->i] == 39) &&
			(line[v->len] == 34 || line[v->len] == 39))
	{
		v->i++;
		v->len--;
	}
	if (ft_strncmp(line, "-e", 2) == 0)
	{
		line = line + 3;
		ft_putendl(carriage_ret(get_str(line, v), v));
	}
	else if (ft_strncmp(line, "$", 1) == 0)
	{
		line = line + 1;
		ft_echo_env(line);
	}
	else if (line[0] == 34 || line[0] == 39)
		ft_echo_normal(line);
	else
		ft_echo_normal(get_str(line, v));
}
