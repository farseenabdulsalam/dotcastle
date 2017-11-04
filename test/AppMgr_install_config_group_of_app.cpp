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
BOOST_FIXTURE_TEST_CASE (install_app_non_existent_app,
                         fixture_valid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  AppMgr app_mgr(dotcastle_dir.string());
  BOOST_CHECK_THROW(
      app_mgr.install_config_group_of_app({"non_existent_cg"},
                                          {"non_existen_app"}
                                         ),
      NonExistentApp);
}
