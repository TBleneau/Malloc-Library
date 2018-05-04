/*
** EPITECH PROJECT, 2018
** malloc.h
** File description:
** malloc.h
*/

#ifndef MALLOC_H_
	#define MALLOC_H_

	#include <pthread.h>
	#include <stdbool.h>
	#include <stddef.h>
	#include <stdint.h>
	#include <sys/types.h>

	#ifdef __x86_64__
		#define ALIGN_SIZE(x) ((((x - 1) >> 4) << 4) + 16)
	#else
		#define ALIGN_SIZE(x) ((((x - 1) >> 3) << 3) + 8)
	#endif

	typedef struct block_s {
		size_t size;
		bool used;
		struct block_s *prev;
		struct block_s *next;
	} block_t;

	typedef struct malloc_s {
		int page_size;
		int nb_pages;
		size_t size_left;
		void *heap;
		block_t *first_block;
		block_t	*last_block;
		pthread_mutex_t mutex;
	} malloc_t;

	#define REAL_SIZE(x, y) (((x / y) + 1) * y)
	#define UPDATE_HEAP(x, y) ((void *)((uintptr_t)x + y))
	#define GET_BBLOCK(x) ((void *)((uintptr_t)x - sizeof(block_t)))
	#define GET_EBLOCK(x) ((void *)((uintptr_t)x + sizeof(block_t)))
	#define BLOCK_SIZE(x) ((void *)((uintptr_t)x + x->size))
	#define RM_PAGES(x, y) (((x / y) * y))

	extern malloc_t g_malloc;

	void *malloc(size_t);
	bool make_call_sbrk(const size_t *const, void **);
	void free(void *);
	void *realloc(void *, size_t);
	void *calloc(size_t, size_t);
	void show_alloc_mem(void);
	ssize_t m_putchar(const int, const int);
	ssize_t	m_putstr(const int, const char *const);
	ssize_t	m_putnbr_base(const int, const size_t, const char *const);
	void *mmalloc(size_t);
	void mfree(void *);
	void *mrealloc(void *, size_t);
	void *mcalloc(size_t, size_t);

#endif /* !MALLOC_H_ */
