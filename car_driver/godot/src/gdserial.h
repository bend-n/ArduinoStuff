#ifndef GDSERIAL_H
#define GDSERIAL_H

#include <Godot.hpp>

namespace godot {

class GDSerial : public Reference {
  GODOT_CLASS(GDSerial, Reference)

private:
  int serial_port;

public:
  static void _register_methods();

  GDSerial();
  ~GDSerial();

  void _init(); // our initializer called by Godot

  bool start(String port, int baud_rate);
  void end();
  void send(String text);
  int get_available();
  String read_string();
};

} // namespace godot

#endif
