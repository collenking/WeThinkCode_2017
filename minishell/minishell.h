/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:02:38 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/13 15:10:20 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <dirent.h>

typedef struct	s_vars
{
	int			i;
	int			j;
	int			len;
	int			flag;
	char		*s;
	char		*ret;
	char		**env;
	char		**token;
}				t_vars;

typedef struct	s_env
{
	char		**env;
}				t_env;

char			*read_line(void);
void			shell_loop(void);
void			ft_echo_normal(char *line);
void			ft_echo(char *line, t_vars *v);
void			ft_echo_env(char *line);
void			ft_echo_loop(char *ln);
void			ft_quote(char *s[1000], int j);
void			ft_dquote(char *s[1000], int j);
void			exec_env(char *line, t_vars *v);
void			exec_builtins(char *line, t_vars *v);
void			sh_execute(char *line);
char			*carriage_ret(char *line, t_vars *v);
char			*get_str(char *s, t_vars *v);
void			ft_env(char *line, t_vars *v);
//void			ft_env_name(char *line, t_vars *v);
void			ft_chdir(char *path);
void			add_env(char *name, char *value, t_vars *v);
void			ft_setenv(char *line, t_vars *v);
void			ft_unsetenv(char *line, t_vars *v);
void			ft_execve(char *line);
void			ft_fork(char *line, char *path);
char			*ft_get_path(char *path, char *cmd);

#endif
