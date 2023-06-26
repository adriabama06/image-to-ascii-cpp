# image-to-ascii-cpp
A copy of github.com/adriabama06/image-to-ascii but it's in C++  
The same of image-to-ascii, only use std, no extra libraryes
```
ffmpeg -i <video> -pix_fmt bgr24 -vf scale=64x36 input/%04d.bmp
```
```
image-to-ascii-cpp -i ../frames -fps 30 -preload
```