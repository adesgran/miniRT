NAME = miniRT

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

C_ROOT = main init_vars shapes_finder cylinder_finder colors_object sphere_finder plan_finder

C_PARSING = parser parser_utils parsing_error atod read_color parse_ambiantlight \
	read_coord parse_light parse_camera parse_sphere parse_cylindre parse_plan

C_UTILS = colors_utils put_pixel geometry_utils t_shapes_utils t_light_utils \
	t_env_utils matrix_rotation norm_vector geometry_utils2 utils_cylinder colors_utils2

C_FILES = $(addsuffix .c, $(C_ROOT) $(addprefix parsing/, $(C_PARSING)) $(addprefix utils/, $(C_UTILS)))

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
	./$(NAME) test.rt

test: $(NAME)
	valgrind --leak-check=full ./$(NAME) test.rt

.PHONY: all clean fclean re
