#ifndef SPU_HEADER
#define SPU_HEADER

typedef int ip_t;
typedef int* stack_t;
typedef int register_t;

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
    JNE = 16,
    CALL = 17,
    RET = 18,
};

enum ERRORS
{
    BAD_FILE_ERROR = 3,
    SYNTAX_ERROR = 6,
    NOT_ENOUGH_REGISTERS = 9,
    BAD_ERROR = 667,
};
const int READING = 1;
const int REG_ARRAY_CAPACITY = 5;
const int START_STK_CAPACITY = 14;
const int JUICY_BALLS = 0;
const int REG_NOT_EXISTS = -1;
const int MAX_CMD_SIZE = 500;

struct assembler_t
{
    char creator[15];
    double version;
};

struct cmd_t
{
    int* ptr_code;
    int ip;
    int size_code;
};

struct spu_t
{
    assembler_t asmbl_info;
    FILE* compiled_file;
    Stack_t* ptr_stk;
    Stack_t* ptr_func_stk;
    cmd_t cdm;
    register_t reg_array [ REG_ARRAY_CAPACITY ];
};

void run ();
int do_this_file ( spu_t* ptr_spu );
int big_dump ( spu_t* ptr_spu );
int make_array_with_code ( spu_t* ptr_spu );

#endif
