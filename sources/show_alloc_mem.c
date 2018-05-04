/*
** EPITECH PROJECT, 2018
** show_alloc_mem.c
** File description:
** show_alloc_mem.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"

ssize_t m_putchar(const int fd, const int c)
{
	return (write(fd, &c, 1));
}

ssize_t m_putstr(const int fd, const char *const str)
{
	return (write(fd, str, strlen(str)));
}

ssize_t m_putnbr_base(const int fd, const size_t n, const char *const b)
{
	if (n / strlen(b))
		m_putnbr_base(fd, n / strlen(b), b);
	return (m_putchar(1, b[n % strlen(b)]));
}

static ssize_t print_block(block_t *block)
{
	if (m_putstr(1, "0x") == -1 ||
		m_putnbr_base(1, (uintptr_t)GET_EBLOCK(block),
		"0123456789ABCDEF") == -1 || m_putstr(1, " - 0x") == -1 ||
		m_putnbr_base(1, (uintptr_t)GET_EBLOCK(block) + block->size -
		ALIGN_SIZE(sizeof(block_t)), "0123456789ABCDEF") == -1 ||
		m_putstr(1, " : ") == -1 || m_putnbr_base(1, block->size -
		ALIGN_SIZE(sizeof(block_t)), "0123456789") == -1 ||
		m_putstr(1, " bytes\n") == -1)
			return (-1);
	return (0);
}

void show_alloc_mem(void)
{
	block_t *block = g_malloc.first_block;
	void *heap = NULL;

	heap = sbrk(0);
	if (heap == (void *)-1 ||
		m_putstr(1, "break : 0x") == -1 ||
		m_putnbr_base(1, (uintptr_t)heap, "0123456789ABCDEF") == -1 ||
		m_putchar(1, '\n') == -1)
		return;
	while (block) {
		if (block->used && print_block(block) == -1)
			return;
		block = block->next;
	}
}
