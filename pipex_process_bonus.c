/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 06:20:26 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/15 16:40:12 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_pipe(t_var *vars, char **av, int ac)
{
	vars->fdo = file_opener(av[1], av[ac -1], 'o', 0);
	vars->fdi = file_opener(av[1], av[ac -1], 'i', 0);
	exit_error(vars->fdi, 0, 'o', av[1]);
	if (vars->fdi == -1)
		vars->fdi = open("/dev/null", O_RDONLY);
}

void	bfork_parent(t_var *vars, char **av, char **envp, int ac)
{
	if (dup2(vars->fdo, 1) == -1)
		exit_error(-1, 0, 'd', NULL);
	vars->path2 = check_path(envp, av[ac]);
	if (execve(vars->path2, trim(ft_split(av[ac], ' ')), envp) == -1)
	{
		free_paths(NULL, &(vars->path1));
		exit_error(-1, 1, 'c', av[ac]);
	}
}

void	redirect(t_var *vars)
{
	wait(NULL);
	close(vars->pipefd[1]);
	if (dup2(vars->pipefd[0], 0) == -1)
		exit_error(-1, 0, 'd', NULL);
	close(vars->pipefd[0]);
}

void	check(t_var *var, char *s)
{
	free_paths(NULL, &(var->path1));
	exit_error(-1, 1, 'c', s);
}

void	bfork_child(t_var *vars, char **av, char **envp, int ac)
{
	int	i;

	i = 2;
	if (dup2(vars->fdi, 0) == -1)
		exit_error(-1, 0, 'o', NULL);
	while (i < ac - 2)
	{
		pipe(vars->pipefd);
		vars->pid1 = fork();
		if (vars->pid1 == 0)
		{
			close(vars->pipefd[0]);
			if (dup2(vars->pipefd[1], 1) == -1)
				exit_error(-1, 0, 'o', NULL);
			vars->path1 = check_path(envp, av[i]);
			if (execve(vars->path1, trim(ft_split(av[i], ' ')), envp) == -1)
				check(vars, av[i]);
		}
		else
			redirect(vars);
		i++;
	}
	bfork_parent(vars, av, envp, ac - 2);
}
//while fork()
