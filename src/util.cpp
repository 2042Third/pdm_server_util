//
// Written by Mike Yang on 1/28/2022.
//

#include "util.h"
#include <iomanip>
#include <numeric>
#include <filesystem>
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

int util::run_util(){
  for(unsigned int i; i<TOTAL_COMMANDS_COUNT;i++){
    if (!cmd_b[i])
      continue;
    switch(i) {
      case 0 : // logs
        system("cat /usr/local/tomcat/logs/catalina.out");
        break;
      case 1 : // restart
        system("sh /usr/local/tomcat/bin/shutdown.sh");
        system("sh /usr/local/tomcat/bin/startup.sh");
        break;
    }
  }
  return 1;
}

int util::set_config(char* argv){
  string a = argv;
  for(unsigned int i=0;i<a.size();i++){
    switch(a[i]) {
      case 'l' : // cmd_b[0]
        cmd_b[0]=1;
        break;
      case 'X': // cmd_b[1]
        cmd_b[1]=1;
        break;
      default :
         cout << "Invalid command \""<< a[i] << << endl;
    }
  }
  return 1;
}

int util::rd_inp(unsigned int argc, char ** argv, string *infile){
  int arg_c=1;
  for (unsigned int i = 1; i< argc;i++){
    if (argv[i][0] == '-'){
      arg_c++;
      set_config(argv[i]);
    }
    else{
      if (infile->empty()){
        *infile = argv[i];
      }
      else
        return 0;
    }
  }
  
  return arg_c;
}

int main(int argc, char ** argv) {
  string infile,oufile,nonce;
  util utl;
  if (utl.rd_inp(argc,argv,&infile)!=2){
    cout<<"No input, -h for help."<<endl;
    return 0;
  }
  utl.run_util();
  return 0;
}