/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:41:39 by hsamir            #+#    #+#             */
/*   Updated: 2025/04/23 16:12:20 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_allocator.h"
#include <stdlib.h>

t_memory_block	**get_memory_head(t_mem_type mem_type)
{
	static t_memory_block	*temp_mem_blocks = NULL;
	static t_memory_block	*pers_mem_blocks = NULL;

	if (mem_type == PERSISTENT)
		return (&pers_mem_blocks);
	return (&temp_mem_blocks);
}

void	*safe_malloc(size_t size, t_mem_type mem_type)
{
	t_memory_block	*mem_block;
	t_memory_block	**head;

	mem_block = (t_memory_block*)malloc(sizeof(t_memory_block) + size);
	if (mem_block == NULL)
		safe_abort(STD_EXIT);
	*mem_block = (t_memory_block){
		.data = mem_block + 1,
		.next = NULL,
		.prev = NULL
	};
	head = get_memory_head(mem_type);
	if (*head == NULL)
		*head = mem_block;
	else
	{
		mem_block->next = *head;
		(*head)->prev = mem_block;
		*head = mem_block;
	}
	return (mem_block->data);
}

void	*safe_talloc(size_t size)
{
	return (safe_malloc(size, TEMPORARY));
}

void	*safe_palloc(size_t size)
{
	return (safe_malloc(size, PERSISTENT));
}
