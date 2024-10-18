#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int GOVNO = 0;

#include "stack.h"
#include "hash.h"
#include "SPU.h"
#include "assembler.h"

int main()
{
    spu_t SPU = {};
    Stack_t gooooal = {};
    Stack_t* tmp_ptr = &gooooal;
    SPU.ptr_stk = tmp_ptr;
    StackCtor ( SPU.ptr_stk, START_STK_CAPACITY );

    file_opener ( SPU );

}
