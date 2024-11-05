#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "colourful.h"
#include "stack.h"
#include "hash.h"
#include "SPU.h"

int RAM[ RAM_CAPACITY ] = {};
// TODO: remove redundant .h files

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

//fprintf ( stderr, "DEBUG1\n");
    StackCtor ( spu.ptr_stk, START_STK_CAPACITY );
    StackCtor ( spu.ptr_func_stk, START_STK_CAPACITY );
//fprintf ( stderr, "DEBUG2\n");
    make_array_with_code ( ptr_spu );
//fprintf ( stderr, "DEBUG3\n");
    big_dump ( ptr_spu );
    do_this_file ( ptr_spu );
}

int big_dump ( spu_t* ptr_spu )
{
    printf ( "\n"
             "<KWGFLKGKFGLKUGFLIUFOUWFIUWTFIUWTFIUTWFIWYFWFUT>\n"
             "|                   " GIVE_MORE_COLOUR (BOLD, RED, DEF_B ) "BIG DUMP" SET_DEFAULT_COLOUR "                   |\n"
             "| CREATOR - (TODO)                             |\n"
             "| VERSION - (TODO)                             |\n"
             "------------------------------------------------\n"
             "|                  " GIVE_MORE_COLOUR ( BOLD, RED, DEF_B) "REGISTERS" SET_DEFAULT_COLOUR"                   |\n");
    for ( int i = 0; i < REG_ARRAY_CAPACITY; i++ )
    {
        printf ( "| register " GIVE_MORE_COLOUR ( KOSOY, BLUE, DEF_B ) "%cX" SET_DEFAULT_COLOUR " = %d                              |\n", 'A' + i, ptr_spu->reg_array [ i ] );
    }
    printf ( "------------------------------------------------\n"
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

    printf ( "\n------------------------------------------------\n"
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
    if ( !ptr_spu )
    {
        fprintf ( stderr, "ERROR WITH OPENING FILE\n");
    }
    int running = 1;

    while ( running )
    {
        int cmd = ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ];
//fprintf ( stderr, "cmd = '%d'\n", cmd );
        int cmd_no_balls = cmd & ~TYPE_FULL_BIT;
        switch ( cmd_no_balls )
        {
            case PUSH:
            {
                //printf ( "%d", ptr_spu->cdm.ptr_code [ ptr_spu->cdm.ip ] );
                int* type_push = get_arg ( ptr_spu );

                StackPush ( ptr_spu->ptr_stk, ( Stack_Elem_Data_t )( *type_push ) );
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
            case DRAW:
            {
                printf ( "\n|                    RAM                         |\n");
                for ( int i = 0; i < RAM_CAPACITY + 1 ; i++ )
                {
                    if ( RAM [ i ] == 1 )
                        printf ( "##");
                    else
                        printf ( ".." );
                    if ( ( ( i )  % ( 100 ) == 0 ) && ( i != 0 ) )
                        printf ( "\n" );
                }
                printf ( "\n");
                ptr_spu->cdm.ip++;
                break;
            }
            case HLT:
            {
                running = 0;
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
                int b = StackPop ( ptr_spu->ptr_stk );
                int a = StackPop ( ptr_spu->ptr_stk );
                StackPush ( ptr_spu->ptr_stk, a / b );
                ptr_spu->cdm.ip++;
                break;
            }
            case POP:
            {
                int* type_pop = get_arg ( ptr_spu );

//StackDump ( ptr_spu->ptr_stk );
//printf ( "\n---------------------------\n");

                if ( ptr_spu->ptr_stk->size == 0 )
fprintf ( stderr, "ZERO ELEMENTS WHILE POPPING! ( ip = %d )\n", ptr_spu->cdm.ip );
                *type_pop = StackPop ( ptr_spu->ptr_stk );
                break;
            }
            case OUT:
            {
                if ( ptr_spu->ptr_stk->size == 0 )
                {
                    running = 0;
                    printf ( "ZERO ELEMS TO OUT!\n" );
                }
                else
                {
                    int c = StackPop ( ptr_spu->ptr_stk );
                    printf ( "returned value: " GIVE_MORE_COLOUR ( BOLD, YELLOW, DEF_B ) "%d" SET_DEFAULT_COLOUR "\n", c );
                    ptr_spu->ptr_stk->data_ptr [ ptr_spu->ptr_stk->size - 1 ] = 0;
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
                running = 0;
                break;
            }
        }
    }

    return FUNC_DONE;
}

int make_array_with_code ( spu_t* ptr_spu )
{
    FILE* ptr_file = fopen ( "compilated.txt", "r" );
    if ( !ptr_file )
    {
        printf ( GIVE_MORE_COLOUR(BOLD, RED, DEF_B ) "FAIL POINTER" SET_DEFAULT_COLOUR "\n");
        return 52;
    }

    ptr_spu->cdm.ptr_code = ( int* ) calloc ( MAX_CMD_SIZE, sizeof ( int ) );
    for ( int i = 0; i < MAX_CMD_SIZE; i++ )
    {
        int symbol = 0;
        if ( ( fscanf ( ptr_file, "%d ", &symbol ) ) == 1 )
        {
            //fprintf ( stderr, "&&^&^&^&^scanf: %d\n", c);
            ptr_spu->cdm.ptr_code[ i ] = symbol;
            ptr_spu->cdm.size_code++;
        }
    }

    fclose ( ptr_file );
    return FUNC_DONE;
}

int* get_arg ( spu_t* ptr_spu )
{

    cmd_t *cmd = &ptr_spu->cdm;
    int operand = cmd->ptr_code [ ptr_spu->cdm.ip++ ];
//fprintf  ( stderr, "operand: %d\n", operand );

    static int arg_value = 0;

    arg_value = 0;

    int* reg_ptr = NULL;
    int* arg_value_ptr = NULL;

    if ( ( operand & TYPE_CONSTANT ) && ( operand & TYPE_REGISTER ) && !( operand & TYPE_MEMORY ) )
    {
//fprintf ( stderr, "instead of using heroin try '[]' ( ip = %d )\n", cmd->ip );
        return 0;
    }

    if ( operand & TYPE_REGISTER)
    {
        reg_ptr = &( ptr_spu->reg_array [ cmd->ptr_code [ ptr_spu->cdm.ip++ ] ] );
        arg_value += *reg_ptr;
    }

    if ( operand & TYPE_CONSTANT )
        arg_value += cmd->ptr_code [ ptr_spu->cdm.ip++ ];

    if ( operand & TYPE_MEMORY )
    {
        if ( arg_value < RAM_CAPACITY+1 )
            arg_value_ptr = &( RAM [ arg_value ] );
        else
            fprintf ( stderr, "RAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM OVERFLOW!\n");
    }

    else if ( operand & TYPE_REGISTER)
        arg_value_ptr = reg_ptr;

    else
        arg_value_ptr = &arg_value;

//fprintf  ( stderr, "argvalue: %d\n", arg_value );
//fprintf  ( stderr, "ptr_argvalue: %d\n-----------------------------\n", *arg_value_ptr );

    return arg_value_ptr;
}

