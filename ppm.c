#include <stdio.h>
#include <stdlib.h>

void writeImageToFile(FILE *output, Image image){
    fprintf(output, "P6\n%d %d 255\n", image.width, image.height);
    int bytePtr;
    for(int i = 0; i < image.height; i++){
        for (int j = 0; j < image.width; j++){
            for(int dim = 0; dim < 3; dim++){
                bytePtr = (i * image.width + j) * 4 + dim;
                fprintf(output, "%c", image.data[bytePtr]);
            }
        }
        // fprintf(output, "\n");
    }
    char eof = 0;
    fprintf(output, "%c", eof);
}