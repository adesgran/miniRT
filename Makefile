NAME = miniRT

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

C_ROOT = main put_pixel init_vars geometry_utils t_shapes_utils colors_utils get_env \
	t_light_utils t_env_utils matrix_rotation parser parser_utils parsing_error atod \
	read_color parse_ambiantlight read_coord parse_light parse_camera parse_sphere \
	parse_cylindre parse_plan

C_FILES = $(addsuffix .c, $(C_ROOT))

O_FILES = $(C_FILES:c=o)

LIBFT = libft/libft.a
MLX = mlx/libmlx_Linux.a

LIBS_FLAGS = -lreadline

H_INCLUDES = -I libft -I . -I mlx
A_INCLUDES = -L libft -lft -L mlx -lmlx_Linux -lm -lXext -lX11

all: ${NAME}

%.o: %.c
	@printf "\033[0;33mGenerating $(NAME) objects... %-33.33s\r\033[0m" $@
	@${CC} ${C_FLAGS} ${H_INCLUDES} -c $< -o $@

${NAME}: $(O_FILES) $(LIBFT) $(MLX)
	@echo "\n"
	@echo "\n\033[0;34mCompiling $(NAME)...\033[0m"
	@${CC} ${O_FILES} ${A_INCLUDES} ${LIBS_FLAGS} -o ${NAME}

$(LIBFT):
	@make -C libft

$(MLX):
	@make -C mlx

clean:
	@make --no-print-directory clean -C libft/ 
	@echo "\n\033[0;31mCleaning $(NAME) binaries...\033[0m"
	@rm -f $(O_FILES)

fclean:
	@#@make --no-print-directory fclean -C libft/
	@echo "\n\033[0;31mCleaning $(NAME) binaries...\033[0m"
	@rm -f $(O_FILES)
	@echo "\n\033[0;31mCleaning $(NAME) executable...\033[0m"
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

test: $(NAME)
	valgrind --leak-check=full ./$(NAME) test.rt

.PHONY: all clean fclean re
