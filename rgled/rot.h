#ifndef ROT_H
#define ROT_H
namespace Rotary {
void setup(const int start = 0);
bool button_just_pressed();

void set(const int n = 0);
int read();
} // namespace Rotary
#endif