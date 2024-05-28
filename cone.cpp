#include "hittable.h"
#include "vec3.h"
#include "sphere.h"
#include "cone.h"
#include "material.h"
#include "color.h"

bool cone::hit(const ray& r, interval ray_t, hit_record& rec) const {
  bool selected = false;
  vec3 ro = r.origin();
  vec3 rd = unit_vector(r.direction());
  vec3 pa = center1;
  vec3 pb = center2;
  auto ra = radius1;
  auto rb = radius2;

  vec3 outward_normal;

  vec3  ba = pb - pa;
  vec3  oa = ro - pa;
  vec3  ob = ro - pb;
  float rr = ra - rb;
  float m0 = dot(ba,ba);
  float m1 = dot(ba,oa);
  float m2 = dot(ba,rd);
  float m3 = dot(rd,oa);
  float m5 = dot(oa,oa);
  float m6 = dot(ob,rd);
  float m7 = dot(ob,ob);

  float h1 = m3*m3 - m5 + ra*ra;
  float h2 = m6*m6 - m7 + rb*rb;

  float t;

  if (ba.length() + ra <= rb && h2 > 0.0 || is_selected(2)) {
      t = -m6 - sqrt( h2 );
      outward_normal = (ob+t*rd)/rb;
  }
  else if (ba.length() + rb <= ra && h1 > 0.0 || is_selected(1)) {
      t = -m3 - sqrt( h1 );
      outward_normal = (oa+t*rd)/ra;
  }
  else {
      float d2 = m0 - rr * rr;

      float k2 = d2 - m2 * m2;
      float k1 = d2 * m3 - m1 * m2 + m2 * rr * ra;
      float k0 = d2 * m5 - m1 * m1 + m1 * rr * ra * 2.0 - m0 * ra * ra;

      float h = k1 * k1 - k0 * k2;
      if (h < 0.0) return false;
      t = (-sqrt(h) - k1) / k2;

      float y = m1 - ra * rr + t * m2;
      if (y > 0.0 && y < d2) {
          outward_normal = unit_vector(d2 * (oa + t * rd) - ba * y);
      } else {
          if (h1 < 0.0 && h2 < 0.0) return false;

          t = +infinity;
          if (h1 > 0.0) {
              t = -m3 - sqrt(h1);
              outward_normal = (oa + t * rd) / ra;
              selected = is_selected(1);
          }
          if (h2 > 0.0) {
              auto tmp_t = -m6 - sqrt(h2);
              if (tmp_t < t) {
                  t = tmp_t;
                  outward_normal = (ob + t * rd) / rb;
                  selected = is_selected(2);
              }
          }
      }
  }

  if( t < 0.001 ) return false;

  rec.t = t / r.direction().length();
  rec.p = r.at(rec.t);
  rec.set_face_normal(r, unit_vector(outward_normal));
  rec.mat = mat;
    if (selected){
        std::cout << "a sohere has been selected" << std::endl;
        auto descr = mat->descriptor();
        std::cout << rec.mat->get_material_color()<< std::endl;
        if (descr.first == "lambertian"){
            std::cout << "lambertian "<< std::endl;
            auto new_mat = make_shared<lambertian>(color(descr.second[0],descr.second[1],descr.second[2]));
            rec.mat = new_mat;
        }
        else if (descr.first == "metal"){
            std::cout << "lambertian "<< std::endl;
            auto new_mat = make_shared<metal>(color(1.0,1.0,1.0), descr.second[3]);
            rec.mat = new_mat;
        }
        
        std::cout << rec.mat->get_material_color()<< std::endl;
    }
  return true;
}

