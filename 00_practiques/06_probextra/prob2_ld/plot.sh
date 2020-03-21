#!/bin/sh
gnuplot << END

#set terminal png size 2160,1440
set terminal png size 1080,720
set output "grafiques.png"
set title "Problema 2"
show title
set xlabel "n"
set format y '%g' 
set logscale y 10

plot "plot.dat" u 0:1 w lp title "R_n", "plot.dat" u 0:2 w lp title "E_n", "plot.dat" u 0:3 w lp title "A_n"

#plot [0:3.142][-10:10] "plot.dat" using 2:1 with points

END

