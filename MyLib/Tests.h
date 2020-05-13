//
// Created by dunka on 27.09.2019.
//

#ifndef MIPT_DED_32_TESTS_H
#define MIPT_DED_32_TESTS_H

#include "stdio.h"
#define __TEST_BOOL__( Function, Result ) if ( Function == Result )          \
                             {                                               \
                             printf ( "Test %d is true\n", counter );        \
                             }                                               \
                             else                                            \
                             {                                               \
                             printf ( "Test %d is false\n", counter);        \
                             }                                               \
                             counter++;

#endif //MIPT_DED_32_TESTS_H
