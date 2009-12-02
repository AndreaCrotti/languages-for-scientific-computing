function mplot = INC(Spectr, m, n)
  ## we must cycle over the square M x N and assign the 2D fft to each of the values
  for x = 1 : m
    for y = 1 : n
      ## one smaller square
      subplot(x, y, x*y)
      fplot(fft2(Spectr(x, y)))
    endfor
  endfor
endfunction