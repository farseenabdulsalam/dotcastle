#include <string>
#include <list>

#include "App.h"
#include "ConfigGroup.h"


using namespace std;

class AppMgr {
  private:
    string path_to_dotcastle_dir;
  public:
    AppMgr(string path_to_dotcastle_dir):
      path_to_dotcastle_dir(path_to_dotcastle_dir) {};
    list<App>         list_apps();
    list<ConfigGroup> list_config_groups_for_app(App app);

    void              make_config_group_of_app(ConfigGroup cg, App app);
    void              install_config_group_of_app(ConfigGroup cg, App app);

};

