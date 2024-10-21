#ifndef CPU_HEADER
#define CPU_HEADER

typedef int ip_t;
typedef int* stack_t;
typedef int* register_t;

struct assembler_t
{
    char creator[15];
    double version;
};

struct file_info_t
{
    FILE* orig_file;
    int elems_amount;
};

struct spu_t
{
    assembler_t asmbl_info; // TODO:
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

enum ERRORS
{
    BAD_FILE_ERROR = 3,
    SYNTAX_ERROR = 6,
};
const int READING = 1;
const int START_STK_CAPACITY = 14;
const int JUICY_BALLS = 0;

#define BIG_DUMP( spu )     {                             \
    printf ( "\n"                                                 \
             "------------------------------------------------\n"   \
             "|                  BIG DUMP                    |\n"   \
             "| CREATOR - (TODO)                             |\n"   \
             "| VERSION - (TODO)                             |\n"   \
             "------------------------------------------------\n"   \
             "|                  REGISTERS                   |\n"   \
             "| there should be registers... TODO....        |\n"   \
             "------------------------------------------------\n"   \
             "|                   STACK                      |\n"); \
    StackDump ( spu.ptr_stk );                                    \
    printf ( "------------------------------------------------\n"); \
    };


void run ();
int do_this_file ( spu_t spu );

#endif
