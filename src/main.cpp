#include <iostream>
#include <iterator>
#include <set>
#include <map>
#include <algorithm>
#include <boost/program_options.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include "AppMgr.h"

using namespace std;
namespace po = boost::program_options;

// GLOBALS
char *exec_name;                               // init by main as argv[0]
po::options_description opts_desc;    
AppMgr app_mgr("/home/farzeen/dotcastle.tmp"); // !!!! FIXME !!!!
// END OF GLOBALS

void show_help();
void list_all();
void list_apps();
void list_config_groups();
void make(string config_slash_appname);
void install(string config_slash_appname);


void register_cli_options(/*global opts_desc*/) {
  opts_desc.add_options()
    ("help,h","Show help message.")
    ("list,l", "List all apps and config-groups hierarchially.")
    ("list-config-groups,c", "List config groups.")
    ("list-apps,a", "List apps")
    ("make,m",po::value<vector<string>>()->composing(),
              "Run make script of config-group/[app-name]. "
              "If app-name is omitted, the entire config-group is processed.")
    ("install,i",po::value<vector<string>>()->composing(),
              "Run install script of config-group/[app-name]. "
              "If app-name is omitted, the entire config-group is processed.")
    ;
}

void process_cli_options_values(const po::variables_map &vm) {
  if(vm.count("help")) {
    show_help();
    return;
  } 

  if (vm.count("list")) {
    list_all();
    return;
  } 

  //
  if(vm.count("list-config-groups")) {
    list_config_groups();
  }
  if(vm.count("list-apps")) {
    list_apps();
  }
  if(vm.count("list-config-groups")||vm.count("list-apps"))
    return;
  //

  if(vm.count("make")) {
    for (auto s : vm["make"].as<vector<string>>())
      make(s);
    return;
  }

  if(vm.count("install")) {
    for (auto s : vm["install"].as<vector<string>>())
      install(s);
    return;
  }
  show_help();
}


int main(int argc, char **argv) {
  exec_name = argv[0];
  register_cli_options();
  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc,argv, opts_desc), vm);
  } catch(const po::error &ex) {
    cerr<<ex.what()<<endl;
  }
  process_cli_options_values(vm);
}


void show_help() {
  cout<<endl;
  cout<<"Usage: "<<exec_name<<" command args "<<endl<<endl;
  cout<<"Commands:"<<endl;
  cout<<opts_desc<<endl;
}

void list_all() {
  map<string,vector<string>> config_group_apps_map;
  auto apps = app_mgr.list_apps();
  for(App app: apps) {
    auto config_groups = app_mgr.list_config_groups_for_app(app);
    for(ConfigGroup cg: config_groups) {
      config_group_apps_map[cg.name].push_back(app.name);
    }
  }
  cout<<"Listing all config-groups and apps: "<<endl; 
  for(auto pair : config_group_apps_map) {
    cout<<" - "<<pair.first<<endl;
    for(auto app : pair.second) {
      cout<<"    - "<<app<<endl;
    }
  }
}

void list_config_groups() {
  set<string> config_groups;
  auto apps = app_mgr.list_apps();
  for(App app: apps) {
    auto config_groups_for_app = app_mgr.list_config_groups_for_app(app);
    for(ConfigGroup cg: config_groups_for_app) {
      config_groups.insert(cg.name);
    }
  }
  cout<<"Listing all config-groups: "<<endl;
  for(auto cg : config_groups) {
    cout<<" - "<<cg<<endl;
  }
}

void list_apps() {
  cout<<"Listing all apps: "<<endl; 
  auto apps = app_mgr.list_apps();
  for(App app: apps)
    cout<<" - "<<app.name<<endl;
}


pair<string,vector<string>> 
__parse_config_slash_appname(string config_slash_appname) {
  auto slash_pos = config_slash_appname.find("/");
  string config_group = config_slash_appname.substr(0,slash_pos);  
  vector<string> apps;

  if(slash_pos == string::npos || 
     slash_pos == config_slash_appname.size() - 1) {
    for(auto app: app_mgr.list_apps()) {
      auto config_groups = app_mgr.list_config_groups_for_app(app);
      auto it = find(
                      config_groups.begin(),
                      config_groups.end(), 
                      ConfigGroup{config_group}
                    );
      if(it!=config_groups.end()) {
        apps.push_back(app.name);
      }
    }
  } else {
    apps.push_back(config_slash_appname.substr(slash_pos+1));
  }
  return {config_group,apps};
}

void make(string config_slash_appname) {
  cout<<"Making: "<<config_slash_appname<<endl; //TODO
  pair<string,vector<string>> config_and_apps =
          __parse_config_slash_appname(config_slash_appname);
  for(auto app: config_and_apps.second) {
    cout<<"   - "<<app<<endl;
    app_mgr.make_config_group_of_app({config_and_apps.first}, {app});
  }
}

void install(string config_slash_appname) {
  cout<<"Installing: "<<config_slash_appname<<endl; //TODO
  pair<string,vector<string>> config_and_apps =
          __parse_config_slash_appname(config_slash_appname);
  for(auto app: config_and_apps.second) {
    cout<<"   - "<<app<<endl;
    app_mgr.install_config_group_of_app({config_and_apps.first}, {app});
  }
}
