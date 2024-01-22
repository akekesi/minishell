# minishell
1. [Notation](#notation)
1. [ToDo](#todo)
1. [Authors](#authors)
1. [Question](#question)
1. [Bug](#bug)
1. [Test](#test)

## Notation
- [ ] 😭
- [p] in prgress
- [i] impelemented
- [e] error
- [x] tested

## ToDo
- [x] Create GitHub repo
- [x] Create automated test file with color
- [x] main.c
- [x] minishell.h
- [x] Makefile
- [p] parser
    - [p] " and '
    - [ ] $
    - [ ] different position of cmd and arg
    - [ ] test
- [p] impelemt cmd
    - [i] cd
    - [i] echo
    - [i] env
    - [i] exit
    - [i] export
    - [i] pwd
    - [i] unset
    - [ ] test
- [p] ctrl + C,D,\
    - [ ] test
- [ ] pipe
    - [ ] test
- [ ] multiple pipe
    - [ ] test
- [ ] redirection
    - [ ] test
- [ ] Display a prompt when waiting for a new command
    - [ ] test
- [ ] Have a working history.
    - [ ] test
- [ ] Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
    - [ ] test
- [ ] Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures.
    - [ ] test

## Question

## Bug

## Test
- multiple pipe
    - pip list |
    - pip list ||
    - pip list |||

## Authors
- [Taka Nakajo](https://github.com/tnakajo42)
- [Attila Kekesi](https://github.com/akekesi)
