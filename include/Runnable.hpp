#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

class Runnable {
public:
  bool run ();
  bool run (char a);
  bool matches(char a);
  bool matches(std::string a);
  std::string description;
  int rderr (int err){
    #ifdef DEBUG//debug
      cout<<"Output: "<< err<<endl;
      system("ls");
    #endif//debug
    return 1;
  }
protected:
  bool is_silent=0;
  char match ;
};

class LogsRead : public Runnable {
public:
  bool run (){
    if(!is_silent)
      std::cout<<"Reading Logs... "<<std::endl;
    rderr(system("cat /usr/local/tomcat/logs/catalina.out"));
    return 1;
  }
  bool matches(char a){
    return a == match;
  }
  std::string description = "See tomcat logs.";
protected:
  char match = 'l';
};

class LogsClean : public Runnable {
public:
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
  bool matches(char a){
    return a == match;
  }
  std::string description = "Clean and back up the logs.";
protected:
  char match = 'c';
};

class RestartTomcat : public Runnable {
public:
  bool run (){
    if(!is_silent)
      std::cout<<"Restarting Tomcat... "<<std::endl;
    rderr(system("sh /usr/local/tomcat/bin/shutdown.sh"));
    rderr(system("sh /usr/local/tomcat/bin/startup.sh"));
    return 1;
  }
  bool matches(char a){
    return a == match;
  }
  std::string description = "Restarts tomcat using provided scripts.";
protected:
  char match = 'x';
};