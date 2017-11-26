#My cmake command to build local VS 2013 solution:
#- this command should be executed from command line in folder that contains source files
#- change DCMAKE_C_COMPILER and DCMAKE_CXX_COMPILER to appropriate paths (if needed)
#- i did not found a solution for define parameters DCMAKE_C_COMPILER and DCMAKE_CXX_COMPILER inside CMakeLists. 
#  Because there is a text coding problem with polish letter 'ó' in my compiler's path.

cmake -DCMAKE_C_COMPILER="D:/Pliki programów (x86)/Microsoft Visual Studio 12.0/VC/bin/cl.exe" -DCMAKE_CXX_COMPILER="D:/Pliki programów (x86)/Microsoft Visual Studio 12.0/VC/bin/cl.exe"