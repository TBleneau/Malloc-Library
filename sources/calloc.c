/*
** EPITECH PROJECT, 2018
** calloc.c
** File description:
** calloc.c
*/

#include <string.h>
#include "malloc.h"

void *calloc(size_t nmemb, size_t size)
{
	void *ptr = NULL;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	pthread_mutex_lock(&g_malloc.mutex);
	memset(ptr, 0, ALIGN_SIZE(nmemb * size));
	pthread_mutex_unlock(&g_malloc.mutex);
	return (ptr);
}
