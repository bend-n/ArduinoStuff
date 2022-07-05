#include "gdserial.h"

#define DEBUG_LOG 0

#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

using namespace godot;

void GDSerial::_register_methods() {
  register_method("start", &GDSerial::start);
  register_method("end", &GDSerial::end);
  register_method("send", &GDSerial::send);
  register_method("read_string", &GDSerial::read_string);
  register_method("get_available", &GDSerial::get_available);
}

GDSerial::GDSerial() {}

GDSerial::~GDSerial() {}

void GDSerial::_init() {}

bool GDSerial::start(String port, int baud_rate) {
  const char *port_c = port.utf8().get_data();
#if DEBUG_LOG
  printf("GDSerial: Trying to open %s at baudrate %s.\n", port_c, baud_rate);
#endif
  serial_port = open(port_c, O_RDWR | O_NOCTTY | O_NDELAY);
  struct termios tty;
  struct termios tty_old;
  memset(&tty, 0, sizeof tty);
  if (tcgetattr(serial_port, &tty) != 0) {
#if DEBUG_LOG
    printf("GDSerial: Failed to get current serial parameters.\n");
#endif
    return false;
  }
  tty_old = tty;
  cfsetospeed(&tty, (speed_t)baud_rate);
  cfsetispeed(&tty, (speed_t)baud_rate);

  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~CRTSCTS;
  tty.c_cflag |= CREAD | CLOCAL;
  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO;
  tty.c_lflag &= ~ECHOE;
  tty.c_lflag &= ~ECHONL;
  tty.c_lflag &= ~ISIG;
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
  tty.c_oflag &= ~OPOST;
  tty.c_oflag &= ~ONLCR;
  tty.c_cc[VTIME] = 0;
  tty.c_cc[VMIN] = 0;

  cfmakeraw(&tty);
  tcflush(serial_port, TCIFLUSH);

  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
#if DEBUG_LOG
    printf("GDSerial: Could not set serial port parameters.\n");
#endif
    return false;
  }
  fcntl(serial_port, F_SETFL, FNDELAY);
#if DEBUG_LOG
  printf("GDSerial: %s opened.\n", port_c);
#endif
  return true;
}

void GDSerial::end() {

  close(serial_port);
  serial_port = 0;

#if DEBUG_LOG
  printf("GDSerial: Serial port closed.\n");
#endif
}

void GDSerial::send(String text) {
  const char *text_c = text.utf8().get_data();
  write(serial_port, text_c, text.length());
}

String GDSerial::read_string() {
  String text = "";

  unsigned char buf[4096];
  int n;
  n = read(serial_port, &buf, sizeof(buf));
  for (int x = 0; x < n; x++) {
    text += buf[x];
  }
  return text;
}

int GDSerial::get_available() {
  int bytes_available = 0;
  ioctl(serial_port, FIONREAD, &bytes_available);
  return bytes_available;
}
