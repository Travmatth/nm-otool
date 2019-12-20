#include "../tests.h"

char* fat_file_params[] = {
	"test/artifacts/fat/fat_hard",
	"test/artifacts/fat/fat_alone",
	"test/artifacts/fat/audiodevice_offset_plus_un_v2",
	"test/artifacts/fat/audiodevice_arch_plus_1",
	"test/artifacts/fat/big_fat",
	"test/artifacts/fat/why_are_you_crashing",
	"test/artifacts/fat/python_returns",
	"test/artifacts/fat/python",
	"test/artifacts/fat/audiodevice_without_last_arch",
	"test/artifacts/fat/appsleepd",
	"test/artifacts/fat/fat_corr2",
	"test/artifacts/fat/fat_corr5",
	"test/artifacts/fat/audiodevice_offset_plus_un",
	"test/artifacts/fat/pboard",
	"test/artifacts/fat/audiodevice_arch_plus_10",
	"test/artifacts/fat/fat_corr4",
	"test/artifacts/fat/fat_corr3",
	"test/artifacts/fat/audiodevice_offset_plus_quatre_v2",
	"test/artifacts/fat/distnoted",
	"test/artifacts/fat/audiodevice_with_partial_last_arch",
	"test/artifacts/fat/audiodevice",
	"test/artifacts/fat/audiodevice_offset_plus_quatre",
	"test/artifacts/fat/fat_hard_corupted",
	"test/artifacts/fat/the_revengeance_of_python",
	"test/artifacts/fat/sqlite3",
	"test/artifacts/fat/cfprefsd",
	"test/artifacts/fat/audiodevice_arch_plus_2",
	"test/artifacts/fat/fatbin",
	"test/artifacts/fat/fat_corr6",
	"test/artifacts/fat/fat_corr1",
	"test/artifacts/fat/fat_stackoverflow",
	"test/artifacts/fat/fat_corr7",
	"test/artifacts/fat/fat",
	"test/artifacts/fat/hmmm_je_met_mon_gros_doigt_de_pied",
	"test/artifacts/fat/audiodevice_corupted",
	"test/artifacts/fat/uuidgen",
	NULL
};

/*
** Mock callbacks to test various functions
*/

int	g_header_calls = 0;
int	g_segment_calls = 0;
int	g_lc_calls = 0;
int	g_section_calls = 0;

int		verify_segments(char *file, t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64) {
	(void)file;
	(void)ctx;
	(void)segment;
	(void)segment_64;
	g_segment_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_load_command(char *file, t_ctx *ctx, struct load_command *lc, void *addr) {
	(void)file;
	(void)ctx;
	(void)lc;
	(void)addr;
	g_lc_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_sections(char *file, t_ctx *ctx, struct section *section, struct section_64 *section_64) {
	(void)file;
	(void)ctx;
	(void)section;
	(void)section_64;
	g_section_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_segment_address(char *file, t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64) {
	(void)ctx;
	(void)segment_64;
	if (!strcmp(segment->segname, "__TEXT")) {
		uint32_t magic = *(uint32_t *)file + segment->fileoff;
		if (magic == MH_MAGIC)
			g_segment_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_section_address(char *file, t_ctx *ctx, struct section *sect, struct section_64 *sect64) {
	(void)ctx;
	(void)sect64;
	if (!strcmp("__text", sect->sectname)) {
		uint64_t val = *(uint64_t*)(file + sect->offset);
		if (val == 0x00E818EC83E58955ULL)
			g_section_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_header(char *file, t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64) {
	(void)file;
	(void)ctx;
	(void)header_64;
	if (header) {
		if (header->magic == MH_MAGIC)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_section64_address(char *file, t_ctx *ctx, struct section *sect, struct section_64 *sect64) {
	(void)ctx;
	(void)sect;
	if (!strcmp("__text", sect64->sectname)) {
		uint64_t val = *(uint64_t*)(file + sect64->offset);
		if (val == 1219493948222425173ULL)
			g_section_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_header64(char *file, t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64) {
	(void)file;
	(void)ctx;
	(void)header;
	if (header_64) {
		if (header_64->magic == MH_MAGIC_64)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

/*
** test utils
*/

int		fd_to_str(int fd, char *out) {
	int bytes = 0;

	if ((bytes = read(fd, out, BUFSIZ)) == -1)
		return EXIT_FAILURE;
	out[bytes] = '\0';
	return EXIT_SUCCESS;
}
