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
int w = 1920, h = 1080;
int pixSize = 3;
int frameSize, buffSize, lineSize;

int absDiff(int a, int b){
    return (a > b)?(a-b):(b-a);
}

//Mean Absolute Difference 
int MAD(u8* block1, u8* block2){
    int result = 0;
    int offset;
    for(int i = 0; i < blockSize; i++){
        for(int j = 0; j < blockSize; j++){
            for(int dim = 0; dim < pixSize; dim++){
                offset = i*lineSize + j + dim;
                result += absDiff(
                    block1[offset],
                    block2[offset]
                );
            }
        }
    }

    result /= (blockSize * blockSize * pixSize);
    return result;
}


int main(){
    FILE *f = fopen("/home/linh/Videos/dota_1920x1080_48fps/dota2.rgb24", "r"),
    *outputFile = fopen("/home/linh/Videos/dota_1920x1080_48fps/dota2.segmented", "w+");

    frameSize =  w*h*pixSize;
    buffSize = frameSize * 48;
    lineSize = w*pixSize;
    u8 *_48frames = (u8 *)malloc(buffSize);
    

    int MBSize = blockSize * blockSize * 3;
    int numVBlock = h/blockSize;
    int numHBlock = w/blockSize;

    // Block vertical & horizontal offset
    int blockVOffset = lineSize * blockSize;
    int blockHOffset = blockSize * pixSize;
    
    size_t read = 0;
    for (int j = 0; j < 10; j++){
        read = fread(_48frames, buffSize, 1, f);
        if(read != buffSize) return;

        //four step search 
        // u8 *current_MB = (u8 *)malloc(MBSize);
        // u8 mX = 0, mY = 0;
        

        u8 *currentMB, *currentFrame, *prevFrame;
        int candidateCount = 0;
        u8 **candidateMBs = (u8 **)malloc(10 * sizeof(u8 *));
        // int x1, y1, x2, y2;

        int MBOffset;
        int stepSize = 2; 
        int cost;
        
        short mVector[2]; 

        for(int frame = 1; frame < 48; frame++){

            currentFrame = _48frames + frame * frameSize;
            prevFrame = _48frames + (frame - 1) * frameSize;

            //four corner
            // candidateCount = 4; 

            // //top left 
            // currentMB
            // candidateMBs = 
            
            
            for(int c = 0; c < numVBlock; c++){
                for(int d = 0; d < numHBlock; d++){
                    MBOffset = (c * blockVOffset) + (d * blockHOffset);
                    currentMB = currentFrame + MBOffset;
                    candidateCount = 0;

                    //same pos
                    cost = MAD(currentMB, prevFrame + MBOffset);
                    if(cost <= 10){
                        // check cost 
                    }
                    
                    //top-left
                    if(c >= stepSize && d >= stepSize){
                        candidateMBs[candidateCount] = 
                        prevFrame + c*(blockSize - stepSize)*lineSize + d*(blockSize - stepSize);

                        candidateCount++;
                    }
                    MAD(currentMB, currentMB);

                }
            }
            // _48frames[1*frameSize + ] 
        }

        

       
        // fwrite(RGB, 3, 1, outputFile);
    }

    // nv12ToPPM(fopen("output.ppm", "w+"), i);
}


