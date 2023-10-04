/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define max_path_length 256


//to read linux library need to use readdir, use man 3 readdir
// learning the proc file system, use man 5 proc\
// getopt command


int main(int argc, char **argv)   {


    DIR *directory;     // initialize directory pointer
            
    struct dirent *entry;           // dir entries pointer 
    char path[max_path_length];     // initialize variable to store file path
    
    directory = opendir("/proc");         //opens the proc directory

    if (directory == NULL) {
        perror("error opeening proc");
        exit(1);
    }
    
    while ((entry = readdir(directory)) != NULL) {    // iterating through proc entries
    
        if (entry->d_type == DT_DIR && strspn(entry->d_name,"0123456789") == strlen(entry->d_name)) {
            // if the entry is a directory with digits, construct the path to the process status file
            
            snprintf(path, sizeof(path), "/proc/%s/status",entry->d_name);
            
            //open the status file
            FILE *status_file = fopen(path,"r");
            if (status_file != NULL) {
                
                char line[256];
                char name[256];
               // int pid;
                
                while (fgets(line, sizeof(line), status_file)) {
                    
                    if (sscanf(line, "Name:\t%s", name) == 1) {
                        printf("PID: %s\n", entry->d_name);
                        printf("Name: %s\n", name);
                    }
                }
                fclose(status_file);
            }
        }
    }
    closedir(directory);
    
    return 0;
}

