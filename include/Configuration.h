#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
using namespace std;

class Configuration {

  public:
    string get_dotcastle_dir();
    Configuration(string dotcastle_config_file);

  private:
    string dotcastle_dir;

};

#endif
