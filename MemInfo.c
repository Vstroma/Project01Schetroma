#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    FILE *file = fopen("/proc/meminfo", "r");		// open directory for reading information

    if (file == NULL) {					// throw error if NULL
        perror("Error opening /proc/meminfo");
        return 1;
    }

    char *line = NULL;			// pointer for reading lines
    size_t len = 0;
    ssize_t read;						// variable to count bytes


    while ((read = getline(&line, &len, file)) != -1) {			// while there are more lines to read

        if (strstr(line, "MemFree:") != NULL) {			// if string == “MemFree:”

            printf("Free Memory: %s", line + 9); 		// prints free memory value without the prefix

        }
        if (strstr(line, "Buffers:") != NULL) {				// if string == “Buffers:”

            printf("Buffers: %s", line + 8);			// prints buffer value without the prefix

        }
    }

    free(line);		// frees memory
    fclose(file);		// closes file

    return 0;
}

