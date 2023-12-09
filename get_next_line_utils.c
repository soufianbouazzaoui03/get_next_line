/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:53:56 by soel-bou          #+#    #+#             */
/*   Updated: 2023/12/09 07:49:53 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstaddback(t_list **list, t_list *new)
{
	t_list	*last;

	last = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

t_list	*ft_lstnew(char *buff)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->val = buff;
	new->next = NULL;
	return (new);
}

int	ft_checknull(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->val[i] && i < BUFFER_SIZE)
		{
			if (list->val[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

size_t	bufflen(t_list *list)
{
	size_t	len;
	size_t	i;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->val[i])
		{
			if (list->val[i] == '\n')
			{
				++len;
				return (len);
			}
			++len;
			++i;
		}
		list = list->next;
	}
	return (len);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;
	int		i;

	i = 0;
	len = 0;
	while (s1[i++])
		len++;
	i = 0;
	p = (char *) malloc(len * sizeof(char) + 1);
	if (!p)
		return (p);
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
