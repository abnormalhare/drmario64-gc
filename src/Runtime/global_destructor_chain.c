#include "Runtime/NMWException.h"

DestructorChain* __global_destructor_chain;

void __destroy_global_chain(void) {
    DestructorChain* iter;
    while ((iter = __global_destructor_chain) != 0) {
        __global_destructor_chain = iter->next;
        DTORCALL(iter->destructor, iter->object);
    }
}

/* clang-format off */
__declspec(section ".dtors")
static void* const __destroy_global_chain_reference = __destroy_global_chain;
/* clang-format on */
