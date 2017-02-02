CC=g++ -Wall -Wextra -Werror -std=c++11
NAME=avm

BUILD_DIR=__build

SRC=\
AbstractVM.cpp\
Command.cpp\
Factory.cpp\
Lexer.cpp\
main.cpp\
Parser.cpp\

OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:.cpp=.o))

all:$(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o:srcs/%.cpp
	$(CC) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $^ -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean:clean
	@rm -f $(NAME)

re:fclean all
