if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
	mkdir -p external/cmake
	pushd external/cmake
	wget https://cmake.org/files/v3.10/cmake-3.10.2-Linux-x86_64.sh
	chmod +x cmake-*-Linux-x86_64.sh
	./cmake-*-Linux-x86_64.sh --exclude-subdir --skip-license
	export PATH="${PWD}/bin:$PATH"
	popd
else
	if ! brew ls --version cmake &>/dev/null; then brew update; brew install cmake; fi
fi
