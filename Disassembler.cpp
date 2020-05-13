#include "MyLib/MyLib.h"
#include "MyLib/LibOfAsm.h"
#include <sys/stat.h>
#include "MyLib/enum.h"
#include <string.h>

struct Label {
    char* address;
    int number;
};

/*!
 * Call Disas
 */
void DisasCall ();


/*!
 * Checks necessarity of compiling
 * @param namein - Name of input file
 * @param nameout - Name of output file
 */
void IfNewVersion (const char* namein, const char* nameout);

/*!
 * Writes info about programm
 * @param out - output file
 * @param namein - Name of input file
 * @return buffer - pointer on the element of code
 */
char* InfoWriting (FILE * out, const char * namein);

/*!
 * Prints register
 * @param buffer - pointer on the element of code
 * @param out - output file
 */
void WhatToPrint (char* buffer, FILE * out);

/*!
 * Prints PUSH arguments
 * @param buffer - pointer on the element of code
 * @param out - output file
 * @return buffer - pointer on the element of code
 */
char* PushArgumentReader (char* buffer, FILE* out);

/*!
 * Prints JUMP arguments
 * @param buffer - pointer on the element of code
 * @param label - massive of labels
 * @param out - output file
 * @return buffer - pointer on the element of code
 */
char* JmpArgumentReader (char* buffer, struct Label * label, FILE* out);

/*!
 * Prints POP argument
 * @param buffer - pointer on the element of code
 * @param out - output file
 * @return buffer - pointer on the element of code
 */
char* PopArgumentReader (char* buffer, FILE* out);

/*!
 * Find all labels and makes necessary notes
 * @param buffer - pointer on the element of code
 * @param namein - input file
 * @return labels
 */
struct Label * LabelRead (char* buffer, int* i_lable, const char* namein);

/*!
 * Disas machine code
 * @param namein - Name of input file
 * @param nameout - Name of output file
 * @return 0 if OK
 */
int Disas (const char* namein, const char* nameout);

int main ()
{
    DisasCall ();
}

///память, сделать через switch
///#define COMPARIN(what) if ( number == what ) /*fprintf (out, #what); */                  \
///                        {                                                                \
///                            const char* c = {#what};                                     \
///                            int i = 0;                                                   \
///                       while ( i < size )                                               \
///                        {                                                                \
///                            command[i] = c[i];                                           \
///                            i++;                                                         \
///                        }                                                                \
///                        }


void  DisasCall ()
{
    const char namein[] = "X:\\binaryCode.bin";

    char nameout[FILENAME_MAX] = {};
    printf ("\nWrite name of file to output or push ENTER to use basic file\n");
    scanf ("%[^(\n)]", nameout);

    if (strcmp(nameout, "\0") == 0)
    {
        memcpy (nameout, "X:\\out.asm", FILENAME_MAX);
    }
    
    IfNewVersion (namein, nameout);
    Disas (namein, nameout);
}

void IfNewVersion (const char* namein, const char* nameout)
{
    ASSERT (namein)
    ASSERT (nameout)

    struct stat in = {};
    stat (namein , &in);

    struct stat out = {};
    stat (nameout, &out);

    /*if (in.st_mtime <= out.st_mtime)
    {
        exit (FileReady);
    }*/
}

char* InfoWriting (FILE * out, const char * namein)
{
    char *buffer = BufferMaker (namein);
    ASSERT (buffer)

    struct WhatIs &version = *(struct WhatIs *)buffer;
    buffer += sizeof (struct WhatIs);

    ON_DEBUG ( printf ("Made by %s version 0.%d\n", version.name, version.version );)
    fprintf (out, "Made by %s version 0.%d\n", version.name, version.version );

    ASSERT (buffer)

    return buffer;
}


void WhatToPrint (char* buffer, FILE * out)
{
    if (*buffer == ax)
    {
        fprintf (out, " ax");
        ON_DEBUG (printf (" $ax$");)
    }
    else
    {
        if (*buffer == bx)
        {
            fprintf (out, " bx");
            ON_DEBUG (printf (" $bx$");)
        }
        else
        {
            if (*buffer == cx)
            {
                fprintf (out, " cx");
                ON_DEBUG (printf (" $cx$");)
            }
            else
            {
                if (*buffer == dx)
                {
                    fprintf (out, " dx");
                    ON_DEBUG (printf (" $dx$");)
                }
                else
                {
                    printf ("Syntax Error");
                    exit (NotSuchCommand);
                }
            }
        }
    }
}

char* MemWrt (FILE* out, char* buffer)
{
    fprintf (out, " [");
    if (*buffer == INT_)
    {
        buffer += sizeof (char);
        fprintf (out, "%d]", *(int*)buffer);
        buffer += sizeof (int);
        return buffer;
    }
    if (*buffer == REG)
    {
        buffer += sizeof (char);
        WhatToPrint (buffer, out);
        buffer += sizeof (char);
        fprintf (out, "]");
        return buffer;
    }
    if (*buffer == INT_REG)
    {
        buffer += sizeof (char);
        fprintf (out, "%d +", *(int*)buffer);
        buffer += sizeof (int);
        WhatToPrint (buffer, out);
        buffer += sizeof (char);
        fprintf (out, "]");
        return buffer;
    }
    printf("Syntax Error");
    exit (NotSuchCommand);
}

char* PushArgumentReader (char* buffer, FILE* out)
{
    buffer += sizeof (char);
    if (*(buffer - 1) == INT_)
    {
        fprintf (out, " %d", *(int*)(buffer));
        ON_DEBUG (printf (" $%d$\n", *(int*)(buffer));)
        buffer += sizeof (int);
    }
    else
    {
        if (*(buffer - 1) == REG)
        {
            WhatToPrint (buffer, out);
            buffer += sizeof (char);
        }
        else
        {
            buffer = MemWrt (out, buffer);
        }
    }
    return buffer;
}

char* JmpArgumentReader (char* buffer, struct Label * label, FILE* out)
{
    for (int i = 0; i < Max_labels; i++)
    {
        if (label[i].number == *(int*)buffer)
        {
            fprintf (out, " LABEL_%d", i);
            buffer += sizeof (int);
            return buffer;
        }
    }
    ON_DEBUG (printf ("%d", *(int*)buffer);)
    printf("Syntax Error");
    exit (NotSuchCommand);
}

char* PopArgumentReader (char* buffer, FILE* out)
{
    ON_DEBUG (printf ("%d", *buffer);)
    ON_DEBUG (printf ("--[%d]--", *buffer);)

    if (*buffer != -1)
    {
        if (*buffer == REG)
        {
            buffer += sizeof (char);
            WhatToPrint (buffer, out);
            buffer += sizeof (char);
        }
        else
        {
            buffer += sizeof (char);
            buffer = MemWrt (out, buffer);
        }
    }

    return buffer;
}

struct Label * LabelRead (char* buffer, int* i_lable, const char* namein)
{
    struct Label * label = (struct Label *) calloc (Max_labels, sizeof (struct Label));

    ON_DEBUG (printf ("--%s--", buffer);)

    for (int i = 0; i < Sizecount (namein) - sizeof (struct WhatIs); i += sizeof (char))
    {
        ON_DEBUG ( printf ("*%d*   ", buffer[i]);)

        if (buffer[i] == CMD_PUSH)
        {
            if (buffer[i + 1] == INT_)
            {
                i += sizeof (int) + sizeof (char);
            }
            else
            {
                if (buffer[i + 1] == REG)
                {
                    i += 2 * sizeof (char);
                }
                else
                {
                    i += sizeof (char);
                    if (buffer[i + 1] == INT_)
                    {
                        i += sizeof (int) + sizeof (char);
                    }
                    else
                    {
                        if (buffer[i + 1] == REG)
                        {
                            i += 2 * sizeof (char);
                        }
                        else
                        {
                            i += 2 * sizeof (char) + sizeof (int);
                        }
                    }
                }
            }
            continue;
        }
        if (buffer[i] == CMD_POP)
        {
            i += sizeof (char);
            if (buffer[i] == REG)
            {
                i += sizeof (char);
            }
            else
            {
                i += sizeof (char);
                if (buffer[i] == INT_)
                {
                    i += sizeof (int);
                }
                else
                {
                    if (buffer[i] == REG)
                    {
                        i += sizeof (char);
                    }
                    else
                    {
                        i += sizeof (char) + sizeof (int);
                    }
                }
            }

            continue;
        }
        if ((buffer[i] >= CMD_JMP) && (buffer[i] <= CMD_CALL))
        {
            ON_DEBUG ( printf ("\ntuta   %d  ",*(int*)(&buffer[i + 1]));)
            for (int k = 0; k < *i_lable; k++)
            {
                if (label[k].number == *(int*)(&buffer[i + 1]))
                    continue;
            }
        
            label[*i_lable].address = &buffer[*(int*)(&buffer[i + 1])];
            label[*i_lable].number = *(int*)(&buffer[i + 1]);
            ON_DEBUG (printf ("^^^^%d   %d\n", label[*i_lable].number, *i_lable);)
            *i_lable += 1;
            i += sizeof (int);
        }
    }
    return label;
}

int Disas (const char* namein, const char* nameout)
{
    FILE *out = fopen(nameout, "w+");

    char* buffer = InfoWriting (out, namein);
    char* buffer_begin = buffer;

    int i_label = 0;
    struct Label * label = LabelRead (buffer, &i_label, namein);
    ON_DEBUG (for( int i =0; i < i_label; i++)
    {
        printf ("\n%x   %d\n", label[i].address, label[i].number);
    })

    while (true)
    {
        for (int i = 0; i < i_label; i++)
        {
            if (buffer == label[i].address)
            {
                fprintf (out, "LABEL_%d:\n", i);
                ON_DEBUG ( printf ("LABEL_%d: %d\n", i, *buffer);)
            }
        }

#define DEF_CMD(name, num, arguments, code, write, disas)           \
        case CMD_##name:                                            \
        {                                                           \
            fprintf (out, #name);                                   \
            ON_DEBUG ( printf ("\n-%d-$%s$", *buffer, #name);  )           \
            if (*buffer == CMD_END)                                 \
            {                                                       \
                free(buffer_begin);                                 \
                free (label);                                       \
                fclose (out);                                       \
                return 0;                                           \
            }                                                       \
            buffer += sizeof(char);                                 \
            disas                                                   \
            fprintf (out, "\n");                                    \
            break;                                                  \
        }

        switch (*buffer)
        {
            #include "MyLib/Commands.h"
            default:
            {
                printf("Syntax Error");
                exit (NotSuchCommand);
                break;
            }
        }

#undef DEF_CMD

    }
}