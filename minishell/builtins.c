/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:44:43 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/21 14:24:07 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_env(char *line)
{
	extern char	**environ;
	char		**env;
	char		*s;
	int			len;

	len = ft_strlen(line);
	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, line, len) == 0)
		{
			s = (char*)malloc(sizeof(s) * (ft_strlen(*env) + 1));
			s = ft_strcpy(s, *env);
			ft_putendl(&s[len + 1]);
			free(s);
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
		ft_putendl(line);
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

void	ft_chdir(char *path, t_vars *v)
{
	char	buff[1000];
	char	*old_wd;
	int		len;

	len = ft_strlen(getcwd(buff, sizeof(buff)));
	old_wd = (char*)malloc(sizeof(old_wd) * (len + 1));
	old_wd = getcwd(buff, sizeof(buff));
	v->len = ft_strlen(path);
	v->token = ft_strsplit(path, ' ');
	if (ft_wrd_cnt(path) > 2)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(v->token[1]);
	}
	else
	{
		ft_redirect(path, old_wd, v);
	}
}
