//
// Created by dunka on 30.09.2019.
//

#ifndef MIPT_DED_32_OPEARTIONS_H
#define MIPT_DED_32_OPEARTIONS_H

#include "MyStack.h"
#include "math.h"
#include "../TX/TXLib.h"
#include <stdlib.h>

double regist[4] = {0, 0, 0, 0};

double memory[4096] = {};

const int accuracy = 100; // Не забудь поменять точность в OUT

/*!
 * Pushes element to stack
 * @param[in, out] this_ Stack
 * @param[in] value element to push
 */
void Push (Stack_t * this_, int value );

/*!
 * Takes element from top of the stack
 * @param[in, out] this_ Stack
 * @return element from top
 */
double Pop ( Stack_t * this_ );

/*!
 * Sum two top elements from stack
 * @param[in, out] this_ Stack
 */
void Add ( Stack_t * this_ );

/*!
 * Subtraction from the top element of stack the second element
 * @param[in, out] this_ Stack
 */
void Sub ( Stack_t * this_ );

/*!
 * Multiply two top elements from stack
 * @param[in, out] this_ Stack
 */
void Mul ( Stack_t * this_ );

/*!
 * Division from the top element of stack the second element
 * @param[in, out] this_ Stack
 */
void Div ( Stack_t * this_ );

/*!
 * End operations
 * @param[in, out] this_ Stack
 */
void End ( Stack_t * this_ );

void Sqrt (Stack_t * this_);

void Meow ();

void Out (Stack_t * this_);

void In (Stack_t * this_);


void End ( Stack_t * this_ )
{
    StackDestruct ( this_ );
    exit (5051);
}



void Push ( Stack_t * this_, int value )
{
    StackPush ( this_, value * accuracy );
}

double Pop ( Stack_t * this_)
{
    int x = StackPop (this_);
    return (double(x) / accuracy);
}

void Add ( Stack_t * this_ )
{
    StackPush ( this_, StackPop ( this_ ) + StackPop ( this_ ) );
}

void Sub ( Stack_t * this_ )
{
    int x1 = StackPop ( this_ );
    int x2 = StackPop ( this_ );
    StackPush ( this_, x2 - x1 );
}

void Mul ( Stack_t * this_ )
{
    StackPush ( this_, StackPop ( this_ ) * StackPop ( this_ ) / accuracy );
}

void Div ( Stack_t * this_ )
{
    int x1 = StackPop ( this_ );
    int x2 = StackPop ( this_ );
    int x = 0;
    if ( x1 == 0 )
    {
        printf("You can't div on Zero");
        x = 0;
    }
    else
    {
        x = x2 * accuracy / x1 ;
    }
    StackPush ( this_, x );
}

void Sqrt (Stack_t * this_)
{
    StackPush (this_, sqrt(StackPop(this_)*accuracy));
}

void Out (Stack_t * this_)
{
    int i = accuracy;
    int k = 0;
    while (i % 10 == 0)
    {
        k++;
        i /= 10;
    }
    printf ("\n%.2lf\n", Pop (this_));
}
#define COMPARE(sig)    if (strcmp (sign, #sig) == 0)                       \
                        {                                                   \
                        double x1 = StackPop (this_);                       \
                        double x2 = StackPop (this_);                       \
                        return x2 sig x1;                                   \
                        }

bool IsSign (const char* sign, Stack_t * this_)
{
    COMPARE (>)
    COMPARE (>=)
    COMPARE (<)
    COMPARE (<=)
    COMPARE (==)
    COMPARE (!=)
    printf("Syntax Error");
    exit (NotSuchCommand);
}

#undef COMPARE

void JumpSign (char* machineCode, int* i, const char sign[2], Stack_t * this_)
{
    if (IsSign (sign, this_))
    {
        ON_DEBUG (printf("\n%d ", *(int*)(&machineCode[*i]));)
        *i = *(int*)(&machineCode[*i]);
        ON_DEBUG (printf ("%d\n", machineCode[*i]);)
    }
    else
    {
        *i += sizeof (int);
    }
}

void In (Stack_t * this_)
{
    int value = 0;
    printf ("\nPrint a value to PUSH :      ");
    scanf ("%d", &value);
    StackPush (this_, value * accuracy);
}

void SetColor (int value)
{
    if (value == 0)     txSetFillColor (TX_BLACK);
    if (value == 1)     txSetFillColor (TX_WHITE);
    if (value == 2)     txSetFillColor (TX_BLUE);
    if (value == 3)     txSetFillColor (TX_GREEN);
    if (value == 4)     txSetFillColor (TX_ORANGE);
    if (value == 5)     txSetFillColor (TX_PINK);
}

void VideoMemory ()
{
    int x = 0;
    int y = 0;
    txCreateWindow (512, 512);
    txSetFillColor (TX_BLACK);
    txSleep (5);
    txClear ();
    for ( int i = 3072; i <= 4096; i++)
    {
        if (x == 512) {y += 16; x = 0;}
        SetColor ((int)memory[i]);
        txRectangle (x, y, x + 16, y + 16);
        x += 16;
        txSleep (0.05);
    }
}



void Meow ()
{
    printf ("________________$$____________$$\n"
           "_______________$___$________$___$\n"
           "_______________$_____$$$$$$_____$\n"
           "_______________$____sss_ __sss____$\n"
           "_______________$____ii_____ii_____$\n"
           "______________$_______$$$________$\n"
           "__$$$$$$$$_____$_______$________$\n"
           "$$______ __$_______$$_________$$\n"
           "_$_________$_____$___$$$$$$___$\n"
           "____$______$____$__$________$__$\n"
           "____$_____$____$__$__________$__$\n"
           "_ __$____$___$$$$__$__________$__$$$$\n"
           "__$___$____$____$__$________$___$___$\n"
           "__$__$_____$____$__$________$__$____$\n"
           "_$___$______$___ _$__$____$_$__$____$\n"
           "___$__$______$____$___$_$_____$___$\n"
           "____$___$$$$$_$___$___$_$____$___$\n"
           "_______$$$$$_$____$____$_____$____$\n"
           "_ ____________$$$_$_____$______$_$$$\n"
           "__________________$$$$___$$$$$\n");
}

#endif //MIPT_DED_32_OPEARTIONS_H
