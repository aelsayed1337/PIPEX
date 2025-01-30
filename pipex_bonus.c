/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:22:22 by aelsayed          #+#    #+#             */
/*   Updated: 2024/12/27 19:29:13 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char *stopper)
{
	char	*line;
	int		fd;
	int		input;

	fd = open(".here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = open(".here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		printfd(2, "%s : Error creating temporary file\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printfd(1, "pipex here_doc> ");
		line = get_next_line(0);
		if (!ft_strncmp(ft_strtrim(line, "\n/"), stopper, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		printfd(fd, "%s", ft_strtrim(line, "/"));
		free(line);
	}
	return (input);
}

static void	bfork_doc(t_var *vars, char **av, char **envp, int ac)
{
	int	i;

	i = 3;
	if (dup2(vars->fdi, 0) == -1)
		exit_error(-1, 0, 'o', NULL);
	unlink(".here_doc_tmp");
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

void	ft_bonus(int ac, char **av, char **envp, t_var *vars)
{
	if (ac >= 6)
	{
		vars->fdi = here_doc(av[2]);
		vars->fdo = file_opener(NULL, av[ac -1], 'o', 1);
		if (!envp || !*envp || !path_index(envp))
			exit(bpath_err(av, ac));
		if (vars->fdi == -1)
			vars->fdi = open("/dev/null", O_RDONLY);
		bfork_doc(vars, av, envp, ac);
		unlink(".here_doc_tmp");
		exit(0);
	}
	printfd(2, "Invalid input for arguments:\nExpected Format:\n");
	printfd(2, "\t./pipex here_doc LIMITER cmd1 ... cmdn <outfile>\n");
	printfd(2, "\t./pipex <infile> cmd1 ... cmdn <outfile>\n");
	exit (1);
}

void	print_err(void)
{
	printfd(2, "Invalid input for arguments:\nExpected Format:\n");
	printfd(2, "\t./pipex <infile> cmd1 ... cmdn <outfile>\n");
	printfd(2, "\t./pipex here_doc LIMITER cmd1 ... cmdn <outfile>\n");
}

int	main(int ac, char **av, char **envp)
{
	t_var	vars;

	if (!envp || !*envp || !path_index(envp))
		printfd(2, "Invalid PATH variable!\n");
	if (ac < 5)
		return (print_err(), 1);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		ft_bonus(ac, av, envp, &vars);
	open_pipe(&vars, av, ac);
	bfork_child(&vars, av, envp, ac);
	return (globale_variable(-1));
}

//here_doc