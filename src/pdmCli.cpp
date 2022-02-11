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
#include <unordered_map>

using namespace std;
namespace fs = filesystem;

pdmCli::pdmCli(){
  comds.insert(pair<string, string>("compile-java","Compiles PDM server-side Java code, recursively."));
}

string pdmCli::all_jars_str(){
  fs::path fp(".\\"+comp_dir_lib+"\\lib/");
  string all_jars = "";
  for (const auto & entry : fs::directory_iterator(fp)){
    if(fs::is_regular_file(entry.path()) && entry.path().extension()==".jar"){
      all_jars+=comp_dir_lib+"\\lib"+"\\"+entry.path().filename().string()+";";
    }
  }
  return all_jars;
}

string pdmCli::comp_file_str(string entry_str){
  fs::path fp(".\\"+comp_dir_lib+"\\lib/");
  string ret_str;
  string err_f = to_string(std::hash<std::string>{}(entry_str));
  if (SUPPRESS_JAVA_COMPILE_OUT){
    if(PDM_WINDOWS){
      ret_str ="javac -cp ..\\..\\lib\\*;.\\"+comp_dir_lib+"\\lib\\*;"+comp_dir_lib+
      "\\classes\\. "+entry_str+" > nul 2>> "+fs::temp_directory_path().string()+"\\"+err_f;
      error_files+=", "+fs::temp_directory_path().string()+"\\"+err_f;
    }    
    else {
      ret_str ="javac -cp ../../lib/*:./"+comp_dir_lib+"/lib/*:"+comp_dir_lib+
      "/classes/. "+entry_str+" > /dev/null 2>> "+fs::temp_directory_path().string()+"/"+err_f;
      error_files+=", "+fs::temp_directory_path().string()+"/"+err_f;
    }
  }
  else {
    ret_str ="javac -cp ..\\..\\lib\\*;.\\"+comp_dir_lib+"\\lib\\*;"+comp_dir_lib+"\\classes\\. "+entry_str;
    cout<<ret_str<<endl;
  }
  return ret_str;
}

/**
 * Recursively compiles all java files in the tomcat (current) directory.
 * */
int pdmCli::comp_java(string path="./",int level=0){
  fs::path fp(path);
  for (const auto & entry : fs::directory_iterator(fp)){
    if(fs::is_directory(entry.path())&&(level!=0 || entry.path().filename()==comp_dir_lib)){
      comp_java(entry.path().relative_path().string(), level+1);
    }
    else if(fs::is_regular_file(entry) && entry.path().extension() == ".java"){
      int ret_val=system(comp_file_str(entry.path().relative_path().string()).c_str());
      if(ret_val==0){
        compiled_java_count++;
      }
      else {
        error_count++;
      }
    }
  }
  if (level==0){
    cout<<"Compiled "<< compiled_java_count<<" java files"<<endl;
    cout<<"Compiled "<< error_files<<" warnings files"<<endl;
    if(error_count!=0){
      cout<<"Compile error "<< error_count<<" times, error output to \""<<fs::temp_directory_path().string()+"{"+error_files+"}"<<endl;
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

int pdmCli::clear_count(){
  error_count=0;
  compiled_java_count=0;
  return 1;
}

int pdmCli::run() {
  clear_count();
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