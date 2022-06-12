extends RichTextLabel
class_name Console


func _ready():
	SerialIO.connect("recieved", self, "add_text")


func add_text(new: String):
	text += new
