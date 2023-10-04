#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>




main(int argc, char **argv) {
    int option_index = 0;

    while ((option_index = getopt(argc, argv, "p:s:U:S:v:c:"))!= -1) {

        switch (option_index) {
            case 'p':
                if (optarg[0] == '-') {
                    fprintf(stderr, "%s\n", optarg);
                    exit(1);
                }
                break;
            case's':
                if (optarg[0] == '-') {
                    fprintf(stderr, "%s\n", optarg);
                    exit(1);
                }
                break;
            case 'U':
                if (optarg[0] == '-') {
                    fprintf(stderr, "%s\n", optarg);
                    exit(1);
                }
                break;
            case 'S':
                if (optarg[0] == '-') {
                    fprintf(stderr, "%s\n", optarg);
                    exit(1);
                }
                break;
            case 'v':
                if (optarg[0] == '-') {
                    fprintf(stderr, "%s\n", optarg);
                    exit(1);
                }
                break;
            case 'c':



}






