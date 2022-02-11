/**
 * Written by Yi Yang
 * 
 * 2/2022
 * 
 * */
#include "pdmCli.h"
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <unistd.h>

using namespace std;
namespace fs = filesystem;

pdmCli::pdmCli(){
  comds.insert(pair<string, string>("compile-java","Compiles PDM server-side Java code, recursively."));
}

string pdmCli::comp_file_str(string entry_str){
  return "javac -cp ..\\..\\lib\\*;"+comp_dir_lib+"\\classes\\lib\\*;"+comp_dir_lib+"\\classes\\. "+entry_str;
}

/**
 * Recursively compiles all java files in the tomcat (current) directory.
 * */
int pdmCli::comp_java(string path="./",int level=0){
  fs::path fp(path);
  for(int i=0;i<=level;i++)
    cout<<"-";
  if(level!=0)
    std::cout << fp.filename() << std::endl;
  for (const auto & entry : fs::directory_iterator(fp)){
    
    if(fs::is_directory(entry.path())&&(level!=0 || entry.path().filename()==comp_dir_lib)){
      
      comp_java(entry.path().relative_path().string(), ++level);
    }
    else if(fs::is_regular_file(entry) && entry.path().extension() == ".java"){

      cout<<comp_file_str(entry.path().relative_path().string())<<endl;
      // cout<<system(comp_file_str(entry.path().relative_path().string()).c_str())<<endl;
      system(comp_file_str(entry.path().relative_path().string()).c_str());
    }
  }

  return 1;
}

int clear_comp_dir(string path=".\\WEB-INF\\classes"){
  fs::path fp(path);
  for (const auto & entry : fs::directory_iterator(fp)){
    if(fs::is_regular_file(entry) && entry.path().extension() == ".class"){
      fs::remove(entry.path());
    }
  }
  return 1;
}

int pdmCli::run() {
  if(comd.empty())
    return 0;
  if(comd=="compile-java"){
    clear_comp_dir();
    comp_java();
  }
  else {
    cout<<"Command \""<<comd<<"\" unknow."<<endl;
  }
  return 1;
}