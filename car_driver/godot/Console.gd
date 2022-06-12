extends RichTextLabel
class_name Console

var thread = Thread.new()

func _physics_process(_delta:=0.0)->void:
	thread.start(self, "readstring")
	thread.wait_to_finish()

func readstring()->void:
	for _i in range(SerialIO.Serial.get_available()):
		text += str(SerialIO.Serial.read())