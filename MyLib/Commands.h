
#define _ ,
DEF_CMD (END, 0, 1, End (this_); , ;, ;)

#define CODE(what)   { what }
#define SYNTAX(what) { what }
#define DISASM(what) { what }

DEF_CMD (PUSH, 1, 3,
        CODE
            (if (machineCode[i] == INT_)
                 {
                     Push (this_ _ *(int*)(&machineCode[i + 1]));
                     i += sizeof(int);
                 }
                 else
                 {
                     if (machineCode[i] == REG)
                     {
                         Push (this_ _ regist[machineCode[i + 1]]);
                         i += sizeof (char);
                     }
                     else
                     {
                         i += sizeof (char);
                         if (machineCode[i] == INT_)
                         {
                             Push (this_ _ memory[*(int*)(&machineCode[i + 1])]);
                             i += sizeof(int);
                         }
                         else
                         {
                             if (machineCode[i] == REG)
                             {
                                 Push (this_ _ memory[(int) regist[machineCode[i + 1]]]);
                                 i += sizeof (char);
                             }
                             if (machineCode[i] == INT_REG)
                             {
                                 Push (this_ _ memory[(*(int*)(&machineCode[i + 1]) + (int) regist[machineCode[i + 1 + sizeof (int)]])]);
                                 i += sizeof (char) + sizeof (int);
                             }
                         }
                     }
                 }
                 i += sizeof (char);
              ),

        SYNTAX
              (
              PushRead (cur _ outmassive _ &sizeofarray);
              ),

        DISASM
               (
               buffer = PushArgumentReader (buffer, out);
               )
        )

DEF_CMD (POP, 2, 2,
        CODE
            (
            if (machineCode[i] == -1)
            {
                double x = Pop (this_);
            }
            else
            {
                if (machineCode[i] == REG)
                {
                    i += sizeof (char);
                    regist[machineCode[i]] = Pop (this_);
                }
                else
                {
                    i += sizeof (char);
                    if (machineCode[i] == REG)
                    {
                        memory[(int)regist[machineCode[i + 1]]] = Pop (this_);
                        i += sizeof (char);
                    }
                    else
                    {
                        if (machineCode[i] == INT_)
                        {
                            memory[*(int*)(&machineCode[i + 1])] = Pop (this_);
                            i += sizeof (int);
                        }
                        if (machineCode[i] == INT_REG)
                        {
                            memory[*(int*)(&machineCode[i + 1]) + (int)regist[machineCode[i + 1 + sizeof(int)]]] = Pop (this_);
                            i += sizeof (int) + sizeof (char);
                        }
                    }
                }
            }
            i += sizeof (char);
            ),
        SYNTAX
              (
               PopRead (cur _ outmassive _ &sizeofarray);
              ),
        DISASM (
                buffer = PopArgumentReader (buffer, out);
               )
        )

DEF_CMD (ADD, 3, 1, Add (this_); , ;, ;)

DEF_CMD (SUB, 4, 1, Sub (this_); , ;, ;)

DEF_CMD (MUL, 5, 1, Mul (this_); , ;, ;)

DEF_CMD (DIV, 6, 1, Div (this_); , ;, ;)

DEF_CMD (SQRT, 7, 1, Sqrt (this_); , ;, ;)

DEF_CMD (IN, 8, 1, In (this_); , ;, ;)

DEF_CMD (OUT, 9, 1, Out (this_); , ;, ;)

DEF_CMD (JMP, 10, 2,
        CODE (
                i = *(int*)(&machineCode[i]);
             ),
        SYNTAX (
                JmpRead (label _ cur _ outmassive _ &sizeofarray);
               ),
        DISASM (
                buffer = JmpArgumentReader (buffer, label, out);
                )
        )

#define DEF_CMD_JUMP(name, number, sign)                                                    \
DEF_CMD (name, number, 2,                                                                   \
        CODE (                                                                              \
                JumpSign(machineCode, &i, #sign, this_);                                    \
             ),                                                                             \
        SYNTAX (                                                                            \
                JmpRead (label _ cur _ outmassive _ &sizeofarray);                          \
               ),                                                                           \
        DISASM (                                                                            \
                buffer = JmpArgumentReader (buffer,label, out);                             \
               )                                                                            \
        )

DEF_CMD_JUMP (JA, 11, >)
DEF_CMD_JUMP (JAE, 12, >=)
DEF_CMD_JUMP (JB, 13, <)
DEF_CMD_JUMP (JBE, 14, <=)
DEF_CMD_JUMP (JE, 15, ==)
DEF_CMD_JUMP (JNE, 16, !=)

#undef DEF_CMD_JUMP

DEF_CMD (CALL, 17, 3,
        CODE
            (
             i += sizeof (int);
             Push (&function, *(int*)(&machineCode[i]));
             i -= sizeof (int);
             i = *(int*)(&machineCode[i]);
            ),
        SYNTAX
            (
             JmpRead (label _ cur _ outmassive _ &sizeofarray);
             *(int*)(&outmassive[sizeofarray]) = sizeofarray + sizeof (int);
             sizeofarray += sizeof (int);
            ),
        DISASM
            (
            buffer = JmpArgumentReader (buffer,label, out);
            buffer += sizeof (int);
            )
        )
DEF_CMD (RET, 18, 1,
        CODE
            (
                i = (int)Pop(&function);
            ),
        SYNTAX ( ),
        DISASM ( )
        )

DEF_CMD (GAV, 19, 1, printf("GAV"); , ;, ;)

DEF_CMD (PIC, 21, 1,
        CODE
            (
                    VideoMemory ();
            ),
        SYNTAX ( ),
        DISASM ( ))


DEF_CMD (MEOW, 20, 1, Meow (); , ;, ;)

/*DEF_CMD (REM, 22, 1,
        CODE
            (
                    int x1 = Pop (&this_);
                    int x2 = Pop (&this_);
                if (x1 == 0) Push (&this_,       0);
                else         Push (&this_, x2 % x1);
            ),
        SYNTAX (),
        DISASM ()
        )*/

#undef _

