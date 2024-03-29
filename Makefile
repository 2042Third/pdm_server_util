
app_name = pdm
inc = -I./include/
srcs = ./src/util.cpp ./src/pdmCli.cpp
headless_srcs = ./src/util.cpp
all:
	make win
linux:
	g++ $(inc) $(headless_srcs) -std=c++17 -Wall -o $(app_name) -DHEADLESS
win:
	g++ $(inc) $(srcs) -std=c++17 -Wall -o $(app_name)
win_debug:
	g++ $(inc) $(srcs) -std=c++17 -Wall -o $(app_name) -DPDM_DEBUG -Wall -g
linux_debug:
	g++ $(inc) $(srcs) -std=c++17 -Wall -g -DPDM_DEBUG -o $(app_name)
update_win:
	mingw32-make win
	xcopy /E /Y pdm.exe \ProgramData\pdm\bin 
update:
	make linux
	cp pdm /usr/local/bin/