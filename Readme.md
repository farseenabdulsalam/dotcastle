
#Dotcastle
###### Version 0.1b

Do you find you .bashrc/.zshrc too large to maintain?
Have you felt that it is finding and updating the right options in vimrc
is a real headache?
Do you have to maintain two versions of almost similar configuration file,
because a few tweaks you made for your home computer are incompatible with
your work environment?

Dotcastle is designed to solve these problems.
It helps to seperate a configuration file into logical units,
preprocess them combine them and copy the resulting file to the respective
configuration dirs.

It also has this concept of configuration group which lets you preprocess
and copy over the files differently for your home computer and work computer.

Plus, you can share the common parts of a configuration file across configuration groups.


## Install
Running `make` creates a single binary `dotcastle`.
Copy it to `/usr/bin` or anywhere you wish.

## Setting up your castle
The configuration files are organized as
```
<DOTCASTLE>/
  -- app
      -- config-group1.make
      -- config-group1.install
      -- config-group2.make
      -- config-group2.install
      -- file1_to_be_processed_by_make
      -- file2_to_be_processed_by_make
      -- output_file1
      -- output_file2
  -- Readme.md

```

Example:

```
/home/farzeen/dotcastle/
  -- vim
      -- home.make
      -- home.install
      -- office.make
      -- office.install
      -- keybindings
      -- plugins
      -- extra_options
      -- vimrc.office
      -- vimrc.home
  -- i3
      -- home.make
      -- home.install
      -- variables
      -- basic_keybindings
      -- auto_start_apps
      -- app_keybindings
      -- i3config.home
  -- bash
      -- office.make
      -- office.install
      -- home.make
      -- home.install
      -- bashrc.home
      -- bashrc.office
  -- zsh
      -- office.make
      -- office.install
      -- home.make
      -- home.install
      -- zshrc.home
      -- zshrc.install
  -- Readme.md
  -- common_env_vars    // This file can be included into bashrc and zshrc by
                        // respective make scripts
```

##Usage:

```
dotcastle
  or
dotcastle -l|--list
   Show a hierarchial list like:
      ConfigGroup1
       .. App1
       .. App2
      ConfigGroup2
       .. App2
       .. App3

dotcastle -lc|--list-config-groups 
   Show the list of config groups

dotcastle -la|--list-apps
   Show the list of apps

dotcastle -m|--make    <config-group>[/<app>]
dotcastle -i|--install <config-group>[/<app>]
  if <app> is omitted, all apps under the <config-group> are processed. 

Example:

dotcastle -m office_conf
dotcastle -m office_conf/vim
```