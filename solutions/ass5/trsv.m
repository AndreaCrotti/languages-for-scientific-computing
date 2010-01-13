#!/usr/bin/octave --persist

# range used to plot the error
dim_range = 3:1:10;

## Taking a triangular lower matrix L as input
## we want to find x such that Lx = y
## Find out how the triangular linear system actually works

## With blocking we need to call recursively TRSV on the inner block
function x = trsv(L, y, b, alg)
  ## No sanity check of the input, assuming is always correct

  x = zeros(length(L), 1); # gets always overwritten

  ## setting initial values
  Ltl = L(1:0, 1:0);
  Lbl = L(:, 1:0);
  Lbr = L(:, :);
  
  xt = x(1:0);
  xb = x(:);
  yt = y(1:0);
  yb = y(:);

  while size(Ltl) < size(L)
    ## partitioning
    L00 = Ltl;
    ## FIXME: when b > 1 this doesn't work
    ## getting an error with the columns dimensions
    L01 = zeros(rows(L00), 1:b);
    L11 = Lbr(1:b, 1:b);
    L10 = Lbl(1:b, :); 
    L20 = Lbl(b+1:end, :);
    L21 = Lbr(b+1:end, 1:b);
    L22 = Lbr(b+1:end, b+1:end);

    x0 = xt;
    x1 = xb(1:b);
    x2 = xb(b+1:end);

    y0 = yt;
    y1 = yb(1:b);
    y2 = yb(b+1:end);
    
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
    ## BUG, L01 can't be simply 0
    Ltl = [ [ L00 L01 ]  ; [ L10 L11 ]];
    Lbl = [ L20  L21 ];
    Lbr = L22;

    xt = [ [x0] ; [x1] ];
    xb = x2;

    yt = [ [y0] ; [y1] ];
    yb = y2;
  endwhile
  x = xt; # finally getting the result in x

endfunction

function err = error(L, y, b, alg)
  x = trsv(L, y, b, alg);
  ## froebius norm is needed to make sure we always get a scalar
  err = norm(L * x - y, "fro");
  
endfunction

# general parameters
hold on;
grid on;
title("analysis of trsv precision");
xlabel("dimension");
ylabel("error");

for b = 1:1
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
#    err1
 #   err2
  #  err3
    # this should put in a for loop
    plot(dim_range, err1, sprintf("+-%d;b=%d,alg=%d,mat=1;", 1*b, b, alg));
    plot(dim_range, err2, sprintf("+-%d;b=%d,alg=%d,mat=2;", 2*b, b, alg));
    plot(dim_range, err3, sprintf("+-%d;b=%d,alg=%d,mat=3;", 3*b, b, alg));
  endfor
endfor

