NAME := PmergeMe

SRCS = main.cpp \
	   PmergeMe.cpp 


BUILD_DIR := .build/

OBJS_DIR := $(addprefix $(BUILD_DIR), objs/)
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

DEPS := $(OBJS:.o=.d)

CPPFLAGS += -MMD -MP
CFLAGS += -Wall -Wextra -Werror -g3 -std=c++98

CC = c++

#                          RULES                           #

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

#                       CLEAN                              #

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean all re

-include $(DEPS)
