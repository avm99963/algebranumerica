function [coeff, norm2_res] = polminquad_marta(x, y, m)
format long;
n = length(x);

M = ones(n, m+1);

% Fem QR.
% Creem matriu M (phis)
for j = 2:(m+1) 
  M(:, j) = x.^(j-1)'; % agafem columna j (col j fixa, totes les files ':' )
endfor

Q = M;
R = zeros(m+1, m+1);

% IMPLEMENTACIO ALGORITME QR

for k = 1:(m+1) #per cada columna
  R(k, k) = norm(Q(:, k)); #r_kk ï¿½s la norma del k vector columna de M
  Q(:,k) = Q(:, k)/R(k,k); #columna q_k normalitzada

  for i = (k+1):(m+1) #per les columnes q i r de la dreta de l'actual k, hem de calcular rs i qs
    R(k, i) = Q(:,k)'*Q(:, i); #calculem r_ki, les r de la dreta de la r diagonal
    Q(:,i) = Q(:, i) - R(k, i)*Q(:, k); # per les columnes a la seva dreta, hem de normalitzar-les respecte la q_k actual
  endfor

endfor

Q;
R;

% RESOLEM SISTEMA (triangular superior) R*a = Q'*y

b = Q'*y';

for k = (m+1):-1:1
  coeff(k) = b(k);
  for i = (k+1):(m+1)
    coeff(k) -= R(k,i)*coeff(i);
  endfor
  coeff(k) /= R(k,k);
endfor

coeff;

% NORMA_inf (de Qt*Q - Id) = max ( sum (els de cada fila en val abs) )

res_inf = Q'*Q - eye(m+1, m+1); % matriu residu
for i = 1:(m+1) 
  norm_inf_vec(i) = sum(abs(res_inf(i,(1:(m+1))))); % suma de cada fila
endfor
norm_inf = max(norm_inf_vec); % la norma_inf és el màxim de la suma de les files
disp(sprintf("norm_inf of || Qt*Q - Id || : %ld ", norm_inf));

% NORMA_2 (de M*coeff - y) = sqrt( sum ( (x_i)^2 ) )

res_2 = M*coeff' - y'; % vector residu
res_2 = res_2.^2; % elevem cada component al quadrat
norm2_res = sum(res_2(1:n)); % sumem les components
norm2_res = power(norm2_res, 1/2); % fem l'arrel quadrada
disp(sprintf("norm_2 of || M*x - y || : %ld ", norm2_res));


endfunction

