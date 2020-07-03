sleep 2 && \
ffmpeg -video_size 1920x1080 -framerate 48 \
-f x11grab -i :0.0 -f rawvideo -pix_fmt rgb24 \
-frames:v 480 dota2.rgb24