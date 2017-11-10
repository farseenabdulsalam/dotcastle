#ifndef APP_H
#define APP_H

#include <string>
using namespace std;
struct App {
  string name;
  bool operator==(const App &app) {
    return name == app.name;
  }
};

#endif
