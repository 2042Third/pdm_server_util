
app_name = pdm
inc = -I./include/
srcs = ./src/util.cpp ./src/pdmCli.cpp

linux:
	g++ $(inc) $(srcs) -std=c++17 -Wall -o $(app_name)
win:
	g++ $(inc) $(srcs) -std=c++17 -Wall -o $(app_name)
win_debug:
	g++ $(inc) $(srcs) -std=c++17 -Wall -o $(app_name) -DWINDOWS_DEBUG -Wall
linux_debug:
	g++ $(inc) $(srcs) -std=c++17 -Wall -g -DDEBUG -o $(app_name)
update_win:
	mingw32-make win
	xcopy /E /Y pdm.exe \ProgramData\pdm\bin 
update:
	make linux
	cp pdm /usr/bin/