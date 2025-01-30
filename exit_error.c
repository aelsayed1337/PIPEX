/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:57:25 by aelsayed          #+#    #+#             */
/*   Updated: 2024/12/22 13:09:10 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(int specifier, int exitt, char error, char *file)
{
	if (specifier == -1)
	{
		unlink(".here_doc_tmp");
		if (error == 'c')
			printfd(2, "pipex: command not found: %s\n", file);
		else if (error == 'o' && file)
			printfd(2, "pipex: %s: %s\n", strerror(errno), file);
		else if (error == 'e' || error == 'd')
			printfd(2, "pipex: %s\n", strerror(errno));
		if (exitt == 2)
			exit(globale_variable(0b01111111));
		if (exitt)
			exit(errno);
	}
}

int	bpath_err(char **av, int ac)
{
	int	i;

	i = 3;
	while (i < ac)
		exit_error(-1, 0, 'c', av[i++]);
	unlink(".here_doc_tmp");
	return (1);
}

int	file_opener(char *infile, char *outfile, char c, int perm)
{
	int	fdi;
	int	fdo;

	if (perm)
		return (open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644));
	fdo = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	fdi = open(infile, O_RDONLY);
	if (fdi == -1 && fdo == -1)
	{
		exit_error(fdi, 0, 'o', infile);
		exit_error(fdo, 0, 'o', outfile);
		exit(1);
	}
	if (fdo == -1)
	{
		exit_error(fdo, 0, 'o', outfile);
		exit(1);
	}
	if (c == 'i')
		return (fdi);
	else
		return (fdo);
}
