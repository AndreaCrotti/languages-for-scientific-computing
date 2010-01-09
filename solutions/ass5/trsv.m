#!/Applications/Octave.app/Contents/Resources/bin/octave
## Taking a triangular lower matrix L as input
## we want to find x such that Lx = y
## Find out how the triangular linear system actually works

## With blocking we need to call recursively TRSV on the inner block
## if necessary
function x = trsv(L, y, b, alg)
  len = length(L);
  req = len / b;
  ## this could be whatever, after I overwrite any value present
  x = 1:len
  for idx = 0:req
    step = idx
    s = idx * b;
    ## avoiding overflow when b > 1
    if s > len
      s = len
    endif
    
    Ltl = L(1:s, 1:s)
    Lbl = L(s+1:len, 1:s)
    Lbr = L(s+1:len, s+1:len)

    ## but where do I instantiate x?
    xt = x(1:s)
    xb = x(s+1:len)

    yt = y(1:s)
    yb = y(s+1:len)

    L00 = Ltl
    L10 = Lbl(

    ## math part
    if alg == 1
      y(1) = y(1) - L(1,0) * y(0)
      x(1) = inverse(L(1,1)) * y(1)
    endif
    if alg == 2
      x(1) = inverse(L(1,1)) * y(1)
      y(2) = y(2) - L(2,1) * x(1)
    endif
    
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
dim = 4
y = 1:dim
m1 = tril(rand(dim))
TRSV(m1, y, 1, 0)