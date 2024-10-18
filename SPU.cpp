#include <stdio.h>

#include "stack.h"
#include "SPU.h"
#include "assembler.h"

void Run ()
{
    spu_t spu = {};
    Stack_t stk = {};
    spu.ptr_stk = &stk;
    spu.ip = 0;

    StackCtor ( spu.ptr_stk, 10 );

    /*while ( READING )
    {
        int cmd = 0;

        if ( cmd == PUSH )
            spu.ip++;
            StackPush ( spu.ptr_stk,
    }*/
}
