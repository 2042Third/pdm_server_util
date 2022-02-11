/**
 * Written by Yi Yang
 * 
 * 2/2022
 * 
 * */
#ifndef PDM_CLIENT_UTIL_H
#define PDM_CLIENT_UTIL_H

#include <stdio.h>
#include <string>
#include <map>

class pdmCli {
public:
  pdmCli();
  int add_command(std::string a){comd=a;return 1;}
  int run();
  int comp_java(std::string path, int level);
  std::string comp_file_str(std::string entry_str);
private:
  std::string comp_dir="WEB-INF/classes";
  std::string comp_dir_lib="WEB-INF";
  std::string comd;
  std::map<std::string, std::string> comds;
};

#endif