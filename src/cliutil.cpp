/**
 * Written by Yi Yang
 * 
 * 2/2022
 * 
 * */
#include "cliutil.h"
#include <filesystem>

using namespace std;

pdmCli::pdmCli(){
  comds.insert(pair<string, string>("compile-java","Compiles PDM server-side Java code, recursively."));
}
/**
 * Recursively compiles all java files in the tomcat (current) directory.
 * */
int pdmCli::comp_java(string path="./"){
  for (const auto & entry : fs::directory_iterator(path))
    std::cout << entry.path() << std::endl;
}

int pdmCli::run() {
  if(comd.empty())
    return 0;
  switch(comd){
    case "compile-java":
      comp_java();
    break;
  }
}