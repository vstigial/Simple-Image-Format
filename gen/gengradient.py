max_gradient = 256 # this value should not exceed 256 or go below 0 (this is the width of the drawing and the color of each pixel)
height = 500       # height of the drawing, should not go negative
offset_x = 900     # where the drawing start
offset_y = 500     # where the drawing starts

with open("output.txt", "w") as file:
    for i in range(max_gradient):
        for x in range(height):
            file.write(f"{str(offset_x+i)} {str(offset_y+x)} (1, 1, {str(i)})\n")
