#include <stdlib.h>
#include <stdio.h>
// #include <png.h>

#include "modules/screenGrabber/index.h"
#include "ppm.c"

int main(int argc, char *argv[]){
    ScreenInfo scri = screenGrabber_init();
    Image image;

    FILE *output;
    output = fopen("output.raw", "w+");

    // char
    int bufferSize = scri.desktopWidth * scri.desktopHeight 
    * 3;  // BGR - 3 channel

    char *buffer = (char *)malloc(bufferSize);
    int bPtr, iPtr; //image pointer, buffer pointer

    int finalPix = (scri.desktopWidth * scri.desktopHeight * 4) - 1;
    for (int i = 0; i < 600; i++){
        image = screenGrabber_getImage();

        bPtr = 0; 
        iPtr = 0; 
        while(iPtr <= finalPix){
            if(iPtr % 4 != 3){
                buffer[bPtr] = image.data[iPtr];
                bPtr++;
                // if(bPtr == 100) break;
            }
            iPtr++;
        }

        fwrite(buffer, 1, bufferSize, output);

        // getchar();
        // for(int y = 0; y < image.height; y++){
        //     for (int x = 0; x < image.width; x++){
        //         pointer = (y * image.width + x) * 4;
        //         char B = image.data[pointer];
        //         char G = image.data[pointer+1];
        //         char R = image.data[pointer+2];

        //         fprintf(output, "%c%c%c", B,G,R);
        //     }
        //     // fprintf(output, "\n");
        // }
        // pointer++;
        // imageToPPM(fopen("output.ppm", "w"), image);
    }
    fputc(0, output);


    
    // while(1){
    //     //grab image
        

    //     //encode video

    //     //send to network

    //     //connect 
    //     //
    // }

    

    //Save_XImage_to_JPG(image, "test.jpg", 100);

    return 0;
}


// #include <jpeglib.h>

// #define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))
// int RGBA(r, g, b, a){
//     return ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24));
// } 

// void Save_XImage_to_JPG(XImage *image, char* FileName, int Quality)
// {
//     FILE* outfile = fopen(FileName, "wb");
//     if(outfile == NULL) return;

//     struct jpeg_compress_struct cinfo;
//     struct jpeg_error_mgr       jerr;

//     cinfo.err = jpeg_std_error(&jerr);
//     jpeg_create_compress(&cinfo);
//     jpeg_stdio_dest(&cinfo, outfile);

//     cinfo.image_width      = image->width;
//     cinfo.image_height     = image->height;
//     cinfo.input_components = image->bitmap_unit >> 3;
//     cinfo.in_color_space   = JCS_EXT_BGRX;

//     jpeg_set_defaults(&cinfo);
//     /*set the quality [0..100]  */
//     jpeg_set_quality(&cinfo, Quality, True);
//     jpeg_start_compress(&cinfo, True);

//     JSAMPROW row_pointer;          /* pointer to a single row */

//     while (cinfo.next_scanline < cinfo.image_height) 
//     {
//         row_pointer = (JSAMPROW) &image->data[cinfo.next_scanline*image->bytes_per_line];
//         jpeg_write_scanlines(&cinfo, &row_pointer, 1);
//     }
//     jpeg_finish_compress(&cinfo);
//     image->data = image->data;
//     fclose(outfile);
// }
