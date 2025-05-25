CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g

SRC = \
    felulet.cpp \
    Tel.cpp \
    NetCs.cpp \
    Csomagok.cpp \
    Combine.cpp \
	 Vevo.cpp \
	 Szolgaltato.cpp \
    string.cpp \
	 test_main.cpp \
    memtrace.cpp

HEADERS = \
    Tel.hpp \
    NetCs.hpp \
    Csomagok.hpp \
    Csomag.hpp \
    Combine.hpp \
	 Vevo.hpp \
	 Szolgaltato.hpp \
    string.h \
    gtest_lite.h \
	 test.hpp \
    memtrace.h

TARGET = program

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET)
