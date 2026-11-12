CXX = g++
CXXFLAGS = -I includes
TARGET = dbms
SRCS = src/main.cpp src/dbms.cpp src/array.cpp src/singlyList.cpp \
       src/doublyList.cpp src/stack.cpp src/queue.cpp src/tree.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)