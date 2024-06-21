#ifndef CONSTANTS_H__
#define CONSTANTS_H__

#define STEP_DELAY 50000
#define DELTA_TIME  STEP_DELAY / 1000000.0

#define GRAVITY (vec2){0, 9.813}

#define ENERGY_LOSS_FACTOR (vec2){0.99, 0.95}

#define RANDOM_RADIUS_MIN 1
#define RANDOM_RADIUS_MAX 5
#define RANDOM_OFFSET_MAX (vec2){25, 10}
#define RANDOM_VELOCITY_MAX (vec2){60, 15}

#endif
