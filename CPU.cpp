#include "MyLib/MyLib.h"
#include "MyLib/LibOfAsm.h"
#include "MyLib/enum.h"
#include "MyLib/Opeartions.h"


/*!
 * Makes buffer with machine code
 * @param[in] name of file
 * @return pointer on the beginning of machine code
 */
char* Reader (const char* name);

/*!
 * Carries out machine code
 * @param[in] machineCode
 * @param this_ Stack
 */
void CPU ( char* machineCode, Stack_t * this_ );


int main ()
{
    const char namein[] = "X:\\binaryCode.bin";

    char* machineCode = Reader (namein);

    Stack_t this_ = {};
    StackInit ( &this_ );

    CPU ( machineCode, &this_ );
}

char* Reader ( const char* namein)
{
    FILE*f = fopen(namein, "rb");

    struct stat file = {};
    stat ( namein , &file );

    struct WhatIs version = {};
    fread( &version, sizeof ( WhatIs ), 1, f );

    char * machineCode = ( char* ) calloc ( file.st_size, sizeof (char) ) ;
    fread ( machineCode, sizeof (char), file.st_size, f);

    return machineCode;
}

void CPU ( char* machineCode, Stack_t * this_ )
{
    int i = 0;

    Stack_t function = {};
    StackInit (&function);

    while (true)
    {
        switch (machineCode[i])
        {

#define DEF_CMD(name, num, arguments, code, write, out)             \
        case (CMD_##name):                                          \
        {                                                           \
        i += sizeof (char);                                         \
        code                                                        \
        ON_DEBUG(Dump(this_, __INFORMATION__, "Just for looking");) \
        break;                                                      \
        }

#include "MyLib/Commands.h"

#undef DEF_CMD
            default:
            {
                printf ("Syntax Error");
                exit (NotSuchCommand);
            }
        }
    }
}