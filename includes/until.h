//
// Written by Mike Yang on 1/28/2022.
//

#ifndef SERVER_UTIL
#define SERVER_UTIL
#include <stdio.h>

#define TOTAL_COMMANDS_COUNT     2

class util {
private:
  int cmd_b[2] = {0,0};
  char* cmd[2] = {"-l: See Tomcat Logs", "-X: Restart Tomcat"};
  int rd_inp(unsigned int argc, char ** argv, string *infile);
  int set_config(char* argv);
};
#endif //SERVER_UTIL
