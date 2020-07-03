#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _img{
    int width;
    int height;
    char *data;
} Image;

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

int blockSize = 8;

//Mean Absolute Difference 
int MAD(u8* block1, int x1, int y1, u8* block2, int x2, int y2){

}


int main(){
    FILE *f = fopen("/home/linh/Videos/dota_1920x1080_48fps/dota2.rgb24", "r"),
    *outputFile = fopen("/home/linh/Videos/dota_1920x1080_48fps/dota2.segmented", "w+");

    int w = 1920, h = 1080;

    int frameSize =  w*h*3;
    int buffSize = frameSize * 48;
    u8 *_48frames = (u8 *)malloc(buffSize);
    

    int MBSize = blockSize * blockSize * 3;
    int numVBlock = h/blockSize;
    int numHBlock = w/blockSize;
    
    size_t read = 0;
    for (int j = 0; j < 10; j++){
        read = fread(_48frames, buffSize, 1, f);
        if(read != buffSize) return;

        //four step search 
        // u8 *current_MB = (u8 *)malloc(MBSize);
        // u8 mX = 0, mY = 0;

        // u8 **candidateMBs = (u8 **)malloc(sizeof(u8 *) * 10);
        // for(int c = 0; c < 10; c++){
        //     candidateMBs[c] = (u8 *)malloc(MBSize);
        // }
        
        //first step
        for(int c = 0; c < blockSize; c++){
            for(int d = 0; d < blockSize; d++){
                
            }
        }

        u8 *currentMB;
        // int x1, y1, x2, y2;
        for(int frame = 1; frame < 48; frame++){

            //first row 
            int candidateCount = 0;

            u8 *currentFrame = _48frames + frame * frameSize;
            for(int c = 0; c < numVBlock; c++){
                for(int d = 0; d < numHBlock; d++){
                    currentMB = currentFrame + (c * MBSize * numHBlock) + (d * blockSize * 3)
                    // same pos
                    MAD(currentMB, d, c, )
                    


                }
            }
            _48frames[1*frameSize + ] 
        }

        

       
        // fwrite(RGB, 3, 1, outputFile);
    }

    // nv12ToPPM(fopen("output.ppm", "w+"), i);
}


