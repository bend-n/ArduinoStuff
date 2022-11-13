extends WindowDialog

onready var send = $V/Send


func _ready():
	call_deferred("popup_centered_minsize")


func _process(_delta := 0.0):
	rect_position.x = clamp(rect_position.x, 0, OS.get_window_size().x - rect_size.x)
	rect_position.y = clamp(rect_position.y, 20, OS.get_window_size().y - rect_size.y)


func _on_Send_text_entered(new_text: String):
	new_text = new_text.strip_edges().strip_escapes()
	if new_text:
		SerialIO.write(new_text)
	send.text = ""
