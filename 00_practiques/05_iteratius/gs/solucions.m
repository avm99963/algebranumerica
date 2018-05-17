clear all
diary('solucions.txt')
format long;
A=load('matriu-A.dat');
% its input format is one column
[m1,n1]=size(A)
display('Ordre de la matriu:')
n=sqrt(n1*m1)
A=reshape(A,n,n)';
% It transforms A into a nxn matrix 
% It reads the initial column row by row
b=load('vector-b.dat');
display('norm(A,2):');
norm2=norm(A,2)
display('norm(A,1):');
norm1=norm(A,1)
display('norm(|A|,inf):');
norm=norm(A,inf)
display('Radi espectral de A, rho(A):');
rho=max(abs(eig(A)))
rho1=max(abs(eig(A)))
display('solucio del sistema:')
x=A\b
fout=fopen('solucio.res','w');
for i=1:n
    fprintf(fout,'%23.15e\n',x(i));
end
fclose(fout);
diary off

