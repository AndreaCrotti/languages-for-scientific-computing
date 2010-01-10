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
  ## the condition on size(Ltl) is automatically fulfilled here 
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

    if (length(Ltl) == len)
      return
    endif

    ## but where do I instantiate x?
    xt = x(1:s)     
    xb = x(s+1:len) 
     		      
    yt = y(1:s)     
    yb = y(s+1:len) 

    ## setting variables needed for both algorithms
    L11 = Lbr(1:b, 1:b)
    x1 = xb(1:b)
    y1 = yb(1:b)
    ## FIXME: the inverse when B is large should not be used

    ## math part, choosing which algorithm to execute
    if alg == 1
      L10 = Lbl(1:b, 1:columns(Lbl))
      y0 = yt

      y(1) = y1 - L10 * x(0)
      x(1) = inverse(L11) * y1
    endif

    if alg == 2
      L21 = Lbr(1:b, b+1:columns(Lbr))
      y2 = yb(b+1:length(yb))
      
      x(1) = inverse(L11) * y1
      y(2) = y2 - L21 * x1
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
trsv(m1, y, 1, 1)