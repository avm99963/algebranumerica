% Ex. 1 preexam
clear;

load('../MSL.mat');
[m, n] = size(A);

%A = rand(m, n)

%m = 4;
%n = 3;

%A = [1, 2, 3; 2, 5, 4; 1, 1, 1; 2, 5, 4]

M = A'*A;

[Q, R] = myqr(M, m, n);

detR = 1;
for i = 1:n
  detR *= R(i, i);
endfor

detR

R(1, 1)
R(2, 2)
R(n, n)
R
