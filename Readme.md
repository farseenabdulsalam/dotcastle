# Dotcastle
###### Version 0.1b

Do you find you .bashrc/.zshrc too large to maintain?
Have you felt that is finding and updating the right options in vimrc
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
Running `make dotcastle` creates a single binary `dotcastle`.
Copy it to `/usr/bin` or anywhere you wish.

### Dependencies
Dotcastle depends upon Boost Filesystem and Boost Unit test and cpp-subprocess libraries.

* Boost libraries and header files must be installed using system package manager.
  On Arch Linux, install the `boost` package.

* Specify `--recursive` option during cloning the repo, or
  Execute:
  ```
  git submodule init
  git submodule update
  ```

  to pull in cpp-subprocess.


## Setting up your castle
The configuration files are organized as:
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

## Usage:

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

## What are .make and .install files
Currently, `.make` and `.install` should be simple executables,
preferably shell scripts or python scripts.
They will be executed when `dotcastle` is called with
`--make` or `--install` options respectively.

## License
This software is free as in free speech and free beer.
Feel free to copy, modify or redistribute.

## Contributing
I would really appreciate any kind of contribution.
If you have any suggestion, feature request or found any bugs,
please open an issue.

FOSS is awesome.
