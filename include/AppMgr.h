#include <string>
#include <list>

#include "App.h"
#include "ConfigGroup.h"

#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

class AppMgr {
  private:
    fs::path dotcastle_dir_path;
  public:
    AppMgr(string path_to_dotcastle_dir);
    list<App>         list_apps();
    list<ConfigGroup> list_config_groups_for_app(App app);

    void              make_config_group_of_app(ConfigGroup cg, App app);
    void              install_config_group_of_app(ConfigGroup cg, App app);

};

