function [Q, R] = myqr(A, m, n)
format long;

% Fem QR.

Q = A;
R = zeros(n, n);

for i = 1:n
  R(i, i) = norm(Q(:, i));
  Q(:, i) /= R(i, i); % Normalitzem vector a_i
  for j = (i+1):n
    % Ortogonalitza els altres vectors a_j
    R(i, j) = Q(:, i)'*Q(:, j);
    Q(:, j) = Q(:, j) - R(i, j)*Q(:, i);
  endfor
endfor

%Q'*Q

disp("Norma inf QtQ - Id");
norm(Q'*Q - eye(n, n), Inf)

disp("Norma inf QR - A");
norm(Q*R - A, Inf)

endfunction
