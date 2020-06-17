#include <stdio.h>
#include <stdbool.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/X.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>

#include <X11/extensions/shape.h>
#include <X11/extensions/XShm.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xxf86dga.h>

int main(){
    char *dName = (char *)malloc(20);
    Display *d = XOpenDisplay(dName);
    if(d == NULL) {
        printf("cannot open display \"%s\"\n", dName ? dName : "DEFAULT");
        exit(-1);
    }
    int screen = XDefaultScreen(d);

    int ev, er, ma, mi;
    if(XDGAQueryExtension(d, &ev, &er)){
        XDGAQueryVersion(d, &ma, &mi);
    }
    else{

    }

    int modeNum = 0;
    XDGAMode *modes;
    modes = XDGAQueryModes(d, screen, &modeNum);

    for(int i = 0; i <modeNum; i++){
        modes[i] = modes[i];
    }

    bool success = XDGAOpenFramebuffer(d, screen);
    XDGADevice *device = XDGASetMode(d, screen, 1);
    
    // puts(device->data);
    // fwrite(device->data, 1, 100, stdout);
    if(device->data == NULL){
        printf("fb cannot be accessed");
    }
    // putchar(device->data[0]);

    return 0;
}


