function [coeff, norm2_res] = polminquad(x, y, m)
format long;
n = length(x);

M = ones(n, m+1);

% Fem QR.
for j = 2:(m+1)
  M(:, j) = x.^(j-1)';
endfor

Q = M;
R = zeros(m+1, m+1);

for i = 1:(m+1)
  R(i, i) = norm(Q(:, i));
  Q(:, i) /= R(i, i); % Normalitzem vector a_i
  for j = (i+1):(m+1)
    % Ortogonalitza els altres vectors a_j
    R(i, j) = Q(:, i)'*Q(:, j);
    Q(:, j) = Q(:, j) - R(i, j)*Q(:, i);
  endfor
endfor

disp("Norma QtQ - Id");
norm(Q'*Q - eye(m+1, m+1), Inf)

% Resolem per a en R*a = Q'*y = b
b = Q'*y';

coeff = zeros(m+1, 1);

for k = (m+1):-1:1
  coeff(k) = b(k);
  for i = (k+1):(m+1)
    coeff(k) -= R(k, i)*coeff(i);
  endfor
  coeff(k) /= R(k, k);
endfor

coeff

disp("Norm");
norm2_res = norm(M*coeff - y', 2)
disp("---");

endfunction
