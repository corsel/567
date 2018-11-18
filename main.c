// Cem Orsel, 2018

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char* FILENAME = "./the1.inp";
const unsigned int LINE_CHAR_LIMIT = 20;

typedef struct triplet_linkedlist_t {
    int first;
    int second;
    int third;
    struct triplet_linkedlist_t* next;
} triplet_linkedlist_t;

triplet_linkedlist_t* g_head = NULL;
triplet_linkedlist_t* g_tail = NULL;
int g_algo = -1;

void read_input(const char* filename)
{
    FILE* fd = fopen(filename, "r");
    char line[LINE_CHAR_LIMIT];
    memset(line, 0, LINE_CHAR_LIMIT);
    char curr_char = '\0';
    
    // Get algo type
    do {
        curr_char = getc(fd);
        strncat(line, &curr_char, 1);
    } while (curr_char != '\n');
    g_algo = atoi(line);
    printf("algo: %d\n", g_algo);
  
    // Get number of entries
    memset(line, 0, LINE_CHAR_LIMIT);
    do {
        curr_char = getc(fd);
        strncat(line, &curr_char, 1);
    } while (curr_char != '\n');
    int num_lines = atoi(line);
    printf("num_lines: %d\n", num_lines);
    
    // Fill the linked-list of building triplets
    unsigned int i = 0;
    for (; i < num_lines; i++) {
        memset(line, 0, LINE_CHAR_LIMIT);
        do {
            curr_char = getc(fd);
            strncat(line, &curr_char, 1);
        } while (curr_char != '\n');
        int a, b, c;
        sscanf(line, "%d %d %d", &a, &b, &c);
        printf("number 1: %d, 2: %d, 3: %d\n", a, b, c);
    }
}

int main(int argc, char* argv[])
{
    read_input(FILENAME);
    return 0;
}
