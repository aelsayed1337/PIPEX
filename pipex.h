/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:27:09 by aelsayed          #+#    #+#             */
/*   Updated: 2025/01/30 20:00:39 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../LIBFT/libft.h"
# include <errno.h>
# include <sys/wait.h>

typedef struct s_variables
{
	int		fdo;
	int		fdi;
	pid_t	pid1;
	pid_t	pid2;
	char	*path1;
	char	*path2;
	char	**args;
	int		pipefd[2];
}			t_var;

char		*ft_strjoin2(char *s1, char *s2);

// pipex fcts
char		**trim(char **ar);
char		*check_path(char **envp, char *cmd);
char		*free_paths(char ***paths, char **cmd);
void		exit_error(int specifier, int exitt, char error, char *file);
int			file_opener(char *infile, char *outfile, char c, int perm);

// main helpers
void		wait_process(pid_t pid1, pid_t pid2);
int			globale_variable(int nb);
int			path_index(char **envp);
int			bpath_err(char **av, int ac);
void		closer(int fdi, int fdo, int *pipefd, int bool);
void		open_pipe(t_var *vars, char **av, int ac);
void		bfork_parent(t_var *vars, char **av, char **envp, int ac);
void		redirect(t_var *vars);
void		check(t_var *var, char *s);
void		fork_child(t_var *vars, char **av, char **envp);
void		bfork_child(t_var *vars, char **av, char **envp, int ac);
void		ft_bonus(int ac, char **av, char **envp, t_var *vars);

#endif
