extends Node

onready var Serial = preload("res://bin/GDsercomm.gdns").new()

const baud_rate := 9600
const endline := "\n"

signal recieved(text)

#a readline function, just add the current Port (based on sercomm)
#and it will return a line, since sercomm always use a timeout, it should not lag


func readline(port):
	if !port.has_method("read"):  #to avoid problems
		return "NOT A PORT"
	var cho = ""
	var chango = ""
	while cho != endline:
		cho = port.read()
		if typeof(cho) == TYPE_STRING:
			if cho != endline:
				chango += cho
		else:
			chango = "FAILED"
			break
	return chango


func _physics_process(_delta: float):
	var text = ""
	for _i in range(Serial.get_available()):
		text += str(Serial.read())
	if text:
		emit_signal("recieved", text)


func send(text: String) -> void:  #"please only use ascii"
	Serial.write(text)


func _ready():
	prints("connecting to", get_ports()[-1])
	Serial.call_deferred("open", get_ports()[-1], baud_rate, 1000)


func get_ports() -> Array:
	return Serial.list_ports()
