# Flamex
A 2d/3d framework for making games, written in C++

# How to compile
## Linux
Make sure you have make, gcc, premake, and OpenGL installed in your system to compile Flamex.

With that set up, all you have to do is run the compile and run scripts to build and run Flamex.

If this doesn't work, run the following commands to manually compile and run everything:
```
premake5 gmake
make
./run
```

## Windows

### Warning for visual studio compilation!
To run the program with visual studio correctly, you need to manually run the application shown in the directory below:
```
project_directory/bin/.../Flamex.exe
```
This is because for Flamex to run properly, it needs to access files at runtime that visual studio fails to find in its default directory location.

### Visual Studio
To compile with visual studio 2022, run the following command in a terminal
```
./premake5 vs2022
```
This should create a .sln file which can be opened with visual studio.
