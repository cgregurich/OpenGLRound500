FILE_NAME = Program
SRC_FILE = $(FILE_NAME).cpp
GLFW_INCLUDE = C:/Users/gregurichcoli/graphics-learning/OpenGLRound500/glfw-3.4.bin.WIN64/include
GLAD_INCLUDE = C:/Users/gregurichcoli/graphics-learning/OpenGLRound500/glad/include
GLAD_SRC = C:/Users/gregurichcoli/graphics-learning/OpenGLRound500/glad/src/glad.c
LIB_DIR = C:/Users/gregurichcoli/graphics-learning/OpenGLRound500/glfw-3.4.bin.WIN64/lib-mingw-w64 
LIBS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32

# Default target
all: $(FILE_NAME)

$(FILE_NAME): $(SRC_FILE)
	g++ -o $@ $< $(GLAD_SRC) -I $(GLFW_INCLUDE) -I $(GLAD_INCLUDE) -L $(LIB_DIR) $(LIBS)

# Run target
run: $(FILE_NAME)
	./$(FILE_NAME).exe

# Clean target
clean:
	rm -f $(FILE_NAME).exe