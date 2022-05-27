#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

class Runnable {
public:
  virtual bool run ()=0 ;
  virtual bool matches(char a)=0;
  int rderr (int err){
    #ifdef DEBUG//debug
      cout<<"Output: "<< err<<endl;
      system("ls");
    #endif//debug
    return 1;
  }
  virtual std::string description()=0;
  virtual char match ()=0;
  bool is_silent=0;
};

class LogsRead : public Runnable {
public:
  bool run (){
    if(!is_silent)
      std::cout<<"Reading Logs... "<<std::endl;
    rderr(system("cat /usr/local/tomcat/logs/catalina.out"));
    return 1;
  }
  bool matches (char a) {return match() == a;}
  char match() {return 'l';}  
  std::string description() { return "See tomcat logs.";}
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
    rderr(system("chmod 777 /usr/local/tomcat/logs/*"));
    rderr(system("chown tomcat:tomcat /usr/local/tomcat/logs/*"));
    
    return 1;
  }
  bool matches (char a) {return match() == a;}
  char match (){return 'c';}  
  std::string description() { return "Back up and clear the logs.";}
};

class RestartTomcat :public Runnable {
public:
  bool run (){
    if(!is_silent)
      std::cout<<"Restarting Tomcat... "<<std::endl;
    rderr(system("sh /usr/local/tomcat/bin/shutdown.sh"));
    rderr(system("sh /usr/local/tomcat/bin/startup.sh"));
    return 1;
  }
  bool matches (char a) {return match() == a;}
  char match() {return 'x'; }  
  std::string description() { return "Restarts tomcat using provided scripts.";}
};

class ToTomcatDir :public Runnable {
public:
  bool run (){
    if(!is_silent)
      std::cout<<"Going tomcat directory."<<std::endl;
    rderr(system("cd /usr/local/tomcat"));
    return 1;
  }
  bool matches (char a) {return match() == a;}
  char match() {return 't';}  
  std::string description() { return "Go to the tomcat directory.";}
};