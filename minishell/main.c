/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 11:00:48 by cnkosi            #+#    #+#             */
/*   Updated: 2017/09/14 14:44:09 by cnkosi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(void)
{
	//extern char **environ;
	/*char		**env;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	env = (char**)malloc(sizeof(env) * (i + 1));
	env [i] = 0;
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	environ = env;*/
    shell_loop();
    return (0);
}
