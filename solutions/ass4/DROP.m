## FIXME: infinite loop maybe?
## Usage:
## img = imread("img")
## newimg = DROP(img, k)
## imshow(newimg)

function image = DROP(img, k)

  ## usage: DROP (img, k)
  ## takes a matrix img and return an image with all
  ## the frequencies outside disk of radius k dropped

  ff = fft2(img);
  ## see here http://www.owlnet.rice.edu/~elec301/Projects01/image_filt/matlab.html
  ## arranging low frequencies to the middle
  ff = fftshift(ff);

  ## create a new matrix of 0, we'll then fill in the taken values from ff
  ## which are inside the circle
  newmat = zeros(rows(ff), columns(ff));

  ## to check if something in in the circle we can use the formula
  ## (x - cx)^2 + (y - cy)^2 <= r^2
  ## where the radius is given by the norm
  cx = rows(ff) / 2;
  cy = columns(ff) / 2;
  r = rows(ff) * k;

  ## If we're sure that the matrix is square we can maybe simplify
  for x = 1 : rows(ff)
    for y = 1 : columns(ff)
      if ((x - cx)^2 + (y - cy)^2 <= r^2)
	newmat(x, y) = ff(x, y);
      endif
    endfor
  endfor
  
  ## returning the inverse ttf
  image = ifft2(newmat);
endfunction
