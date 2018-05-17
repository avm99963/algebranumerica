clear all
diary('solucions.txt')
format long;
A=load('matriu-A.dat');
% its input format is one column
[m1,n1]=size(A);
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
display('Determinant de A:');
det(A)
display('Solucio del sistema:')
x=A\b
display('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%')
display('Solucio del sistema usant Jacobi:')
x0=zeros(n,1);
[xansJ,iterJ]=jacobi(A,b,x0);
xansJ;
fout=fopen('solucionsDirecteJacobi.res','w')
fprintf(fout,'Usant Resolucio Directa \t\t Jacobi\n');
for i=1:n
    fprintf(fout,'%23.15e,  \t %23.15e  \n',x(i),xansJ(i));
end
fprintf(fout,'# iteracions per precisio 1.e-12 :');
fprintf(fout,'\n  Jacobi: %d \n',iterJ);
fclose(fout);
diary off

