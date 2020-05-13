//
// Created by dunka on 27.09.2019.
//

#ifndef MIPT_DED_32_MYHASH_H
#define MIPT_DED_32_MYHASH_H



unsigned long int Hash ( void* beginning, int length)
{
    //printf("Length is: %d\n",length );
    unsigned long int hash = 0;
    char* place = (char*) beginning;
    for ( int i = 0; i < length; i++ )
    {
        //printf("In function   0    : %lu        place-%x", hash, place);
        hash += ~(unsigned int)(*place)^345<<3;
        //printf("                In function        1     : %lu\n", hash);
        place++;
        //printf("                In function        1     : %lu\n", hash);
    }
    //printf("Returned hash: %lu\n", hash);
    return hash;
}

#endif //MIPT_DED_32_MYHASH_H
