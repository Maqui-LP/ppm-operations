#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "ppm.h"
#include "ppm-operations.h"

extern int errno;
int main(int argc, char **argv) {
    /* Opt args variables */
    int c;
    int option_index;
    int blur_value = -1;

    /* Input and output files config */
    char *source_file_path = NULL;
	char *output_file_path = NULL;
	FILE *source_file = NULL;
    FILE *operations_file = NULL;
    FILE *output_file = NULL;

    /* Input and operations images*/
    t_ppm i_ppm, op_ppm;

    /* Verifying amount of arguments */
    if (argc == 2 && (strcmp(argv[1], "-?")==0 || strcmp(argv[1], "--help")==0)) {
        printf("Aca va a estar la funcion de ayuda");
        exit(0);
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
    i_ppm = ppm_from_file(source_file);
    op_ppm = i_ppm;
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
            /* Escribir todo esto en ingles */
            printf("Ingrese \"-i entrada.pmm\" o \"--input entrada.pmm\" para seleccionar el archivo \"entrada.ppm\" como archivo de origen.\
            \nIngrese \"-o salida.pmm\" o \"--output salida.pmm\" para seleccionar el archivo \"salida.ppm\" como archivo de salida.\
            \nIngrese \"-n\" o \"--negative\" para obtener el negativo de la imagen.\
            \nIngrese \"-r\" o \"--rotate\" para rotar la imagen 90 grados.\
            \nIngrese \"-h\" o \"--horizontal\" para espejar la imagen horizontalmente.\
            \nIngrese \"-v\" o \"--vertical\" para espejar la imagen verticalmente.\
            \nIngrese \"-b NUM\" o \"--blur NUM\" para desenfocar la imagen con radio NUM.\
            \nIngrese \"-?\" o \"--help\" para visualizar el menu de ayuda.\n");
            
            exit(0);
            break;

        case 'o':
            if (!output_file_path) {
                    if (optarg && strcmp(optarg, "") && optarg[0] != '-') { 
                        output_file_path = optarg;
                        if ((output_file = fopen(output_file_path, "wb")) == NULL) {
                            error(1, errno, "An error ocurred opening output file\n");
	                    }
                    } else {
                        error(1, 0, "Missing argument <output_file>\n");
                    }
                } else {
                    error(1, 0, "Extra argument\n");
                }
            break; 
        case 'n':
            op_ppm = ppm_operation_negative(op_ppm);
            break;
        /*
        case 'r':
            r = true;
            break;
        case 'v':
            v = true;
            break;
        case 'h':
            h = true;
            break;
        */
        case 'b':
            if (optarg && strcmp(optarg, "") && (optarg[0] != '-') && atoi(optarg) > 0) {
				blur_value = atoi(optarg);
			}
			else if (atoi(optarg) <= 0) {
				fprintf(stderr, "El valor debe ser un numero positivo mayor a 0\n");
				exit(73);
			}
			break;
        }
    }
    
    
    ppm_save(op_ppm, output_file);

    return 0;
}