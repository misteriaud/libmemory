/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:07:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/14 18:45:13 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libmemory.h"

void	*Xmalloc(size_t size, int group, t_bool set2zero)
{
	t_alloc **first;
	t_alloc	*dest;

	first = get_first_alloc(group);
	dest = new_alloc(first, size);
	if (!dest)
		return (NULL);
	if (set2zero)
		ft_bzero(dest->ptr, size);
	return (dest->ptr);
}

void	*Xrealloc(int group, void *ptr, size_t size, t_bool set2zero)
{
	t_alloc **first;
	t_alloc *curr;
	t_alloc	*dest;

	first = get_first_alloc(group);
	curr = *first;
	while(curr && curr->ptr != ptr)
		curr = curr->next;
	if (!curr)
		return (NULL);
	dest = new_alloc(first, size + curr->size);
	if (!dest)
		return (NULL);
	ft_memcpy(dest->ptr, curr->ptr, curr->size);
	if (set2zero)
		ft_bzero(dest->ptr + curr->size, size);
	return (dest->ptr);
}

void Xfree_all()
{
	t_node	**first;
	t_node	*to_remove;

	first = get_first_node();
	if (!*first)
		return ;
	while (*first)
	{
		to_remove = *first;
		*first = to_remove->next;
		Xfree_group(to_remove->group);
		free(to_remove);
	}
}

