#ifndef _QUEUE_H
#define _QUEUE_H


#include <stdint.h>

#include <macros.h>


#define queue_destroy(...)      _queue_destroy(_NARG(__VA_ARGS__), __VA_ARGS__)

#define queue_initialise(...)   _queue_initialise(_NARG(__VA_ARGS__), __VA_ARGS__)

#define queue_push(...)         _queue_push(_NARG(__VA_ARGS__), __VA_ARGS__)

#define queue_size(...)         _queue_size(_NARG(__VA_ARGS__), __VA_ARGS__)


typedef int (*_QUEUE_COMPARE)(const void *pA, const void *pB);

typedef void (*_QUEUE_DESTROY)(void *pArg);

typedef struct _QUEUE {

    _QUEUE_COMPARE Compare;

    _QUEUE_DESTROY Destroy;

    void ** Queue;

    size_t Count;

    size_t Size;

    uint8_t Alloc;
}
QUEUE;


void _queue_destroy(size_t Arg, QUEUE *Queue, ...);

void _queue_initialise(size_t Arg, QUEUE *Queue, ...);

int _queue_push(size_t Arg, QUEUE *Queue, ...);

size_t _queue_size(size_t Arg, QUEUE *Queue, ...);

QUEUE * queue_new(void);

void * queue_peek(QUEUE *Queue);

void * queue_pop(QUEUE *Queue);


#endif  /* _QUEUE_H */
