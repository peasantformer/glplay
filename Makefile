all: git make-libs configure compile

clean:
	rm -rf cmake-build
	rm -rf libs/glfw/cmake-build


make-libs:
	mkdir -p libs/glfw/cmake-build && \
		cd libs/glfw/cmake-build && \
		cmake ../ \
			-DGLFW_BUILD_EXAMPLES=OFF \
			-DGLFW_BUILD_TESTS=OFF
	cd libs/glfw/cmake-build && make

git: git-init

git-init:
	git submodule init
	git submodule update

configure:
	mkdir -p cmake-build
	cd cmake-build && cmake ../

compile:
	cd cmake-build && make


