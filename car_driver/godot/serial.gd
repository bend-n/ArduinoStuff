extends Node

onready var Serial = preload("res://bin/GDsercomm.gdns").new()

const baud_rate := 9600
const endline := "\n"


func send(text: String) -> void:  #"please only use ascii"
	Serial.write(text)


func _ready():
	prints("connecting to", get_ports()[-1])
	Serial.call_deferred("open", get_ports()[-1], baud_rate, 1000)


func get_ports() -> Array:
	return Serial.list_ports()
