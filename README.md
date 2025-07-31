# Tiny Config

This is a lightweight POC implementation made to learn the fundementals of c++ configuration parsers and such.
This project can be compiled into different things, but first to test it run this:
```sh
ẞ anon [tconfig] → sudo pacman -S gtest # or install gtest in your system of choice(using apt, dnf)
ẞ anon [tconfig] → make test
ẞ anon [tconfig] → cd build/ && ./test
NOTE: This file must run into the build/ directory, where the Testing directory is located, to get the data for the data assertions.
[==========] Running 6 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 1 test from str
[ RUN      ] str.basic
[       OK ] str.basic (0 ms)
[----------] 1 test from str (0 ms total)

[----------] 2 tests from ch
[ RUN      ] ch.basic
[       OK ] ch.basic (0 ms)
[ RUN      ] ch.spaces
[       OK ] ch.spaces (0 ms)
[----------] 2 tests from ch (0 ms total)

[----------] 2 tests from i32
[ RUN      ] i32.basic
[       OK ] i32.basic (0 ms)
[ RUN      ] i32.largequantity
[       OK ] i32.largequantity (0 ms)
[----------] 2 tests from i32 (0 ms total)

[----------] 1 test from boolean
[ RUN      ] boolean.basic
[       OK ] boolean.basic (0 ms)
[----------] 1 test from boolean (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 4 test suites ran. (0 ms total)
[  PASSED  ] 6 tests.
```

It supports 4 datatypes: `char`,`str`,`i32` and `boolean`
the program currently does not support having different sections(like toml, and ini), but for a
POC it is more than enough.

## Example

```
# config/config.cf
# Example of a program proxy implementation

program1.proxy.host="127.0.0.1" #(this is a string)
program1.proxy.port=9050        #(this is an i32)
program1.proxy.type="socks5"    #...
program1.proxy.enabled=true
program1.character='*'
```

to use such configuration you would do:

```c++
// program1_module.cpp

tconfig::TCParser
load_configuration()
{
 std::ifstream t("config/config.cf");
 std::stringstream buffer;
 buffer << t.rdbuf();
 tconfig::TCParser parser_result(buffer.str());
 parser_result.parse();
 return parser_result;
}
```

or whatever you would like.
