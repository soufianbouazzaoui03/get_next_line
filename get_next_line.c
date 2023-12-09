/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 07:43:01 by soel-bou          #+#    #+#             */
/*   Updated: 2023/12/09 07:47:01 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	setlist(t_list **list, int fd)
{
	char	*buffer;
	int		rd;

	while (!ft_checknull(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[rd] = '\0';
		ft_lstaddback(list, ft_lstnew(ft_strdup(buffer)));
		free(buffer);
	}
}

char	*ft_getline(t_list *list, size_t len)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (list)
	{
		j = 0;
		while (list->val[j])
		{
			if (list->val[j] == '\n')
			{
				line[i++] = '\n';
				line[i] = '\0';
				return (line);
			}
			line[i++] = list->val[j++];
		}
		list = list->next;
	}
	line[i] = '\0';
	return (line);
}

void	freelist(t_list **list, t_list *node, char *aftern)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->val);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (node->val[0])
		*list = node;
	else
	{
		free(aftern);
		free(node);
	}
}

void	ft_clean(t_list **list)
{
	t_list	*tmp;
	char	*aftern;
	t_list	*node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aftern = (char *)malloc(BUFFER_SIZE + 1);
	node = malloc(sizeof(t_list));
	if (!aftern || !node)
		return ;
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->val[i] && tmp->val[i] != '\n')
		i++;
	while (tmp->val[i] && tmp->val[++i])
		aftern[j++] = tmp->val[i];
	aftern[j] = '\0';
	node->val = aftern;
	node->next = NULL;
	freelist(list, node, aftern);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (!list)
		list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
	{
		if (list)
		{
			free(list->val);
			free(list);
			list = NULL;
		}
		return (NULL);
	}
	setlist(&list, fd);
	if (!list)
		return (NULL);
	line = ft_getline(list, bufflen(list));
	ft_clean(&list);
	return (line);
}
