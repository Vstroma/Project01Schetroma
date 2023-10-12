#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    FILE *proc = fopen("/proc/cpuinfo", "r");		// open proc filesystem for reading

    if (proc == NULL) {
        perror("Error opening /proc/cpuinfo");		//if proc does not open
        exit(1);
    }

    char *line = NULL;				// pointer to store text from each line 
    size_t len = 0;					// length of the line 
    ssize_t read;				// characters read
    int pro_count = 0;

    while ((read = getline(&line, &len, proc)) != -1) {			// while there are lines to read
        if (strstr(line, "cache size") != NULL) {				// if “cache size” is present
            printf("Processor %d with a %s", pro_count, line);
            pro_count++;
        }
    }

    fclose(proc);
    if (line) {
        free(line);				// frees memory 
    }


    return 0;
}






