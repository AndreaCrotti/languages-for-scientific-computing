function M = D (k, n)

  D = [];
  for j = 0 : n - 1
    D (j + 1, j + 1) = exp (-2 * pi * i * j / n / k);
  endfor
    
  M = [];
  for a = 0 : k - 1
    M (1 + n * a : n * (a + 1), 1 + n * a : n * (a + 1)) = D ^ a;
  endfor

endfunction

    
      