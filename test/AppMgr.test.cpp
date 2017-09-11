#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AppMgr
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

#include "AppMgr.h"
#include "Exceptions.h"

using namespace std;
namespace fs = boost::filesystem;


// ----- Basic setup

struct fixture_base {
  fs::path dotcastle_dir;
};

struct fixture_valid_dotcastle_dir : public fixture_base {
  fixture_valid_dotcastle_dir() { // setup
    auto temp_path = fs::temp_directory_path();
    dotcastle_dir = temp_path / "temp_dotcastle";
    fs::create_directory(dotcastle_dir);
  }
  ~fixture_valid_dotcastle_dir() { // teardown
    fs::remove_all(dotcastle_dir);
  }
};

struct fixture_invalid_dotcastle_dir : public fixture_base {
  fixture_invalid_dotcastle_dir() { // setup
    auto temp_path = fs::temp_directory_path();
    dotcastle_dir = temp_path / "temp_dotcastle";
    fs::remove_all(dotcastle_dir);
  }
  ~fixture_invalid_dotcastle_dir() { // teardown
    fs::remove_all(dotcastle_dir);
  }
};


BOOST_FIXTURE_TEST_CASE (list_apps, fixture_valid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  vector<App> created_apps;
  for(int i=0;i<3;i++) {
    string app_name = string("app_")+(char)('0'+i);
    created_apps.push_back({app_name});
    fs::create_directory(dotcastle_dir/app_name);
  }
  AppMgr app_mgr(dotcastle_dir.string());
  auto listed_apps = app_mgr.list_apps();
  for(auto app: created_apps) {
    bool is_app_found = false;
    for(auto app_listed: listed_apps) { 
      if(app.name==app_listed.name) {
        is_app_found = true; break;
      }
    }
    BOOST_CHECK_MESSAGE(/*ifnot*/ is_app_found,"App "+app.name+" not listed.");
  }
}

BOOST_FIXTURE_TEST_CASE (list_apps_invalid_dotcastle_dir,
                         fixture_invalid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  AppMgr app_mgr(dotcastle_dir.string());
  BOOST_CHECK_THROW(app_mgr.list_apps(),InvalidDotcastleDir);
}

BOOST_FIXTURE_TEST_CASE (list_config_groups_for_app_invalid_dotcastle_dir,
                         fixture_invalid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  AppMgr app_mgr(dotcastle_dir.string());
  BOOST_CHECK_THROW(app_mgr.list_config_groups_for_app({"doesnt matter"}),
                    InvalidDotcastleDir);
}
  
BOOST_FIXTURE_TEST_CASE (list_config_groups_for_app_non_existent_app,
                         fixture_valid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  AppMgr app_mgr(dotcastle_dir.string());
  BOOST_CHECK_THROW(app_mgr.list_config_groups_for_app({"doesnt matter"}),
                    NonExistentApp);
}

BOOST_FIXTURE_TEST_CASE (list_config_groups_for_app,
                         fixture_valid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  AppMgr app_mgr(dotcastle_dir.string());

  string app_name("app_test");
  auto app_dir_path = dotcastle_dir/app_name;
  string config_group_name("config_group_test");
  auto config_group_install_file = app_dir_path/(config_group_name+".install");
app_dir_path/(config_group_name+".install");
  fs::create_directory(app_dir_path);
  fs::ofstream file_stream(config_group_install_file);
  file_stream.close();

  auto listed_config_groups = app_mgr.list_config_groups_for_app({app_name});
  
  BOOST_CHECK_EQUAL(listed_config_groups.front().name,config_group_name);

}

