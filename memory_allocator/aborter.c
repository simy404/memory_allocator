/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aborter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:57:12 by hsamir            #+#    #+#             */
/*   Updated: 2025/04/23 21:37:09 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_allocator.h"
#include <stdlib.h>

void	safe_free(t_mem_type mem_type)
{
	t_memory_block	**head;
	t_memory_block	*mem_block;
	t_memory_block	*next_mem_block;

	head = get_memory_head(mem_type);
	if (*head == NULL)
		return ;
	mem_block = *head;
	while (mem_block != NULL)
	{
		next_mem_block = mem_block->next;
		free(mem_block);
		mem_block = next_mem_block;
	}
	*head = NULL;
}

void	safe_free_ptr(void *ptr, t_mem_type mem_type)
{
	t_memory_block	**head;
	t_memory_block	*mem_block;

	head = get_memory_head(mem_type);
	if (ptr == NULL || *head == NULL)
		return ;
	mem_block = (t_memory_block*)ptr - 1;
	if (mem_block->magic != (MAGIC | (size_t)mem_type))
		return ;
	if (mem_block->prev != NULL)
		mem_block->prev->next = mem_block->next;
	if (mem_block->next != NULL)
		mem_block->next->prev = mem_block->prev;
	if (*head == mem_block)
		*head = mem_block->next;
	free(mem_block);
}

void	safe_abort(int exit_code)
{
	safe_free(PERSISTENT);
	safe_free(TEMPORARY);
	exit(exit_code);
}
