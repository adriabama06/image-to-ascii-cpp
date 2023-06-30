# image-to-ascii-cpp
A copy of github.com/adriabama06/image-to-ascii but it's in C++  
The same of image-to-ascii, only use std, no extra libraries  
Please first read the original github to know how complie the code, limitations and other things: https://github.com/adriabama06/image-to-ascii#readme
## 4:3 Recomendation:
```bash
ffmpeg -i <video> -pix_fmt bgr24 -vf scale=64x36 input/%04d.bmp
```
## 16:9 Recomendation:
```bash
ffmpeg -i <video> -pix_fmt bgr24 -vf scale=64x18 input/%04d.bmp
```
Then you can use multiples of this number keeping the aspect radio, like:  
64 * 2 -> 128 * 2 -> 256 ...
18 * 2 -> 36 * 2  -> 72 ...
```bash
$ > image-to-ascii-cpp --help

image-to-ascii-cpp -i <input file/folder>
  --help                       (Optional) - Show this menu
  -i             <file/folder>            - Input file or folder, if the input is a folder you can use multithread or play, only supports bitmap (.bmp) format at 8bit per pixel and 
uncompressed
  -o             <file/folder> (Optional) - Output file or folder, optional if you just want to play it, if you play the input it will not save any file
  -fps           <number>                 - (Optional only if "-o" is not set) Set framerate in frames per second, example: 30, 24, 60, 23.976023976 (for cinema using float numbers 
use: "1000 / (1001 / fps)")
  -pallete       <string>      (Optional) - Set custom color pallete for ascii, the default is: " .,-~:=$#@"
  -no-clear-console            (Optional) - Prevent clear console everyframe, good for ssh connections
  -t             <number>      (Optional) - Threads for paralel frame conversion, sometimes can be slow than single thread, recomended on slow computers or if the folder has plenty 
of files
  -preload                     (Optional) - Set if preload the files in memory before play, if you no set this the playback will be converted in realtime
  -txt                         (Optional) - Set this to true if the input is a preconverted bmp file as txt
  -v                           (Optional) - Verbose output
```