/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:09:09 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/13 15:10:16 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *read_line(void)
{
    int     i;
    char    buff;
    char    *tmp;
    char    *line;

    i  = 0;
    line = ft_strnew(1);
    while (read(STDIN_FILENO, &buff, 1))
    {
        tmp = ft_strnew(1);
        ft_strncpy(tmp, &buff, 1);
        line = ft_strjoin(line, tmp);
        free(tmp);
        i++;
        if (buff == '\n')
            break;
    }
    line[i - 1] =  0;
    return (line);
}

void	exec_env(char *line, t_vars *v)
{
	if (ft_strncmp(line, "env", 3) == 0)
	{
		line += 4;
		ft_env(line, v);
	}
    else if (ft_strncmp(line, "setenv", 6) == 0)
    {
        line += 7;
        ft_setenv(line, v);
    }
	else if (ft_strncmp(line, "unsetenv", 8) == 0)
	{
		line += 9;
		ft_unsetenv(line, v);
	}
}

void	exec_builtins(char *line, t_vars *v)
{
	if (ft_strncmp(line, "echo", 4) == 0)
	{
		line = line + 4;
		ft_echo(line, v);
	}
	/*else if (ft_strncmp(line, "cd", 2) == 0 ///|| 
			ft_strcmp(line, "pwd") == 0 || 
			ft_strcmp(line, "/bin/pwd") == 0*///)
        /*ft_chdir(line);
	else if (ft_strncmp(line, "env", 3) == 0 ||
			ft_strncmp(line, "setenv", 6) == 0 ||
			ft_strncmp(line, "unsetenv", 8) == 0)
		exec_env(line, v);
	else
		ft_execve(line);*/
}

void	sh_execute(char *line)
{
    t_vars	v;

    v.i = 0;
    if (ft_isspace(line[v.i]))
        while (ft_isspace(line[v.i]))
            v.i++;
    line = line + v.i;
	exec_builtins(line, &v);
}

void    shell_loop(void)
{
    int     status;
    char    *line;

    status = 1;
    while (status != 0)
    {
        ft_putstr("%> ");
        line = read_line();
        if (ft_strcmp(line, "exit") == 0)
            status = 0;
		else
			sh_execute(line);
    }
}
