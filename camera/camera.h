#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <memory>
#include "../utilities/interval.h"
#include "../utilities/color.h"
#include "../scene_objects/hittable.h"
#include "../utilities/material.h"
#include "../scene_objects/light.h"
#include "../image/span3D.h"
#include "../image/screen_segment.h"
#include "../scene_objects/hittable_list.h"

using std::shared_ptr;

/**
 * This class is the base class for phong_camera and beautiful_camera.
 * The render is not implemented in this class because it depends on the type of camera (and it wouldn't have
 * been useful to put a virtual render() here, since the render functions in phong_camera and beautiful_camera
 * have different arguments.)
 * Only the functions that are independent of the render method are present here, such as
 * functions related to the camera's position and movement.
 */

inline constexpr double ambient_occlusion = 0.5;

class camera {
  public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width  = 100;  // Rendered image width in pixel count
    int    samples_per_pixel = 1;   // Count of random samples for each pixel
    int    max_depth         = 1;   // Maximum number of ray bounces into scene

    camera(){}
    
    camera(double _aspect_ratio, int _image_width, int _samples_per_pixel, int _max_depth) :
                                    aspect_ratio(_aspect_ratio), image_width(_image_width),
                                    samples_per_pixel(_samples_per_pixel), max_depth(_max_depth) {
        initialize();
    }

    ray get_ray(int i, int j) const;

    void rotate_camera(double horizontal_angle, double vertical_angle, point3 rot_center);

    void move_camera_sideways(double delta_pos_x, double delta_pos_y);

    void move_camera_forward(double delta_pos);

    point3 get_center() const {
        return center;
    }

    point3 get_pixel00_loc() const {
        return pixel00_loc;
    }

    vec3 get_viewport_u() const {
        return viewport_u;
    }

    vec3 get_viewport_v() const {
        return viewport_v;
    }

  protected:
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0 (top left corner)

    double focal_length;
    double viewport_height;
    double viewport_width;

    // the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u;
    vec3 viewport_v;

    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize();

    vec3 pixel_sample_square() const;
};

#endif