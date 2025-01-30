/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:28:23 by aelsayed          #+#    #+#             */
/*   Updated: 2025/01/30 20:01:17 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*join;
	size_t	l1;
	size_t	l2;

	l1 = 0;
	l2 = 0;
	if (!s1)
		return (ft_strndup(s2, ft_strlen(s2)));
	if (!s2)
		return (ft_strndup(s1, ft_strlen(s1)));
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!join)
		return (NULL);
	while (s1[l1])
	{
		join[l1] = s1[l1];
		l1++;
	}
	join[l1++] = '/';
	while (s2[l2])
		join[l1++] = s2[l2++];
	join[l1] = '\0';
	return (join);
}

char	**trim(char **ar)
{
	int		i;
	char	**arr;

	i = 0;
	while (ar[i])
		i++;
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (ar[i])
	{
		arr[i] = ft_strtrim(ar[i], "'\"");
		i++;
	}
	arr[i] = NULL;
	free_paths(&ar, NULL);
	return (arr);
}
