% example
clear;
% original table
%x=[37, 61, 88, 114, 138, 169, 198, 228, 258, 290, 325, 364, 398, 435, 478, 520, 568, 621, 678, 747, 828, 985];
%y=[22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1];
x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24]
y = [5.0083, 12.0086, 29.0077, 62.0015, 117.009, 200.004, 317.009, 474.009, 677.005, 932.002, 1245.01, 1622, 2069.01, 2592.01, 3197.01, 3890, 4677, 5564, 6557.01, 7662, 8885, 10232, 11709, 13322, 15077]
m=3;
[coeff, norm2_res]=polminquad(x,y,m); % routine computing the latter polynomial - THIS IS WHAT WE HAVE TO DOscatter(xrr,yrr,'r','filled'); hold on % scatter points
scatter(x,y,'r','filled'); hold on % scatter points
xC=0:0.01:25;
yC=coeff(1)+xC*coeff(2)+xC.^2*coeff(3)+xC.^3*coeff(4);
plot(xC,yC,'b');
hold off;
