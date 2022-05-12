//
// Written by Mike Yang on 1/28/2022.
//

#ifndef SERVER_UTIL
#define SERVER_UTIL
#include <stdio.h>
#include "Runnable.hpp"
#include <string>
#include <vector>
using namespace std;

#ifdef PDM_DEBUG
#define NON_SILENT_RUNNING 0
#else 
#define NON_SILENT_RUNNING 1
#endif

#define TOTAL_COMMANDS_COUNT              3 // make sure is same as the length of cmd_b
#define TOTAL_HEADLESS_COMMANDS_COUNT     2 // make sure is same as the length of cmd_headless

class util {
public:
  util();
  ~util();
  int rd_inp(unsigned int argc, char ** argv, string* infile);
  int run_util();
  std::vector<Runnable> apps();
private:
  void* cli;
  int cmd_b[TOTAL_COMMANDS_COUNT] = {0,0,0};
  string cmd[TOTAL_COMMANDS_COUNT] = {"-l: See Tomcat Logs", "-X: Restart Tomcat", "-c: clean logs"};
  string cmd_headless[TOTAL_HEADLESS_COMMANDS_COUNT] = { "-h: help"};
  int set_config(char* argv, int argc, std::vector<Runnable> app);
  int rderr(int err);
  void get_help_view();
};
#endif //SERVER_UTIL
