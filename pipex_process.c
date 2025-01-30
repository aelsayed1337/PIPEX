/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:15:05 by aelsayed          #+#    #+#             */
/*   Updated: 2024/12/22 22:27:45 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	closer(int fdi, int fdo, int *pipefd, int bool)
{
	if (pipefd && bool != 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (fdi != -1 && bool != 1)
		close(fdi);
	if (fdo != -1 && bool != 1)
		close(fdo);
}

void	wait_process(pid_t pid1, pid_t pid2)
{
	if (pid1 != -1)
		waitpid(pid1, NULL, 0);
	if (pid2 != -1)
		waitpid(pid2, NULL, 0);
}

void	fork_parent(t_var *vars, char **av, char **envp)
{
	wait(NULL);
	close(vars->pipefd[1]);
	if (dup2(vars->pipefd[0], 0) == -1)
		exit_error(-1, 0, 'd', NULL);
	close(vars->pipefd[0]);
	if (dup2(vars->fdo, 1) == -1)
		exit_error(-1, 0, 'd', NULL);
	closer(-1, vars->fdo, vars->pipefd, 2);
	vars->path2 = check_path(envp, av[3]);
	if (execve(vars->path2, trim(ft_split(av[3], ' ')), envp) == -1)
	{
		free_paths(NULL, &(vars->path1));
		exit_error(-1, 1, 'c', av[3]);
	}
}

void	fork_child(t_var *vars, char **av, char **envp)
{
	vars->pid1 = fork();
	if (vars->pid1 == 0)
	{
		close(vars->pipefd[0]);
		if (dup2(vars->fdi, 0) == -1)
			exit_error(-1, 0, 'o', NULL);
		if (dup2(vars->pipefd[1], 1) == -1)
			exit_error(-1, 0, 'o', NULL);
		closer(vars->fdi, -1, vars->pipefd, 2);
		vars->path1 = check_path(envp, av[2]);
		if (execve(vars->path1, ft_split(av[2], ' '), envp) == -1)
		{
			free_paths(NULL, &(vars->path1));
			exit_error(-1, 1, 'c', av[2]);
		}
	}
	else
		fork_parent(vars, av, envp);
}
