/*
** EPITECH PROJECT, 2018
** malloc.c
** File description:
** malloc.c
*/

#include <unistd.h>
#include "malloc.h"

malloc_t g_malloc = {
	.page_size = 0,
	.nb_pages = 0,
	.size_left = 0,
	.heap = NULL,
	.last_block = NULL,
	.first_block = NULL,
	.mutex = PTHREAD_MUTEX_INITIALIZER
};

static void *end_malloc(void *ret)
{
	pthread_mutex_unlock(&g_malloc.mutex);
	if (ret)
		return (GET_EBLOCK(ret));
	return (NULL);
}

static bool init_malloc(size_t *size)
{
	pthread_mutex_lock(&g_malloc.mutex);
	if (!g_malloc.page_size && !g_malloc.nb_pages) {
		g_malloc.page_size = sysconf(_SC_PAGE_SIZE);
		g_malloc.nb_pages = sysconf(_SC_PHYS_PAGES);
		if (g_malloc.page_size == -1 || g_malloc.nb_pages == -1)
			return (false);
	} if (*size < 32)
		*size = 32;
	*size = ALIGN_SIZE(*size) + ALIGN_SIZE(sizeof(block_t));
	if ((size_t)(g_malloc.page_size * g_malloc.nb_pages) < *size)
		return (false);
	return (true);
}

void *malloc(size_t size)
{
	void *ptr = NULL;

	if (!init_malloc(&size))
		return (end_malloc(NULL));
	if (!make_call_sbrk(&size, &ptr))
		return (end_malloc(NULL));
	return (end_malloc(ptr));
}
