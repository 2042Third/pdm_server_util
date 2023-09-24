//
// Written by Mike Yang on 1/28/2022.
//

#include "util.h"
#ifndef HEADLESS
#include "pdmCli.h"
#endif
#include <iomanip>
#include <numeric>
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>

using namespace std;



int util::run_util(){
  for(unsigned int i=0; i<TOTAL_COMMANDS_COUNT;i++){
    
  }
#ifndef HEADLESS
  (*(pdmCli*)cli).run();
#endif
  return 1;
}

void util::get_help_view (){
  cout<<"pdm server-side utilities\n help menu\n"<<endl;
  for(const auto& f: app){
    cout<<"\t"<< f.second->match()<<": "<<f.second->description()<<endl;
  }
}

int util::set_config(const char* argv,int argc){
  for(int i = 1; i < argc; i++){
    std::string arg(1,argv[i]);
    if(arg == "-h") {
      get_help_view();
    } else if(app.find(arg) != app.end()) {
      app[arg]->run();
    } else {
      std::cout << "Invalid command \"" << arg << "\"\n";
    }
  }
  return 1;
}

/**
 * Get a vector of all features of the application
 * 
 * */
void util::apps(){
  app["h"] = std::make_unique<LogsRead>();
  app["c"] = std::make_unique<LogsClean>();
  app["x"] = std::make_unique<RestartTomcat>();

}

int util::rd_inp(unsigned int argc, char ** argv, string *infile){
  int arg_c=1;

  for (unsigned int i = 1; i< argc;i++){
    if (argv[i][0] == '-'){
      set_config(argv[i],argc);
    }
    else{
      if (infile->empty()){
        *infile = argv[i];
      }
#ifndef HEADLESS
      (*(pdmCli*)cli).add_command(string(argv[i]));
#endif
    }
    arg_c++;
  }
  
  return arg_c;
}

util::util(){
  apps();
#ifndef HEADLESS
  cli=(void*)new pdmCli();
#endif
}

util::~util(){

#ifndef HEADLESS
  if(cli!=NULL)
    delete (pdmCli*)cli;
#endif
}

