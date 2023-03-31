#!/bin/bash

# ffmpeg -f image2 -r 8 -pattern_type glob -i '*.png' -vcodec libx264 -crf 22 video.gif
# convert -delay 20 -loop 0 *.png animation.gif

ffmpeg -framerate 10 -pattern_type glob -i '*.png' -r 15 -vf scale=512:-1 out.gif 