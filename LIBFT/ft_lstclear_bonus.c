/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:06:32 by aelsayed          #+#    #+#             */
/*   Updated: 2025/01/29 11:21:41 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_bonus(t_list **lst, void (*del)(void *))
{
	t_list	*store;

	if (lst && *lst && del)
	{
		while (*lst)
		{
			store = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = store;
		}
		*lst = NULL;
	}
}
