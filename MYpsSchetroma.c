#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
//#include "flag.h"

struct Flags                        // flag struct
{
    _Bool p;
    _Bool s;
    _Bool U;
    _Bool S;
    _Bool v;
    _Bool c;
};

void displayProc(const char *pid, struct Flags flags);

int main(int argc, char *argv[])
{
    struct Flags flags = {false, false, true, true, false, true};       //flag values

    char *path = NULL;
    int option_index;

    while ((option_index = getopt(argc, argv, "p:sUSvc")) != -1) {
        switch (option_index) {
        case 'p':               // change p flag to show specific pid
            path = optarg;
            flags.p = true; 
            break;
        case 's':                       // change s flag to display state information
            flags.s = true;         
            break;
        case 'U':                       // change U to not display user time
            flags.U = false; 
            break;
        case 'S':                       // change S to display the system time consumed
            flags.S = true; 
            break;
        case 'v':                       // change v to display amount of virtual memory currently used
            flags.v = true;     
            break;
        case 'c':                   // change c so the command line is not displayed
            flags.c = false; 
            break;
        case '?':
        fprintf(stderr, "Usage: %s [-p <pid>] [-s] [-U] [-S] [-v] [-c]",argv[0]);
        default:
            exit(1);
        }
    }

    if (!flags.p && !flags.s && !flags.U && !flags.S && !flags.c && !flags.v) {  //if there are no flags 

        char currentUID[32];                

        snprintf(currentUID, sizeof(currentUID), "%d", getuid());       // fetch UID

        DIR *procDir = opendir("/proc");        // open proc directory
        if (procDir) {

            struct dirent *entry;
            while ((entry = readdir(procDir)) != NULL) {    // while there are entries
                if (isdigit(entry->d_name[0])) {            
                    displayProc(entry->d_name, flags);    
                }
            }
            closedir(procDir);      //close proc directory
        } else {
            perror("procDir could not be opened.");    
        }
    }
    else if (flags.p) {             // if p is true run displayProcInfo
        displayProc(path, flags);
    }

    return 0;
}

// Function to display process information
void displayProc(const char *pid, struct Flags flags) {
    char procPath[256];

    snprintf(procPath, sizeof(procPath), "/proc/%s", pid);          // opens proc file system, uses PID 

    struct stat procStat;

    if (stat(procPath, &procStat) == 0) {      // if proc exists get info
    
        printf("PID: %s\n", pid);



        if (flags.s) {         // if s is present display state information about the process.
        
            char statusPath[271];

            snprintf(statusPath, sizeof(statusPath), "%s/status", procPath);    // construct path for status file 
            FILE *statusFile = fopen(statusPath, "r");       // open file for reading                      
            if (statusFile) {
                char line[269];

                while (fgets(line, sizeof(line), statusFile)) { // split into line by line
                
                    if (strncmp(line, "State:", 6) == 0) {   // if line starts with "State:" print line
                    
                        printf("%s", line);
                    }
                }
                fclose(statusFile);     // close statusFile 
            }
        }

        char statPath[269];
        snprintf(statPath, sizeof(statPath), "%s/stat", procPath);  // construct path for stat
        FILE *statFile = fopen(statPath, "r");      // open file for reading
        if (statFile) {

            char line[256];
            if (fgets(line, sizeof(line), statFile)) {     
                char *token = strtok(line, " ");        // tokenize spaces

                int count = 1;
                while (token) {
                    if (!flags.U && count == 14) {   // if U is false and count is 14
                        printf("User Time: %s\n", token);
                    }
                    else if (flags.S && count == 15) {     // if S is true and count is 15
                        printf("System Time: %s\n", token);
                    }
                    token = strtok(NULL, " ");
                    count++;
                }
                fclose(statFile);       // closes the stat file
            }
        }

        if (flags.v) {      // if flag v is true

            char statmPath[271];
            snprintf(statmPath, sizeof(statmPath), "%s/statm", procPath); //constructs file path to statm
            FILE *statmFile = fopen(statmPath, "r");
            if (statmFile) {
                char line[256];
                if (fgets(line, sizeof(line), statmFile)) {     

                    char *token = strtok(line, " ");   
                    if (token) {
                        printf("Virtual Memory: %s pages\n", token);    // print memory value from token
                    }
                }
                fclose(statmFile);         //closes statm file
            }
        }

        if (flags.c) {  //if c is present do not display cmdline

            char cmdlinePath[272];
            snprintf(cmdlinePath, sizeof(cmdlinePath), "%s/cmdline", procPath); //construct path to cmdline file
            FILE *cmdlineFile = fopen(cmdlinePath, "r");
            if (cmdlineFile) {
                char cmdLine[264];
                if (fgets(cmdLine, sizeof(cmdLine), cmdlineFile)) {
                    printf("Command Line: %s\n", cmdLine);      // print commandline value
                }
                fclose(cmdlineFile);        //close cmdline file
            }
        }

        printf("\n");
    }
}




