#include <math.h>

#include "vec2.h"

// adds two vec2s
vec2 add_vec2(vec2 a, vec2 b){
    vec2 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}
// subtracts a vec2 from another
vec2 subtract_vec2(vec2 a, vec2 b){
    vec2 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}
// scales a vec2 by a factor
vec2 scale_vec2(vec2 a, double b){
    vec2 c;
    c.x = a.x * b;
    c.y = a.y * b;
    return c;
}
// returns the cross product of two vec2s
vec2 cross_vec2(vec2 a, vec2 b){
    vec2 c;
    c.x = a.x * b.x;
    c.y = a.y * b.y;
    return c;
}
// divides a vec2 by another
vec2 cross_div_vec2(vec2 a, vec2 b){
    return cross_vec2(a, reciprocal_vec2(b));
}
// returns the reciprocal of a vec2
vec2 reciprocal_vec2(vec2 vec){
    vec2 o;
    o.x = 1 / vec.x;
    o.y = 1 / vec.y;
    return o;
}
// squared length of a vec2
double squared_length_vec2(vec2 vec){
    return (vec.x * vec.x) + (vec.y * vec.y);
}
// length of a vec2
double length_vec2(vec2 vec){
    return sqrt(squared_length_vec2(vec));
}
// returns a version of a vec2 where its size is 1
vec2 normalized_vec2(vec2 vec){
    return scale_vec2(vec, 1 / length_vec2(vec));
}
