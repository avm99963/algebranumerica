clear all
format long;

A=load('matriu-Alarge.dat');
% its input format is one column
[m1,n1]=size(A);
n=sqrt(n1*m1);
A=reshape(A,n,n)';
% It transforms A into a nxn matrix 
% It reads the initial column row by row

b=load('vector-blarge.dat');

D = diag(diag(A));
L = tril(A, -1);
U = triu(A, 1);

x = 0.1:0.1:2;
yn = zeros(1, columns(x));
y = yn;

for i = 1:columns(x)
  omega = i/10;
  Bw = inv(D+omega*L)*((1-omega)*D-omega*U);
  yn(1, i) = norm(Bw, 2);
  y(1, i) = max(abs(eig(Bw)));
endfor

plot(x, y)

x
y
yn
