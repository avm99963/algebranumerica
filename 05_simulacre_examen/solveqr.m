function [x, norm2_res] = solveqr(A, Q, R, a, m, n)

% Resolem per x en R*x = Q'*a = b
b = Q'*a;

Q
b
R

x = zeros(n, 1);

for k = n:-1:1
  x(k) = b(k);
  for i = (k+1):n
    x(k) -= R(k, i)*x(i);
  endfor
  x(k) /= R(k, k);
endfor

disp("Norm");
Q*R*x
a
Q*R*x - a
norm2_res = norm(A*x - a, 2)
disp("---");

endfunction
