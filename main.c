#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "ppm.h"
#include "ppm-operations.h"
#include "util.h"

extern int errno;
int main(int argc, char **argv) {
    /* Opt args variables */
    int c;
    int option_index;
    int blur_ratio = -1;

    /* Input and output files config */
    char *source_file_path = NULL;
	char *output_file_path = NULL;
	FILE *source_file = NULL;
    FILE *operations_file = NULL;
    FILE *output_file = NULL;

    /* Input and operations images*/
    t_ppm op_ppm, tmp;

    /* Verifying amount of arguments */
    if (argc == 2 && (strcmp(argv[1], "-?")==0 || strcmp(argv[1], "--help")==0)) {
        print_help();
    }

    if(argc < 5) error(1, 0, "You must provide at least -i <source_file> and -o <output_file> options");

    /* verifiying -i is the first argument */
    if (strcmp(argv[1], "-i") != 0) error(1,0, "First argument must be -i");
    

    if (strcmp(argv[2], "") && argv[2][0] != '-') {
        source_file_path = argv[2];
    } else {
        error(1, 0, "Missing argument <source_file>\n");
    }
    
    if ((source_file = fopen(source_file_path, "rb")) == NULL) {
        error(1, errno, "An error ocurred opening source file\n");
    }
    op_ppm = ppm_from_file(source_file);
    fclose(source_file);
    while(1) {
        option_index = 0;

        static struct option long_options[] = {
            {"help"     	, no_argument       , 0 ,  	'?'},
            {"output"   	, required_argument , 0 ,  	'o'},
		    {"negative" 	, no_argument	    , 0	,	'n'},
			{"rotate"   	, no_argument	    , 0	,	'r'},
            {"horizontal"   , no_argument	    , 0	,	'h'},
            {"vertical"   	, no_argument	    , 0	,	'v'},
            {"blur"   	    , required_argument , 0	,	'b'},
		    {0				,        0          , 0 ,	 0 }
		};

        c = getopt_long_only(argc-2, argv+2, "?o:nrhvb:", long_options, &option_index);

        if(c == -1) {
            break;
        }

        switch(c) {
        case '?':
            print_help();
            
            break;

        case 'o':
            if (!output_file_path) {
                    if (optarg && strcmp(optarg, "") && optarg[0] != '-') { 
                        output_file_path = optarg;
                        if ((output_file = fopen(output_file_path, "wb")) == NULL) {
                            ppm_free(op_ppm);
                            error(1, errno, "An error ocurred opening output file\n");
	                    }
                    } else {
                        ppm_free(op_ppm);
                        error(1, 0, "Missing argument <output_file>\n");
                    }
                } else {
                    ppm_free(op_ppm);
                    error(1, 0, "Extra argument\n");
                }
            break; 
        case 'n':
            tmp = ppm_operation_negative(op_ppm);
            ppm_free(op_ppm);
            op_ppm = tmp;
            
            break;

        case 'r':
            tmp = ppm_operation_rotate90(op_ppm);
            ppm_free(op_ppm);
            op_ppm = tmp;
            break;

        case 'v':
            tmp = ppm_operation_flip_vertical(op_ppm);
            ppm_free(op_ppm);
            op_ppm = tmp;

            break;

        case 'h':
            tmp = ppm_operation_flip_horizontal(op_ppm);
            ppm_free(op_ppm);
            op_ppm = tmp;

            break;

        case 'b':
            if (optarg && strcmp(optarg, "")) {
                if(optarg[0] != '-' && is_number(optarg)){
                    blur_ratio = atoi(optarg);
                } else if ( is_number(optarg+1)) {
                    ppm_free(op_ppm);
                    error(1,0, "Blur ratio must be a positive number");
                } else {
                    ppm_free(op_ppm);
                    error(1,0, "Missing argument blur ratio");
                }
            }
            if (blur_ratio != -1) {
                tmp = ppm_operation_blur(op_ppm, blur_ratio);
                ppm_free(op_ppm);
                op_ppm = tmp;
		    }
            break;
        }
    }
    
    ppm_save(op_ppm, output_file);
    ppm_free(op_ppm);

    fclose(output_file);

    return 0;
}