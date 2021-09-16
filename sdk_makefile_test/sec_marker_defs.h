// //! define a var in the section \p var_name + "_marker" and the var
// #define DEF_SECTION_AND_VAR(var_name, v)                                       \
//   static size_t __attribute__((section("." #var_name "_marker"))) var_name = v

// #define DEF_INIT_FINI(init_fini, begin_end, v)                                 \
//   DEF_SECTION_AND_VAR(megtee_##init_fini##_array_##begin_end, v)

// #define DEF_DATA(begin_end, v) DEF_SECTION_AND_VAR(megtee_data_##begin_end, v)

// #define DEF_BSS(begin_end, v) DEF_SECTION_AND_VAR(megtee_bss_##begin_end, v)

// // to be placed at the right place by linker script
// DEF_INIT_FINI(init, begin, 23);
// DEF_INIT_FINI(init, end, 24);
// DEF_INIT_FINI(fini, begin, 25);
// DEF_INIT_FINI(fini, end, 26);
// DEF_DATA(begin, 27);
// DEF_DATA(end, 28);
// DEF_BSS(begin, 0);
// DEF_BSS(end, 0);
// #undef DEF_BSS
// #undef DEF_DATA
// #undef DEF_INIT_FINI
// #undef DEF_SECTION_AND_VAR


static size_t __attribute__((section("." "megtee_init_array_begin" "_marker"))) megtee_init_array_begin = 23;
static size_t __attribute__((section("." "megtee_init_array_end" "_marker"))) megtee_init_array_end = 24;
static size_t __attribute__((section("." "megtee_fini_array_begin" "_marker"))) megtee_fini_array_begin = 25;
static size_t __attribute__((section("." "megtee_fini_array_end" "_marker"))) megtee_fini_array_end = 26;
static size_t __attribute__((section("." "megtee_data_begin" "_marker"))) megtee_data_begin = 27;
static size_t __attribute__((section("." "megtee_data_end" "_marker"))) megtee_data_end = 28;
static size_t __attribute__((section("." "megtee_bss_begin" "_marker"))) megtee_bss_begin = 0;
static size_t __attribute__((section("." "megtee_bss_end" "_marker"))) megtee_bss_end = 0;