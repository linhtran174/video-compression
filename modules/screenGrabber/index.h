typedef struct __screen_info {
    char * displayname;
    int desktopWidth;
    int desktopHeight; 
    int desktopDepth;
} ScreenInfo;

typedef struct __image {
	int width;
	int height;
	char * data; //BGRA 
	int depth;
	int bytes_per_line;
	int bits_per_pixel;
} Image ;

//Initialize grabber
ScreenInfo screenGrabber_init();
Image screenGrabber_getImage();

// Platform check
#ifdef _WIN32
    // Windows (x64 and x86)
    #include "windows.c"
#elif __unix__
    // Unix
    #include "x11.c"
#elif __linux__
    #include "x11.c"
#elif __APPLE__
    // Mac OS
#endif

