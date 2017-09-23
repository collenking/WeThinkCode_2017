/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:02:38 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/22 22:58:41 by cnkosi           ###   ########.fr       */
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
	int			status;
	int			fok;
	char		*s;
	char		*ret;
	char		**env;
	char		**token;
	char		*fullpath;
	char		*path;
	char		**cmd;
	int			chd;
}				t_vars;

typedef struct	s_env
{
	char		**env;
}				t_env;

char			*read_line(void);
char    		*spaces(char *s, t_vars *v);
void			shell_loop(void);
void			ft_echo_normal(char *line);
void			ft_echo(char *line, t_vars *v);
void			ft_echo_env(char *line);
void			ft_echo_loop(char *ln);
void			ft_quote(char *s[1000], int j);
void			ft_dquote(char *s[1000], int j);
//void			exec_env(char *line, t_vars *v);
//void			exec_builtins(char *line, t_vars *v);
int	    		sh_exec_path(char *line, t_vars *v);
void			sh_execute(char *line, t_vars *v);
char			*carriage_ret(char *line, t_vars *v);
char			*get_str(char *s, t_vars *v);
void			ft_env();
//void			ft_env_name(char *line, t_vars *v);
char			*chdir_home(void);
char			*chdir_prev(void);
void			update_pwd(char *old_pwd, char *cur_pwd);
void			change_dir(char *path, char *old_wd, t_vars *v);
void			ft_redirect(char *path, char *old_wd, t_vars *v);
void			ft_chdir(char *path, t_vars *v);
char			**add_env(char *name, char *value, t_vars *v);
void			ft_setenv(char *line, t_vars *v);
void			ft_unsetenv(char *line, t_vars *v);
void			ft_execve(char *line, t_vars *v);
int				ft_fork(char *line, char *path);
char			*ft_get_path(char *path, char *cmd);

#endif
