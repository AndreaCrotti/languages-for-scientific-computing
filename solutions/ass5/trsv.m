#!/usr/bin/env octave --persist

## Taking a triangular lower matrix L as input
## we want to find x such that Lx = y
## Find out how the triangular linear system actually works

## With blocking we need to call recursively TRSV on the inner block
## if necessary
function x = trsv(L, y, b, alg)
  ## No sanity check of the input, assuming is always correct

  len = length(L);
  ## this could be whatever, after I overwrite any value present
  x = rand(len, 1)
  ## the condition on size(Ltl) is automatically fulfilled here 
  for idx = 0:(len/b)
    s = idx * b;
    ## avoiding overflow when b > 1
    if s > len
      s = len
    endif
    
    Ltl = L(1:s, 1:s);
    Lbl = L(s+1:len, 1:s);
    Lbr = L(s+1:len, s+1:len);

    if (length(Ltl) == len)
      return
    endif

    ## partition x and y
    xt = x(1:s);
    xb = x(s+1:len);
     		      
    yt = y(1:s);
    yb = y(s+1:len);

    ## setting variables needed for both algorithms
    L11 = Lbr(1:b, 1:b);
    x1 = xb(1:b);
    y1 = yb(1:b);
    x0 = xt;

    ## TODO: pass to unblocked algorithm in case b == 1
    ## math part, choosing which algorithm to execute
    if (alg == 1)
      L10 = Lbl(1:b, 1:columns(Lbl));
      y0 = yt;

      y(1) = y1 - L10 * x0;

      ## when we have a matrix instead of inverting we call recursively trsv
      if (b > 1)
	x(1) = trsv(L11, y1, b, alg);
      else
	x(1) = L11^(-1) * y1;
      endif

    endif

    if (alg == 2)
      L21 = Lbr(1:b, b+1:columns(Lbr));
      y2 = yb(b+1:length(yb));
      
      if (b > 1)
	x(1) = trsv(L11, y1, b, alg);
      else
	x(1) = L11^(-1) * y1;
      endif
      x1
      L21
      y(2) = y2 - L21 * x1;

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
  endfor
endfunction


## get the accuracy and print it nicely
## x = problem size
## y = accuracy (different lines for different problem)

function acc = accuracy(L, y, b, alg)
  x = trsv(L, y, b, alg)
  acc = norm(L * x - y)
endfunction

function gen_plot(b)
  idx = 1
  range = 10:10:100
  for d = range
    mat = tril(rand(d))
    ## generate also a random vector instead
    y = 1:d
    acc1(idx) = accuracy(mat, y, 1, 1)
    acc2(idx) = accuracy(mat, y, 1, 1)
  endfor

  # only one figure or more plots?
  xlabel('dimension');
  ylabel('accuracy');
  legend('alg 1', 'alg 2');
  grid on;

  ## maybe using saveas is better?
  plot(range, acc1, acc2);

endfunction

l1 = [[1 0]; [1 1]]
##y1 = rand(2, 1)
y1 = vec([1 1])
acc = accuracy(l1, y1, 1, 1)

acc2 = accuracy(l1, y1, 1, 2)