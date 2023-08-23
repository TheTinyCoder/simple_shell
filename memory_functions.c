#include "main.h"
#include <stdlib.h>

/**
 * *_memcpy -  function entry-point
 *
 * Description: 'copies memory area btwn pointers'
 * @dest: destination void pointer
 * @src: source void pointer
 * @size: size of dest pointer
 * Return: void
 */

void _memcpy(void *dest, void *src, unsigned int size)
{
	char *char_src = (char *)src, *char_dest = (char *)dest;
	unsigned int i = 0;

	for (; i < size; i++)
		char_dest[i] = char_src[i];
}


/**
 * *_realloc - function entry-point
 *
 * Description: reallocates memory using malloc and free
 * @ptr: pointer to previous memory allocation
 * @old_size: size, in bytes, of the allocated space for ptr
 * @new_size: new size, in bytes of the new memory block
 * Return: pointer to created array
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(new_ptr, ptr, new_size);
	else
		_memcpy(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}


/**
 * _reallocdp - function entry-point
 *
 * Description: reallocates a memory (of a double pointer)
 * @old: double pointer to the memory previously allocated
 * @old_size: previous allocation
 * @new_size: new allocation
 * Return: pointer or NULL
 */

char **_reallocdp(char **old, unsigned int old_size, unsigned int new_size)
{
	char **new;
	unsigned int i;

	if (old == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (old);

	new = malloc(sizeof(char *) * new_size);
	if (new == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		new[i] = old[i];

	free(old);

	return (new);
}
