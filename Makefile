DEBUG =
# compile with debugging and fsantize enabled
ifdef TEST
        DEBUG = -g -fsanitize=address -fsanitize=undefined
else
        DEBUG =
endif
# compile with debugging enabled
ifdef LEAKS
        DEBUG = -g
endif

LIBFT = libftprintf/libftprintf.a
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -Llibftprintf -lftprintf -I./includes
IS_DEBUG =

# common variables
COMMON = file_multiplexer format fat mach_o mach_i386_sections mach_x86_64_sections magics utils validate_file
COMMON_FILES = $(addprefix src/common/, $(COMMON))
COMMON_SRC = $(addsuffix .c, $(COMMON_FILES))
COMMON_OBJ = $(COMMON_SRC:.c=.o)

# nm variables
NM_NAME = ft_nm
NM_MAIN = src/nm/main.c
NM = utils
NM_FILES = $(addprefix src/nm/, $(NM))
NM_SRC = $(addsuffix .c, $(NM_FILES))
NM_OBJ = $(NM_SRC:.c=.o)

# otool variables
OTOOL_NAME = ft_otool
OTOOL_MAIN = src/otool/main.c
OTOOL = utils print_x86_64 print_i386 otool
OTOOL_FILES = $(addprefix src/otool/, $(OTOOL))
OTOOL_SRC = $(addsuffix .c, $(OTOOL_FILES))
OTOOL_OBJ = $(OTOOL_SRC:.c=.o)

# test variables
TESTFLAGS = -I./test -I./test/fff
TEST_FILE = test/test.c
TEST_NAME = test/run_test
TESTS = utils test_utils test_format test_mach_o test_mach_print test_fat test_dir_structs test_otool
TEST_LIB = test/munit/munit.c
TEST_FILES = $(addprefix test/tests/, $(TESTS))  
TEST_SRC = $(addsuffix .c, $(TEST_FILES))
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_LIB_OBJ = $(TEST_LIB:.c=.o)

.PHONY = all clean fclean re

# compile nm and otool executables
all: $(NM_NAME) $(OTOOL_NAME)

# compile libft
$(LIBFT):
	@$(MAKE) -C libftprintf

# compile common object files
$(COMMON_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

# compile nm object files
$(NM_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

# compile otool object files
$(OTOOL_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

# compile test munit library
$(TEST_LIB_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $< -o $@

# compile test object files
$(TEST_OBJ): %.o: %.c
	@$(CC) -c $(IS_DEBUG) $(DEBUG) -I. $(CFLAGS) $< -o $@

# compile nm executable
$(NM_NAME): $(LIBFT) $(COMMON_OBJ) $(NM_OBJ)
	@echo -n 'Compiling nm... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJ) $(NM_OBJ) $(NM_MAIN) -o $@
	@echo "\033[32mdone\033[0m"

# compile otool executable
$(OTOOL_NAME): $(LIBFT) $(COMMON_OBJ) $(OTOOL_OBJ)
	@echo -n 'Compiling otool... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJ) $(OTOOL_OBJ) $(OTOOL_MAIN) -o $@
	@echo "\033[32mdone\033[0m"

# set debug mode for runtime debugging statements
debug: set-debug $(COMMON_OBJ)

# compile test program
test: set-debug $(LIBFT) $(COMMON_OBJ) $(NM_OBJ) $(OTOOL_OBJ) $(TEST_LIB_OBJ) $(TEST_OBJ)
	@echo -n 'Compiling nm-otool tests... '
	@$(CC) $(IS_DEBUG) $(DEBUG) $(CFLAGS) $(LDFLAGS) $(TESTFLAGS) $(COMMON_OBJ) $(NM_OBJ) $(OTOOL_OBJ) $(TEST_LIB_OBJ) $(TEST_OBJ) $(TEST_FILE) -o $(TEST_NAME)
	@echo "\033[32mdone\033[0m"

# run test program
run_test:
	@./$(TEST_NAME)

# enable debugging statements
set-debug:
	@echo 'Compiling nm-otool with debugging logs enabled'
	$(eval IS_DEBUG='-D__DEBUG__') 

# remove executables and test files in project, not dependencies
shallow_clean:
	@echo -n 'Shallow cleaning nm-otool object files... '
	@rm -rf $(COMMON_OBJ) $(OTOOL_OBJ) $(NM_OBJ) $(TEST_OBJ) *.dSYM test/*.dSYM *.DS_Store
	@echo "\033[32mdone\033[0m"

# remove executables, debugging dirs
clean:
	@$(MAKE) clean -C libftprintf
	@echo -n 'Cleaning nm-otool object files... '
	@rm -rf $(COMMON_OBJ) $(OTOOL_OBJ) $(NM_OBJ) $(TEST_OBJ) *.dSYM test/*.dSYM *.DS_Store test/munit/munit.o
	@echo "\033[32mdone\033[0m"

# remove executables, object files, debugging dirs, archives
fclean: clean
	@$(MAKE) fclean -C libftprintf
	@echo -n 'Cleaning nm-otool executables... '
	@rm -rf $(NAME) $(TEST_NAME)
	@echo "\033[32mdone\033[0m"

re: fclean all
