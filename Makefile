
app_name = pdm
inc = -I./include/
srcs = ./src/util.cpp
linux:
	g++ $(inc) $(srcs) -Wall -o $(app_name)
linux_debug:
	g++ $(inc) $(srcs) -Wall -g -DDEBUG -o $(app_name)