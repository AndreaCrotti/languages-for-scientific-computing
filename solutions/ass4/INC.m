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


## FIRST problem, no "rgb2gray" present on octave
## imread and imshow are working
imread("WorldChampions.png")
imshow("WorldChampions.png")
