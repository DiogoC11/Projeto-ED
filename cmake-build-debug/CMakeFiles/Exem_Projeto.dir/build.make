# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Users\diogoacardoso\AppData\Local\JetBrains\CLion 2024.1.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\diogoacardoso\AppData\Local\JetBrains\CLion 2024.1.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\diogoacardoso\Documents\Projeto-ED

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Exem_Projeto.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Exem_Projeto.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Exem_Projeto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Exem_Projeto.dir/flags.make

CMakeFiles/Exem_Projeto.dir/main.c.obj: CMakeFiles/Exem_Projeto.dir/flags.make
CMakeFiles/Exem_Projeto.dir/main.c.obj: C:/Users/diogoacardoso/Documents/Projeto-ED/main.c
CMakeFiles/Exem_Projeto.dir/main.c.obj: CMakeFiles/Exem_Projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Exem_Projeto.dir/main.c.obj"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Exem_Projeto.dir/main.c.obj -MF CMakeFiles\Exem_Projeto.dir\main.c.obj.d -o CMakeFiles\Exem_Projeto.dir\main.c.obj -c C:\Users\diogoacardoso\Documents\Projeto-ED\main.c

CMakeFiles/Exem_Projeto.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Exem_Projeto.dir/main.c.i"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\diogoacardoso\Documents\Projeto-ED\main.c > CMakeFiles\Exem_Projeto.dir\main.c.i

CMakeFiles/Exem_Projeto.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Exem_Projeto.dir/main.c.s"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\diogoacardoso\Documents\Projeto-ED\main.c -o CMakeFiles\Exem_Projeto.dir\main.c.s

CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.obj: CMakeFiles/Exem_Projeto.dir/flags.make
CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.obj: C:/Users/diogoacardoso/Documents/Projeto-ED/src/Biblioteca.c
CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.obj: CMakeFiles/Exem_Projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.obj"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.obj -MF CMakeFiles\Exem_Projeto.dir\src\Biblioteca.c.obj.d -o CMakeFiles\Exem_Projeto.dir\src\Biblioteca.c.obj -c C:\Users\diogoacardoso\Documents\Projeto-ED\src\Biblioteca.c

CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.i"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\diogoacardoso\Documents\Projeto-ED\src\Biblioteca.c > CMakeFiles\Exem_Projeto.dir\src\Biblioteca.c.i

CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.s"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\diogoacardoso\Documents\Projeto-ED\src\Biblioteca.c -o CMakeFiles\Exem_Projeto.dir\src\Biblioteca.c.s

CMakeFiles/Exem_Projeto.dir/src/Livro.c.obj: CMakeFiles/Exem_Projeto.dir/flags.make
CMakeFiles/Exem_Projeto.dir/src/Livro.c.obj: C:/Users/diogoacardoso/Documents/Projeto-ED/src/Livro.c
CMakeFiles/Exem_Projeto.dir/src/Livro.c.obj: CMakeFiles/Exem_Projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Exem_Projeto.dir/src/Livro.c.obj"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Exem_Projeto.dir/src/Livro.c.obj -MF CMakeFiles\Exem_Projeto.dir\src\Livro.c.obj.d -o CMakeFiles\Exem_Projeto.dir\src\Livro.c.obj -c C:\Users\diogoacardoso\Documents\Projeto-ED\src\Livro.c

CMakeFiles/Exem_Projeto.dir/src/Livro.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Exem_Projeto.dir/src/Livro.c.i"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\diogoacardoso\Documents\Projeto-ED\src\Livro.c > CMakeFiles\Exem_Projeto.dir\src\Livro.c.i

CMakeFiles/Exem_Projeto.dir/src/Livro.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Exem_Projeto.dir/src/Livro.c.s"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\diogoacardoso\Documents\Projeto-ED\src\Livro.c -o CMakeFiles\Exem_Projeto.dir\src\Livro.c.s

CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.obj: CMakeFiles/Exem_Projeto.dir/flags.make
CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.obj: C:/Users/diogoacardoso/Documents/Projeto-ED/src/Pessoa.c
CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.obj: CMakeFiles/Exem_Projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.obj"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.obj -MF CMakeFiles\Exem_Projeto.dir\src\Pessoa.c.obj.d -o CMakeFiles\Exem_Projeto.dir\src\Pessoa.c.obj -c C:\Users\diogoacardoso\Documents\Projeto-ED\src\Pessoa.c

CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.i"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\diogoacardoso\Documents\Projeto-ED\src\Pessoa.c > CMakeFiles\Exem_Projeto.dir\src\Pessoa.c.i

CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.s"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\diogoacardoso\Documents\Projeto-ED\src\Pessoa.c -o CMakeFiles\Exem_Projeto.dir\src\Pessoa.c.s

CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.obj: CMakeFiles/Exem_Projeto.dir/flags.make
CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.obj: C:/Users/diogoacardoso/Documents/Projeto-ED/src/Requisicao.c
CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.obj: CMakeFiles/Exem_Projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.obj"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.obj -MF CMakeFiles\Exem_Projeto.dir\src\Requisicao.c.obj.d -o CMakeFiles\Exem_Projeto.dir\src\Requisicao.c.obj -c C:\Users\diogoacardoso\Documents\Projeto-ED\src\Requisicao.c

CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.i"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\diogoacardoso\Documents\Projeto-ED\src\Requisicao.c > CMakeFiles\Exem_Projeto.dir\src\Requisicao.c.i

CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.s"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\diogoacardoso\Documents\Projeto-ED\src\Requisicao.c -o CMakeFiles\Exem_Projeto.dir\src\Requisicao.c.s

CMakeFiles/Exem_Projeto.dir/src/Uteis.c.obj: CMakeFiles/Exem_Projeto.dir/flags.make
CMakeFiles/Exem_Projeto.dir/src/Uteis.c.obj: C:/Users/diogoacardoso/Documents/Projeto-ED/src/Uteis.c
CMakeFiles/Exem_Projeto.dir/src/Uteis.c.obj: CMakeFiles/Exem_Projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Exem_Projeto.dir/src/Uteis.c.obj"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Exem_Projeto.dir/src/Uteis.c.obj -MF CMakeFiles\Exem_Projeto.dir\src\Uteis.c.obj.d -o CMakeFiles\Exem_Projeto.dir\src\Uteis.c.obj -c C:\Users\diogoacardoso\Documents\Projeto-ED\src\Uteis.c

CMakeFiles/Exem_Projeto.dir/src/Uteis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Exem_Projeto.dir/src/Uteis.c.i"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\diogoacardoso\Documents\Projeto-ED\src\Uteis.c > CMakeFiles\Exem_Projeto.dir\src\Uteis.c.i

CMakeFiles/Exem_Projeto.dir/src/Uteis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Exem_Projeto.dir/src/Uteis.c.s"
	C:\Users\DIOGOA~1\AppData\Local\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\diogoacardoso\Documents\Projeto-ED\src\Uteis.c -o CMakeFiles\Exem_Projeto.dir\src\Uteis.c.s

# Object files for target Exem_Projeto
Exem_Projeto_OBJECTS = \
"CMakeFiles/Exem_Projeto.dir/main.c.obj" \
"CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.obj" \
"CMakeFiles/Exem_Projeto.dir/src/Livro.c.obj" \
"CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.obj" \
"CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.obj" \
"CMakeFiles/Exem_Projeto.dir/src/Uteis.c.obj"

# External object files for target Exem_Projeto
Exem_Projeto_EXTERNAL_OBJECTS =

Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/main.c.obj
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/src/Biblioteca.c.obj
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/src/Livro.c.obj
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/src/Pessoa.c.obj
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/src/Requisicao.c.obj
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/src/Uteis.c.obj
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/build.make
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/linkLibs.rsp
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/objects1.rsp
Exem_Projeto.exe: CMakeFiles/Exem_Projeto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable Exem_Projeto.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Exem_Projeto.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Exem_Projeto.dir/build: Exem_Projeto.exe
.PHONY : CMakeFiles/Exem_Projeto.dir/build

CMakeFiles/Exem_Projeto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Exem_Projeto.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Exem_Projeto.dir/clean

CMakeFiles/Exem_Projeto.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\diogoacardoso\Documents\Projeto-ED C:\Users\diogoacardoso\Documents\Projeto-ED C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug C:\Users\diogoacardoso\Documents\Projeto-ED\cmake-build-debug\CMakeFiles\Exem_Projeto.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Exem_Projeto.dir/depend

