#include <string>
using namespace std;
struct App {
  string name;
  bool operator==(const App &app) {
    return name == app.name;
  }
};
