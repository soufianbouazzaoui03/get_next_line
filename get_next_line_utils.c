/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:53:56 by soel-bou          #+#    #+#             */
/*   Updated: 2023/12/08 21:20:51 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	ft_lstaddback(t_list **list,t_list *new)
{
	t_list	*last;
	
	last = *list;
	if(*list == NULL)
	{
		*list = new;
		return ;
	}
	while(last->next)
		last = last->next;
	last->next = new;
}

t_list	*ft_lstnew(char *buff)
{
	t_list	*new;
	new = malloc(sizeof(t_list));
	if(!new)
		return (NULL);
	new->val = buff;
	new->next = NULL;
	return (new);
}