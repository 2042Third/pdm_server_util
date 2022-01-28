//
// Written by Mike Yang on 1/28/2022.
//

#include "util.h"
#include <iomanip>
#include <numeric>
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

int util::rderr (int err){
  #ifdef DEBUG//debug
    cout<<"Output: "<< err<<endl;
    system("ls");
  #endif//debug
  return 1;
}

int util::run_util(){
  for(unsigned int i=0; i<TOTAL_COMMANDS_COUNT;i++){
    if (!cmd_b[i])
      continue;
    
    if(i==0){// logs
      if(NON_SILENT_RUNNING)
        cout<<"Reading Logs... "<<endl;
      rderr(system("cat /usr/local/tomcat/logs/catalina.out"));
      
    }
    else if(i==1){// restart
      if(NON_SILENT_RUNNING)
        cout<<"Restarting Tomcat... "<<endl;
      rderr(system("sh /usr/local/tomcat/bin/shutdown.sh"));
      rderr(system("sh /usr/local/tomcat/bin/startup.sh"));
    }
    else if(i==2){// clean logs
      if(NON_SILENT_RUNNING)
        cout<<"Cleaning logs... "<<endl;
      rderr(system("echo \"\" > /usr/local/tomcat/logs/catalina.out"));
    }
  }
  return 1;
}

void util::get_help_view (){
  cout<<"pdm server-side utilities\n help menu\n"<<endl;
  for(unsigned int i=0 ; i< TOTAL_COMMANDS_COUNT;i++){
    cout<<cmd[i]<<endl;
  }
  cout<<endl;
  for(unsigned int i=0 ; i< TOTAL_HEADLESS_COMMANDS_COUNT;i++){
    cout<<cmd_headless[i]<<endl;
  }
  cout<<endl;
}

int util::set_config(char* argv){
  string a = argv;
  for(unsigned int i=0;i<a.size();i++){
    switch(a[i]) {
      case '-' : 
        break;
      case 'l' : // cmd_b[0]
        cmd_b[0]=1;
        break;
      case 'X': // cmd_b[1]
        cmd_b[1]=1;
        break;
      case 'c': // cmd_b[2]
        cmd_b[2]=1;
        break;
      case 'S':
        NON_SILENT_RUNNING=0;
        break;
      case 'h':
        get_help_view();
        return 1;
      default :
         cout << "Invalid command \""<< a[i] <<"\""<< endl;
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