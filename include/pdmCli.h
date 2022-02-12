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

#ifdef PDM_DEBUG
#define SUPPRESS_JAVA_COMPILE_OUT 0
#else 
#define SUPPRESS_JAVA_COMPILE_OUT 1
#endif

#ifdef _WIN32
#define PDM_WINDOWS 1
#else
#define PDM_WINDOWS 0
#endif

class pdmCli {
public:
  pdmCli();
  int add_command(std::string a){comd=a;return 1;}
  int run();
  int comp_java(std::string path, int level);
  std::string comp_file_str(std::string entry_str);
  std::string all_jars_str();
private:
  int compiled_java_count = 0;
  int error_count = 0;
  int clear_count();
  int init_run();
  std::string err_f = "pdm_client_errors.log";
  std::string error_files = "";
  std::string comp_dir="WEB-INF/classes";
  std::string comp_dir_lib="WEB-INF";
  std::string comd;
  std::map<std::string, std::string> comds;
};

#endif