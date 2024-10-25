#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

#include "colourful.h"
#include "stack.h"
#include "hash.h"
#include "SPU.h"


void run()
{
    spu_t spu = {};
    spu_t* ptr_spu = &spu;
    Stack_t stk = {};
    spu.ptr_stk = &stk;
    Stack_t func_stk = {};
    spu.ptr_func_stk = &func_stk;
    spu.reg_array[ REG_ARRAY_CAPACITY ] = {};
    spu.cdm.ip = 0;
    StackCtor ( spu.ptr_stk, START_STK_CAPACITY );
    StackCtor ( spu.ptr_func_stk, START_STK_CAPACITY );
    make_array_with_code ( ptr_spu );

    do_this_file ( ptr_spu );
}

int big_dump ( spu_t* ptr_spu )
{
    printf ( "\n"
             "------------------------------------------------\n"
             "|                   " GIVE_MORE_COLOUR (BOLD, RED, DEF_B ) "BIG DUMP" SET_DEFAULT_COLOUR "                   |\n"
             "| CREATOR - (TODO)                             |\n"
             "| VERSION - (TODO)                             |\n"
             "------------------------------------------------\n"
             "|                  " GIVE_MORE_COLOUR ( BOLD, RED, DEF_B) "REGISTERS" SET_DEFAULT_COLOUR"                   |\n");
    for ( int i = 0; i < REG_ARRAY_CAPACITY; i++ )
    {
        printf ( "| register " GIVE_MORE_COLOUR ( KOSOY, BLUE, DEF_B ) "%cX" SET_DEFAULT_COLOUR " = %d                              |\n", 'A' + i, ptr_spu->reg_array [ i ] );
    }
    printf (  "------------------------------------------------\n"
              "|                 " GIVE_MORE_COLOUR ( BOLD, MAGENTA, DEF_B ) "PROGRAMM CODE" SET_DEFAULT_COLOUR"                |\n");
    printf ( "|   ________                 \n"
             "|  /  DED   \\               \n"
             "| |          |               \n|");
    for ( int i = 0; i < ptr_spu->cdm.size_code; i++ )
    {
        if ( ptr_spu->cdm.ip == i )
        {
            printf ( GIVE_MORE_COLOUR ( DEF_FORMAT, DEF_COLOUR, REDB ) "%3d" SET_DEFAULT_COLOUR " ", ptr_spu->cdm.ptr_code [ i ] );
        }
        else
        {
            printf ( "%3d ", ptr_spu->cdm.ptr_code [ i ] );
        }
    }
    printf ( "\n" );
    printf ( "|" );
    for ( int i = 0; i < ptr_spu->cdm.size_code; i++ )
    {
        printf ( "%3d ", i );
    }
    printf ( "\n| |          |   \n"
             "| \\   LOH    /   \n"
             "|  \\________/   \n");

    printf (  "\n------------------------------------------------\n"
             "|                     STACK                      |\n");
    StackDump ( ptr_spu->ptr_stk );
    printf ( "------------------------------------------------\n");

    printf ( "\n|                FUNC STACK                      |\n");
    StackDump ( ptr_spu->ptr_func_stk );
    printf ( "------------------------------------------------\n");
    return FUNC_DONE;
}

int do_this_file ( spu_t* ptr_spu )
{
    int RUNNING = 1;
    while ( RUNNING )
    {
        int cmd = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
        switch ( cmd )
        {
            case PUSH:
            {
                ptr_spu->cdm.ip++;
                //printf ( "%d", ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ] );
                StackPush ( ptr_spu->ptr_stk, ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ] );
                ptr_spu->cdm.ip++;
                break;
            }
            case SUM:
            {
                StackPush ( ptr_spu->ptr_stk, ( StackPop ( ptr_spu->ptr_stk ) + StackPop ( ptr_spu->ptr_stk ) ) );
                ptr_spu->cdm.ip++;
                break;
            }
            case DUMP:
            {
                big_dump ( ptr_spu );
                ptr_spu->cdm.ip++;
                break;
            }
            case HLT:
            {
                RUNNING = 0;
                break;
            }
            case SUB:
            {
                int a = StackPop ( ptr_spu->ptr_stk );
                int b = StackPop ( ptr_spu->ptr_stk );
                StackPush ( ptr_spu->ptr_stk, b - a );
                ptr_spu->cdm.ip++;
                break;
            }
            case MUL:
            {
                StackPush ( ptr_spu->ptr_stk, StackPop ( ptr_spu->ptr_stk ) * StackPop ( ptr_spu->ptr_stk ) );
                ptr_spu->cdm.ip++;
                break;
            }
            case DIV:
            {
                int a = StackPop ( ptr_spu->ptr_stk );
                int b = StackPop ( ptr_spu->ptr_stk );
                StackPush ( ptr_spu->ptr_stk, b / a );
                ptr_spu->cdm.ip++;
                break;
            }
            case PUSHR:
            {
                ptr_spu->cdm.ip ++;
                int reg_numb = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                StackPush ( ptr_spu->ptr_stk, ptr_spu->reg_array [ reg_numb ] );
                ptr_spu->cdm.ip ++;
                break;
            }

            case POP:
            {
                ptr_spu->cdm.ip ++;
                int reg_numb = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                ptr_spu->reg_array [ reg_numb ] = StackPop ( ptr_spu->ptr_stk );
                ptr_spu->cdm.ip++;
                break;
            }
            case OUT:
            {
                if ( ptr_spu->ptr_stk->size == 0 )
                {
                    RUNNING = 0;
                    printf ( "ZERO ELEMS TO OUT!\n" );
                }
                else
                {
                    int c = StackPop ( ptr_spu->ptr_stk );
                    printf ( "returned value: " GIVE_MORE_COLOUR ( BOLD, YELLOW, DEF_B ) "%d" SET_DEFAULT_COLOUR "\n", c );
                    ptr_spu->ptr_stk->data_ptr [ ptr_spu->ptr_stk->size ] = 0;
                    ptr_spu->cdm.ip++;
                    break;
                }
            }

            case JMP:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                ptr_spu->cdm.ip = where;
                break;
            }

            case JA:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                int b = StackPop ( ptr_spu->ptr_stk );
                int a = StackPop ( ptr_spu->ptr_stk );
                if ( a > b )
                {
                    ptr_spu->cdm.ip = where;
                }
                else
                {
                    ptr_spu->cdm.ip++;
                }
                break;
            }

            case JAE:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                int b = StackPop ( ptr_spu->ptr_stk );
                int a = StackPop ( ptr_spu->ptr_stk );
                if ( a >= b )
                {
                    ptr_spu->cdm.ip = where;
                }
                else
                {
                    ptr_spu->cdm.ip++;
                }
                break;
            }

            case JB:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                int b = StackPop ( ptr_spu->ptr_stk );
                int a = StackPop ( ptr_spu->ptr_stk );
                if ( a < b )
                {
                    ptr_spu->cdm.ip = where;
                }
                else
                {
                    ptr_spu->cdm.ip++;
                }
                break;
            }

            case JBE:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                int b = StackPop ( ptr_spu->ptr_stk );
                int a = StackPop ( ptr_spu->ptr_stk );
                if ( a <= b )
                {
                    ptr_spu->cdm.ip = where;
                }
                else
                {
                    ptr_spu->cdm.ip++;
                }
                break;
            }

            case JE:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                int b = StackPop ( ptr_spu->ptr_stk );
                int a = StackPop ( ptr_spu->ptr_stk );
                if ( a == b )
                {
                    ptr_spu->cdm.ip = where;
                }
                else
                {
                    ptr_spu->cdm.ip++;
                }
                break;
            }

            case JNE:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
                int b = StackPop ( ptr_spu->ptr_stk );
                int a = StackPop ( ptr_spu->ptr_stk );
                if ( a != b )
                {
                    ptr_spu->cdm.ip = where;
                }
                else
                {
                    ptr_spu->cdm.ip++;
                }
                break;
            }

            case CALL:
            {
                ptr_spu->cdm.ip++;
                int where = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];

                ptr_spu->cdm.ip++;
                StackPush ( ptr_spu->ptr_func_stk, ptr_spu->cdm.ip );
                ptr_spu->cdm.ip = where;
                break;
            }

            case RET:
            {
                ptr_spu->cdm.ip = StackPop ( ptr_spu->ptr_func_stk );
                break;
            }

            default:
            {
                fprintf ( stderr, "SYNTAX_ERROR - '%d, ip=%d'", cmd, ptr_spu->cdm.ip);
                RUNNING = 0;
                break;
            }
        }
    }

    return JUICY_BALLS;
}

int make_array_with_code ( spu_t* ptr_spu )
{
    FILE* ptr_file = fopen ( "compilated.txt", "r" );
    if ( !ptr_file )
    {
        printf ( GIVE_MORE_COLOUR(BOLD, RED, DEF_B ) "FAIL POINTER" SET_DEFAULT_COLOUR "\n");
        exit(52);
    }

    ptr_spu->cdm.ptr_code = ( int* ) calloc ( MAX_CMD_SIZE, sizeof ( int ) );
    for ( int i = 0; i < MAX_CMD_SIZE; i++ )
    {
        int c = 0;
        if ( ( fscanf ( ptr_file, "%d ", &c ) ) == 1 )
        {
            //fprintf ( stderr, "&&^&^&^&^scanf: %d\n", c);
            ptr_spu->cdm.ptr_code[ i ] = c;
            ptr_spu->cdm.size_code++;
        }
    }

    fclose ( ptr_file );
    return FUNC_DONE;
}


