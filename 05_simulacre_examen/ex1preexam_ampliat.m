% Ex. 1 preexam
clear;

m = 4;
n = 3;

A = rand(m, n)
b = rand(m, 1)

%m = 4;
%n = 3;

%A = [1, 0, 0; 0, 0, 2; 0, 1, 0; 1, 1, 0]
%b = [1; 2; 3; 4]

[Q, R] = myqr(A, m, n)

detR = 1;
for i = 1:n
  detR *= R(i, i);
endfor

[x, norm2_res] = solveqr(A, Q, R, b, m, n);
x

detR
