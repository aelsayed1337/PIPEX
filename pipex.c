/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:29:50 by aelsayed          #+#    #+#             */
/*   Updated: 2024/12/22 22:30:48 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_var	vars;

	if (!envp || !*envp || !path_index(envp))
		printfd(2, "Invalid PATH variable!\n");
	if (ac == 5)
	{
		vars.fdo = file_opener(av[1], av[ac -1], 'o', 0);
		vars.fdi = file_opener(av[1], av[ac -1], 'i', 0);
		exit_error(vars.fdi, 0, 'o', av[1]);
		if (vars.fdi == -1)
			vars.fdi = open("/dev/null", O_RDONLY);
		if (pipe(vars.pipefd) == -1)
			exit_error(-1, 1, 'e', NULL);
		fork_child(&vars, av, envp);
		closer(vars.fdi, vars.fdo, vars.pipefd, 2);
		wait_process(vars.pid1, vars.pid2);
		return (globale_variable(-1));
	}
	printfd(2, "Invalid input for arguments:\nExpected Format:\n");
	printfd(2, "\t./pipex <infile> cmd1 cmd2 <outfile>\n");
	return (1);
}
//madatory 