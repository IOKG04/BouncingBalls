#ifndef VEC2_H__
#define VEC2_H__

// 2d vector
typedef struct{
    double x, y;
} vec2;

// adds two vec2s
vec2 add_vec2(vec2 a, vec2 b);
// subtracts a vec2 from another
vec2 subtract_vec2(vec2 a, vec2 b);
// scales a vec2 by a factor
vec2 scale_vec2(vec2 a, double b);
// returns the cross product of two vec2s
vec2 cross_vec2(vec2 a, vec2 b);
// divides a vec2 by another
vec2 cross_div_vec2(vec2 a, vec2 b);
// returns the reciprocal of a vec2
vec2 reciprocal_vec2(vec2 vec);
// squared length of a vec2
double squared_length_vec2(vec2 vec);
// length of a vec2
double length_vec2(vec2 vec);
// returns a version of a vec2 where its size is 1
vec2 normalized_vec2(vec2 vec);

#endif
