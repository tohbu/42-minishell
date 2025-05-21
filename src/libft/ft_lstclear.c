/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:12:36 by tohbu             #+#    #+#             */
/*   Updated: 2024/11/06 14:09:25 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*dast;

	tmp = *lst;
	if (*lst == NULL || lst == NULL)
		return ;
	while (tmp->next != NULL)
	{
		dast = tmp;
		tmp = tmp->next;
		(*del)(dast->content);
		free(dast);
	}
	(*del)(tmp->content);
	free(tmp);
	*lst = NULL;
}
