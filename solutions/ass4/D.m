############################
# Twiddle factor function  #
############################

function M = D (k, n)

  F = [];
  for j = 0 : n - 1
    F (j + 1, j + 1) = exp (-2 * pi * i * j / n / k);
  endfor
    
  M = [];
  for a = 0 : k - 1
    M (1 + n * a : n * (a + 1), 1 + n * a : n * (a + 1)) = F ^ a;
  endfor

endfunction