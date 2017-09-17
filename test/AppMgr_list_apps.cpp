#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AppMgr
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include "AppMgr.h"
#include "Exceptions.h"
#include "fixtures.h"

using namespace std;
namespace fs = boost::filesystem;


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

BOOST_FIXTURE_TEST_CASE (make_app_non_existent_app,
                         fixture_valid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  AppMgr app_mgr(dotcastle_dir.string());
  BOOST_CHECK_THROW(app_mgr.make_config_group_of_app({"doesnt matter"},{"doesnt matter"}),
                    NonExistentApp);
}