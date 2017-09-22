/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:09:09 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/22 22:58:31 by cnkosi           ###   ########.fr       */
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
            break ;
    }
    line[i - 1] = '\0';
    if (line)
        return (line);
    //free(line);
    return (NULL);
}

char    *spaces(char *s, t_vars *v)
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

void    sh_exec_path(char *line, t_vars *v)
{
    if (ft_strncmp(line, "/bin/", 5) == 0)
        ft_execve(&line[4], v);
    else if (ft_strncmp(line, "/usr/local/sbin/", 16) == 0)
        ft_execve(&line[15], v);
    else if (ft_strncmp(line, "/usr/local/bin/", 15) == 0)
        ft_execve(&line[14], v);
    else if (ft_strncmp(line, "/usr/sbin/", 10) == 0)
        ft_execve(&line[9], v);
    else if (ft_strncmp(line, "/usr/bin/", 9) == 0)
        ft_execve(&line[8], v);
    else if (ft_strncmp(line, "/sbin/", 6) == 0)
        ft_execve(&line[5], v);
    else if (ft_strncmp(line, "/usr/games/", 11) == 0)
        ft_execve(&line[10], v);
    else if (ft_strncmp(line, "/usr/local/games/", 17) == 0)
        ft_execve(&line[16], v);
    else
        ft_execve(line, v);
}

void	sh_execute(char *line, t_vars *v)
{
    v->i = 0;
    if (ft_isspace(line[v->i]))
        while (ft_isspace(line[v->i]))
            v->i++;
	v->len = ft_strlen(line);
    if (ft_isspace(line[v->len - 1]))
        while (ft_isspace(line[v->len - 1]))
            v->len++;
	if (ft_strncmp(line, "echo", 4) == 0)
		ft_echo(&line[5], v);
	else if (ft_strncmp(line, "cd", 2) == 0)
		ft_chdir(line, v);
	else if (ft_strncmp(line, "env", 3) == 0)
		ft_env();
    else if (ft_strncmp(line, "export", 6) == 0)
		ft_setenv(&line[7], v);
	else if (ft_strncmp(line, "unsetenv", 8) == 0)
		ft_unsetenv(&line[9], v);
	else
    {
        sh_exec_path(line, v);
    }
}

void    shell_loop(void)
{
    char    *line;
	t_vars	v;

    while (1)
    {
        ft_putstr("%> ");
        line = read_line();
        if (ft_strcmp(line, "exit") == 0)
           exit(EXIT_SUCCESS);
		else if (!ft_isempty(line))
			sh_execute(line, &v);
		free(line);
    }
	free(line);
}
