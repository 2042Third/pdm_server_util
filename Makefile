
app_name = pdm
inc = -I./include/
srcs = ./src/util.cpp

linux:
	g++ $(inc) $(srcs) -std=c++11 -Wall -o $(app_name)
windows:
	g++ $(inc) $(srcs) -std=c++11 -Wall -o $(app_name)
linux_debug:
	g++ $(inc) $(srcs) -std=c++11 -Wall -g -DDEBUG -o $(app_name)
update_win:
	make windows
	cp pdm.exe 'C:\ProgramData\pdm\bin'
update:
	make linux
	cp pdm /usr/bin/