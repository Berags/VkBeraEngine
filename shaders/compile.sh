#!/bin/zsh

# loop through vert and frag file
for i in *.{vert,frag}; do
  echo "Processing: " "$i" "${i}.spv";
  glslc "$i" -o "${i}.spv";
done