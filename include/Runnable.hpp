#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

class Runnable {
public:
  bool run () {return 0;};
  bool run (char a);
  bool matches(char a){
    return a == match;
  }
  bool matches(std::string a);
  std::string description;
  int rderr (int err){
    #ifdef DEBUG//debug
      cout<<"Output: "<< err<<endl;
      system("ls");
    #endif//debug
    return 1;
  }
  char match ;
  bool is_silent=0;
};

class LogsRead : public Runnable {
public:
  LogsRead(){
    description = "See tomcat logs.";
    match = 'l'; 
  }
  bool run (){
    if(!is_silent)
      std::cout<<"Reading Logs... "<<std::endl;
    rderr(system("cat /usr/local/tomcat/logs/catalina.out"));
    return 1;
  }
};

class LogsClean : public Runnable {
public:
  
  LogsClean(){
    description = "Clean and back up the logs.";
    match = 'c'; 
  }
  bool run (){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    auto time_str = oss.str();

    std::string command_out = "mv /usr/local/tomcat/logs/catalina.out /usr/local/tomcat/logs/back_";
    command_out += time_str;
    command_out += ".txt";
    if(!is_silent)
      std::cout<<"Cleaning logs... "<<std::endl;
    system(command_out.data());
    rderr(system("echo \"\" > /usr/local/tomcat/logs/catalina.out"));
    return 1;
  }
  
};

class RestartTomcat : public Runnable {
public:
  RestartTomcat(){
    description = "Restarts tomcat using provided scripts.";
    match = 'x'; 
  }
  bool run (){
    if(!is_silent)
      std::cout<<"Restarting Tomcat... "<<std::endl;
    rderr(system("sh /usr/local/tomcat/bin/shutdown.sh"));
    rderr(system("sh /usr/local/tomcat/bin/startup.sh"));
    return 1;
  }
};

class ToTomcatDir : public Runnable {
public:
  ToTomcatDir(){
    description = "Go to the tomcat directory.";
    match = 't'; 
  }
  bool run (){
    if(!is_silent)
      std::cout<<"Going tomcat directory."<<std::endl;
    rderr(system("cd /usr/local/tomcat"));
    return 1;
  }
};