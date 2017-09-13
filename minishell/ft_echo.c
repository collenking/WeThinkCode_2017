/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:02:09 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/12 17:05:00 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*carriage_ret(char *line, t_vars *v)
{
	v->s = NULL;
	v->i = 0;
	v->len = ft_strlen(line) - 1;
	(line[v->i] == 34 || line[v->i] == 39) ? v->i++ : 0;
	v->j = v->i;
	(line[v->len] == 34 || line[v->len] == 39) ? v->len-- : 0;
	while (line[v->i])
	{
		if (line[v->i] == 92 && line[v->i + 1] == 114 && v->i++)
		{
			v->s = ft_strsub(line, v->i + 1, v->len - v->i);
			break ;
		}
		else if (line[v->i] == 92 && line[v->i + 1] == 99 && v->i--)
		{
			v->s = ft_strsub(line, v->j, v->i);
			break ;
		}
		v->i++;
	}
	return (v->s);
}

char	*spaces(char *s, t_vars *v)
{
	v->i = 0;
	v->j = 0;
	v->len = ft_strlen(s);
	v->ret = (char*)malloc(sizeof(char) * v->len + 1);
	while (s[v->i])
	{
		if (ft_isspace(s[v->i]))
		{
			v->ret[v->j++] = 32;
			while (ft_isspace(s[v->i]))
				v->i++;
		}
		v->ret[v->j++] = s[v->i++];
	}
	v->ret[v->j] = '\0';
	return (v->ret);
}

char	*get_str(char *s, t_vars *v)
{
	v->i = 0;
	v->j = 0;
	if (ft_isspace(s[v->i]))
		while (ft_isspace(s[v->i]) && ++v->i);
	v->len = ft_strlen(s);
	v->ret = (char*)malloc(sizeof(char) * v->len + 1);
	if (s[v->i] == 34 || s[v->i] == 39)
	{
		while (s[v->i])
		{
			(s[v->i] == 34 || s[v->i] == 39) ? v->i++ : 0;
			v->ret[v->j++] = s[v->i++];
		}
		v->ret[v->j] = '\0';
	}
	else
	{
		s = s + v->i;
		v->ret = spaces(s, v);
	}
	return (v->ret);
}

void	ft_echo_loop(char *ln)
{
	int		status;
	int		i;
	int		j;
	int		z;
	char	*line;
	char	*s[1000];

	j = 1;
	status = 1;
	s[0] = (char*)malloc(sizeof(char) * (ft_strlen(ln + 1)));
	s[0] = ln;
	while (status != 0)
	{
		ft_putstr("dquote>");
		line = read_line();
		s[j] = (char*)malloc(sizeof(char) * (ft_strlen(line + 1)));
		s[j] = line;
		j++;
		i = 0;
		while (line[i])
			(line[i++] == 34) ? status = 0 : 0;
	}
	i = 0;
	z = 0;
	while (z < j)
	{
		while (s[z][i])
		{
			ft_putchar(s[z][i++]);
		}
		ft_putchar('\n');
		z++;
		//ft_putendl(s[i++]);
	}
}

void	ft_echo_normal(char *line)
{
	/*size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(line) - 1;
	(line[i] == 34 || line[i] == 39) ? i++ : 0;
	while (i <= (int)len)
	{
		(line[i] == 34) ? i++ : 0;
		if (line[i] == 92 && line[i + 1] == 110 && i++)
			ft_putchar('\n');
		else if (line[i] == 92 && line[i + 1] == 116 && i++)
			ft_putchar('\t');
		else if (line[i] == 92 && line[i + 1] == 118 && i++)
			ft_putchar('\v');
		else
			ft_putchar(line[i]);
		i++;
	}
	(line[len] == 34 || line[len] == 39) ? len-- : 0;*/
	//line = ft_strcat(line, "\r cool");
	ft_echo_loop(line);
	//ft_putstr(line);
	//ft_putchar('\n');
}

void    ft_echo_env(char *line)
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
