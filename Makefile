game: 
	eval clang++ --std=c++17 -stdlib=libc++ main.cpp $$(find ./src/ -type f -iregex ".*\.cpp") $$(pkg-config --libs --cflags raylib) -o play.out 