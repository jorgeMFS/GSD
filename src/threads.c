#include <pthread.h>
#include <stdlib.h>
#include "threads.h"
#include "mem.h"

THREADS *CreateThreads(uint32_t id, uint32_t nt){
    THREADS *T = (THREADS *) Calloc(1, sizeof(THREADS));
    T->id = id;
    T->nt = nt;
    return T;
}

void DeleteThreads(THREADS *T){
    Free(T);
} 