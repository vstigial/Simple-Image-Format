from math import sqrt

center_x, center_y = 1027, 627  # center of the face (middle of smiley)
radius = 100  # radius of the circular face
eye_offset_x, eye_offset_y = 35, 30  # horizontal and vertical offset for eyes
eye_radius = 10  # radius for the eyes
mouth_radius = 50  # radius for the mouth curve (arc shape)
mouth_thickness = 3  # thickness of the mouth curve

with open("output.txt", "w") as file:
    for i in range(255):
        for x in range(500):
            pixel_x = 900 + i
            pixel_y = 500 + x

            dx_face = pixel_x - center_x
            dy_face = pixel_y - center_y
            distance_from_center = sqrt(dx_face ** 2 + dy_face ** 2)
            if distance_from_center <= radius:
                file.write(f"{pixel_x} {pixel_y} (255, 255, 0)\n")

            left_eye_dx = pixel_x - (center_x - eye_offset_x)
            left_eye_dy = pixel_y - (center_y - eye_offset_y)
            left_eye_distance = sqrt(left_eye_dx ** 2 + left_eye_dy ** 2)
            if left_eye_distance <= eye_radius:
                file.write(f"{pixel_x} {pixel_y} (0, 0, 0)\n")

            right_eye_dx = pixel_x - (center_x + eye_offset_x)
            right_eye_dy = pixel_y - (center_y - eye_offset_y)
            right_eye_distance = sqrt(right_eye_dx ** 2 + right_eye_dy ** 2)
            if right_eye_distance <= eye_radius:
                file.write(f"{pixel_x} {pixel_y} (0, 0, 0)\n")

            mouth_dx = pixel_x - center_x
            mouth_dy = pixel_y - (center_y + eye_offset_y)
            mouth_distance = sqrt(mouth_dx ** 2 + mouth_dy ** 2)
            if mouth_radius - mouth_thickness <= mouth_distance <= mouth_radius + mouth_thickness and mouth_dy > 0:
                file.write(f"{pixel_x} {pixel_y} (255, 0, 0)\n")
