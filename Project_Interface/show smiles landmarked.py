import FaceLandMarks
import cv2
import os


def stretch_and_align_points(points):
    new_max_x = 500
    new_min_x = 0
    new_max_y = 500
    new_min_y = 0

    x_values = [point[0] for point in points]
    y_values = [point[1] for point in points]

    min_x = min(x_values)
    max_x = max(x_values)
    min_y = min(y_values)
    max_y = max(y_values)

    stretched_points = []
    for point in points:
        new_x = int((((point[0] - min_x) / (max_x - min_x)) * (new_max_x - new_min_x) + new_min_x))
        new_y = int((((point[1] - min_y) / (max_y - min_y)) * (new_max_y - new_min_y) + new_min_y))
        stretched_points.append([new_x, new_y])

    return stretched_points


detector = FaceLandMarks.FaceLandMarks()


def pick_points(points,
                indexes_to_extract=[463, 263, 133, 33, 1, 2, 98, 327, 0, 61, 17, 291, 152, 447, 366, 401, 227, 137, 177,
                                    10]):
    points = [points[idx] for idx in indexes_to_extract]
    return points


def create_database_from(addr: str):
    frame = cv2.imread(addr)
    image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    image_org = image.copy()
    detector = FaceLandMarks.FaceLandMarks()

    image2, faces = detector.findFaceLandmark(image)
    points = pick_points([[int(point[0]), int(point[1])] for point in faces[0]] ) # stretch_and_align_points(faces[0])

    # Define the desired width and height for the resized image
    desired_width = 500
    desired_height = 500

    # Draw the points on the image
    for point in points:
        cv2.circle(image_org, (point[0], point[1]), 20, (230, 0, 255), -1)  # Draws a green circle of radius 5
        # at each
        # point
    # Resize the image
    resized_image = cv2.resize(image_org, (desired_width, desired_height))
    resized_image = cv2.cvtColor(resized_image, cv2.COLOR_BGR2RGB)
    cv2.imshow("smile", resized_image)
    cv2.waitKey(0)


def load_n_images_to_matrix(directory_path):
    # Dictionary to store image names grouped by number
    images_by_number = {}

    for filename in os.listdir(directory_path):
        file_path = os.path.join(directory_path, filename)

        # Check if it's a file
        if os.path.isfile(file_path):
            # Split the filename by "_"
            name_parts = filename.split("_")

            # Check if there are at least 4 parts and if the 4th part is neither "h" nor "n"
            if len(name_parts) >= 2 and name_parts[3] in ["h", "n"]:
                # Extract the number from the filename
                number = name_parts[0]

                # Create a key for this number if it doesn't exist
                if number not in images_by_number:
                    images_by_number[number] = []

                # Add the filename to the list for this number
                images_by_number[number].append(filename)

    # Create a matrix with rows containing 4 images with the same number
    matrix = []
    for number, filenames in sorted(images_by_number.items(), key=lambda x: (int(x[0]), x[0][1] != 'n')):
        matrix.extend([[int(number)] + filenames[i:i + 2] for i in range(0, len(filenames), 2)])

    return matrix


if __name__ == '__main__':
    # Specify the directory containing the images
    image_directory = './for_smile_images'

    # Get a list of all files in the directory
    file_list = os.listdir(image_directory)

    # Filter the list to include only image files (you can add more image extensions if needed)
    image_files = [file for file in file_list if file.lower().endswith(('.png', '.jpg', '.jpeg', '.gif', '.bmp'))]

    # Create an array to store the image paths
    image_paths = [os.path.join(image_directory, image_file) for image_file in image_files]

    for addr in image_paths:
        create_database_from(addr)
