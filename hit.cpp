#include "hit.h"

/*
        a = 2
        piriform = a^2 * (y^2 + z^2) - a * x^3 + x^4 = 0
        hit if <= 0
*/
bool hit_test(float x, float y, float z) {
    return (4 * ((y * y) + (z * z)) - 2 * (x * x * x) + (x * x * x * x)) <= 0;
}


const float* get_axis_range() {
    const float* range = new float[6]{0.0f, 2.0f, -0.6495f,  0.6495f, -0.6495f,  0.6495f};
	return range;
}
