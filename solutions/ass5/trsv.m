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
    ## partitioning
    L00 = Ltl;
    L10 = Lbl(1:b, :);
    L20 = Lbl(b+1:end, :);
    L11 = Lbr(1:b, 1:b);
    L21 = Lbr(b+1:end, 1:b);
    L22 = Lbr(b+1:end, b+1:end);

    x0 = xt;
    x1 = xb(1:b);
    x2 = xb(b+1:end);

    y0 = yt;
    y1 = yb(1:b);
    y2 = yb(b+1:end);
    
    ## TODO: pass to unblocked algorithm?
    ## math part, choosing which algorithm to execute
    if (alg == 1)
      y1 = y1 - L10 * x0;

      ## when we have a matrix instead of inverting we call recursively trsv
      ## the inner calls are now unblocked
      if (b > 1)
	x1 = trsv(L11, y1, 1, alg);
      else
	x1 = L11^(-1) * y1;
      endif

    endif

    if (alg == 2)
      if (b > 1)
	x1 = trsv(L11, y1, 1, alg);
      else
	x1 = L11^(-1) * y1;
      endif
      y2 = vec(y2) - L21 * x1; ## here vec is needed to force a column vector

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

function err = error(L, y, b, alg)
  x = trsv(L, y, b, alg);
  ## froebius norm is needed to make sure we always get a scalar
  err = norm(L * x - y, "fro");
  if (err > 1)
    printf("length(L) = %d and err = %f\n", length(L), err);
  endif
    
endfunction

function test_trsv(dim, alg)
  ## Testing my function, returns true if satisfied
  ## matrices to test
  m1 = tril(rand(dim));
  m2 = tril(rand(dim) + eye(dim));
  m3 = tril(randn(dim));
  y = randn(dim, 1);

  error(m1, y, 1, alg)
  error(m2, y, 1, alg)

endfunction

## get the error of the algorithm and plot it nicely
## x = problem size
## y = error (different lines for different problem)
## Plotting should contain also the precision working with the different kind of matrices
function gen_plot(range, err1, err2)
  xlabel('dimension');
  ylabel('error');
  ## why ignoring extra labels?
  legend('alg 1', 'alg 2');
  grid on;

  ## maybe using saveas is better?
  plot(range, err1, err2)
endfunction

# 
dim_range = 2:2:100;

## those 4 indented loops are needed to make the code more elegant and avoid
## creating a thousand variables

hold on;
grid on;
for b = 1:2
  ## adding info about what algorithm and if blocked/non blocked code
  for alg = 1:2
    xax = 1;
    for dim = dim_range
      y = rand(dim, 1);
      m1 = tril(rand(dim));
      m2 = tril(rand(dim) + eye(dim));
      m3 = tril(randn(dim));	  
      err1(xax) = error(m1, y, b, alg);
      err2(xax) = error(m2, y, b, alg);
      err3(xax) = error(m3, y, b, alg);
      xax = xax + 1;
    endfor
    err1
    err2
    err3
#    plot(dim_range, err2);
#    plot(dim_range, err3);
  endfor			
endfor


#gen_plot(range, err11, err12, err13, err21, err22, err23)