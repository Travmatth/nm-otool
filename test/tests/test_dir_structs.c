#include "../tests.h"

char	*archive_file_params[] = {
	"test/artifacts/archive/macho_lft_macho.a",
	"test/artifacts/archive/libft32.a",
	"test/artifacts/archive/libmlx.a",
	"test/artifacts/archive/libftprintf32.a",
	"test/artifacts/archive/ar_corr6.a",
	"test/artifacts/archive/ar_corr2.a",
	"test/artifacts/archive/libftprintf.a",
	"test/artifacts/archive/fat_binary_ar.a",
	"test/artifacts/archive/macho_fat.a",
	"test/artifacts/archive/test.a",
	"test/artifacts/archive/libft.a",
	"test/artifacts/archive/ar_corr5.a",
	"test/artifacts/archive/macho_lft.a",
	"test/artifacts/archive/ar_corr1.a",
	"test/artifacts/archive/fat_macho.a",
	"test/artifacts/archive/ar_corr4.a",
	"test/artifacts/archive/archiveception_niv2.a",
	"test/artifacts/archive/_lft.a",
	"test/artifacts/archive/macho.a",
	"test/artifacts/archive/fat_file.a",
	"test/artifacts/archive/archive_fat.a",
	"test/artifacts/archive/ar_corr3.a",
	"test/artifacts/archive/archiveception_niv1.a",
	NULL
};

// Too long, test outside
	// "test/artifacts/binary/64_exe_hard",
	// "test/artifacts/binary/cvfsdb_sbin",
	// "test/artifacts/binary/bash",
	// "test/artifacts/binary/32_exe_hard",
	// "test/artifacts/binary/undumpedbin",
	// "test/artifacts/binary/64_bundle",
	// "test/artifacts/binary/emacs-undumped",

char	*binary_file_params[] = {
	"test/artifacts/binary/hard_test_1",
	"test/artifacts/binary/sa_seg",
	"test/artifacts/binary/ls_string_table_corr5",
	"test/artifacts/binary/ls_string_table_corr2",
	"test/artifacts/binary/void32",
	"test/artifacts/binary/ls_text_overwritten",
	"test/artifacts/binary/hello_je_diff",
	"test/artifacts/binary/ls_string_table_corr3",
	"test/artifacts/binary/ls_string_table_corr4",
	"test/artifacts/binary/loadCommand.o",
	"test/artifacts/binary/ls_lc_growed",
	"test/artifacts/binary/ls_reversed_magic",
	"test/artifacts/binary/test_wrong_lc_command_size",
	"test/artifacts/binary/main32",
	"test/artifacts/binary/helloworldx64_samevalue_samename1",
	"test/artifacts/binary/hard_test",
	"test/artifacts/binary/curl_chibre",
	"test/artifacts/binary/test_facile",
	"test/artifacts/binary/ls_string_table_corr",
	"test/artifacts/binary/corr1",
	"test/artifacts/binary/helloworldx64_samevalue1",
	"test/artifacts/binary/salam",
	"test/artifacts/binary/64_exe_easy",
	"test/artifacts/binary/ls_lc_growed_1",
	"test/artifacts/binary/object_easy",
	"test/artifacts/binary/bomb",
	"test/artifacts/binary/test_moins_facile",
	"test/artifacts/binary/helloworldx32",
	"test/artifacts/binary/ls_zeroed_data_section_number",
	"test/artifacts/binary/ls_data_overwritten",
	"test/artifacts/binary/test_de_la_muerte",
	"test/artifacts/binary/ds_store",
	"test/artifacts/binary/a.out",
	"test/artifacts/binary/new",
	"test/artifacts/binary/ppc_only",
	"test/artifacts/binary/test_half_obj",
	"test/artifacts/binary/spec_binary64",
	"test/artifacts/binary/ft_nm32",
	"test/artifacts/binary/corr2",
	"test/artifacts/binary/ls_with_too_much_symbol",
	"test/artifacts/binary/bin32",
	"test/artifacts/binary/64_exe_hard_corupted",
	"test/artifacts/binary/object_medium",
	"test/artifacts/binary/prise_astrale_unijambiste",
	"test/artifacts/binary/ls_growed_7_data_section_number",
	"test/artifacts/binary/le_retour_du_seg",
	"test/artifacts/binary/ls_growed_1_data_section_number",
	"test/artifacts/binary/ahah",
	"test/artifacts/binary/helloworldx64",
	"test/artifacts/binary/ls_0_lc",
	"test/artifacts/binary/32_exe_hard_corupted",
	"test/artifacts/binary/littleEndian",
	"test/artifacts/binary/64_exe_medium",
	NULL,
};

// Too long, test outside
	// "test/artifacts/fat/big_fat",
	// "test/artifacts/fat/distnoted",
	// "test/artifacts/fat/sqlite3",
	// "test/artifacts/fat/fat_corr6",

char	*fat_file_params[] = {
	"test/artifacts/fat/fat_hard",
	"test/artifacts/fat/fat_alone",
	"test/artifacts/fat/audiodevice_offset_plus_un_v2",
	// "test/artifacts/fat/audiodevice_arch_plus_1",
	"test/artifacts/fat/why_are_you_crashing",
	"test/artifacts/fat/python_returns",
	"test/artifacts/fat/python",
	// "test/artifacts/fat/audiodevice_without_last_arch",
	"test/artifacts/fat/appsleepd",
	// "test/artifacts/fat/fat_corr2",
	// "test/artifacts/fat/fat_corr5",
	// "test/artifacts/fat/audiodevice_offset_plus_un",
	"test/artifacts/fat/pboard",
	// "test/artifacts/fat/audiodevice_arch_plus_10",
	// "test/artifacts/fat/fat_corr4",
	// "test/artifacts/fat/fat_corr3",
	// "test/artifacts/fat/audiodevice_offset_plus_quatre_v2",
	// "test/artifacts/fat/audiodevice_with_partial_last_arch",
	"test/artifacts/fat/audiodevice",
	// "test/artifacts/fat/audiodevice_offset_plus_quatre",
	// "test/artifacts/fat/fat_hard_corupted",
	// "test/artifacts/fat/the_revengeance_of_python",
	"test/artifacts/fat/cfprefsd",
	// "test/artifacts/fat/audiodevice_arch_plus_2",
	"test/artifacts/fat/fatbin",
	// "test/artifacts/fat/fat_corr1",
	// "test/artifacts/fat/fat_stackoverflow",
	// "test/artifacts/fat/fat_corr7",
	// "test/artifacts/fat/fat",
	// "test/artifacts/fat/fat_test1",
	// "test/artifacts/fat/audiodevice_corupted",
	"test/artifacts/fat/uuidgen",
	NULL
};

char	*files_file_params[] = {
	"test/artifacts/files/fichier_vide",
	"test/artifacts/files/big_ar.c",
	"test/artifacts/files/errftnm",
	"test/artifacts/files/res",
	"test/artifacts/files/resftnm",
	"test/artifacts/files/errnm",
	"test/artifacts/files/test1.c",
	"test/artifacts/files/resnm",
	"test/artifacts/files/empty_file",
	"test/artifacts/files/diff",
	"test/artifacts/files/test.c",
	"test/artifacts/files/mine",
	"test/artifacts/files/mine_err",
	"test/artifacts/files/corr1",
	NULL,
};


char	*lib_file_params[] = {
	"test/artifacts/lib/libsqlite3.dylib",
	"test/artifacts/lib/libblas.dylib",
	"test/artifacts/lib/libz.1.dylib",
	"test/artifacts/lib/libcblas.dylib",
	"test/artifacts/lib/libkrb4.dylib",
	"test/artifacts/lib/libz.dylib",
	"test/artifacts/lib/lib_archive_medium",
	"test/artifacts/lib/libicucore.dylib",
	"test/artifacts/lib/PN548_OSX.dylib",
	"test/artifacts/lib/libmx.A.dylib",
	"test/artifacts/lib/libobjc.A.dylib",
	"test/artifacts/lib/libk5crypto.dylib",
	"test/artifacts/lib/PN548_HAL_OSX.dylib",
	"test/artifacts/lib/libpmenergy.dylib",
	"test/artifacts/lib/libAccountPolicyTranslation.dylib",
	"test/artifacts/lib/libobjc.dylib",
	"test/artifacts/lib/libclapack.dylib",
	"test/artifacts/lib/libstdc++.6.0.9.dylib",
	"test/artifacts/lib/libpmsample.dylib",
	"test/artifacts/lib/libform.5.4.dylib",
	"test/artifacts/lib/libc++.1.dylib",
	"test/artifacts/lib/libkrb524.dylib",
	"test/artifacts/lib/libstdc++.6.dylib",
	"test/artifacts/lib/libsqlite3.0.dylib",
	"test/artifacts/lib/libextension.dylib",
	"test/artifacts/lib/libkrb5support.dylib",
	"test/artifacts/lib/libgssapi_krb5.dylib",
	"test/artifacts/lib/libFosl_dynamic.dylib",
	"test/artifacts/lib/a",
	"test/artifacts/lib/liblapack.dylib",
	"test/artifacts/lib/libft_malloc_x86_64_Darwin.so",
	"test/artifacts/lib/libc++.dylib",
	"test/artifacts/lib/libcoretls.dylib",
	"test/artifacts/lib/libcom_err.dylib",
	"test/artifacts/lib/libkrb5.dylib",
	"test/artifacts/lib/libstdc++.dylib",
	"test/artifacts/lib/libdns_services.dylib",
	"test/artifacts/lib/libdes425.dylib",
	"test/artifacts/lib/64_lib_dynamic_medium",
	"test/artifacts/lib/libinfo.dylib",
	"test/artifacts/lib/libmenu.dylib",
	"test/artifacts/lib/64_lib_dynamic_hard",
	"test/artifacts/lib/PN548_API.dylib",
	"test/artifacts/lib/libsystemstats.dylib",
	"test/artifacts/lib/libform.dylib",
	"test/artifacts/lib/libswiftCore.dylib",
	"test/artifacts/lib/ssh-keychain.dylib",
	"test/artifacts/lib/libf77lapack.dylib",
	NULL
};

char	*object_file_params[] = {
	"test/artifacts/object/ft_strlen64.o",
	"test/artifacts/object/ft_bzero32.o",
	"test/artifacts/object/main32.o",
	"test/artifacts/object/testmain.o",
	"test/artifacts/object/ft_putstr32.o",
	"test/artifacts/object/ft_strlen32.o",
	"test/artifacts/object/electric_troll.o",
	"test/artifacts/object/test1.o",
	"test/artifacts/object/ft_cat64.o",
	"test/artifacts/object/object_easy",
	"test/artifacts/object/ft_bzero64.o",
	"test/artifacts/object/ft_cat.o",
	"test/artifacts/object/ft_cat32.o",
	"test/artifacts/object/main.o",
	"test/artifacts/object/ft_strcpy64.o",
	"test/artifacts/object/ft_strcpy32.o",
	"test/artifacts/object/object_medium",
	"test/artifacts/object/ft_putstr64.o",
	"test/artifacts/object/main64.o",
	NULL
};
