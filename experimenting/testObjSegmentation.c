#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 

typedef struct _img{
    int width;
    int height;
    char *data;
} Image;

typedef unsigned int u32;
typedef int i32;
typedef unsigned short u16;
typedef short i16;
typedef unsigned char u8;
typedef short i8;


double max(double a, double b, double c) {
   return ((a > b)? (a > c ? a : c) : (b > c ? b : c));
}
double min(double a, double b, double c) {
   return ((a < b)? (a < c ? a : c) : (b < c ? b : c));
}

int blockSize = 8;
int w = 1920, h = 1080;
int pixSize = 3;
int frameSize, buffSize, lineSize, MBSize;
int blockVOffset, blockHOffset;

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

    result /= MBSize;
    return result;
}

enum _frameMode {intra, segmenting, segmented};
enum _MBtype {background, mObj};

void motionSearch(u8 *currentFrame, u8 *prevFrame, int x, int y, i8 *motionVector, i8 *costOfMatchBlock){
    int stepSize = 2; 
    int cost;
    char mVector[2]; 

    int MBOffset = (x * blockVOffset) + (y * blockHOffset);
    u8 *currentMB = currentFrame + MBOffset;
    u8 **candidateMBs = (u8 **)malloc(10 * sizeof(u8 *));
    int candidateCount = 0;

    //same pos
    cost = MAD(currentMB, prevFrame + MBOffset);
    if(cost <= 10){
        // check cost 
        mVector[0] = 0;
        mVector[1] = 0;
    }
    
    //top-left
    if(x >= stepSize && y >= stepSize){
        candidateMBs[candidateCount] = 
        prevFrame + x*(blockSize - stepSize)*lineSize + y*(blockSize - stepSize);

        candidateCount++;
    }
    MAD(currentMB, currentMB);

}

int main(){
    FILE *f = fopen("/home/linhtt/Videos/dota_1920x1080_48fps/dota2.rgb24", "r"),
    *outputFile = fopen("/home/linhtt/Videos/dota_1920x1080_48fps/dota2.coded", "w+");

    frameSize =  w*h*pixSize;
    buffSize = frameSize * 48;
    lineSize = w*pixSize;
    u8 *_48frames = (u8 *)malloc(buffSize);
    
    MBSize = blockSize * blockSize * 3;
    int numVBlock = h/blockSize;
    int numHBlock = w/blockSize;

    // Block vertical & horizontal offset
    blockVOffset = lineSize * blockSize;
    blockHOffset = blockSize * pixSize;

    size_t read = fread(_48frames, buffSize, 1, f);
    u8 fMode = intra;

    //previousMotionVectors 
    i8 prevMV[numVBlock][numHBlock][2];
    // memset(prevMV, 0, numVBlock * numHBlock * 2)
    u8 blockType[numVBlock][numHBlock];

    for(int frameI = 0; read != 1; frameI++){

        //four step search 
        // u8 *current_MB = (u8 *)malloc(MBSize);
        // u8 mX = 0, mY = 0;
        
        u8 *currentMB, *currentFrame, *prevFrame;

        currentFrame = _48frames + frameI * frameSize;
        prevFrame = _48frames + (frameI - 1) * frameSize;

        //common buffer var
        i8 cMotionVector[2];
        int meanCostValue = 0;
        i8 costOfMatchBlock = 0; 

        // Intra mode
        if(fMode == intra){
            //Dump raw RGB pixels
            fwrite(&fMode, 1, 1, outputFile);
            fwrite(currentFrame, frameSize, 1, outputFile);
            fMode = segmenting;
            read = fread(_48frames, buffSize, 1, f);
            continue;
        }

        if(fMode == segmenting){
            fwrite(&fMode, 1, 1, outputFile);

            // histogram of X and Y value. Range -128 -> 127 (halved precision).
            int hisX[64]; 
            memset(hisX, 0, 64*4); 
            int hisY[64];
            memset(hisX, 0, 64*4);

            //For blocks - first pass: calculate histogram of motion vectors
            memset(blockType, -1, numHBlock * numVBlock);
            for(int c = 0; c < numVBlock; c++){
                for(int d = 0; d < numHBlock; d++){
                    
                    // Do normal motion search
                    motionSearch(currentFrame, prevFrame, c, d, cMotionVector, &costOfMatchBlock);
                    //Save mv
                    memcpy(prevMV[c][d], cMotionVector, 2);
                    // prevMV[c][d][0] = cMotionVector[0]

                    //Put motion vector to histogram
                    //Scale value + shift to range (0-64) to put into histogram
                    i8 mX = (cMotionVector[0] >> 1) + 64;
                    i8 mY = (cMotionVector[1] >> 1) + 64;
                    hisX[mX]++;
                    hisY[mY]++;

                    //Calculate mean cost of blocks 
                    meanCostValue += costOfMatchBlock;
                }
            }

            //scene cut detection
            meanCostValue /= (numHBlock * numVBlock);
            // threshold = 20
            if(meanCostValue >= 20){
                fMode = intra;
                read = fread(_48frames, buffSize, 1, f);
                continue;
            }

            //calculate most frequent vector
            i8 mostX = 0, mostY = 0, freqX = 0, freqY = 0;
            for (int i = 0; i < 64; i++)
            {
                if(freqX < hisX[i]){
                    mostX = i;
                    freqX = hisX[i];
                }
                if(freqY < hisY[i]){
                    mostY = i;
                    freqY = hisY[i];
                }
            }

            //For blocks - second pass: decide block types for next frame:
            for(int c = 0; c < numVBlock; c++){
                for(int d = 0; d < numHBlock; d++){
                    i8 prevMx = prevMV[c][d][0];
                    i8 prevMy = prevMV[c][d][1];

                    // If motion vector = (0,0) or most frequent mv in histogram
                    if( prevMx == 0 && prevMy == 0 ){
                        //background block type
                        blockType[c][d] = background;
                    }
                    else if((prevMx << 1 == mostX) && (prevMy << 1 == mostY)){
                        int bYIndex = c - prevMy/blockSize;
                        int bXIndex = d - prevMx/blockSize;
                        if(bXIndex > 0 && bXIndex < numHBlock && bYIndex > 0 && bYIndex < numVBlock){
                            blockType[bXIndex][bYIndex] = background;
                        }
                    }
                    else
                    {
                        //current block + block moved by previousMV
                        // blockType[c][d] = mObj;
                        int bYIndex = c - prevMy/blockSize;
                        int bXIndex = d - prevMx/blockSize;
                        if(bXIndex > 0 && bXIndex < numHBlock && bYIndex > 0 && bYIndex < numVBlock){
                            blockType[bXIndex][bYIndex] = mObj;
                        }
                    }
                }
            }
            fMode = segmented;
            read = fread(_48frames, buffSize, 1, f);
            continue;
        }

        if(fMode == segmented){
            //For blocks
            for(int c = 0; c < numVBlock; c++){
                for(int d = 0; d < numHBlock; d++){

                    // If blockType = background 
                    if(blockType[c][d] == background){

                        // motion vector = previous vector 
                        memcpy(cMotionVector, prevMV[c][d], 2);
                        int currentMBOffset = (c * blockVOffset) + (d * blockHOffset);
                        int matchMBOffset = currentMBOffset +
                                            cMotionVector[1] * lineSize +
                                            cMotionVector[0] * blockSize;

                        // calculate cost function
                        int cost = MAD(currentFrame + currentMBOffset, prevFrame + matchMBOffset);

                        // if cost value >= threshold 
                        if (cost >= 20){
                            //mode = segmenting
                            fMode = segmenting;
                        }
                        meanCostValue += cost;
                    }

                    // If blockType = moving objects || unset (-1)
                    else{
                        // motion vector = normal motion search()
                        motionSearch(currentFrame, prevFrame, c, d, cMotionVector, &costOfMatchBlock);
                        meanCostValue += costOfMatchBlock;
                        //
                    }
                }
            }
            meanCostValue /= numVBlock * numHBlock;
            //If mean cost value of all blocks >= threshold:
            //Mode = intra
            if(meanCostValue >= 20){
                fMode = intra;
            }
        }

        read = fread(_48frames, buffSize, 1, f);
    }
    
    // nv12ToPPM(fopen("output.ppm", "w+"), i);
}

