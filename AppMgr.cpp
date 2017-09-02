#include "AppMgr.h"
#include "Exceptions.h"
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

list<App> AppMgr::list_apps() {
  fs::path dotcastle_dir_path(path_to_dotcastle_dir);  

  if(!fs::is_directory(dotcastle_dir_path))
    throw InvalidDotcastleDir();

  fs::directory_iterator dotcastle_dir_itr(dotcastle_dir_path);

  list<App> app_list;

  for(auto itr: dotcastle_dir_itr) {
    auto dir_ent_path = itr.path();
    auto app_name = dir_ent_path.filename().string(); 
    app_list.push_back(App {app_name});
  }
  
  return app_list;
}
