#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AppMgr
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "AppMgr.h"
#include "Exceptions.h"
#include "fixtures.h"
using namespace std;
namespace fs = boost::filesystem;

BOOST_FIXTURE_TEST_CASE (app_mgr_constructor_invalid_dotcastle_dir_exception,
                         fixture_invalid_dotcastle_dir) {
  // fs::path dotcastle_dir from fixture
  BOOST_CHECK_THROW(AppMgr app_mgr(dotcastle_dir.string()),
                    InvalidDotcastleDir);
}
