//
// Created by dunka on 11.10.2019.
//

#ifndef MIPT_DED_32_ENUM_H
#define MIPT_DED_32_ENUM_H

/*!
 * Enum for operations
 */
#define DEF_CMD(name, num, arguments, code, write, out)      \
        CMD_##name = num,

enum Asm {
    #include "Commands.h"
    THE_LONGEST_COMMAND = 4
};
#undef DEF_CMD

#endif //MIPT_DED_32_ENUM_H
