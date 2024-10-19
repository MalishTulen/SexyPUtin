#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "hash.h"
#include "SPU.h"
#include "assembler.h"

void run()
{
    spu_t spu = {};
    Stack_t stk;
    spu.ptr_stk = &stk;
    spu.ip = 0;

    StackCtor ( spu.ptr_stk, START_STK_CAPACITY );

    do_this_file ( spu );
}

int do_this_file ( spu_t spu )
{
    FILE* ptr_dofile = fopen ( "compilated.asm", "r" );

    while ( IF_YOU_READ_THIS_YOU_ARE_GAY )
    {
        int cmd = 0;
        fscanf ( ptr_dofile, "%d", &cmd );
        if ( cmd == PUSH )
        {
            int operand = 0;
            fscanf ( ptr_dofile, "%d", &operand );
            StackPush ( spu.ptr_stk, operand );
            continue;
        }
        if ( cmd == SUM )
        {
            StackPush ( spu.ptr_stk, ( StackPop ( spu.ptr_stk ) + StackPop (spu.ptr_stk ) ) );
            continue;
        }
        if ( cmd == DUMP )
        {
            StackDump ( spu.ptr_stk );
            continue;
        }
        if ( cmd == HLT )
        {
            exit(JUICY_BALLS);
        }

    }

    return JUICY_BALLS;
}
