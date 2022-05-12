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
  for(Runnable f: app ){
    cout<< f.match<<": "<<f.description<<endl;
  }
}

int util::set_config(char* argv,int argc){
  int i=0, k=0;
  while(argv[i]!='\0'){
    k=0;
    if(argv[i] == '-'){
      i++;
      continue;
    }
    // if (i+1 == argc)
    //   return 1;
    for (Runnable f : app){
      if (f.matches(argv[i])){
        k=1;
        f.run();
      }
      else if (argv[i] == 'h'){
        k=1;
        get_help_view();
      }
    }
    if(!k)
      cout << "Invalid command \""<< argv[i] <<"\""<< endl;
    i++;
  }
  return 1;
}

/**
 * Get a vector of all features of the application
 * 
 * */
vector<Runnable> util::apps(){
  vector<Runnable> app;
  app.push_back(LogsRead());
  app.push_back(LogsClean());
  app.push_back(RestartTomcat());
  return app;
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
  app = apps();
#ifndef HEADLESS
  cli=(void*)new pdmCli();
#endif
}

util::~util(){
#ifndef HEADLESS
  if(cli!=NULL)
    delete[] (pdmCli*)cli;
#endif
}

int main(int argc, char ** argv) {
  string infile,oufile,nonce;
  util utl;
  if (utl.rd_inp(argc,argv,&infile)<2){
    cout<<"No input, -h for help."<<endl;
    return 0;
  }
  utl.run_util();
  return 0;
}