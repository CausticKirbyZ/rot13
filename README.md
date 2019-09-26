# rot13
[![Build Status](https://travis-ci.org/CausticKirbyZ/rot13.svg?branch=master)](https://travis-ci.org/CausticKirbyZ/rot13)

https://github.com/CausticKirbyZ/rot13
>```
>           _   _ _____
>  _ __ ___ | |_/ |___ /
>| '__/ _ \| __| | |_ \
>| | | (_) | |_| |___) |
>|_|  \___/ \__|_|____/
>
## Install
> $ git clone https://github.com/CausticKirbyZ/rot13.git

## Syntax
>rot13 (-d | -e) [-o ``<charoffset``>][-ex <exclusion list][-ch ``<charset``>] ( (-f ``<filename``>) | ``<message``> )

## Usage
```
 ./rot13 -e message
 ./rot13 -e -o 7 -f file1.txt
 ./rot13 -d -o 3 -ch abcd -f file2.txt
 ./rot13 -e -o 5 -ex , -f file3.csv
``` 

## Flags
```  
  options:
 -------------------

  -d               decode
  -e               encode
  -o               offset
  -f               file input
  -ex              exclusion list
  -ch              character set, default is entire ascii table
  -h, --help       help me
