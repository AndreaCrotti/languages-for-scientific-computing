function M = P(n,p)
 
  M = eye(n);
  m = n/p;
  v = zeros(n,1);


  for j=1:p
    v((j - 1) * m+1:j * m) = j:p:n;
    end

    M = M(v,:);
   
endfunction