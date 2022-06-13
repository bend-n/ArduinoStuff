extends Node

const Serial = preload("res://bin/gdserial.gdns")
var serial : Serial

const baud_rate := 9600
const endline := "\n"


#@param text the text to send
func write(text: String) -> void:
	serial.write_text(text)


func create_serial():
	if serial:
		serial.close_port()
	serial = Serial.new()
	serial.open_port("/dev/ttyACM0", baud_rate)


func _ready():
	create_serial()