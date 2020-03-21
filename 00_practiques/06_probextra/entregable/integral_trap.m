clear;
format long;
% input here your table
% n = 11;
% x = 0:0.1:1;
n = 11;
x = 0:0.1:1;
y = (1 - x.^2).^(1/2);
y = e.^x;
%y = x.^(1/2) + e.^(x)

intvalue = 0

for i = 1:(n-1)
  intvalue += (x(i+1) - x(i))*(y(i+1) + y(i));
endfor

intvalue /= 2;

intvalue