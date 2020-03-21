% example
clear;
% original table
x = -4:5
y = 2*x.^2 - x - 5
m=2;
[coeff, norm2_res]=polminquad(x,y,m); % routine computing the latter polynomial - THIS IS WHAT WE HAVE TO DOscatter(xrr,yrr,'r','filled'); hold on % scatter points
scatter(x,y,'r','filled'); hold on % scatter points
xC=-4:0.01:5;
yC = 0;
for i = 0:m
  yC += coeff(i+1)*xC.^i;
endfor
plot(xC,yC,'b');
hold off;
