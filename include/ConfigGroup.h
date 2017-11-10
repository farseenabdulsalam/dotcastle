#ifndef CONFIG_GROUP_H
#define CONFIG_GROUP_H

#include <string>

struct ConfigGroup {
  string name;
  bool operator== (const ConfigGroup &config_group) {
    return name == config_group.name;
  }
};

#endif
