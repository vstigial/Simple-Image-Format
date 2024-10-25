from math import sqrt

center_x, center_y = 1027, 627  # center of the face (middle of smiley)
radius = 100  # radius of the circular face
eye_offset_x, eye_offset_y = 35, 30  # horizontal and vertical offset for eyes
eye_radius = 10  # radius for the eyes
mouth_radius = 50  # radius for the mouth curve (arc shape)
mouth_thickness = 3  # thickness of the mouth curve

compression = False # generate the compressed version of an image file

face_pixels = []
left_eye_pixels = []
right_eye_pixels = []
mouth_pixels = []

def write_ranges(pixels, color, file):
    if not pixels:
        return
    pixels.sort()
    start_x, start_y = pixels[0]
    end_x, end_y = start_x, start_y
    for x, y in pixels:
        if x == end_x and y == end_y + 1:
            end_y = y
        elif x == end_x and y == end_y:
            continue
        else:
            file.write(f"{start_x}-{end_x + 1} {start_y}-{end_y + 1} {color}\n")
            start_x, start_y = x, y
            end_x, end_y = x, y
    file.write(f"{start_x}-{end_x + 1} {start_y}-{end_y + 1} {color}\n")

with open("output.txt", "w") as file:
    for i in range(255):
        for x in range(500):
            pixel_x = 900 + i
            pixel_y = 500 + x

            dx_face = pixel_x - center_x
            dy_face = pixel_y - center_y
            distance_from_center = sqrt(dx_face ** 2 + dy_face ** 2)

            if distance_from_center <= radius:
                if compression:
                    face_pixels.append((pixel_x, pixel_y))
                else:
                    file.write(f"{pixel_x} {pixel_y} (255, 255, 0)\n")

            left_eye_dx = pixel_x - (center_x - eye_offset_x)
            left_eye_dy = pixel_y - (center_y - eye_offset_y)
            left_eye_distance = sqrt(left_eye_dx ** 2 + left_eye_dy ** 2)

            if left_eye_distance <= eye_radius:
                if compression:
                    left_eye_pixels.append((pixel_x, pixel_y))
                else:
                    file.write(f"{pixel_x} {pixel_y} (0, 0, 0)\n")

            right_eye_dx = pixel_x - (center_x + eye_offset_x)
            right_eye_dy = pixel_y - (center_y - eye_offset_y)
            right_eye_distance = sqrt(right_eye_dx ** 2 + right_eye_dy ** 2)

            if right_eye_distance <= eye_radius:
                if compression:
                    right_eye_pixels.append((pixel_x, pixel_y))
                else:
                    file.write(f"{pixel_x} {pixel_y} (0, 0, 0)\n")

            mouth_dx = pixel_x - center_x
            mouth_dy = pixel_y - (center_y + eye_offset_y)
            mouth_distance = sqrt(mouth_dx ** 2 + mouth_dy ** 2)

            if mouth_radius - mouth_thickness <= mouth_distance <= mouth_radius + mouth_thickness and mouth_dy > 0:
                if compression:
                    mouth_pixels.append((pixel_x, pixel_y))
                else:
                    file.write(f"{pixel_x} {pixel_y} (255, 0, 0)\n")

    if compression:
        write_ranges(face_pixels, "(255, 255, 0)", file)
        write_ranges(left_eye_pixels, "(0, 0, 0)", file)
        write_ranges(right_eye_pixels, "(0, 0, 0)", file)
        write_ranges(mouth_pixels, "(255, 0, 0)", file)
