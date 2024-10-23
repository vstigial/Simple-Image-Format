## An uncompressed, human readable format for storing images. Inspired by Wavefront obj.

Planning to implement a simple GUI editor for this format.

This program currently only draws the data directly to the screen using `SetPixel`.
```
This is the data for one pixel. It's location on the screen is 900, 500. 900 is the x value of the pixel on the display, and 500 is the y value. (1, 2, 3) is the RGB color of the pixel.
900 500 (1, 2, 3)
```

# Examples

Some Examples are located in the `imgs` folder. 

### `2col.txt` 
This file draws 10 pixels on the screen, 2 rows with 5 pixels in each row. A gradient from black to blue is drawn.

### `smile.txt`
This file draws a simple smile to the screen.

### `largegradient.txt`
An enlarged version of 2col.txt.

### `test1.txt`
A gradient using all 0-255 values of blue. One pixel tall.

# Generators
Take a look at the `gen` folder to see the python scripts used for generating the examples in the `imgs` folder.

