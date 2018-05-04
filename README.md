# Malloc-Library
Memory Allocation

Using only brk/sbrk, rewrite the 4 following C library functions :  

	• malloc
	• free
	• realloc
	• calloc

In order to give you more control, also write a show_alloc_mem() function.
It displays the status of the allocated areas on the screen.  

The display must look like the following, with the addresses in ascending order :  

	break : 0xB0000
	0xA0000  - 0xA41CA : 16842  bytes
	0xAE000  - 0xAE03F : 63 bytes