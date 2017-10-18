
#USAGE:

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

Example:

dotcastle -m office_conf
dotcastle -m office_conf/vim
```
