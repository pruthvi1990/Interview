/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    unsigned int x = 0xA0102346;
    
    char* array[4];
    int offset[4];
    
    // allocate memory for each byte
    for (size_t i=0; i<4; i++)
    {
        array[i] = (char *)malloc(4*sizeof(char));
    }
    
    for (size_t i=0; i<4 ; i++)
    {
        char* byte_ptr = (char *)(&x) + i;
        
        uint8_t byte = *byte_ptr;
        offset[i] = sprintf(array[i], "%d", byte);
    }
    
    // concat all the bytes now;
    
    char *ipv4 = (char*)malloc(4*4*sizeof(char));
    
    int index = 0;
    for(size_t i=0; i<4; i++)
    {
        for (size_t j=0; j<offset[i]; j++)
        {
            *(ipv4 + index) = array[i][j];
            index++;
        }
        if (i == 0 || i == 1 || i== 2)
        {
            *(ipv4 + index) = '.';
            index++;
        }
    }
    *(ipv4 + index) = '\0';
    printf("IPV4 address: %s", ipv4);
    return 0;
}

