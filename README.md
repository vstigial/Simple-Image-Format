## An uncompressed, human readable format for storing images. Inspired by Wavefront obj.

Planning to implement a simple GUI editor for this format.

This program draws data pixel by pixel to a GLFW window with OpenGL.
```
This is the data for one pixel. 
Its location on the window is 900, 500.
900 is the x value of the pixel on the display, and 500 is the y value. 
(1, 2, 3) is the RGB color of the pixel.

900 500 (1, 2, 3)
```

# Examples

All image files are located in the `imgs` folder. 

### `2col.txt` 
This file draws 10 pixels on the window, 2 rows with 5 pixels in each row. A gradient from black to blue is drawn.

### `smile.txt`
This file draws a simple smile to the window.

### `largegradient.txt`
An enlarged version of 2col.txt.

### `test1.txt`
A gradient using all 0-255 values of blue. One pixel tall.

# Generators
Take a look at the `gen` folder to see the python scripts used for generating the examples in the `imgs` folder.

