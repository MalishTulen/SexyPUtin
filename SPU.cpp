#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "hash.h"
#include "SPU.h"

void run()
{
    spu_t spu = {};
    Stack_t stk;
    spu.ptr_stk = &stk;
    spu.ip = 0;

    StackCtor ( spu.ptr_stk, START_STK_CAPACITY );
//fprintf ( stderr, "ptr1" );
    do_this_file ( spu );
//fprintf ( stderr, "ptr2" );
}

int do_this_file ( spu_t spu )
{
    FILE* ptr_dofile = fopen ( "compilated.asm", "r" );

    if ( !ptr_dofile )
        return BAD_FILE_ERROR;

//fprintf ( stderr, "ptr3" );
    int RUNNING = 1;
    while ( RUNNING == 1 )
    {
        int cmd = 0;
        fscanf ( ptr_dofile, "%d", &cmd );
        switch ( cmd )
        {
            case PUSH:
            {
//fprintf ( stderr, "ptr4\n" );
                int operand = 0;
                fscanf ( ptr_dofile, "%d", &operand );
                StackPush ( spu.ptr_stk, operand );
                //StackDump ( spu.ptr_stk );
//fprintf ( stderr, "ptr41\n" );
                continue;
            }
            case SUM:
            {
                //StackDump ( spu.ptr_stk );
                int a = StackPop ( spu.ptr_stk );
                //StackDump ( spu.ptr_stk );
                int b = StackPop ( spu.ptr_stk );
                //StackDump ( spu.ptr_stk );
                StackPush ( spu.ptr_stk, ( a + b ) );
//fprintf ( stderr, "ptr5\n" );
                continue;
            }
            case DUMP:
            {
//fprintf ( stderr, "ptr6\n" );
                BIG_DUMP ( spu )
                continue;
            }
            case HLT:
            {
                RUNNING = 0;
            }
            case OUT:
            {
                int returned_value = StackPop ( spu.ptr_stk );
                printf ( "returned value: %d\n", returned_value );
                continue;
            }
            default:
                fprintf ( stderr, "SYNTAX_ERROR");
                break;
        }

    }
    fclose ( ptr_dofile );
    return JUICY_BALLS;
}
