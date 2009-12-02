function mplot = INC(Spectr, m, n)
  ## we must cycle over the square M x N and assign the 2D fft to each of the values
  for x = 1 : m
    for y = 1 : n
      ## one smaller square
      subplot(x, y, x*y)
      fplot(fft2(Spectr(x : x + m, y : y + m)))
    endfor
  endfor
endfunction


## FIRST problem, no "rgb2gray" present on octave
## imread and imshow are working
img = imread("WorldChampions.png");

## we get the image as a matrix


## Second argument of imshow is the range limit given as vector
## mm no the display range is not so interestingma
imshow("WorldChampions.png")