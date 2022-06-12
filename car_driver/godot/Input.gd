extends Node

var input := Vector2.ZERO

var fast := false

onready var lb = $Label


func _physics_process(_delta):
	var inp := get_input()
	if inp != input:
		input = inp
		lb.text = str(input)
		SerialIO.write("H%s,%s" % [input.x, input.y])


func _ready():
	yield(get_tree(), "idle_frame")
	SerialIO.write("H0,0")  #stop
	lb.text = str(input)


func get_input() -> Vector2:
	if Input.is_action_just_pressed("sped"):
		fast = !fast
	var x := Input.get_action_strength("leftpaddle")
	var y := Input.get_action_strength("rightpaddle")
	var multiplier := 100 if fast else 50
	var v := Vector2(x, y) * multiplier
	# if button is pressed, reverse, if no paddle input, move slow
	if Input.is_action_pressed("lb"):
		v.x = -v.x if v.x else -multiplier / 4.0
	if Input.is_action_pressed("rb"):
		v.y = -v.y if v.y else -multiplier / 4.0
	return (v).round()
