#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
 * This is a circular buffer that allows enqueue or dequeue arbitrary
 * amount of bytes. The buffer size is limited to BUF_SIZE.
 */

static char *GetErrorString(int x);

#define BUF_SIZE    4096

typedef struct {
    int write_index;
    int read_index;
    char *buf;

    // have  a ptr, whuch points to the begining of the struct
    char* buf_start_addr;
    int size;
} circular_buf_t;

// use designated initilizer for struct inititlization
circular_buf_t buf = {.write_index = 0, .read_index = 0, .buf = NULL, .size = 0};

/*
 * Enqueue (size) bytes from (client_buf) to the local buf
 * memory of (client_buf) is allocated by the caller
 */

// you need to define the src as const, we dont want the function to corrupt the src buffer
int enqueue(const char *client_buf, int size)
{
    if (size > BUF_SIZE) {
        printf("%s", GetErrorString(3));
        return 3;
    }
    
    int part1 = buf.size - buf.write_index;

    // u need to swap the src and destinaition. our destination is a local buffer 
    memcpy(buf.buf+ buf.write_index, client_buf, part1);
    
    if (part1 != size) {
        int part2 = size - part1;
	memcpy(buf.buf, client_buf+part1, part2);
    }
    
    return 0;
}

/*
 * Dequeue (size) bytes from the local buf to (client_buf),
 * (client_buf) is allocated by the caller. It is okay to assume
 * (client_buf) is big enough to hold all the (size) bytes
 */
int dequeue(char *client_buf, int size)
{
    if (size < BUF_SIZE) {
        printf("%s", GetErrorString(2));
        return 2;
    }
    
    int copy_size = buf.write_index - buf.read_index + 1;
    memcpy(client_buf, buf.buf + buf.write_index, copy_size);
    
    return 0;
}

static char *GetErrorString(int x)
{
    static char errorString[21];

    // we need 21 becz, strcpy requires length(string) + '\0`
    //char *errorString = malloc (sizeof (char) * 20); 
    switch ( x )
    {
        case 0:
            strcpy(errorString, "Success -- No error.");
            break;
        case 2:
            strcpy(errorString, "Overflow!");
            break;
    }
    
    return errorString;
}


int main(int argc,char* argv[])
{
    // initialize buffer
    // malloc returns void * ptr , you need to type cast to required data type
    buf.buf = (char *)malloc(BUF_SIZE);
    buf.size = BUF_SIZE;
    buf.buf_start_addr = buf.buf;
    
    

    // Perform enqueue() and dequeue();
    
    // All completed, return
    // release the memory on heap
    free (buf.buf);
    return 0;
}

