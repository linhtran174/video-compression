#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _img{
    int width;
    int height;
    char *data;
} Image;

// void bgraToPPM(FILE *output, Image image){
//     fprintf(output, "P6\n%d %d 255\n", image.width, image.height);
//     int bytePtr;
//     for(int i = 0; i < image.height; i++){
//         for (int j = 0; j < image.width; j++){
//             fprintf(output, "%c", image.data[bytePtr+2]); //R
//             fprintf(output, "%c", image.data[bytePtr+1]); //G
//             fprintf(output, "%c", image.data[bytePtr+0]); //B
//             bytePtr+=4;
//         }
//         // fprintf(output, "\n");
//     }
//     char eof = 0;
//     fprintf(output, "%c", eof);
// }


// // Studio swing
// void yuvToRgb(char y, char u, char v, char *RGB){
//     long Y, U, V;
//     Y = (long) y - 16;
//     U = (long) u - 128;
//     V = (long) v - 128;
//     Y = (Y<<8) - 128;
//     U = (U<<8) - 128;
//     V = (V<<8) - 128

//     // R 
//     // 1/220   -7/652300   8149/1304600
//     // RGB[0] = 
// }



// void nv12ToPPM(FILE *output, Image image){
//     char *buffer = (char *)malloc(1920 * 1080 * 3);

//     // Frame size in bytes
//     int fSizeiBytes = image.width * image.height * 6 / 4;
//     int yPlaneOffset = image.width * image.height;

//     char Y, U, V, RGB[3];
//     for (size_t i = 0; i < fSizeiBytes; i++)
//     {
//         Y = image.data[i]; 
//         U = image.data[fSizeiBytes + i/2];
//         V = image.data[fSizeiBytes + i/2 + 1];
//         // var yPlaneOffset
//         yuvToRgb(Y,U,V, &RGB);

//         fputc()
//     }
// }

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

// char max(char a, char b){
//     return (a > b)?a:b;
// }
// char min(char a, char b){
//     return (a < b)?a:b;
// }
// u32 max(u32 a, u32 b){
//     return (a > b)?a:b;
// }
// u32 min(u32 a, u32 b){
//     return (a < b)?a:b;
// }

double max(double a, double b, double c) {
   return ((a > b)? (a > c ? a : c) : (b > c ? b : c));
}
double min(double a, double b, double c) {
   return ((a < b)? (a < c ? a : c) : (b < c ? b : c));
}

//
int nHueBin; //8bit
int nSatBin; //8bit
int nValBin; //8bit
// int nTotalBin = 256 * 16 * 16;




// int thirdRange, twoThirdRange;
// void RGB24ToHSV(u8 *RGB, u32 *HSV){
//     u32 r = (u32) RGB[0], g = (u32) RGB[1], b = (u32) RGB[2];

//     u32 cmax = max(max(r,g), b);
//     u32 cmin = min(min(r,g), b);
//     u32 diff = cmax - cmin;

//     //
//     if(cmax == 0){
//         HSV[0] = 0;
//         HSV[1] = 0;
//         HSV[2] = 0;
//         return;
//     }
//     u32 H, S, V;

//     if(diff == 0){
//         H = 0;
//     } 
//     else {
//         if(cmax == r){
//             H = ( ((g - b + 255) << nHBit)
//              / ((2 * diff * 3) << nHBit));
//         }
//         if(cmax == g){
//             // H = (((b - r + 255) << nHBit) / (2 * diff * 3)  + thirdRange) % nHueBin;
//             H = ( ((b - r + 255) << nHBit)
//              / ((2 * diff * 3) << nHBit)  + thirdRange);
//             // H = (3 * (b - r)/ % 3) *
//         }
//         if(cmax == b){
//             H = ( ((r - g + 255) << nHBit)
//              / ((2 * diff * 3) << nHBit)  + twoThirdRange);
//         }
//     }

//     S = (diff << nSBit) / cmax;
//     V = (cmax << nVBit) / 256;

//     (*HSV) = (u32)(
//         (u32)(H << (nTotalBit - nHBit)) +
//         (u32)(S << (nTotalBit - nHBit - nSBit)) + 
//         (u32)(V << (nTotalBit - nHBit - nSBit - nVBit))
//     );
// }

// void HSVToRGB24(u8 *RGB, u32 *HSV){
//     // int 
//     u32 H = (u32) ((*HSV) >> (nTotalBit - nHBit));
//     u32 S = ( (u32)((*HSV) << nHBit) ) >> (nTotalBit - nVBit);
//     u32 V = ( (u32)((*HSV) << (nHBit + nVBit)) ) >> (nTotalBit - nSBit);

//     u32 cmax = V * 256 / nValBin;
//     u32 diff = S * cmax / nSatBin;

//     u32 R,G,B;
//     int G_B, B_R, R_G;
//     //0 -> nHueBin/3 

//     if(S == 0){
//         RGB[0] = cmax;
//         RGB[1] = cmax;
//         RGB[2] = cmax;
//         return;
//     }

//     if(H < nHueBin/3){
//         R = cmax;
//         G_B = (H * diff * 2 * 3) - 255;
//         if(G_B < 0){
//             G = cmax - diff;
//             B = G - G_B;
//         }
//         else{
//             B = cmax - diff;
//             G = G_B + B;
//         }
//     } 
//     else if(H >= thirdRange && H < twoThirdRange){
//         //            H = ( ((b - r + 255) << nHBit)
//         //  / ((2 * diff * 3) << nHBit)  + thirdRange);
//         G = cmax;
//         B_R = (int)((H - thirdRange) * (diff * 2 * 3) - 255);
//         if(B_R < 0){
//             B = cmax - diff;
//             R = B - B_R;
//         }
//         else{
//             R = cmax - diff;
//             B = B_R + R;
//         }
//     }
//     else{
//         B = cmax;
//         R_G = ((H - twoThirdRange)* diff * 2 * 3) - 255;
//         if(R_G < 0){
//             R = cmax - diff;
//             G = R - R_G;
//         }
//         else{
//             G = cmax - diff;
//             R = R_G + G;
//         }
//     }

//     RGB[0] = R; RGB[1] = G; RGB[2] = B;
// }


int RGBToHSV(u8 *RGB, double *HSV) {

    double r = (double)RGB[0], g = (double)RGB[1], b = (double)RGB[2];
    // R, G, B values are divided by 255
    // to change the range from 0..255 to 0..1:
    double h, s, v;
    r /= 255.0;
    g /= 255.0;
    b /= 255.0;
    double cmax = max(r, g, b); // maximum of r, g, b
    double cmin = min(r, g, b); // minimum of r, g, b
    double diff = cmax-cmin; // diff of cmax and cmin.
    if (cmax == cmin)
        h = 0;
    else if (cmax == r)
        h = fmod((60 * ((g - b) / diff) + 360), 360.0);
    else if (cmax == g)
        h = fmod((60 * ((b - r) / diff) + 120), 360.0);
    else if (cmax == b)
        h = fmod((60 * ((r - g) / diff) + 240), 360.0);
    // if cmax equal zero
        if (cmax == 0)
            s = 0;
        else
            s = (diff / cmax);
    // compute v
    v = cmax;
    

    HSV[0] = h, HSV[1] = s, HSV[2] = v;
    return 0;
}



int Clamp(int i)
{
  if (i < 0) return 0;
  if (i > 255) return 255;
  return i;
}

void HSVToRGB(u8 *RGB, double *HSV)
{

    double H = HSV[0], S = HSV[1], V = HSV[2];
    while (H < 0) { H += 360; };
    while (H >= 360) { H -= 360; };
    double R, G, B;
    if (V <= 0)
        { R = G = B = 0; }
    else if (S <= 0)
    {
        R = G = B = V;
    }
    else
    {
        double hf = H / 60.0;
        int i = (int) floor(hf);
        double f = hf - i;
        double pv = V * (1 - S);
        double qv = V * (1 - S * f);
        double tv = V * (1 - S * (1 - f));
        switch (i)
        {
            // Red is the dominant color
            case 0:
                R = V;
                G = tv;
                B = pv;
                break;

            // Green is the dominant color
            case 1:
                R = qv;
                G = V;
                B = pv;
                break;

            case 2:
                R = pv;
                G = V;
                B = tv;
                break;

            // Blue is the dominant color
            case 3:
                R = pv;
                G = qv;
                B = V;
                break;
            case 4:
                R = tv;
                G = pv;
                B = V;
                break;

            // Red is the dominant color
            case 5:
                R = V;
                G = pv;
                B = qv;
                break;

            // Just in case we overshoot on our math by a little, we put these here. Since its a switch it won't slow us down at all to put these here.

            case 6:
                R = V;
                G = tv;
                B = pv;
                break;
            case -1:
                R = V;
                G = pv;
                B = qv;
                break;

            // The color is not defined, we should throw an error.
            default:
                //LFATAL("i Value error in Pixel conversion, Value is %d", i);
                R = G = B = V; // Just pretend its black/white
                break;
        }
    }
    RGB[0] = Clamp((int)(R * 255.0));
    RGB[1] = Clamp((int)(G * 255.0));
    RGB[2] = Clamp((int)(B * 255.0));
}


//

int nHBit = 5;
int nSBit = 6;
int nVBit = 5;
int nTotalBit = 32;
int main(){
    // thirdRange = (1 << nHBit) /3;
    // twoThirdRange = 2 * thirdRange;
    nHueBin = 1 << nHBit;
    nSatBin = 1 << nSBit;
    nValBin = 1 << nVBit;


    FILE *f = fopen("/home/linh/Videos/dota_1920x1080_48fps/dota0.rgb24", "r"),
    *outputFile = fopen("/home/linh/Videos/dota_1920x1080_48fps/dota0_binned_565.rgb24", "w+");

    int w = 1920, h = 1080;
    char *y = (char *)malloc(w*h);

    // Image i;
    // i.width = w;
    // i.height = h;
    int dataSize = w*h;
    // i.data = (char *)malloc(dataSize);

    u8 *RGB = (u8 *)malloc(3);
    RGB[0] = 13; RGB[1] = 17; RGB[2] = 13;
    double *HSV = (double *)malloc(3*sizeof(double));
    // RGB24ToHSV(RGB, &HSV);
    // HSVToRGB24(RGB, &HSV);

    // for (size_t c = 0; c < 480; c++){
    //     for (size_t j = 0; j < dataSize; j++)
    //     {
    //         RGB[0] = fgetc(f);
    //         RGB[1] = fgetc(f);
    //         RGB[2] = fgetc(f);
    //         RGB24ToHSV(RGB, &HSV);
    //         HSVToRGB24(RGB, &HSV);
    //         fwrite(&HSV, 2, 1, outputFile);
    //     }
    // }
    size_t read = 0;
    for (size_t j = 0; j < dataSize*481; j++){
        read = fread(RGB, 3, 1, f);
        if(read != 1) return;
        RGBToHSV(RGB, HSV);

        HSV[0] = (double)( floor((HSV[0] / 360) * nHueBin) /nHueBin * 360);
        HSV[1] = (double)( floor(HSV[1] * nSatBin)/nSatBin);
        HSV[2] = (double)( floor(HSV[2] * nValBin)/nValBin);

        HSVToRGB(RGB, HSV);
        fwrite(RGB, 3, 1, outputFile);
    }

    // nv12ToPPM(fopen("output.ppm", "w+"), i);
}
