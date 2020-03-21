% example
clear;
x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37];
y = [0.4, 0.9, 1.1, 0.3, 0., -0.4, 0.1, 0.4, 0.3, -1.7, -2., -1.4, -0.7, -0.2, 0.3, -0.3, -0.1, -0.3, 0.8, 1.1, 1.9, -0.5, -0.8, -0.8, 0.1, 0., 0.1, -0.3, -0.1, -0.1, 0.7, 1.1, 1.2, -0.9, -0.7, -0.6, 0.1];
m=7;
[coeff, norm2_res]=polminquad(x,y,m); % routine computing the latter polynomial - THIS IS WHAT WE HAVE TO DOscatter(xrr,yrr,'r','filled'); hold on % scatter points
scatter(x,y,'r','filled'); hold on % scatter points
xC=1:0.1:39;
yC = 0;
for i = 0:m
  yC += coeff(i+1)*xC.^i;
endfor
y_predicted = 0;
for i = 0:m
  y_predicted += coeff(i+1)*38.^i;
endfor
plot(xC,yC,'b');
y_predicted
scatter(38,y_predicted,'g','filled')
hold off;
