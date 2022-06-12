extends Node

const Serial = preload("res://bin/GDsercomm.gdns")
onready var serial = Serial.new()

const baud_rate := 9600
const endline := "\n"


#@param text the text to send
func write(text: String) -> void:  #"please only use ascii"
	if serial.write(text) != 0:  #asshole used unicode
		print("serial broke, reloading(%s)" % text)
		create_serial()


func create_serial():
	if serial:
		serial.close()
	serial = Serial.new()
	serial.call_deferred("open", get_ports()[-1], baud_rate, 1000)


func _ready():
	prints("connecting to", get_ports()[-1])
	create_serial()


func get_ports() -> Array:
	return serial.list_ports()
