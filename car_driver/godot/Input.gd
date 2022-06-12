extends Node

var input: Vector2

onready var lb = $Label


func prepare(v: Vector2) -> Vector2:
	v = v.normalized()
	if v.x < 0:
		v.x = 1 - v.x
	if v.y < 0:
		v.y = 1 - v.y
	v = v.round()
	return v


func _physics_process(_delta):
	input = get_input()
	lb.text =str(input)
	SerialIO.send("H%s,%s" % [input.x, input.y])


func get_input() -> Vector2:
	var x := Input.get_action_strength("leftpaddle")
	var y := Input.get_action_strength("rightpaddle")
	if Input.is_action_pressed("lb"):
		x = x + 1 if x != 0 else 1.01
	if Input.is_action_pressed("rb"):
		y = y + 1 if y != 0 else 1.01
	return (Vector2(x, y) * 100).round()
