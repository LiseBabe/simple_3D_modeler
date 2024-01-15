#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "cone.h"
#include "linked_spheres_group.h"
#include "interactions.h"

int main() {
    hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));

    //world.add(make_shared<cone>(point3(-1.5, 0.25, -2.0), point3(0.75, 0.25, -2.0), 0.2, 0.8, material_right));
    
    linked_spheres_group spheres(&world, make_shared<sphere>(point3(-1.5, 0.25, -2.0), 0.2, material_right));
    spheres.add_sphere(make_shared<sphere>(point3(0.75, 0.25, -2.0), 0.8, material_right), 0);

    light white_light = new_light(point3(-1.0, 0.5, -1.0));
    light red_light = new_colored_light(point3(0.0, 0.5, -1), point3(0.7, 0.2, 0.2));
    light blue_light = new_colored_light(point3(1.0, -0.25, -1), point3(0.0, 0.0, 0.8));
    std::vector<light> lights {white_light};
    //std::vector<light> lights {white_light, red_light, blue_light};

    camera cam(16.0 / 9.0, 800, 1, 1);

    interactions inter(spheres, &world, &cam);
    inter.add_sphere_at_pos(500, 100);

    // world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.2, material_right));
    // point3 center = {0.0, 0.0, -1.0};
    // point3 p = point3 {0.0, 0.0, -0.5} - center;
    // double horizontal_angle = 6.2;
    // world.add(make_shared<sphere>(center + point3 {dot(point3 {cos(horizontal_angle), 0, sin(horizontal_angle)}, p),
    //                                                 p.y(),
    //                                                 dot(point3 {-sin(horizontal_angle), 0, cos(horizontal_angle)}, p)},
    //                             0.05, material_right));

    point3 center = {0.0, 0.25, -2.0};
    inter.rotate_camera(0.0, 0, center);

    cam.render_phong_file(world, lights);
    //cam.render_file(world);
}