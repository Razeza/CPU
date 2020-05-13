#include "MyLib/MyLib.h"

int main ()
{
    system ("g++ X:\\Assembler.cpp -o assembler.exe");
    system ("g++ X:\\Disassembler.cpp -o disassembler.exe");
    system ("g++ X:\\CPU.cpp -o cpu.exe");

    system ("assembler.exe");
    system ("disassembler.exe");
    system ("cpu.exe");
}


