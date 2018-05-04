/*
** EPITECH PROJECT, 2018
** realloc.c
** File description:
** realloc.c
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "malloc.h"

static void *realloc_block(block_t *tmp, block_t *new, size_t *size, void *ptr)
{
	size_t size_to_use = 0;
	size_t block_size = ALIGN_SIZE(sizeof(block_t));

	new = malloc(*size);
	if (!new)
		return (NULL);
	*size = ALIGN_SIZE(*size);
	size_to_use = (*size <= tmp->size) ? (*size) : (tmp->size);
	pthread_mutex_lock(&g_malloc.mutex);
	memcpy(new, (void *)((uintptr_t)ptr + block_size), size_to_use);
	pthread_mutex_unlock(&g_malloc.mutex);
	free((void *)((uintptr_t)ptr + block_size));
	return (new);
}

void *realloc(void *ptr, size_t size)
{
	block_t *new;
	block_t *tmp;
	size_t block_size = ALIGN_SIZE(sizeof(block_t));

	if (!ptr)
		return (malloc(size));
	if (!size) {
		free(ptr);
		return (NULL);
	}
	ptr = (void *)((uintptr_t)ptr - block_size);
	tmp = (block_t *)ptr;
	new = ptr;
	if (size + block_size > tmp->size)
		new = realloc_block(tmp, new, &size, ptr);
	else
		new = GET_EBLOCK(new);
	return (new);
}
