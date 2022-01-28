//
// Written by Mike Yang on 1/28/2022.
//

#ifndef SERVER_UTIL
#define SERVER_UTIL
#include <stdio.h>
#include <string>

using namespace std;

#define TOTAL_COMMANDS_COUNT              2
#define TOTAL_HEADLESS_COMMANDS_COUNT     1

class util {
public:
  int rd_inp(unsigned int argc, char ** argv, string* infile);
  int run_util();
private:
  int NON_SILENT_RUNNING =1;
  int cmd_b[2] = {0,0};
  string cmd[2] = {"-l: See Tomcat Logs", "-X: Restart Tomcat"};
  string cmd_headless[2] = {"-S: silent"};
  int set_config(char* argv);
  int rderr(int err);
};
#endif //SERVER_UTIL
