#include "get_next_line.h"

int ft_checknull(t_list *list)
{
    int i;

    if(!list)
        return (0);
    while(list)
    {
        i = 0;
        while(list->val[i] && i < BUFFER_SIZE)
        {
            if(list->val[i] == '\n')
                return (1);
            ++i;
        }
        list = list->next;
    }
    return (0);
}

size_t  bufflen(t_list *list)
{
    size_t  len;
    size_t  i;

    if(!list)
        return (0);
    len = 0;
    while(list)
    {
        i = 0;
        while(list->val[i])
        {
            if(list->val[i] == '\n')
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
void    setlist(t_list **list, int fd)
{
    char    *buffer;
    int     rd;

    while(!ft_checknull(*list))
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if(!buffer)
            return ;
        rd = read(fd, buffer,BUFFER_SIZE);
        if(rd <= 0)
        {
            free(buffer);
            return ;
        }
        buffer[rd] = '\0';
        ft_lstaddback(list, ft_lstnew(strdup(buffer)));
        free(buffer);
    }
}
char    *ft_getline(t_list *list)
{
    char    *line;
    size_t  len;
    int     i;
    int     j;

    i = 0;
    len = bufflen(list);
    line = malloc(len + 1);
    if(!line)
        return (NULL);
    while(list)
    {
        j = 0;
        while(list->val[j])
        {
            if(list->val[j] == '\n')
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

void    freelist(t_list **list, t_list *node, char *aftern)
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

void    ft_clean(t_list **list)
{
    t_list  *tmp;
    char    *aftern;
    t_list  *node;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    aftern = (char *)malloc(BUFFER_SIZE + 1);
    node = malloc(sizeof(t_list));
    if(!aftern || !node)
        return ;
    tmp = *list;
    while(tmp->next)
        tmp = tmp->next;
    while(tmp->val[i] && tmp->val[i] != '\n')
        i++;
    while(tmp->val[i] && tmp->val[++i])
        aftern[j++] = tmp->val[i];
    aftern[j] = '\0';
    node->val = aftern;
    node->next = NULL;
    freelist(list, node, aftern);
}

char    *get_next_line(int fd)
{
    static t_list   *list;
    char            *line;

    if(!list)
        list = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1 )
    {
        if(list)
        {
            free(list->val);
            free(list);
            list = NULL;
        }
        return (NULL);
    }
    setlist(&list, fd);
    if(!list)
        return (NULL);
    line = ft_getline(list);
    ft_clean(&list);
    return (line);
}
// int main()
// {
//     int fd = open("test.txt", O_RDONLY);
	
//     printf("1%s", get_next_line(fd));
//     printf("2%s", get_next_line(fd));
// 		// set the next read call to return -1
//     close(fd);
    
//     printf("3%s", get_next_line(fd));
//     printf("4%s", get_next_line(fd));
//     fd = open("test.txt", O_RDONLY);
//     printf("5%s\n", get_next_line(fd));
//     printf("6%s\n", get_next_line(fd));
// }
  
