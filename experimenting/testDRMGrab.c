// #include <drm.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm_fourcc.h>
#include <drm_mode.h>
#include <libdrm/amdgpu_drm.h>
// #include <nouveau_drm.h>

#include <X11/Xlib.h>
// #include <X11/Xutil.h>
// #include <X11/X.h>
// #include <X11/Xlibint.h>
// #include <X11/Xproto.h>
// #include <X11/Xutil.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
// #include <libv4l1.h>
#include <libv4l2.h>
// #include <libv4l1-videodev.h>
#include <linux/dma-buf.h>
#include <linux/videodev2.h>



#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

int main(){
    perror("LINH");
    //get X11 screeninfo
    // XOpenDisplay(scri.displayname);
    // int scrgrb_drm_screenWidth = 1920;
    // int scrgrb_drm_screenHeight = 1080;
    



    //check drm support
    if (!drmAvailable())
		return 1;

    const int drmfd = open("/dev/dri/card0", O_RDONLY);
    drmSetClientCap(drmfd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
    drmModeResPtr res = drmModeGetResources(drmfd);

    printf("searching for the correct framebuffer");
    drmModeFBPtr targetFb = NULL;
    //planes enum 
    drmModePlaneResPtr planes = drmModeGetPlaneResources(drmfd);
    for(int i = 0; i < planes->count_planes; i++){
        drmModePlanePtr p = drmModeGetPlane(drmfd, planes->planes[i]);
        if(p && p->fb_id){
            drmModeFBPtr fb = drmModeGetFB(drmfd, p->fb_id);
            targetFb = 
            (fb && fb->width == SCR_WIDTH && fb->height == SCR_HEIGHT)?
            fb:targetFb;
        }
        drmModeFreePlane(p);
    }
    drmModeFreePlaneResources(planes);

    int DMABUF_fd = -1;
    const int ret = drmPrimeHandleToFD(drmfd, targetFb->handle, 0, &DMABUF_fd);

    struct v4l2_requestbuffers reqbuf;
    memset(&reqbuf, 0, sizeof (reqbuf));
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    reqbuf.memory = V4L2_MEMORY_DMABUF;
    reqbuf.count = 1;

    perror("err");
    FILE *BUFFFILE = fdopen(DMABUF_fd,"r");
    perror("err");
    printf("%d", fgetc(BUFFFILE));
    char *buffer = (char *)malloc(SCR_WIDTH*SCR_HEIGHT*10);
    buffer = mmap(NULL,SCR_WIDTH*SCR_HEIGHT*10,PROT_READ,MAP_SHARED,DMABUF_fd, 0);
    perror("err");

    if (ioctl(DMABUF_fd, VIDIOC_REQBUFS, &reqbuf) == -1) {
        if (errno == EINVAL)
            printf("Video capturing or DMABUF streaming is not supported\\n");
        else
            perror("VIDIOC_REQBUFS");

        exit(EXIT_FAILURE);
    }

    // Display *xdisp = XOpenDisplay(NULL);
    // eglBindAPI(EGL_OPENGL_API);
    // EGLDisplay edisp = eglGetDisplay(xdisp);
    // EGLint ver_min, ver_maj;
	// eglInitialize(edisp, &ver_maj, &ver_min);

    // static const EGLint econfattrs[] = {
	// 	EGL_BUFFER_SIZE, 32,
	// 	EGL_RED_SIZE, 8,
	// 	EGL_GREEN_SIZE, 8,
	// 	EGL_BLUE_SIZE, 8,
	// 	EGL_ALPHA_SIZE, 8,

	// 	EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
	// 	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,

	// 	EGL_NONE
	// };

    // EGLConfig config;
	// EGLint num_config;
	// eglChooseConfig(edisp, econfattrs, &config, 1, &num_config);

    // XVisualInfo xvisual_info = {0};
    // eglGetConfigAttrib(edisp, config, EGL_NATIVE_VISUAL_ID, (EGLint*)&xvisual_info.visualid);

    // // EGLContext ectx = eglCreateContext(edisp, config,
	// // 	EGL_NO_CONTEXT, ectx_attrs);
	// // ASSERT(EGL_NO_CONTEXT != ectx);


    // // SCR_WIDTH, SCR_HEIGHT, targetFb->pitch, offset = 0, DMABUF_fd;
    // uint32_t fourcc = DRM_FORMAT_XRGB8888;
    // EGLAttrib eimg_attrs[] = {
	// 	EGL_WIDTH, SCR_WIDTH,
	// 	EGL_HEIGHT, SCR_HEIGHT,
	// 	EGL_LINUX_DRM_FOURCC_EXT, fourcc,
	// 	EGL_DMA_BUF_PLANE0_FD_EXT, DMABUF_fd,
	// 	EGL_DMA_BUF_PLANE0_OFFSET_EXT, 0,
	// 	EGL_DMA_BUF_PLANE0_PITCH_EXT, targetFb->pitch,
	// 	EGL_NONE
	// };
    // EGLImage eimg = eglCreateImage(edisp, EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, 0,
	// 	eimg_attrs);



    // u_int32_t fb_id = 0;
    // drmModeFBPtr fb = drmModeGetFB(drmfd, fb_id);
    // drmModeResPtr res = drmModeGetResources(fd);

    drmModeFreeResources(res);
    close(drmfd);
}
