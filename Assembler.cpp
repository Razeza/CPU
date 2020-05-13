#include "MyLib/MyLib.h"
#include "MyLib/LibOfAsm.h"
#include "MyLib/enum.h"
#include <string.h>
#include "ctype.h"

#define DEBUG
#define WHERE "X:\\"

const char nameout[] = "X:\\binaryCode.bin";
// "C:\\Users\\dunka\\CLionProjects\\mipt_ded_32\\"

struct Label {
    char name[Max_label_size];
    int numberOfelement;
};

/*!
 * Input Text
 * @param nameout Name of output file
 * @return Text
 */
struct Text * FileInput (const char* nameout);

/*!
 * If necessary to ass)))
 */
void LongLongTimeAgo (const char* namein, const char* nameout);

/*!
 * Writes info of user to machine code
 * @param[in] out filestream to output
 */
void InfoWriting (FILE* out);

/*!
 * Read JUMP arguments
 * @param label - Structure with labels
 * @param cur - current pointer in the line
 * @param outmassive - massive with outpuy code
 * @param sizeofarray
 */
void JmpRead (struct Label * label, char* cur, char* outmassive, int* sizeofarray);

/*!
 * Read push arguments
 * @param cur - current pointer in the line
 * @param outmassive - massive with outpuy code
 * @param sizeofarray
 */
void PushRead (char* cur, char* outmassive, int* sizeofarray);

void MemArgRead (char* outmassive, int* sizeofarray, char* cur);

/*!
 * Return the necessary token
 * @param cur - current pointer in the line
 * @return the necessary token
 */
int Push_Symb (char* cur);

/*!
 * Read push arguments
 * @param cur - current pointer in the line
 * @param outmassive - massive with outpuy code
 * @param sizeofarray
 */
void PopRead (char* cur, char* outmassive, int* sizeofarray);

/*!
 *
 * @param cur - current pointer in the line
 * @param label - Structure with labels
 * @param i_label - number used of labels
 * @param check - The first word on the line
 * @param sizeofarray
 * @return 0 if lable
 * @return 1 else
 */
int labels (char* cur, struct Label * label, int *i_label, char* check, int sizeofarray);

/*!
 * Makes a machine code
 * @param Code - Input text
 * @param outmassive - massive with outpuy code
 * @param label - Structure with labels
 * @return sizeofarray
 */
int Assambler (struct Text * Code, char* outmassive, struct Label * label);

/*!
 * Call Assembler and outputcode
 * @param Code - Input text
 * @param nameout - name of file to output
 * @return 0 - everythig is Ok
 */
int AssamblerCall (struct Text * Code, const char* nameout);


int main ()
{


    struct Text * Code = FileInput (nameout);

    AssamblerCall (Code, nameout);

    return 0;
}


void Dump (char* outmassive, int sizeofarray)
{
    for (int i = 0; i <= sizeofarray; i++)
    {
        printf ("\noutmassive[%d]   =   %d   size :=   %d     ", i, outmassive[i], sizeofarray);
    }
    printf ("\n\n\n");
}

struct Text * FileInput (const char* nameout)
{
    char namein[FILENAME_MAX] = {};
    printf ("\nWrite name of file to input or push ENTER to use basic file\n");
    scanf("%[^(\n)]", namein);

    struct Text * Code = nullptr;

    if (strcmp(namein, "\0") == 0)
    {
        memcpy (namein, "C:\\Users\\dunka\\CLionProjects\\mipt_ded_32\\factorial.asm", FILENAME_MAX);
    }

    LongLongTimeAgo ( namein, nameout);
    Code = Input (namein);

    return Code;
}

void LongLongTimeAgo (const char* namein, const char* nameout)
{
    ASSERT (namein)
    ASSERT (nameout)

    struct stat in = {};
    stat (namein , &in);

    struct stat out = {};
    stat (nameout , &out);


    /*if ( in.st_mtime >= out.st_mtime )
    {
        exit(FileReady);
    }*/
}


void InfoWriting (FILE * out)
{
    ASSERT (out)
    struct WhatIs In = {};
    In.version = 89;

    fwrite(&In, sizeof (WhatIs), 1, out);
}

int Push_Symb (char* cur)
{
    char str[Max_Sign] = {};
    int how = 0;
    ON_DEBUG (printf ("%s", cur);)
    sscanf (cur, "%s%n", str, &how);
    ON_DEBUG (printf ("++%s++", str);)
    cur += how;

    if (str[0] == 'a') return ax;
    if (str[0] == 'b') return bx;
    if (str[0] == 'c') return cx;
    if (str[0] == 'd') return dx;

    else
        {
            printf("Syntax Error");
            exit (NotSuchCommand);
        }
}

void JmpRead (struct Label * label, char* cur, char* outmassive, int* sizeofarray)
{
    char labe[Max_String] = {};
    sscanf (cur, "%s", labe);

    for (int k = 0; k < Max_labels; k++)
    {
        if (strcmp(label[k].name, labe) == 0)
        {
            *(int*) (&outmassive[*sizeofarray]) = label[k].numberOfelement;

            ON_DEBUG (printf ("////////----%d----", outmassive[*sizeofarray]);)

            break;
        }
    }
    *sizeofarray += sizeof (int);
}

void PopRead (char* cur, char* outmassive, int* sizeofarray)
{
    int str[Max_String] = {};
    int skip = 0;
    if (sscanf (cur, "%d", str) == 1)
    {
        outmassive[*sizeofarray] = -1;
        *sizeofarray += sizeof (char);
    }
    else
    {
        if (sscanf (cur, "%*[ ]%[a-z]", str) == 1)
        {
            outmassive[*sizeofarray] = REG;
            *sizeofarray += sizeof (char);

            outmassive[*sizeofarray] = (char) Push_Symb (cur);
            *sizeofarray += sizeof (char);
        }
        else
        {
            MemArgRead (outmassive, sizeofarray, cur);
        }
    }
}

void MemArgRead (char* outmassive, int* sizeofarray, char* cur)
{
    int skip = 0;
    char str[Max_String] = "";
    int value = 0;
    char* reg = nullptr;
    char skip_str[Max_String] = {};

    outmassive[*sizeofarray] = MEM;
    *sizeofarray += sizeof (char);

    sscanf (cur,"%[^([)]%n", str, &skip);
    cur += skip + 1;

    ON_DEBUG (printf ("   %s", cur);)

    if (sscanf (cur, "%d%n", &value, &skip) == 1)
    {
        cur += skip;

        sscanf (cur, "%[^(+ || ])]%n", &skip_str, &skip);
        cur += skip + 1;

        if (sscanf (cur, "%*[(+)||( )]%[(a-z)]", str) == 1)
        {
            ON_DEBUG (printf ("\nmemory int + reg\n");)
            ON_DEBUG (printf (" %d", INT_REG);)

            outmassive[*sizeofarray] = INT_REG;
            *sizeofarray += sizeof (char);

            ON_DEBUG (printf (" %d", value);)

            *(int*) (&outmassive[*sizeofarray]) = value;
            *sizeofarray += sizeof (int);

            outmassive[*sizeofarray] = (char) Push_Symb (cur);
            *sizeofarray += sizeof (char);

            ON_DEBUG (printf (" %d", (char) Push_Symb (cur));)
        }
        else
        {
            ON_DEBUG (printf ("\nmemory int\n");)
            outmassive[*sizeofarray] = INT_;
            *sizeofarray += sizeof (char);

            *(int*) (&outmassive[*sizeofarray]) = value;
            *sizeofarray += sizeof (int);
        }
    }
    else
    {
        reg = cur;
        sscanf (cur, "%s%n", str, &skip);
        cur += skip;
        if (sscanf (cur, "%*[( ) || (+)]%d", &value) == 1)
        {
            ON_DEBUG (printf ("\nmemory int + reg\n");)
            outmassive[*sizeofarray] = INT_REG;
            *sizeofarray += sizeof (char);

            *(int*) (&outmassive[*sizeofarray]) = value;
            *sizeofarray += sizeof (int);

            outmassive[*sizeofarray] = (char) Push_Symb (reg);
            *sizeofarray += sizeof (char);
        }
        else
        {
            ON_DEBUG (printf ("\nmemory reg\n");)

            outmassive[*sizeofarray] = REG;
            *sizeofarray += sizeof (char);
            outmassive[*sizeofarray] = Push_Symb (reg);
            *sizeofarray += sizeof (char);

        }
    }
}

void PushRead (char* cur, char* outmassive, int* sizeofarray)
{
    int value = 0;
    char str[Max_String] = "";
    int skip = 0;
    if (sscanf (cur,"%d", &value) == 1)
    {
        ON_DEBUG (printf ("\nint push\n");)
        outmassive[*sizeofarray] = INT_;
        *(int*)(&outmassive[*sizeofarray + 1]) = value;

        ON_DEBUG (printf ("%d\n", *(int*)(&outmassive[*sizeofarray + 1]));)

        *sizeofarray += sizeof (int) + sizeof (char);
    }
    else
    {
        if (sscanf (cur,"%*[ ]%[[]", str) == 0)
        {
            ON_DEBUG (printf ("\n size - %d\n", *sizeofarray);)
            ON_DEBUG (printf ("\n%s\n", cur);)

            ON_DEBUG (printf ("\nregist push\n");)
            outmassive[*sizeofarray] = REG;
            *sizeofarray += sizeof (char);

            outmassive[*sizeofarray] = (char) Push_Symb (cur);
            *sizeofarray += sizeof (char);

        }
        else
        {
            ON_DEBUG (printf ("\nmemory push\n");)
            ON_DEBUG (printf ("%s", cur);)
            MemArgRead (outmassive, sizeofarray, cur);
        }
    }

    //*sizeofarray += sizeof (char);
}

int labels (char* cur, struct Label * label, int *i_label, char* check, int sizeofarray)
{
    char jump[Max_String] = {};
    sscanf (cur, "%s", jump);

    if (jump[0] == ':')
    {
        for (int i =0; i < *i_label; i++)
        {
            if (strcmp (label[i].name, check) == 0)
                return 1;
        }
        memcpy (label[*i_label].name, check, Max_String);
        ON_DEBUG ( ("!!!!!!!!!!!!!!!%d", *i_label);)
        label[*i_label].numberOfelement = sizeofarray;
        *i_label += 1;
        ON_DEBUG ( ("!!!!!!!!!!!!!%d\n", *i_label);)
        ON_DEBUG (printf ("#############%d#########%d", label[*i_label - 1].name, label[*i_label - 1].numberOfelement);)

        return 0;
    }
    return 1;
}



int Assambler (struct Text * Code, char* outmassive, struct Label * label)
{
    char check[Max_String] = "";
    int Line = 0;
    int sizeofarray = 0;
    int i_label = 0;

    while (true)
    {
        ///ASSERT(((check[i] >= 'A') && (check[i] <= 'Z')) != 0) // For the memory of The Posvyat. Please do NOT change to ASSERT (isupper (check[i]));


        int how = 0;

        char* cur = Code[Line].begin;
        ASSERT (cur)
        Line++;


        sscanf (cur, "%[A-Z||a-z||0-9]%n", check, &how);
        ON_DEBUG (printf ("%s", check);)
        cur += how;

        if (labels (cur, label, &i_label, check, sizeofarray) == 0)
        {
            continue;
        }

        ON_DEBUG (printf("\n  *-%s-*  \n", check);)

        int command = -1;

        ON_DEBUG (printf("  -%s-  ", check);)

        #define DEF_CMD(name, num, arguments, code, write, out)         \
        if (strcmp(StringUpper(check, Max_String), #name) == 0)         \
        {                                                               \
            command = CMD_##name;                                       \
            outmassive[sizeofarray] = command;                          \
            ON_DEBUG (printf ("$%d$", outmassive[sizeofarray]);)        \
            if (command == CMD_END)                                     \
            {                                                           \
                return sizeofarray;                                     \
            }                                                           \
            sizeofarray += sizeof (char);                               \
            write                                                       \
            continue;                                                   \
        }

#include "MyLib/Commands.h"

        if (command == -1)
        {
    printf ("---%s---", check);
            printf("Syntax Error");
            exit (NotSuchCommand);
        }

#undef DEF_CMD


    }
}

int AssamblerCall (struct Text * Code, const char* nameout)
{
    char* outmassive = (char*) calloc (size, sizeof(char));

    struct Label * label = (struct Label *) calloc (Max_labels, sizeof (struct Label));

    FILE * out = fopen (nameout, "wb");

    InfoWriting (out);
    Assambler (Code, outmassive, label);
    int sizeofarray = Assambler (Code, outmassive, label);


    ON_DEBUG (for (int i = 0; i < 20; i++)
    {
        printf ("\n%s   %d\n", label[i].name, label[i].numberOfelement);
    })

    fwrite (outmassive, sizeof(char), sizeofarray, out);

    free (label);
    free (outmassive);
    free (Code);
    fclose (out);
    return 0;
}