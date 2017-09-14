/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:09:09 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/14 16:21:18 by cnkosi           ###   ########.fr       */
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

void	sh_execute(char *line, t_vars *v)
{
    v->i = 0;
    if (ft_isspace(line[v->i]))
        while (ft_isspace(line[v->i]))
            v->i++;
	if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(&line[5], v);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_chdir(line);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env(&line[4], v);
    else if (ft_strncmp(line, "export", 6) == 0)
		ft_setenv(&line[7], v);
	else if (ft_strncmp(line, "unsetenv", 8) == 0)
		ft_unsetenv(&line[9], v);
	else if (ft_strcmp(line, "exit") == 0)
		ft_putendl("Don't come here");
	else
		ft_execve(line);
}

void    shell_loop(void)
{
    char    *line;
	t_vars	v;

    v.status = 1;
    while (/*v.status != 0*/1)
    {
        ft_putstr("%> ");
        line = read_line();
        if (ft_strcmp(line, "exit") == 0)
           exit(EXIT_SUCCESS);
			// v.status = 0;
		else
			sh_execute(line, &v);
	//	free(line);
    }
}
