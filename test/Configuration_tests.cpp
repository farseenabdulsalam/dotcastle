#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Configuration

#include <boost/test/unit_test.hpp>
#include "fixtures.h"

#include <boost/filesystem.hpp>
#include "Exceptions.h"
#include "Configuration.h"

namespace fs = boost::filesystem;

BOOST_FIXTURE_TEST_CASE (configuration_read_test,
                         fixture_valid_config_file) {
  // fs::path config_file from fixture

  // NOTE: config_file is not created by the fixture.
  //       Writing to its stream creates it.

  fs::ofstream file_stream(config_file);
  string dotcastle_dir("/home/test/dotcastle.tmp");
  file_stream << dotcastle_dir <<endl;
  file_stream.close();
  Configuration config(config_file.string());
  BOOST_CHECK_EQUAL(config.get_dotcastle_dir(), dotcastle_dir);
}
