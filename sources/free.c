/*
** EPITECH PROJECT, 2018
** free.c
** File description:
** free.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

static void free_block(block_t *block)
{
	if (block->prev) {
		block->prev->next = NULL;
		g_malloc.last_block = block->prev;
		g_malloc.heap = BLOCK_SIZE(g_malloc.last_block);
	} else {
		g_malloc.heap = g_malloc.last_block;
		g_malloc.last_block = NULL;
	}
	g_malloc.size_left += block->size;
	sbrk(-RM_PAGES(g_malloc.size_left, g_malloc.page_size));
	g_malloc.size_left = g_malloc.size_left -
	RM_PAGES(g_malloc.size_left, g_malloc.page_size);
}

static block_t *fusion_block(block_t *block)
{
	if (block->prev && !block->prev->used) {
		block->prev->size += block->size;
		block->prev->next = block->next;
	} if (block->next && !block->next->used) {
		block->size += block->next->size;
		block->next = block->next->next;
	}
	return (block);
}

static void free_error(const char *const err_message, void *ptr)
{
	m_putstr(2, err_message);
	m_putstr(2, "0x");
	m_putnbr_base(2, (uintptr_t)ptr, "0123456789ABCDEF");
	m_putchar(2, '\n');
	abort();
}

void free(void *ptr)
{
	block_t	*block = NULL;

	if (!ptr)
		return;
	pthread_mutex_lock(&g_malloc.mutex);
	block = GET_BBLOCK(ptr);
	if (block->used == false)
		free_error("double free or corruption: ", ptr);
	block = fusion_block(block);
	if (!block->next)
		free_block(block);
	pthread_mutex_unlock(&g_malloc.mutex);
}
