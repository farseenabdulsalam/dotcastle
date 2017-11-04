#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AppMgr
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include "AppMgr.h"
#include "Exceptions.h"
#include "fixtures.h"
using namespace std;
namespace fs = boost::filesystem;

BOOST_FIXTURE_TEST_CASE (list_config_groups_for_app_non_existent_app,
                         fixture_valid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  AppMgr app_mgr(dotcastle_dir.string());
  BOOST_CHECK_THROW(app_mgr.list_config_groups_for_app({"non_existent_app"}),
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
  fs::create_directory(app_dir_path);
  fs::ofstream file_stream(config_group_install_file);
  file_stream.close();

  auto listed_config_groups = app_mgr.list_config_groups_for_app({app_name});
  
  BOOST_CHECK_EQUAL(listed_config_groups.size(),1);
  BOOST_CHECK_EQUAL(listed_config_groups.front().name,config_group_name);

}
