% Jacobi
function [x,iter]=jacobi(A,b,x)
format long ;	
tol=10^-12;
maxit=300;
D=diag(diag(A));
BJ=inv(D)*(D-A);
normB=norm(BJ,2);
X1=sprintf('Norma sub-2 de B_J: %f', normB);
disp(X1)
if (normB>=1) 
  disp('Radi espectral de B mes gran o igual que 1. Jacobi no convergeix')
  return; 
  endif;
XDDD = sprintf('Radi espectral de B_J: %f', max(abs(eig(BJ))));
disp(XDDD)
cJ=inv(D)*b;
iter=0;
errabs=1;
x0=x;xnext=x0;
while ( (abs(errabs)>tol) && (iter<maxit))
    x=xnext;		 
    iter=iter+1;
    xnext=BJ*x+cJ;
    errabs=norm(b-A*xnext,2)/norm(b-A*x0, 2); 
end
XD=sprintf('\nEstimacio RESIDU a la solucio iterativa: %e',errabs);
disp(XD) 
XD1=sprintf('\nIteracions usades: %d \n',iter);
disp(XD1) 
disp('Solucio aproximada usant Jacobi:');
disp(xnext)
endfunction


% Exemple de crida des de la finestra de comandes:
% >>A=[5 -2 1;-1 -7 3;2 -1 8];
% >> x=[0 0 0]';
% >> b=[3 -2 1]';
% >> jacobi(A,b,x)
