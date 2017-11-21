#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
using namespace std;

class Configuration {

  public:
    string get_dotcastle_dir();

   /* Currently, the caller is responsible for expanding env vars in 
    * dotcastle_config_file path string.
    * Should it be the responsibility of this class? */
    Configuration(string dotcastle_config_file);

  private:
    string dotcastle_dir;

};

#endif
