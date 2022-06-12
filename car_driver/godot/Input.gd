extends Node

var input : Vector2

func prepare(v: Vector2) -> Vector2:
	v = v.normalized()
	if v.x < 0:
		v.x = 1 - v.x
	if v.y < 0:
		v.y = 1 - v.y
	v=v.round()
	return v


func _physics_process(_delta):
	var inp := get_input()
	if input != inp:
		print(inp)
		input = inp
		SerialIO.send("H%s%s" % [inp.x, inp.y])

func get_input()->Vector2:
	var x := Input.get_axis("ui_left", "ui_right")
	var y := Input.get_axis("ui_up", "ui_down")
	return prepare(Vector2(x, y))
