function mplot = INC(Spectr, m, n)
  mplot = zeros(rows (Spectr), columns (Spectr));
  ## we must cycle over the square M x N and assign the 2D fft to each of the values
  for x = 1 : m : rows(Spectr)
    for y = 1 : n : columns(Spectr)
      ## one smaller square
      A = Spectr(x : x + m - 1, y : y + n - 1);
      mplot(x : x + m - 1, y : y + n - 1) = fft2(A);
    endfor
  endfor
endfunction


## no "rgb2gray" present on octave, we can do
## as given here http://www.montefiore.ulg.ac.be/~piater/Cours/octave+matlab.php

img = sum(double(imread("WorldChampions.png")), 3)

## we get the image as a matrix


## Second argument of imshow is the range limit given as vector
## mm no the display range is not so interestingma
imshow("WorldChampions.png")