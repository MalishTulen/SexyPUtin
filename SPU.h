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
    HLT = 31,
    DUMP = 7,
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
    BAD_FILE_ERROR = -1,
    SYNTAX_ERROR = -2,
    NOT_ENOUGH_REGISTERS = -3,
    BAD_ERROR = 667,
};

enum PUSH_TYPES
{
    TYPE_CONSTANT = 1 << 5,
    TYPE_REGISTER = 1 << 6,
    TYPE_MEMORY   = 1 << 7,
    TYPE_FULL_BIT = TYPE_CONSTANT | TYPE_REGISTER | TYPE_MEMORY,
};

const int READING = 1;
const int REG_ARRAY_CAPACITY = 5;
const int START_STK_CAPACITY = 14;
const int JUICY_BALLS = 0;
const int REG_NOT_EXISTS = -1;
const int MAX_CMD_SIZE = 500;
const int RAM_CAPACITY = 10;

struct assembler_t
{
    char    creator[15];
    double  version;
};

struct cmd_t
{
    int*    ptr_code;
    int     ip;
    int     size_code;
};

struct spu_t
{
    assembler_t asmbl_info;
    FILE*       compiled_file;
    Stack_t*    ptr_stk;
    Stack_t*    ptr_func_stk;
    cmd_t       cdm;
    register_t  reg_array [ REG_ARRAY_CAPACITY ];
};

void               run                  ();
int                do_this_file         ( spu_t* ptr_spu );
int                big_dump             ( spu_t* ptr_spu );
int                make_array_with_code ( spu_t* ptr_spu );
int* get_arg              ( spu_t* ptr_spu );

#endif
