CC = g++ 
CC_FLAG = -std=c++11 -O3
LIBS = -lopencv_core -lopencv_highgui
LIBS +=-lopencv_objdetect -lopencv_ml -lopencv_videoio -lopencv_imgproc  -lopencv_imgcodecs
DLIB = 	-ldlib
INC_DIR = -I/usr/local/include \
	-I/usr/local/include/
LIB_DIR = -L/usr/local/lib $(LIBS)  -L/usr/local/lib $(DLIB)
# 可执行文件/home/blacklong/tool/dlib-19.4/build/dlib
TARGET = test
# C文件
SRCS = face_detection_test.cpp
# 目标文件
OBJS = $(SRCS:.cpp=.o)
# 库文件


# 链接为可执行文件
# 编译规则 $@代表目标文件 $< 代表第一个依赖文件
$(TARGET):$(OBJS)
	$(CC)  $(INC_DIR)  -o $@ $^ $(LIB_DIR) 
%.o:%.cpp
	$(CC) $(CC_FLAG) $(INC_DIR) -o $@ -c $< 
clean:
	rm -rf $(TARGET) $(OBJS)
