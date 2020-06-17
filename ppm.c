#include <stdio.h>
#include <stdlib.h>

void imageToPPM(FILE *output, Image image){
    fprintf(output, "P6\n%d %d 255\n", image.width, image.height);
    int bytePtr;
    for(int i = 0; i < image.height; i++){
        for (int j = 0; j < image.width; j++){
            fprintf(output, "%c", image.data[bytePtr+2]); //R
            fprintf(output, "%c", image.data[bytePtr+1]); //G
            fprintf(output, "%c", image.data[bytePtr+0]); //B
            bytePtr+=4;
        }
        // fprintf(output, "\n");
    }
    char eof = 0;
    fprintf(output, "%c", eof);
}