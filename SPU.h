#ifndef CPU_HEADER
#define CPU_HEADER

typedef int ip_t;
typedef int* stack_t;
typedef int* register_t;

struct file_info_t
{
    FILE* orig_file;
    int elems_amount;
};

struct spu_t
{
    file_info_t file_info;
    FILE* compiled_file;
    Stack_t* ptr_stk;
    ip_t ip;
    register_t reg_array[10];
};

enum FUNC_INITS
{
    PUSH = 1,
    SUM = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    OUT = 6,
    HLT = -1,
    DUMP = 69,
    PUSHR = 7,
    POP = 8,
    JMP = 10,
    JA = 11,
    JAE = 12,
    JB = 13,
    JBE  = 14,
    JE = 15,
    JNE = 16
};

const int READING = 1;
const int VOZRAST_SOGLASIYA_V_KITAYE = 14;
const int START_STK_CAPACITY = VOZRAST_SOGLASIYA_V_KITAYE;

void Run ();

#endif