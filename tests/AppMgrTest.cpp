#include "../AppMgr.h"
#include "../Exceptions.h"

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <fmt/format.h>

using namespace std;
namespace fs = boost::filesystem;

// ----- Basic setup

fs::path give_a_valid_dotcastle_dir() {
  auto temp_path = fs::temp_directory_path();
  auto dotcastle_dir = temp_path / "temp_dotcastle";
  fs::create_directory(dotcastle_dir);
  return dotcastle_dir;
}

fs::path give_an_invalid_dotcastle_dir() {
  auto temp_path = fs::temp_directory_path();
  auto dotcastle_dir = temp_path / "temp_dotcastle";
  fs::remove_all(dotcastle_dir);
  return dotcastle_dir;
}

// ------ Test list_apps()

bool list_apps_normal() {
  auto dotcastle_dir = give_a_valid_dotcastle_dir();
  struct AppTest {
    string name;
    bool tested_ok;
  };
  AppTest apps_test[3];
  for(int i=0;i<3;i++) {
    apps_test[i] = AppTest {fmt::format("app_{0}",i), false};
    fs::create_directory(dotcastle_dir/apps_test[i].name);
  }

  AppMgr app_mgr(dotcastle_dir.string());
  auto apps_list = app_mgr.list_apps();
  for(App &app: apps_list) {
    for(AppTest &app_test: apps_test) {
      if(app_test.tested_ok) continue;
      if(app_test.name.compare(app.name)==0) {
        app_test.tested_ok = true;
        break;
      } 
    }
  }

  bool all_test_passed = true;
  for(AppTest app_test: apps_test) {
    if(app_test.tested_ok) continue;
    cout<<" ERROR: App "<<app_test.name<<" was not listed."<<endl;
    all_test_passed = false;
  }
  cout<<(all_test_passed?"PASSED":"FAILED")<<": AppMgr::list_apps() test."<<endl;
  fs::remove_all(dotcastle_dir);
  return all_test_passed;
}

bool list_apps_exception() {
  auto dotcastle_dir = give_an_invalid_dotcastle_dir();
  AppMgr app_mgr(dotcastle_dir.string());
  try {
    app_mgr.list_apps();
    cout<<"FAILED: Exception not thrown - InvalidDotcastleDir"<<endl;
    return false;
  } catch (InvalidDotcastleDir& d) {
    cout<<"PASSED: Exception caught - InvalidDotcastleDir"<<endl;
    return true;
  }
}
  
    

// --- MAIN ----

int main() {
  bool all_test_passed = true;
  all_test_passed &= list_apps_normal();
  all_test_passed &= list_apps_exception();
  
  if(all_test_passed)
    cout<<"* All tests have passed successfully."<<endl;
  else
    cout<<"* Some tests have failed."<<endl;
  return all_test_passed?0:-1;
}

