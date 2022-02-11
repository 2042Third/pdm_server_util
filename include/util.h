//
// Written by Mike Yang on 1/28/2022.
//

#ifndef SERVER_UTIL
#define SERVER_UTIL
#include <stdio.h>
#include <string>

using namespace std;

#define TOTAL_COMMANDS_COUNT              3 // make sure is same as the length of cmd_b
#define TOTAL_HEADLESS_COMMANDS_COUNT     2 // make sure is same as the length of cmd_headless

class util {
public:
  util();
  ~util();
  int rd_inp(unsigned int argc, char ** argv, string* infile);
  int run_util();
private:
  void* cli;
  int NON_SILENT_RUNNING =1;
  int cmd_b[3] = {0,0,0};
  string cmd[3] = {"-l: See Tomcat Logs", "-X: Restart Tomcat", "-c: clean logs"};
  string cmd_headless[2] = {"-S: silent", "-h: help"};
  int set_config(char* argv);
  int rderr(int err);
  void get_help_view();
};
#endif //SERVER_UTIL
