% Ex. 1 preexam
clear;

m = 4;
n = 3;

A = rand(m, n)

%m = 4;
%n = 3;

%A = [1, 2, 3; 2, 5, 4; 1, 1, 1; 2, 5, 4]

[Q, R] = myqr(A, m, n);

detR = 1;
for i = 1:n
  detR *= R(i, i);
endfor

detR