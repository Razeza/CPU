//
// Created by dunka on 28.09.2019.
//

#ifndef MIPT_DED_32_LIBOFASM_H
#define MIPT_DED_32_LIBOFASM_H



const int size = 20000;
const int Max_String = 20;
const int Max_Sign = 2;
const int Max_label_size = 32;
const int Max_labels = 1024;

/*!
 * Indeficator of assambler machine
 */
struct WhatIs {
    const char name[4] = "DAN";
    int version;
};

enum Error {NotSuchCommand = 5051, FileReady = 228, BadReallocation = 4551};

enum regist {ax = 0, bx = 1, cx = 2, dx = 3};

enum push {INT_ = 0, REG = 1, INT_REG = 2, MEM = 3};

#endif //MIPT_DED_32_LIBOFASM_H
