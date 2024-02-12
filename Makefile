CXX := g++
# -std=gnu+11 adds extra features that plog makes use of
CXXFLAGS := -std=gnu++11 -Wall -Wextra

SRC := main.cpp shader.cpp constants.cpp util.cpp glad.c

INCLUDE := -IC:/dependencies/glfw-3.3.9-mingw/build/include \
	-IC:/dependencies/glad-cpp-3.3-core/include \
	-IC:/dependencies/glm-1.0.0 \
	-IC:/dependencies/plog-1.1.10/include

LIB := -LC:\dependencies\glfw-3.3.9-mingw\build\lib
LIBFLAGS := -lglfw3 -lgdi32

OUT := a.exe

main: ${SRC}
	${CXX} ${SRC} ${CXXFLAGS} ${INCLUDE} ${LIB} ${LIBFLAGS} -o ${OUT}

release: ${SRC}
	${CXX} ${SRC} ${CXXFLAGS} ${INCLUDE} ${LIB} ${LIBFLAGS} -o r_${OUT} -O2

clean:
	del *.exe