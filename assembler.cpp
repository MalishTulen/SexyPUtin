#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <strings.h>
#include <stdlib.h>

#include "stack.h"
#include "SPU.h"
#include "assembler.h"

int file_translator ( spu_t spu )
{
    file_opener ( spu );
    //code_translator ( spu );
}

char* file_opener ( spu_t spu )
{
    spu.file_info.orig_file = fopen ( "original.txt", "r" );
    FILE* ptr_end = fopen ( "compilated.asm", "w" );

    struct stat wfile_info;
    fstat ( fileno ( spu.file_info.orig_file ), &wfile_info );

    spu.file_info.elems_amount = ( wfile_info.st_size );

    char cmd[10] = {};
    while  ( fscanf ( spu.file_info.orig_file, "%s", cmd ) != EOF )
    {
        if ( strcmp ( cmd, "PUSH" ) == 0) {
            char penis[10] = {};
            fscanf ( spu.file_info.orig_file, "%s", penis );
            fprintf ( ptr_end, "%d %s\n", PUSH, penis );
            continue;
        }
        if ( strcmp ( cmd, "SUM" ) == 0){
        fprintf ( ptr_end, "%d\n", SUM );
        continue;
        }
        if ( strcmp ( cmd, "SUB" ) == 0){
        fprintf ( ptr_end, "%d\n", SUB );
        continue;
        }
        if ( strcmp ( cmd, "MUL" ) == 0){
        fprintf ( ptr_end, "%d\n", MUL );
        continue;
        }
        if ( strcmp ( cmd, "DIV" ) == 0){
        fprintf ( ptr_end, "%d\n", DIV );
        continue;
        }
        if ( strcmp ( cmd, "OUT" ) == 0){
        fprintf ( ptr_end, "%d\n", OUT );
        continue;
        }
        if ( strcmp ( cmd, "HLT" ) == 0){
        fprintf ( ptr_end, "%d\n", HLT );
        continue;
        }
        if ( strcmp ( cmd, "DUMP" ) == 0){
        fprintf ( ptr_end, "%d\n", DUMP );
        continue;
        }
        if ( strcmp ( cmd, "PUSHR" ) == 0){
        fprintf ( ptr_end, "%d\n", PUSHR );
        continue;
        }
        if ( strcmp ( cmd, "POP" ) == 0){
        fprintf ( ptr_end, "%d\n", POP );
        continue;
        }
        if ( strcmp ( cmd, "JMP" ) == 0){
        fprintf ( ptr_end, "%d\n", JMP );
        continue;
        }
        if ( strcmp ( cmd, "JA" ) == 0){
        fprintf ( ptr_end, "%d\n", JA );
        continue;
        }
        if ( strcmp ( cmd, "JAE" ) == 0){
        fprintf ( ptr_end, "%d\n", JAE );
        continue;
        }
        if ( strcmp ( cmd, "JB" ) == 0){
        fprintf ( ptr_end, "%d\n", JB );
        continue;
        }
        if ( strcmp ( cmd, "JBE" ) == 0){
        fprintf ( ptr_end, "%d\n", JBE );
        continue;
        }
        if ( strcmp ( cmd, "JE" ) == 0){
        fprintf ( ptr_end, "%d\n", JE );
        continue;
        }
        if ( strcmp ( cmd, "JNE" ) == 0){
        fprintf ( ptr_end, "%d\n", JNE );
        continue;
        }
    }



    //ptr [ spu.file_info.elems_amount ] = '\0';
}
/*
FILE* code_translator ( spu_t spu )
{
    FILE* ptr_end = fopen ( "compilated.asm", "r" );

    for ( int i = 0; i < spu.file_info.elems_amount; i++ )
    {
        string cmd = "";
        char c = 0;
        if ( ( c = spu.file_info.ptr_tmp_file [ i ]) != " " )
        {
            cmd += c;
        }
        else
        {
            if ( cmd == "PUSH" )
                fprintf ( ptr_end, "%s ",
        }
    }
}*/
