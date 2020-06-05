#include <stdlib.h>
#include <stdio.h>

#include "modules/screenGrabber/index.h"

int main(int argc, char *argv[]){
    ScreenInfo scri = screenGrabber_init();
    Image image;

    for (int i = 0; i < 600; i++)
    {
        image = screenGrabber_getImage();
    }

    
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
