#ifndef MATH_H
#define MATH_H
static constexpr inline float lerp(float from, float to, float weight) { return from + (to - from) * weight; }

static inline int wrapi(int value, int min, int max) {
  int range = max - min;
  return range == 0 ? min : min + ((((value - min) % range) + range) % range);
}

static inline int clamp(long value, long minv, long maxv) {
  if (value < minv)
    return minv;
  else if (value > maxv)
    return maxv;
  return value;
}

#endif
