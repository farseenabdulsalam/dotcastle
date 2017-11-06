#include "Configuration.h"
#include "Exceptions.h"
#include <fstream>
#include <string>

using namespace std;

Configuration::Configuration(string dotcastle_config_file) {
  auto infile = ifstream(dotcastle_config_file);
  if(!infile.is_open())
    throw ConfigurationFileDoesnotExist();
  string first_line;
  getline(infile, first_line);
  dotcastle_dir = first_line.substr(0,first_line.size());
}

string Configuration::get_dotcastle_dir() {
  return dotcastle_dir;
}
  

