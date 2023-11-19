NAME = philo

CFLAGS = -g -Wall -Wextra -Werror 

SRCS = ./srcs/main.c ./srcs/routines.c ./srcs/prep_dinner_room.c ./srcs/staff_assignment.c ./srcs/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling..."
	@cc $(CFLAGS) $(OBJS) -o $(NAME) -lpthread
	@echo "Done!"

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJS)
	@echo "Done!"

fclean: clean
	@echo "Cleaning..."
	@rm -rf $(NAME)
	@echo "Done!"

re: fclean all

.PHONY: all clean fclean re
