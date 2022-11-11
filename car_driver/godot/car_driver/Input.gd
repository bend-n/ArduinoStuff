extends Node

onready var lb := $Label

var prev_input: PoolIntArray

func _physics_process(_delta):
	var input := get_input()
	write(input) # write it multiple times because packet loss (idk either but it happens)
	if prev_input != input:
		prev_input = input
		print(input)
		lb.text = str(input)

func write(motors: PoolIntArray) -> void:
	SerialIO.write("H%d,%d" % [motors[0], motors[1]])

func get_input() -> PoolIntArray:
	var force: float = Input.get_axis("decel", "accel")
	var torque: float = Input.get_axis("ui_left", "ui_right")
	var turn_sign := sign(torque)
	var turn_amount := abs(torque)
	var input: PoolIntArray = [mult(lerp(force, turn_sign, turn_amount)), mult(lerp(force, -turn_sign, turn_amount))]
	if force < 0:
		input.invert()
	return input

func mult(n: float) -> int:
	return int(clamp(n * 100, -100, 100))

func reset() -> void:
	write([0, 0])

func _exit_tree() -> void:
	reset()
