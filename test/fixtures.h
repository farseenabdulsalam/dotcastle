#include <boost/filesystem.hpp>
#include <string>

using namespace std;

namespace fs = boost::filesystem;


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

