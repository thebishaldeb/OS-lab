//Implementing own malloc() in C programming language

/*
Memory Layout:
----Stack
----Heap
----Uninitialized data
----Initialized data
----Text/code segment

Interested in Heap
-top end of the heap->program break
-can move the program break in C using sbrk() and brk()
-sbrk()-->moves the program break to the address pointed by its argument
-brk()-->increments the program break by increment bytes(passed in the argument)

*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct memoryblock
{
	size_t size;
	struct memoryblock *next;
	struct memoryblock *prev;
} block;

static block *head = NULL;
#define BLOCK_MEM(ptr) ((void *)((unsigned long)ptr + sizeof(block)))
#define BHEADER(ptr) ((void *)((unsigned long)ptr - sizeof(block)))

//removing memory blocks from the free list
void freelist_remove(block *b)
{
	if (!b->prev)
	{
		if (b->next)
		{
			head = b->next;
		}
		else
		{
			head = NULL;
		}
	}
	else
	{
		b->prev->next = b->next;
	}
	if (b->next)
	{
		b->next->prev = b->prev;
	}
}

//adding memory blocks to the free list
void freelist_add(block *b)
{
	b->prev = NULL;
	b->next = NULL;
	if (!head || (unsigned long)head > (unsigned long)b)
	{
		if (head)
		{
			head->prev = b;
		}
		b->next = head;
		head = b;
	}
	else
	{
		block *curr = head;
		while (curr->next && (unsigned long)curr->next < (unsigned long)b)
		{
			curr = curr->next;
		}
		b->next = curr->next;
		curr->next = b;
	}
}

block *split(block *b, size_t size)
{
	void *mem_block = BLOCK_MEM(b);
	block *newptr = (block *)((unsigned long)mem_block + size);
	newptr->size = b->size - (size + sizeof(block));
	b->size = size;
	return newptr;
}

void *myMalloc(size_t size)
{
	void *block_mem;
	block *ptr, *newptr;
	size_t alloc_size = size + sizeof(block);

	//finding the best fit block for the memory requirement
	ptr = head;
	while (ptr)
	{
		if (ptr->size >= alloc_size)
		{
			block_mem = BLOCK_MEM(ptr);
			freelist_remove(ptr);

			if (ptr->size == alloc_size)
			{
				//CASE1:found the perfect fit and returned it
				return block_mem;
			}
			//CASE2:else the block is larger in size and we have to split it
			//and add the spare to the free list
			newptr = split(ptr, size);
			freelist_add(newptr);
			return block_mem;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	//CASE3: We couldn't find appropriate sized blocks from the free list so we ask the system/OS for additional memory using sbrk().
	ptr = sbrk(alloc_size);

	if (!ptr)
	{
		printf("failed to alloc %ld\n", alloc_size);
		return NULL;
	}

	ptr->next = NULL;
	ptr->prev = NULL;
	ptr->size = size;
	if (alloc_size > size + sizeof(block))
	{
		newptr = split(ptr, size);
		freelist_add(newptr);
	}
	return BLOCK_MEM(ptr);
}

void show_data()
{
	printf("\n program break: %10p\n", sbrk(0));
	block *ptr = head;

	int c = 0;
	while (ptr)
	{
		if (c == 0)
			printf("free list: \n");
		printf("(%d) <%10p> (size: %ld)\n", c, ptr, ptr->size);
		ptr = ptr->next;
		c++;
	}
}
void myfree(void *ptr)
{
	freelist_add(BHEADER(ptr));
}

int main()
{
	printf("\nEntering into main");

	printf("\nStarting stats");
	show_data();
	printf("\nCalling the mymalloc()");
	int *p1 = (int *)myMalloc(4 * sizeof(int));
	printf("\nStats after calling mymalloc()");
	// int a = 10;
	// p1 = &a;
	*p1 = 10;
	printf("\n%d\n", *p1);
	show_data();
	printf("\nStats after calling myfree()");
	myfree(p1);
	show_data();

	return 0;
}