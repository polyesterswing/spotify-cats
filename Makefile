CXX = g++
LDFLAGS = -ldl
INCLUDEDIR = include

build/debug: src/shim.cpp
	mkdir -p build
	$(CXX) -shared -fPIC -o $@ $^ $(LDFLAGS) -I$(INCLUDEDIR) -DDEBUG

build/release: src/shim.cpp
	mkdir -p build
	$(CXX) -O3 -shared -fPIC -o $@ $^ $(LDFLAGS) -I$(INCLUDEDIR)

run: build/release
	LD_PRELOAD=./$^ spotify 1>/dev/null 2>/dev/null &

debug: build/debug
	LD_PRELOAD=./$^ spotify

.PHONY: run debug
