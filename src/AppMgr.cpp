#include "AppMgr.h"
#include "Exceptions.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/convenience.hpp>
#include "cpp-subprocess/subprocess.hpp"

using namespace std;
namespace fs = boost::filesystem;

AppMgr::AppMgr(string path_to_dotcastle_dir) {
  dotcastle_dir_path = path_to_dotcastle_dir;
  if(!fs::is_directory(dotcastle_dir_path))
    throw InvalidDotcastleDir();
}


list<App> AppMgr::list_apps() {
  fs::directory_iterator dotcastle_dir_itr(dotcastle_dir_path);
  list<App> app_list;
  for(auto itr: dotcastle_dir_itr) {
    auto dir_ent_path = itr.path();
    if(!fs::is_directory(dir_ent_path)) continue;
    auto app_name = dir_ent_path.filename().string();
    app_list.push_back(App {app_name});
  }
  return app_list;
}

list<ConfigGroup> AppMgr::list_config_groups_for_app(App app) {
  auto app_dir_path = dotcastle_dir_path / app.name;
  if(!fs::is_directory(app_dir_path))
      throw NonExistentApp();

  list<ConfigGroup> config_groups_list;
  fs::directory_iterator app_dir_itr(app_dir_path);

  string install_file_ext(".install");

  for(auto itr_entry: app_dir_itr) {
    auto file = itr_entry.path();
    if(fs::extension(file) == install_file_ext) {
      config_groups_list.push_back({fs::basename(file)});
    }
  }
  return config_groups_list;
}

void AppMgr::make_config_group_of_app(ConfigGroup cg, App app) {
  namespace proc = subprocess;
  auto app_dir_path = dotcastle_dir_path / app.name;
  if(!fs::is_directory(app_dir_path))
      throw NonExistentApp();

  auto retcode = proc::call((app_dir_path/(cg.name+".make")).string(),
                             proc::cwd{app_dir_path.string()});
  if(retcode!=0)
    throw AppConfigGroupMakeFailed();
}

void AppMgr::install_config_group_of_app(ConfigGroup cg, App app) {
  namespace proc = subprocess;
  auto app_dir_path = dotcastle_dir_path / app.name;
  if(!fs::is_directory(app_dir_path))
      throw NonExistentApp();

  auto retcode = proc::call((app_dir_path/(cg.name+".install")).string(),
                             proc::cwd{app_dir_path.string()});
  if(retcode!=0)
    throw AppConfigGroupMakeFailed();
}
