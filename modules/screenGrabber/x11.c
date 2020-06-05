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

// namespace: scrgrb
static int screenNumber;
static Display *scrgrb_display = NULL;
static Window scrgrb_rootWindow;
static Screen *scrgrb_screen = NULL;
XImage *scrgrb_ximage = NULL;
static XShmSegmentInfo __sharedMem;

ScreenInfo newScreenInfo(){
    ScreenInfo r; //= (ScreenInfo *)malloc(sizeof(ScreenInfo *));
    r.displayname = (char *)malloc(20);
    r.desktopWidth = 0;
    r.desktopHeight = 0;
    r.desktopDepth = 0;
    return r;
}

ScreenInfo screenGrabber_init(){
    ScreenInfo scri = newScreenInfo();
    // init
    int ignore = 0;
    bzero(&__sharedMem, sizeof(__sharedMem));

    // open display
    scrgrb_display = XOpenDisplay(scri.displayname);
    if(scrgrb_display == NULL) {
        printf("cannot open display \"%s\"\n", scri.displayname ? scri.displayname : "DEFAULT");
        exit(-1);
    }

    // check MIT extension
    if(XQueryExtension(scrgrb_display, "MIT-SHM", &ignore, &ignore, &ignore) ) {
        int major, minor;
        Bool pixmaps;
        if(XShmQueryVersion(scrgrb_display, &major, &minor, &pixmaps) == True) {
            printf("XShm extention version %d.%d %s shared pixmaps\n",
                    major, minor, (pixmaps==True) ? "with" : "without");
        } else {
            printf("XShm extension not supported.\n");
        }
    }
    // get default screen
    screenNumber = XDefaultScreen(scrgrb_display);
    if((scrgrb_screen = XScreenOfDisplay(scrgrb_display, screenNumber)) == NULL) {
        printf("cannot obtain screen #%d\n", screenNumber);
    }

    // get screen hight, width, depth
    scri.desktopWidth = XDisplayWidth(scrgrb_display, screenNumber);
    scri.desktopHeight = XDisplayHeight(scrgrb_display, screenNumber);
    scri.desktopDepth = XDisplayPlanes(scrgrb_display, screenNumber);
    printf("X-Window-init: dimension: %dx%dx%d @ %d/%d\n",
            scri.desktopWidth, scri.desktopHeight, scri.desktopDepth,
            screenNumber, XScreenCount(scrgrb_display));

    //create image context
    if((scrgrb_ximage = XShmCreateImage(scrgrb_display,
        XDefaultVisual(scrgrb_display, screenNumber),
        scri.desktopDepth, ZPixmap, NULL, &__sharedMem,
        scri.desktopWidth, scri.desktopHeight)) == NULL) {
        printf("XShmCreateImage failed.\n");
    }

    //get shm info
    if((__sharedMem.shmid = shmget(IPC_PRIVATE,
        scrgrb_ximage->bytes_per_line*scrgrb_ximage->height,
        IPC_CREAT | 0777)) < 0) {
        printf("shmget error");
    }

    __sharedMem.shmaddr = scrgrb_ximage->data = (char*) shmat(__sharedMem.shmid, 0, 0);
    __sharedMem.readOnly = False;
    if(XShmAttach(scrgrb_display, &__sharedMem) == 0) {
        printf("XShmAttach failed.\n");
    }

    scrgrb_rootWindow = XRootWindow(scrgrb_display, screenNumber);

    return scri;
}

Image screenGrabber_getImage(){
    Image image;
    bool success = XShmGetImage(scrgrb_display, scrgrb_rootWindow, scrgrb_ximage, 0, 0, XAllPlanes());
    if(!success) {
        // image->data RGBA
        printf("FATAL: XShmGetImage failed.\n");
        exit(-1);
    }

    image.width = scrgrb_ximage->width;
    image.height = scrgrb_ximage->height;
    image.data = scrgrb_ximage->data;
    image.depth = scrgrb_ximage->depth;
    image.bytes_per_line = scrgrb_ximage->bytes_per_line;
    image.bits_per_pixel = scrgrb_ximage->bits_per_pixel;

    return image;
}
