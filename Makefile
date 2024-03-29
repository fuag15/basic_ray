# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mike/old/ECS275B

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mike/ECS275B

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mike/ECS275B/CMakeFiles /home/mike/ECS275B/CMakeFiles/progress.make
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mike/ECS275B/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named specter

# Build rule for target.
specter: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 specter
.PHONY : specter

# fast build rule for target.
specter/fast:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/build
.PHONY : specter/fast

# target to build an object file
Background.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Background.o
.PHONY : Background.o

# target to preprocess a source file
Background.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Background.i
.PHONY : Background.i

# target to generate assembly for a file
Background.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Background.s
.PHONY : Background.s

# target to build an object file
BoundingBox.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/BoundingBox.o
.PHONY : BoundingBox.o

# target to preprocess a source file
BoundingBox.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/BoundingBox.i
.PHONY : BoundingBox.i

# target to generate assembly for a file
BoundingBox.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/BoundingBox.s
.PHONY : BoundingBox.s

# target to build an object file
Camera.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Camera.o
.PHONY : Camera.o

# target to preprocess a source file
Camera.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Camera.i
.PHONY : Camera.i

# target to generate assembly for a file
Camera.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Camera.s
.PHONY : Camera.s

# target to build an object file
Color.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Color.o
.PHONY : Color.o

# target to preprocess a source file
Color.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Color.i
.PHONY : Color.i

# target to generate assembly for a file
Color.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Color.s
.PHONY : Color.s

# target to build an object file
ConstantBackground.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/ConstantBackground.o
.PHONY : ConstantBackground.o

# target to preprocess a source file
ConstantBackground.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/ConstantBackground.i
.PHONY : ConstantBackground.i

# target to generate assembly for a file
ConstantBackground.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/ConstantBackground.s
.PHONY : ConstantBackground.s

# target to build an object file
DOFCamera.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/DOFCamera.o
.PHONY : DOFCamera.o

# target to preprocess a source file
DOFCamera.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/DOFCamera.i
.PHONY : DOFCamera.i

# target to generate assembly for a file
DOFCamera.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/DOFCamera.s
.PHONY : DOFCamera.s

# target to build an object file
Group.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Group.o
.PHONY : Group.o

# target to preprocess a source file
Group.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Group.i
.PHONY : Group.i

# target to generate assembly for a file
Group.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Group.s
.PHONY : Group.s

# target to build an object file
Image.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Image.o
.PHONY : Image.o

# target to preprocess a source file
Image.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Image.i
.PHONY : Image.i

# target to generate assembly for a file
Image.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Image.s
.PHONY : Image.s

# target to build an object file
LambertianMaterial.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/LambertianMaterial.o
.PHONY : LambertianMaterial.o

# target to preprocess a source file
LambertianMaterial.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/LambertianMaterial.i
.PHONY : LambertianMaterial.i

# target to generate assembly for a file
LambertianMaterial.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/LambertianMaterial.s
.PHONY : LambertianMaterial.s

# target to build an object file
Light.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Light.o
.PHONY : Light.o

# target to preprocess a source file
Light.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Light.i
.PHONY : Light.i

# target to generate assembly for a file
Light.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Light.s
.PHONY : Light.s

# target to build an object file
Material.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Material.o
.PHONY : Material.o

# target to preprocess a source file
Material.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Material.i
.PHONY : Material.i

# target to generate assembly for a file
Material.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Material.s
.PHONY : Material.s

# target to build an object file
MovingSphere.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/MovingSphere.o
.PHONY : MovingSphere.o

# target to preprocess a source file
MovingSphere.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/MovingSphere.i
.PHONY : MovingSphere.i

# target to generate assembly for a file
MovingSphere.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/MovingSphere.s
.PHONY : MovingSphere.s

# target to build an object file
Object.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Object.o
.PHONY : Object.o

# target to preprocess a source file
Object.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Object.i
.PHONY : Object.i

# target to generate assembly for a file
Object.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Object.s
.PHONY : Object.s

# target to build an object file
OctTree.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/OctTree.o
.PHONY : OctTree.o

# target to preprocess a source file
OctTree.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/OctTree.i
.PHONY : OctTree.i

# target to generate assembly for a file
OctTree.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/OctTree.s
.PHONY : OctTree.s

# target to build an object file
Parser.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Parser.o
.PHONY : Parser.o

# target to preprocess a source file
Parser.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Parser.i
.PHONY : Parser.i

# target to generate assembly for a file
Parser.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Parser.s
.PHONY : Parser.s

# target to build an object file
PinholeCamera.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/PinholeCamera.o
.PHONY : PinholeCamera.o

# target to preprocess a source file
PinholeCamera.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/PinholeCamera.i
.PHONY : PinholeCamera.i

# target to generate assembly for a file
PinholeCamera.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/PinholeCamera.s
.PHONY : PinholeCamera.s

# target to build an object file
Plane.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Plane.o
.PHONY : Plane.o

# target to preprocess a source file
Plane.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Plane.i
.PHONY : Plane.i

# target to generate assembly for a file
Plane.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Plane.s
.PHONY : Plane.s

# target to build an object file
Point.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Point.o
.PHONY : Point.o

# target to preprocess a source file
Point.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Point.i
.PHONY : Point.i

# target to generate assembly for a file
Point.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Point.s
.PHONY : Point.s

# target to build an object file
PointLight.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/PointLight.o
.PHONY : PointLight.o

# target to preprocess a source file
PointLight.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/PointLight.i
.PHONY : PointLight.i

# target to generate assembly for a file
PointLight.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/PointLight.s
.PHONY : PointLight.s

# target to build an object file
Primitive.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Primitive.o
.PHONY : Primitive.o

# target to preprocess a source file
Primitive.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Primitive.i
.PHONY : Primitive.i

# target to generate assembly for a file
Primitive.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Primitive.s
.PHONY : Primitive.s

# target to build an object file
Scene.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Scene.o
.PHONY : Scene.o

# target to preprocess a source file
Scene.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Scene.i
.PHONY : Scene.i

# target to generate assembly for a file
Scene.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Scene.s
.PHONY : Scene.s

# target to build an object file
Sphere.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Sphere.o
.PHONY : Sphere.o

# target to preprocess a source file
Sphere.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Sphere.i
.PHONY : Sphere.i

# target to generate assembly for a file
Sphere.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Sphere.s
.PHONY : Sphere.s

# target to build an object file
Time.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Time.o
.PHONY : Time.o

# target to preprocess a source file
Time.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Time.i
.PHONY : Time.i

# target to generate assembly for a file
Time.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Time.s
.PHONY : Time.s

# target to build an object file
Transformation.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Transformation.o
.PHONY : Transformation.o

# target to preprocess a source file
Transformation.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Transformation.i
.PHONY : Transformation.i

# target to generate assembly for a file
Transformation.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Transformation.s
.PHONY : Transformation.s

# target to build an object file
Vector.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Vector.o
.PHONY : Vector.o

# target to preprocess a source file
Vector.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Vector.i
.PHONY : Vector.i

# target to generate assembly for a file
Vector.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/Vector.s
.PHONY : Vector.s

# target to build an object file
specter.o:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/specter.o
.PHONY : specter.o

# target to preprocess a source file
specter.i:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/specter.i
.PHONY : specter.i

# target to generate assembly for a file
specter.s:
	$(MAKE) -f CMakeFiles/specter.dir/build.make CMakeFiles/specter.dir/specter.s
.PHONY : specter.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... specter"
	@echo "... Background.o"
	@echo "... Background.i"
	@echo "... Background.s"
	@echo "... BoundingBox.o"
	@echo "... BoundingBox.i"
	@echo "... BoundingBox.s"
	@echo "... Camera.o"
	@echo "... Camera.i"
	@echo "... Camera.s"
	@echo "... Color.o"
	@echo "... Color.i"
	@echo "... Color.s"
	@echo "... ConstantBackground.o"
	@echo "... ConstantBackground.i"
	@echo "... ConstantBackground.s"
	@echo "... DOFCamera.o"
	@echo "... DOFCamera.i"
	@echo "... DOFCamera.s"
	@echo "... Group.o"
	@echo "... Group.i"
	@echo "... Group.s"
	@echo "... Image.o"
	@echo "... Image.i"
	@echo "... Image.s"
	@echo "... LambertianMaterial.o"
	@echo "... LambertianMaterial.i"
	@echo "... LambertianMaterial.s"
	@echo "... Light.o"
	@echo "... Light.i"
	@echo "... Light.s"
	@echo "... Material.o"
	@echo "... Material.i"
	@echo "... Material.s"
	@echo "... MovingSphere.o"
	@echo "... MovingSphere.i"
	@echo "... MovingSphere.s"
	@echo "... Object.o"
	@echo "... Object.i"
	@echo "... Object.s"
	@echo "... OctTree.o"
	@echo "... OctTree.i"
	@echo "... OctTree.s"
	@echo "... Parser.o"
	@echo "... Parser.i"
	@echo "... Parser.s"
	@echo "... PinholeCamera.o"
	@echo "... PinholeCamera.i"
	@echo "... PinholeCamera.s"
	@echo "... Plane.o"
	@echo "... Plane.i"
	@echo "... Plane.s"
	@echo "... Point.o"
	@echo "... Point.i"
	@echo "... Point.s"
	@echo "... PointLight.o"
	@echo "... PointLight.i"
	@echo "... PointLight.s"
	@echo "... Primitive.o"
	@echo "... Primitive.i"
	@echo "... Primitive.s"
	@echo "... Scene.o"
	@echo "... Scene.i"
	@echo "... Scene.s"
	@echo "... Sphere.o"
	@echo "... Sphere.i"
	@echo "... Sphere.s"
	@echo "... Time.o"
	@echo "... Time.i"
	@echo "... Time.s"
	@echo "... Transformation.o"
	@echo "... Transformation.i"
	@echo "... Transformation.s"
	@echo "... Vector.o"
	@echo "... Vector.i"
	@echo "... Vector.s"
	@echo "... specter.o"
	@echo "... specter.i"
	@echo "... specter.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

