/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:41:39 by hsamir            #+#    #+#             */
/*   Updated: 2025/04/24 20:04:16 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_allocator.h"
#include <stdlib.h>

t_memory_block	**get_memory_head(t_mem_type mem_type)
{
	static t_memory_block	*mem_blocks[2] = {0};

	return (&mem_blocks[mem_type]);
}

void	*safe_malloc(size_t size, t_mem_type mem_type)
{
	t_memory_block	*mem_block;
	t_memory_block	**head;

	mem_block = malloc(sizeof(t_memory_block) + size);
	if (mem_block == NULL)
		safe_abort(STD_EXIT);
	head = get_memory_head(mem_type);
	*mem_block = (t_memory_block){
		.magic = MAGIC | (size_t)mem_type,
		.next = *head,
		.prev = NULL,
	};
	if (*head != NULL)
		(*head)->prev = mem_block;
	*head = mem_block;
	return (mem_block + 1);
}

void	*safe_talloc(size_t size)
{
	return (safe_malloc(size, TEMPORARY));
}

void	*safe_palloc(size_t size)
{
	return (safe_malloc(size, PERSISTENT));
}
