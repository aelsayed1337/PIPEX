/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:27:22 by aelsayed          #+#    #+#             */
/*   Updated: 2025/01/30 20:05:51 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_paths(char ***paths, char **cmd)
{
	int	i;

	i = 0;
	if (cmd && *cmd)
	{
		free(*cmd);
		*cmd = NULL;
	}
	if (*paths)
	{
		while ((*paths)[i])
		{
			free((*paths)[i]);
			(*paths)[i] = NULL;
			i++;
		}
		free(*paths);
		*paths = NULL;
	}
	return (NULL);
}

int	globale_variable(int nb)
{
	static int	amine;

	amine = 0;
	if (nb == -1)
		return (amine);
	else
	{
		amine = nb;
		return (amine);
	}
}

int	path_index(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp("PATH=", envp[i], 5))
			return (i);
		i++;
	}
	globale_variable(1);
	return (0);
}

char	*check_path(char **envp, char *cmd)
{
	char	**paths;
	char	*checker;
	char	**cmds;
	int		i;

	i = 0;
	paths = ft_split(envp[path_index(envp)], ':');
	cmds = ft_split(cmd, ' ');
	if (access(cmds[0], X_OK) == 0)
		return (cmds[0]);
	while (paths && paths[i])
	{
		checker = ft_strjoin2(paths[i], cmds[0]);
		if (access(checker, X_OK) == 0)
			return (free_paths(&paths, NULL), free_paths(&cmds, NULL), checker);
		free(checker);
		i++;
	}
	free_paths(&paths, NULL);
	free_paths(&cmds, NULL);
	globale_variable(127);
	return (exit_error(-1, 2, 'c', cmd), NULL);
}
