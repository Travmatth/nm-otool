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
TEST_NAME = test/test

NM_NAME = ft_nm
NM_MAIN = src/nm_main.c
NM = utils
NM_FILES = $(addprefix src/nm/, $(NM))
NM_SRC = $(addsuffix .c, $(NM_FILES))
NM_OBJ = $(NM_SRC:.c=.o)

OTOOL_NAME = ft_otool
OTOOL_MAIN = src/otool_main.c
OTOOL = utils
OTOOL_FILES = $(addprefix src/otool/, $(OTOOL))
OTOOL_SRC = $(addsuffix .c, $(OTOOL_FILES))
OTOOL_OBJ = $(OTOOL_SRC:.c=.o)

.PHONY = all clean fclean re

all: $(SUBMODULES) $(NM_NAME) $(OTOOL_NAME)

debug: set-debug all

test: set-debug all
	@echo -n 'Compiling nm-otool tests... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(NM_OBJ) $(OTOOL_OBJ) $(TEST_FILE) -o $(TEST_NAME)
	@echo "\033[32mdone\033[0m"

set-debug:
	@echo 'Compiling nm-otool with debugging logs enabled'
	$(eval IS_DEBUG='-D__DEBUG__') 

$(LIBFT):
	@$(MAKE) -C libftprintf

$(NM_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

$(OTOOL_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

$(NM_NAME): $(LIBFT) $(NM_OBJ)
	@echo -n 'Compiling nm... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(NM_OBJ) $(NM_MAIN) -o $@
	@echo "\033[32mdone\033[0m"

$(OTOOL_NAME): $(LIBFT) $(OTOOL_OBJ)
	@echo -n 'Compiling otool... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(OTOOL_OBJ) $(OTOOL_MAIN) -o $@
	@echo "\033[32mdone\033[0m"

clean:
	@$(MAKE) clean -C libftprintf
	@echo -n 'Cleaning nm-otool object files... '
	@rm -rf $(OBJ) *.dSYM test/*.dSYM *.DS_Store typescript
	@echo "\033[32mdone\033[0m"

fclean: clean
	@$(MAKE) fclean -C libftprintf
	@echo -n 'Cleaning nm-otool executables... '
	@rm -rf $(NAME) $(TEST_NAME)
	@echo "\033[32mdone\033[0m"

re: fclean all
