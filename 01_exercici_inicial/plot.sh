#!/bin/sh
gnuplot << END

set terminal png size 2160,1440
set output "grafiques.png"
set key off
set title "Chirikov Standard map"
show title
set xlabel "Theta"
set ylabel "p"

plot [0:6.284][-3.14:3.14] for[IDX=0:1000] "plot.dat" index IDX using 2:1 with dots
#plot [0:3.142][-10:10] "plot.dat" using 2:1 with points

END

