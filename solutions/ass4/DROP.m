function image = DROP(img, k)

  ## usage: DROP (img, k)
  ## takes a matrix img and return an image with all
  ## the frequencies outside disk of radius k dropped

  ff = fft2(img)
  ## see here http://www.owlnet.rice.edu/~elec301/Projects01/image_filt/matlab.html
  ## arranging low frequencies to the middle
  ff = fftshift(ff)

  ## dropping frequencies outside radius k
  
  ## in this way returning the new function
  image = ifft2(ff)
endfunction