#### VARS ####

RMRF = rm -rf
MKDIRP = mkdir -p
PROJECT_LIBDIR = lib
CD = cd
CMAKE = cmake

#### PARAMETERS ####

CMAKE_BUILD = cmake-build

#### TARGETS ####

all: git libs make

git: git-init

make: main

clean: main-clean libs-clean

libs: glfw3

libs-clean: glfw3-clean

#### GIT ####

git-init:
	git submodule init
	git submodule update

#### MAIN ####

main: main-configure main-make

main-configure:
	$(MKDIRP) ${CMAKE_BUILD}
	$(CD) ${CMAKE_BUILD} && $(CMAKE) ../

main-make:
	$(CD) ${CMAKE_BUILD} && $(MAKE)

main-clean:
	$(RMRF) ${CMAKE_BUILD}

#### GFLW3 ####

glfw3: glfw3-configure glfw3-make

glfw3-configure:
	$(MKDIRP) ${PROJECT_LIBDIR}/glfw/${CMAKE_BUILD} && \
		$(CD) ${PROJECT_LIBDIR}/glfw/${CMAKE_BUILD} && \
		$(CMAKE) ../ \
			-DGLFW_BUILD_EXAMPLES=OFF \
			-DGLFW_BUILD_TESTS=OFF

glfw3-make:
	$(CD) ${PROJECT_LIBDIR}/glfw/${CMAKE_BUILD} && $(MAKE)

glfw3-clean:
	$(RMRF) ${PROJECT_LIBDIR}/glfw/${CMAKE_BUILD}


