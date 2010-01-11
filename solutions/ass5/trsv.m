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
  x = zeros(len, 1);

  ## setting initial values
  Ltl = L(1:0, 1:0);
  Lbl = L(1:len, 1:0);
  Lbr = L(1:len, 1:len);
  
  xt = x(1:0);
  xb = x(1:len);
  yt = y(1:0);
  yb = y(1:len);

  while size(Ltl) < size(L)
    L00 = Ltl;
    L10 = Lbl(1:b, :);
    L20 = Lbl(b+1:rows(Lbl), :);
    L11 = Lbr(1:b, 1:b);
    L21 = Lbr(b+1:rows(Lbr), 1:b);
    L22 = Lbr(b+1:rows(Lbr), b+1:columns(Lbr));

    x0 = xt;
    x1 = xb(1:b);
    x2 = xb(b+1:length(xb));

    y0 = yt;
    y1 = yb(1:b);
    y2 = yb(b+1:length(yb));
    
    ## TODO: pass to unblocked algorithm?
    ## math part, choosing which algorithm to execute
    if (alg == 1)
      y1 = y1 - L10 * x0;

      ## when we have a matrix instead of inverting we call recursively trsv
      if (b > 1)
	x1 = trsv(L11, y1, b, alg);
      else
	x1 = L11^(-1) * y1;
      endif

    endif

    if (alg == 2)
      if (b > 1)
	x1 = trsv(L11, y1, b, alg);
      else
	x1 = L11^(-1) * y1;
      endif
      y2
      L21
      x1
      ## FIXME: Still an error here of nonconformant operators
      y2 = y2 - L21 * x1;

    endif

    ## continue with part
    Ltl = [[ L00 zeros(rows(L00), columns(L11)) ] ; [ L10 L11 ]];
    Lbl = [ L20  L21 ];
    Lbr = L22;

    xt = [ [x0] ; [x1] ];
    xb = x2;

    yt = [ [y0] ; [y1] ];
    yb = y2;
  endwhile
  ## this is the result in the end
  x = xt;
endfunction

function acc = accuracy(L, y, b, alg)
  x = trsv(L, y, b, alg);
  acc = norm(L * x - y);
  if (acc > 1)
    printf("length(L) = %d and acc = %f\n", length(L), acc);
  endif
    
endfunction

function test_trsv(dim, alg)
  ## Testing my function, returns true if satisfied
  ## matrices to test
  m1 = tril(rand(dim));
  m2 = tril(rand(dim) + eye(dim));
  m3 = tril(randn(dim));
  y = randn(dim, 1);

  accuracy(m1, y, 1, alg)
  accuracy(m2, y, 1, alg)

endfunction

## get the accuracy of the algorithm and plot it nicely
## x = problem size
## y = accuracy (different lines for different problem)
function gen_plot(range, acc1, acc2)
  xlabel('dimension');
  ylabel('accuracy');
  ## why ignoring extra labels?
  legend('alg 1', 'alg 2');
  grid on;

  ## maybe using saveas is better?
  plot(range, acc1, acc2)
endfunction

range = 2:10:100;
idx = 1
for d = range
  mat = tril(rand(d));
  y = rand(d, 1);
  acc1(idx) = accuracy(mat, y, 1, 1);
  idx += 1;
endfor

##gen_plot(range, acc1, acc1)