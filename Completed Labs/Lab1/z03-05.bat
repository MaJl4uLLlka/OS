@echo off
@chcp 65001 > nul

@echo -- строка параметров: %*
@echo -- параметр 1: %1
@echo -- параметр 2: %2
@echo -- параметр 3: %3

set p1=%1
set p2=%2
set p3=%3

set /a result=p1%p3%p2

@echo result = %result%