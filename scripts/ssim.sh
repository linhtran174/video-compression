ffmpeg -s 1920x1080 -f rawvideo -pix_fmt rgb24 -i dota0.rgb24 \
 -s 1920x1080 -f rawvideo -pix_fmt rgb24 -i dota0_binned.rgb24 \
-lavfi "ssim" -f null -

