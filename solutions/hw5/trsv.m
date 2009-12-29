## Taking a triangular lower matrix L as input
## we want to find x such that Lx = y
## Find out how the triangular linear system actually works

function x = TRSV(L, y, b, alg)
  ## partitioning
  ## it's also square so we compute only once the half
  ## TODO: check that the dimension is even
  half = length(L) / 2
  LTL = L(1:half, 1:half)
  LBL = L(1:half, half+1:length(L))
  LBR = L(half : length(L(1:)), half+1:length(L))

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
      return 0
    endif
  endfor

endfunction

## check the accuracy of what we've computed plotting the different results
