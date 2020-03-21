% Relaxacio
function [x, iter] = relaxacio(A, b, omega, x)
format long;
tol = 10^-12
maxit = 300
D = diag(diag(A));
L = tril(A, -1);
U = triu(A, 1);
Bw = inv(D+omega*L)*((1-omega)*D-omega*U);
normB = norm(Bw, 2);
X1 = sprintf('Norma sub-2 de B_w: %f', normB);
disp(X1);

radi = max(abs(eig(Bw)));
if (radi >= 1)
  disp ('Radi espectral de B mes gran o igual que 1. Relaxacio no convergeix')
  return;
endif

radi

Cw = omega*inv(D+omega*L)*b;
iter = 0;
errabs = 1;
x0 = x;
xnext = x0;

while (abs(errabs) > tol && iter < maxit)
  x = xnext;
  iter = iter+1;
  xnext = Bw*x + Cw;
  errabs = norm(b-A*xnext, 2)/norm(b-A*x0, 2);
endwhile

XD=sprintf('\nEstimacio RESIDU RELATIU a la solucio iterativa: %e',errabs);
disp(XD) 
XD1=sprintf('\nIteracions usades: %d \n',iter);
disp(XD1) 
disp('Solucio aproximada usant Relaxacio:');
disp(xnext)

endfunction
