# Cub3d

## Raycasting

### Introduction

Raycasting is a fundamental technique used in computer graphics to render 3D environments in real-time. It simulates the behavior of light rays to determine what objects or surfaces are visible from a specific point of view. This technique has been widely used in various applications, including video games, architectural visualization, and virtual reality. One of the most notable early examples of raycasting in video games is the iconic game Wolfenstein 3D, released in 1992.

Raycasting gained popularity during the early days of gaming due to its efficient use of computational resources. In 1992, powerful machines were not as readily available, and raycasting provided a clever alternative to more computationally expensive rendering techniques. Compared to methods like ray tracing or polygonal rendering, raycasting consumes considerably less CPU resources, making it well-suited for creating immersive 3D experiences on limited hardware.

### About the Project
This project is a 3D application that utilizes raycasting to render interactive environments. The implementation of raycasting allows for the creation of a realistic first-person perspective, enabling the user to navigate and interact with the virtual world.

### Raycasting Logic
The raycasting algorithm implemented in this project follows the following steps:

0. **Raycaster Loop**: The raycaster_loop function serves as the main loop for the raycasting process. It iterates over each pixel column of the screen and performs the necessary calculations to cast rays and render the 3D environmentent'''
 ```
 void raycaster_loop(t_raycaster *rc, t_data *data, t_frame *frame) {
    rc->screen_x = 0;
    while (rc->screen_x < SCREEN_WIDTH) {
        // Raycasting steps and calculations
        calculate_ray_position(rc);
        calculate_ray_direction(rc, data);
        rc->map_x = (int)data->pos_x;
        rc->map_y = (int)data->pos_y;
        set_delta_dist(rc);
        calculate_ray_step(rc);
        calculate_side_dist(rc, data);
        dda_loop(rc, data);
        set_wall_texture(rc, data, frame);
        calculate_camera_dist(rc);
        calculate_wall_data(rc);
        set_wall_pixel_x(rc, data);
        buffer_ceil_v_line(rc, data, frame);
        buffer_floor_v_line(rc, data, frame);
        set_texture_x(rc, data);
        buffer_wall_v_line(rc, data, frame);
        
        rc->screen_x++;
    }
    return;
}
 ```
1. **Calculate Ray Position**: The position of the ray is determined based on the screen coordinates. This step calculates the x-coordinate of the ray's position in the virtual camera space.
```
void calculate_ray_position(t_raycaster *rc) {
    rc->camera_x = 2 * rc->screen_x / (double)(SCREEN_WIDTH) - 1;
    return;
}
```
Explanation:

The function calculate_ray_position takes a t_raycaster structure pointer (rc) as an input parameter.
rc->screen_x represents the current x-coordinate of the screen pixel being processed.
SCREEN_WIDTH refers to the total width of the screen.
The calculation 2 * rc->screen_x / (double)(SCREEN_WIDTH) - 1 maps the screen coordinates to a range between -1 and 1. This is achieved by dividing rc->screen_x by SCREEN_WIDTH to normalize the value to the range [0, 1], then scaling it by 2 and subtracting 1 to obtain the range [-1, 1].
The resulting value is stored in rc->camera_x, representing the x-coordinate of the ray's position in the virtual camera space.
This calculation is essential for determining the initial position of the ray in the 3D environment and is used as a starting point for the raycasting process.

2. **Calculate Ray Direction**: [Add the description for this step]
After determining the position of the ray in the virtual camera space, we need to calculate the direction in which the ray will be cast. This is essential for accurately rendering the 3D environment. In the calculate_ray_direction function, the ray's direction vector is calculated based on the player's viewing direction and camera position.

```
void calculate_ray_direction(t_raycaster *rc, t_data *data) {
    rc->ray_dir_x = data->dir_x + data->plane_x * rc->camera_x;
    rc->ray_dir_y = data->dir_y + data->plane_y * rc->camera_x;
    return;
}
```
The calculation involves adding the player's viewing direction (data->dir_x and data->dir_y) to the camera plane values (data->plane_x and data->plane_y) scaled by the ray's position in the virtual camera space (rc->camera_x). The resulting values, rc->ray_dir_x and rc->ray_dir_y, represent the x and y components of the ray's direction vector.

This calculation determines the direction in which the ray will be cast from the player's position, enabling us to determine what objects or surfaces the ray will intersect in the 3D environment. The accurate calculation of the ray's direction is crucial for achieving realistic rendering and interaction within the virtual world.

By correctly setting the ray's direction, we ensure that the rays traverse the environment in the desired manner, providing an immersive and visually accurate representation of the 3D scene.

3. **Set Delta Dist**: [Add the description for this step]
In the raycasting algorithm, the "delta distance" (delta_dist) represents the distance that the ray must travel in the x and y directions to move from one grid cell to the next. The set_delta_dist function calculates these delta distances based on the ray's direction vector.

```
void set_delta_dist(t_raycaster *rc) {
    if (rc->ray_dir_x == 0)
        rc->delta_dist_x = INFINITY;
    else
        rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
    if (rc->ray_dir_y == 0)
        rc->delta_dist_y = INFINITY;
    else
        rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
    return;
}
```

The calculation involves taking the reciprocal of the ray's direction components (rc->ray_dir_x and rc->ray_dir_y) and obtaining the absolute value. This is done to ensure that the delta distances are positive.

The purpose of calculating delta distances is to determine how far the ray needs to move in the x and y directions to traverse a single grid cell in the 3D environment. These distances are crucial for implementing the Digital Differential Analyzer (DDA) algorithm, which is responsible for stepping the ray through the environment and finding intersections with walls or other objects.

By setting the delta distances, we ensure that the ray moves incrementally in a consistent manner, allowing it to accurately intersect grid cells and detect objects or walls along its path. The delta distances play a vital role in determining the precise locations where the ray intersects with the virtual environment, contributing to the realistic rendering of the 3D scene.

In summary, the set_delta_dist function calculates and assigns the delta distances for the ray's movement in the x and y directions. These distances are essential for accurately stepping the ray through the environment and determining its intersections with objects or walls.

4. **Calculate Ray Step**: [Add the description for this step]

5. **Calculate Side Dist**: [Add the description for this step]

6. **DDA Loop**: [Add the description for this step]

### Implementation Details
In this project, the raycasting algorithm is implemented using [programming language or framework/library]. Here are some code snippets that illustrate the logic:

[Include code snippets that correspond to the mentioned steps]

### Getting Started
To run the project on your local machine, follow these steps:

Clone the repository: git clone https://github.com/your-repository.git
Install the necessary dependencies: npm install or pip install -r requirements.txt, depending on your setup.
Configure any project-specific settings or parameters, if applicable.
Run the application: npm start or `
