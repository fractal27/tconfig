# tconfig

A minimal configurations library with 4 types: char,str,int and boolean.

## Installation

It can be installed using the affiliated program `./install_sh` that can or can also not run on superprivileges, the only difference, will be the locality of the installation.

```bash
$ sudo ./install_sh
[ WARNING       ] installing as root: using `/usr` path to install library.
[ PROCESS       ] library directory: /usr/lib
[ PROCESS       ] initializing installation
...
[ OK    ] Library successfully made.
[ WARNING       ] library 'libtconfig.a' already installed
```
Where in `...` there is the cmake building process of the static library.

## Syntax

The syntax is as follows, as an example i will make a configuration for a project of a logger.

```
projectname = "test_project"
path= "/path/to/project"
base-debugging-level = 10

color-debug="lightblue"
color-info="green"
color-warning="orange"
color-error="red"
color-fatal="darkred"

static=false
format="({date}) [ {levelname}\t] {message}\n"
datefmt=%H:%M:%S
```

A way to do comments is underway development.


