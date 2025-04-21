/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:42:12 by tohbu             #+#    #+#             */
/*   Updated: 2024/11/02 15:39:48 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_lst;

	if (lst == NULL)
		return (NULL);
	new = NULL;
	new_lst = NULL;
	while (lst != NULL)
	{
		if (!f)
			new = ft_lstnew((lst->content));
		else
			new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&new_lst, new);
	}
	return (new_lst);
}
