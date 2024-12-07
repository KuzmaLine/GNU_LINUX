/**
 * @file buf.h
 * @brief Provides functions for managing growable memory buffers in C99.
 *
 * This file contains a set of functions to manage dynamic, growable memory buffers.
 * The functions allow for adding and removing elements, growing and truncating buffers,
 * and freeing memory. These functions work by manipulating the buffer pointer, so any
 * previously obtained pointers may be invalidated after certain operations.
 *
 * @note buf_push(), buf_grow(), buf_trunc(), and buf_free() may change the buffer pointer,
 *       and any previously-taken pointers should be considered invalidated.
 *
 * Example usage:
 * 
 * @code
 *     float *values = 0;
 *     for (size_t i = 0; i < 25; i++)
 *         buf_push(values, rand() / (float)RAND_MAX);
 *     for (size_t i = 0; i < buf_size(values); i++)
 *         printf("values[%zu] = %f\n", i, values[i]);
 *     buf_free(values);
 * @endcode
 *
 * @section functions Functions:
 * 
 * - `buf_size(v)`        : Returns the number of elements in the buffer.
 * - `buf_capacity(v)`    : Returns the total capacity of the buffer.
 * - `buf_free(v)`        : Destroys and frees the buffer.
 * - `buf_push(v, e)`     : Appends an element to the end of the buffer.
 * - `buf_pop(v)`         : Removes and returns an element from the end of the buffer.
 * - `buf_grow(v, n)`     : Increases the buffer capacity by `n` elements.
 * - `buf_trunc(v, n)`    : Sets the buffer capacity to exactly `n` elements.
 * - `buf_clear(v, n)`    : Sets the buffer size to 0 (for push/pop operations).
 */
#include <stddef.h>
#include <stdlib.h>

/** @brief Initial capacity of a buffer. */
#ifndef BUF_INIT_CAPACITY
#  define BUF_INIT_CAPACITY 8
#endif

/** @brief Abort the program on buffer allocation error. */
#ifndef BUF_ABORT
#  define BUF_ABORT abort()
#endif

/** 
 * @brief Represents a dynamically allocated buffer structure.
 * 
 * The buffer structure contains information about the size and capacity of the allocated
 * memory, and the actual data is stored in a flexible array member.
 */
struct buf {
    size_t capacity;
    size_t size;
    char buffer[];
};

/**
 * @brief Converts a buffer pointer to a struct buf pointer.
 * 
 * This macro calculates the address of the `struct buf` structure from the given buffer pointer.
 * It is used internally by other macros to manage buffer operations.
 * 
 * @param v The buffer pointer.
 * @return A pointer to the buffer structure.
 */
#define buf_ptr(v) \
    ((struct buf *)((char *)(v) - offsetof(struct buf, buffer)))


/**
 * @brief Frees the dynamically allocated buffer.
 * 
 * This macro frees the memory allocated for the buffer and invalidates the pointer.
 * 
 * @param v The buffer pointer to be freed.
 */
#define buf_free(v) \
    do { \
        if (v) { \
            free(buf_ptr((v))); \
            (v) = 0; \
        } \
    } while (0)

/**
 * @brief Returns the number of elements in the buffer.
 * 
 * This macro returns the current size of the buffer, or 0 if the buffer is NULL.
 * 
 * @param v The buffer pointer.
 * @return The number of elements in the buffer.
 */
#define buf_size(v) \
    ((v) ? buf_ptr((v))->size : 0)

/**
 * @brief Returns the total capacity of the buffer.
 * 
 * This macro returns the total capacity of the buffer, or 0 if the buffer is NULL.
 * 
 * @param v The buffer pointer.
 * @return The capacity of the buffer.
 */
#define buf_capacity(v) \
    ((v) ? buf_ptr((v))->capacity : 0)

/**
 * @brief Appends an element to the buffer.
 * 
 * This macro appends the element `e` to the buffer. If the buffer is full, it will be grown
 * to accommodate the new element.
 * 
 * @param v The buffer pointer.
 * @param e The element to append to the buffer.
 */
#define buf_push(v, e) \
    do { \
        if (buf_capacity((v)) == buf_size((v))) { \
            (v) = buf_grow1(v, sizeof(*(v)), \
                            !buf_capacity((v)) ? \
                              BUF_INIT_CAPACITY : \
                              buf_capacity((v))); \
        } \
        (v)[buf_ptr((v))->size++] = (e); \
    } while (0)

/**
 * @brief Removes and returns the last element from the buffer.
 * 
 * This macro removes and returns the last element of the buffer.
 * 
 * @param v The buffer pointer.
 * @return The last element of the buffer.
 */
#define buf_pop(v) \
    ((v)[--buf_ptr(v)->size])

/**
 * @brief Increases the buffer's capacity.
 * 
 * This macro grows the buffer by `n` elements. It is equivalent to calling `buf_grow1()`.
 * 
 * @param v The buffer pointer.
 * @param n The number of elements to add to the buffer's capacity.
 */
#define buf_grow(v, n) \
    ((v) = buf_grow1((v), sizeof(*(v)), n))

/**
 * @brief Truncates the buffer to a specified capacity.
 * 
 * This macro sets the buffer's capacity to exactly `n` elements.
 * 
 * @param v The buffer pointer.
 * @param n The new capacity of the buffer.
 */
#define buf_trunc(v, n) \
    ((v) = buf_grow1((v), sizeof(*(v)), n - buf_capacity(v)))

/**
 * @brief Clears the buffer, setting its size to 0.
 * 
 * This macro sets the size of the buffer to 0, effectively clearing it.
 * 
 * @param v The buffer pointer.
 */
#define buf_clear(v) \
    ((v) ? (buf_ptr((v))->size = 0) : 0)


/**
 * @brief Grows the buffer to accommodate `n` more elements.
 * 
 * This static function reallocates memory for the buffer, increasing its capacity.
 * If an error occurs during memory allocation, the program is aborted.
 * 
 * @param v The buffer pointer.
 * @param esize The size of each element in the buffer.
 * @param n The number of elements to increase the buffer's capacity by.
 * @return A pointer to the buffer's data.
 * @note This function is used internally by other macros.
 */
static void * buf_grow1(void *v, size_t esize, ptrdiff_t n)
{
    struct buf *p;
    size_t max = (size_t)-1 - sizeof(struct buf);
    if (v) {
        p = buf_ptr(v);
        if (n > 0 && p->capacity + n > max / esize)
            goto fail; /* overflow */
        p = realloc(p, sizeof(struct buf) + esize * (p->capacity + n));
        if (!p)
            goto fail;
        p->capacity += n;
        if (p->size > p->capacity)
            p->size = p->capacity;
    } else {
        if ((size_t)n > max / esize)
            goto fail; /* overflow */
        p = malloc(sizeof(struct buf) + esize * n);
        if (!p)
            goto fail;
        p->capacity = n;
        p->size = 0;
    }
    return p->buffer;
fail:
    BUF_ABORT;
    return 0;
}
