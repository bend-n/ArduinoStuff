extends Node


func prepare(v: Vector2) -> Vector2:
	v = v.normalized()
	if v.x < 0:
		v.x = 1 - v.x
	if v.y < 0:
		v.y = 1 - v.y
	return v
