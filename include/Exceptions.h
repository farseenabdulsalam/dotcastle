
class DotcastleError {};

// TODO: add given_path to the exception class
class InvalidDotcastleDir: public DotcastleError {};
// TODO: add name of app to the exception class
class NonExistentApp: public DotcastleError {};
// TODO: add retcode, app name, config group name to the exception class
class AppConfigGroupMakeFailed: public DotcastleError {};

class ConfigurationFileDoesnotExist: public DotcastleError {};

class InvalidConfigurationFile: public DotcastleError {};
