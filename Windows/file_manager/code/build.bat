@echo off

mkdir ..\build
pushd ..\build
cl -Zi ..\code\manager.c
popd
