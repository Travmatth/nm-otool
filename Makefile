DEBUG =
ifdef TEST
        DEBUG = -g -fsanitize=address -fsanitize=undefined
else
        DEBUG =
endif
ifdef LEAKS
        DEBUG = -g
endif

LIBFT = libftprintf/libftprintf.a
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -Llibftprintf -lftprintf -I./includes
IS_DEBUG =
TEST_FILE = test/test.c
TEST_NAME = test/run_test

COMMON = fat mach_o utils
COMMON_FILES = $(addprefix src/common/, $(COMMON))
COMMON_SRC = $(addsuffix .c, $(COMMON_FILES))
COMMON_OBJ = $(COMMON_SRC:.c=.o)

NM_NAME = ft_nm
NM_MAIN = src/nm/main.c
NM = utils
NM_FILES = $(addprefix src/nm/, $(NM))
NM_SRC = $(addsuffix .c, $(NM_FILES))
NM_OBJ = $(NM_SRC:.c=.o)

OTOOL_NAME = ft_otool
OTOOL_MAIN = src/otool/main.c
OTOOL = utils print
OTOOL_FILES = $(addprefix src/otool/, $(OTOOL))
OTOOL_SRC = $(addsuffix .c, $(OTOOL_FILES))
OTOOL_OBJ = $(OTOOL_SRC:.c=.o)

.PHONY = all clean fclean re

all: $(NM_NAME) $(OTOOL_NAME)

$(LIBFT):
	@$(MAKE) -C libftprintf

$(COMMON_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

$(NM_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

$(OTOOL_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

$(NM_NAME): $(LIBFT) $(COMMON_OBJ) $(NM_OBJ)
	@echo -n 'Compiling nm... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJ) $(NM_OBJ) $(NM_MAIN) -o $@
	@echo "\033[32mdone\033[0m"

$(OTOOL_NAME): $(LIBFT) $(COMMON_OBJ) $(OTOOL_OBJ)
	@echo -n 'Compiling otool... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJ) $(OTOOL_OBJ) $(OTOOL_MAIN) -o $@
	@echo "\033[32mdone\033[0m"

debug: set-debug $(COMMON_OBJ)

test: set-debug all
	@echo -n 'Compiling nm-otool tests... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJ) $(TEST_FILE) -o $(TEST_NAME)
	@echo "\033[32mdone\033[0m"

run_test:
	@./$(TEST_NAME)

set-debug:
	@echo 'Compiling nm-otool with debugging logs enabled'
	$(eval IS_DEBUG='-D__DEBUG__') 

shallow_clean:
	@rm -rf $(NAME) $(TEST_NAME)

clean:
	@$(MAKE) clean -C libftprintf
	@echo -n 'Cleaning nm-otool object files... '
	@rm -rf $(OBJ) *.dSYM test/*.dSYM *.DS_Store
	@echo "\033[32mdone\033[0m"

fclean: clean
	@$(MAKE) fclean -C libftprintf
	@echo -n 'Cleaning nm-otool executables... '
	@rm -rf $(NAME) $(TEST_NAME)
	@echo "\033[32mdone\033[0m"

re: fclean all
