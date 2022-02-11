/**
 * Written by Yi Yang
 * 
 * 2/2022
 * 
 * */
#ifdef CLIENT_UTIL_H
#define CLIENT_UTIL_H

#include <stdio.h>
#include <string>
#include <map>

class pdmCli {
public:
  pdmCli();
  int add_command(std::string a){comd=a;return 1;}
  int run();
  int comp_java(std::string path);
private:
  std::string comd;
  std::map<std::string, std::string> comds;
};

#endif