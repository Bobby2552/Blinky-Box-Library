INO := $(shell find './' -name '*.ino')

upload : $(INO)
	@arduino --upload $(INO:./%=%)

serial : upload
	@platformio serialports monitor --baud=115200
