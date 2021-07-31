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

    /* Input and output files config */
    char *source_file_path = NULL;
	char *output_file_path = NULL;
	FILE *source_file = NULL;
    FILE *output_file = NULL;
    
    while(1) {
        option_index = 0;

        static struct option long_options[] = {
            {"help"     	, no_argument       , 0 ,  	'?'},
		    {"input"		, required_argument , 0 ,  	'i'},
		    {"output"   	, required_argument , 0 ,  	'o'},
			{"negative" 	, no_argument	    , 0	,	'n'},
			{"rotate"   	, no_argument	    , 0	,	'r'},
            {"horizontal"   , no_argument	    , 0	,	'h'},
            {"vertical"   	, no_argument	    , 0	,	'v'},
            {"blur"   	    , required_argument , 0	,	'b'},
		    {0				,        0          , 0 ,	 0 }
		};

        c = getopt_long_only(argc, argv, "?i:o:nrhvb:", long_options, &option_index);

        if(c == -1) {
            break;
        }

        switch(c) {
            case '?':
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
        }
    }
    
    return 0;
}