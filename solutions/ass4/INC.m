## FIXME: we get this problem error: A(I): Index exceeds matrix dimension.
## check the indexes

function mplot = INC(Spectr, m, n)
  mplot = zeros(rows (Spectr), columns (Spectr));
  ## we must cycle over the square M x N and assign the 2D fft to each of the values
  for x = 1 : m : rows(Spectr)
    for y = 1 : n : columns(Spectr)
      ## one smaller square
      ## FIXME: HERE goes out of bounds
      A = Spectr(x : x + m - 1, y : y + n - 1);
      ##mplot(x : x + m - 1, y : y + n - 1) = fft2(A);
      ## divide the "screen"
      subplot(x, y, x*y)
      ## If I understood correctly we should create an image
      ## split in M x N small images as the professor showed in class
      fplot(fft2(A))
    endfor
  endfor
endfunction


## no "rgb2gray" present on octave, we can do
## as given here http://www.montefiore.ulg.ac.be/~piater/Cours/octave+matlab.php

img = sum(double(imread("WorldChampions.png")), 3);

## we get the image as a matrix
newimg = INC(fft2(img), 2, 2);

## Necessary also to use abs to go
## abs can also convert entire matrices
imshow(abs(newimg));