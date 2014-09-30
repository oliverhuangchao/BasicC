/* geninput.c
 * MP3
 * Harlan Russell
 * ECE 223, Fall 2014
 *
 * Compile with (link the math library)
 *     gcc -g -Wall geninput.c -o geninput -lm
 *
 * Purpose: Generate an input file for MP3 
 * Assumptions: Input file is for testing sort.  Creates
 *              an unsorted list, uses pushback to insert items, and
 *              calls sort to sort the list
 *
 * Command line arguments:
 *    1st -- number of records to create
 *    2nd -- type of list to create
 *           1: random addresses [0, 3/4 number records)
 *           2: assending and sequential
 *           3: descending and sequential
 *
 * Pipe the output of this program into lab3. For example
 *     ./geninput 10000 1 | ./lab3 1
 *
 * See also mp3test.sh 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int records = 0, list_type = -1;
    int addr_range;
    int soc_id;

    if (argc != 3) {
        printf("Usage: ./geninput listsize listype\n");
        printf("\tlistsize: number of records to create\n");
        printf("\tlisttype: {1, 2, 3} for random, ascending or descending\n");
        exit(1);
    }
    records = atoi(argv[1]);
    if (records < 2) {
        printf("genniput has invalid number records: %d\n", records);
        exit(2);
    }
    list_type = atoi(argv[2]);
    addr_range = records * 0.75;
    srand48(22);

    int i;
    if (list_type == 1) {
        // random addresses, 
        for (i = 0; i < records; i++) {
            soc_id = (int) (addr_range * drand48()) + 1;
            printf("pushback\n%d\n", soc_id);
        }
        printf("sort\n");
        printf("quit\n");
    }
    else if (list_type == 2) {
        // ascending addresses
        for (i = 0; i < records; i++) {
            printf("pushback\n%d\n", i+1);
        }
        printf("sort\n");
        printf("quit\n");
    }
    else if (list_type == 3) {
        // descending addresses
        for (i = 0; i < records; i++) {
            printf("pushback\n%d\n", records - i);
        }
        printf("sort\n");
        printf("quit\n");
    }
    else {
        printf("geninput has invalid list type: %d\n", list_type);
        exit(3);
    }
    exit(0);
}

