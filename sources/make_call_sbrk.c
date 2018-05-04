/*
** EPITECH PROJECT, 2018
** make_call_sbrk.c
** File description:
** make_call_sbrk.c
*/

#include <unistd.h>
#include "malloc.h"

static void *get_block_created(const size_t *const size)
{
	block_t *block = NULL;

	block = g_malloc.heap;
	block->size = *size;
	block->used = true;
	block->next = NULL;
	block->prev = g_malloc.last_block;
	if (g_malloc.last_block)
		g_malloc.last_block->next = block;
	g_malloc.last_block = block;
	g_malloc.heap = UPDATE_HEAP(block, *size);
	return (block);
}

static bool get_new_pages(size_t *new, const size_t *const size)
{
	*new = REAL_SIZE(*size, g_malloc.page_size);
	if (!g_malloc.heap) {
		g_malloc.heap = sbrk(0);
		if (g_malloc.heap == (void *)-1)
			return (false);
		g_malloc.first_block = g_malloc.heap;
	} if (sbrk(*new) == (void *)-1)
		return (false);
	return (true);
}

bool make_call_sbrk(const size_t *const size, void **ptr)
{
	size_t new_pages = 0;

	if (g_malloc.size_left < *size) {
		if (!get_new_pages(&new_pages, size))
			return (false);
		g_malloc.size_left += new_pages;
	}
	g_malloc.size_left -= *size;
	*ptr = get_block_created(size);
	return (true);
}
