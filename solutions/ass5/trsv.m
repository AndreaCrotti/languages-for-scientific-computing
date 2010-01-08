#!/Applications/Octave.app/Contents/Resources/bin/octave
## Taking a triangular lower matrix L as input
## we want to find x such that Lx = y
## Find out how the triangular linear system actually works

function x = TRSV(L, y, b, alg)
  len = length(L);
  req = len / b;
  for idx = 1:req
    step = idx
    s = idx * b;
    ## avoiding overflow
    if s > len
      s = len
    endif

    Ltl = L(1:s, 1:s)
    Lbl = L(s+1:len, 1:s)
    Lbr = L(s+1:len, s+1:len)
  endfor
    
endfunction

function passed = test_TRSV()
  ## Testing my function, returns true if satisfied
  dim = 10
  m1 = rand(dim)
  m2 = rand(dim) + eye(dim)
  m3 = randn(dim)

  for i = m1, m2, m3
    if TRSV(i, y, i, 1) != TRSV(i, y, i, 2)
      printf("something wrong happened")
      return
    endif
  endfor
  return
endfunction

## check the accuracy of what we've computed plotting the different results
y = 1:10
m1 = tril(rand(10))
TRSV(m1, y, 1, 0)