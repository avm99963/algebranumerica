clear;
format long;
% input here your table

% n = 11;
% x = 0:0.1:1;

n = 11;
x = 0:0.1:1;
y = (1 - x.^2).^(1/2);
%y = x.^(1/2) + e.^(x)
m=9;
[coeff, norm2_res]=polminquad(x,y,m); % routine computing the latter polynomial
scatter(x,y,'r','filled'); hold on % scatter points
xC=0:0.01:1;
yC = 0;
for i = 0:m
  yC += coeff(i+1)*xC.^i;
endfor
plot(xC,yC,'b');
hold off;

intvalue = 0;

for i = 0:m
  intvalue += (coeff(i+1)/(i+1))*(x(n)^(i+1) - (x(1))^(i+1));
endfor

intvalue