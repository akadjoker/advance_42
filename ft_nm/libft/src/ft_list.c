#include "libft.h"

void ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *node;

	node = lst;
	while (node) {
		(*f)(node->content);
		node = node->next;
	}
}

t_list *ft_lstnew(void *content)
{
	t_list *node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

size_t ft_lstsize(t_list *lst)
{
	size_t size;
	t_list *node;

	size = 0;
	node = lst;
	while (node) {
		++size;
		node = node->next;
	}
	return size;
}
