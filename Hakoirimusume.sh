#!/bin/bash

mkdir -p build && \
    cd build && \
    cmake .. && \
    make && \
    ./Hakoirimusume && \
    cd .. && \
    python3 make_fig.py && \
    ffmpeg -framerate 2 -pattern_type glob -i  "clearroute_images/*.png" -c:v libx264 -r 30 -pix_fmt yuv420p output_video.mp4




