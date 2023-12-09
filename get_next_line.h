/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:49 by soel-bou          #+#    #+#             */
/*   Updated: 2023/12/08 20:14:15 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
    #define BUFFER_SIZE 10
#endif

#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
typedef struct s_list
{
    char *val;
    struct s_list *next;
}t_list;

char    *get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	ft_addback(char *line, char *buffer);
void	ft_lstaddback(t_list **list,t_list *new);
t_list	*ft_lstnew(char *buff);

#endif
