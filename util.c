#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int is_number(char* str){
    for (int i = 0; str[i]!= '\0'; i++) {
        if(isdigit(str[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void print_help() {
    printf("Enter \"-i <input_file.ppm>\" or \"--input <input_file.ppm>\" to select <input_file.ppm> as source file.\
    \nEnter \"-o <output_file.ppm>\" or \"--output <output_file.ppm>\" to select <otuput_file.ppm> as output file.\
    \nEnter \"-n\" or \"--negative\" to get the negative of the image.\
    \nEnter \"-r\" or \"--rotate\" to rotate the image 90 degrees.\
    \nEnter \"-h\" or \"--horizontal\" to mirror the image horizontally.\
    \nEnter \"-v\" or \"--vertical\" to mirror the image vertically.\
    \nEnter \"-b <number>\" or \"--blur <number>\" to blur the image with the given radius number.\
    \nEnter \"-?\" or \"--help\" to dispay the help menu.\n");

    exit(0);
}