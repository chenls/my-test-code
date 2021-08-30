#include <cstdio>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <cstdlib>

#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

template<typename T>
T* visit(void *base, size_t offset) {
    return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(base) + offset);
}

int work_elf32(void* map, bool change_target1) {
    auto elf_hdr = static_cast<Elf32_Ehdr*>(map);
    auto shstrtab_hdr = visit<Elf32_Shdr>(map, elf_hdr->e_shoff) +
        elf_hdr->e_shstrndx;
    auto shstrtab = visit<const char>(map, shstrtab_hdr->sh_offset);
    int nr_target1 = 0;
    for (size_t i = 0; i < elf_hdr->e_shnum; ++ i) {
        auto sec_hdr = visit<Elf32_Shdr>(map, elf_hdr->e_shoff) + i;
        const char *name = shstrtab + sec_hdr->sh_name;
        if (sec_hdr->sh_type == SHT_INIT_ARRAY ||
                sec_hdr->sh_type == SHT_FINI_ARRAY) {
            printf("section %zu: %s type=%d size=%d\n",
                    i, name,
                    static_cast<int>(sec_hdr->sh_type),
                    static_cast<int>(sec_hdr->sh_size));
            sec_hdr->sh_type = SHT_PROGBITS;
            // might be modified in reallocation so it has WRITE flag
            assert(sec_hdr->sh_flags == (SHF_ALLOC | SHF_WRITE));
        }
        if (sec_hdr->sh_type == SHT_REL && change_target1 &&
                !strstr(name, ".ARM.exidx") && !strstr(name, ".text")) {
            auto relocs = visit<Elf32_Rel>(map, sec_hdr->sh_offset);
            assert(sec_hdr->sh_size % sizeof(Elf32_Rel) == 0);
            for (uint32_t j = 0, nr = sec_hdr->sh_size / sizeof(Elf32_Rel);
                    j < nr; ++ j) {
                auto &&r = relocs[j].r_info;
                auto type = ELF32_R_TYPE(r);
                if (type == R_ARM_TARGET1) {
                    // see ELF for the ARM Architecture
                    // The relocation must be processed either in the same way
                    // as R_ARM_REL32 or as R_ARM_ABS32
                    r &= ~0xff;
                    r |= R_ARM_ABS32;
                    ++ nr_target1;
                } else {
                    if (type != R_ARM_ABS32) {
                        fprintf(stderr, "section %s bad type: %d\n", name, type);
                        return -1;
                    }
                }
            }
        }
    }
    if (change_target1) {
        printf("target1 changed: %d\n", nr_target1);
    }
}

int work_elf64(void* map, bool change_target1) {
    if (change_target1) {
        printf("change_target1 not supported for elf64\n");
        return -1;
    }
    auto elf_hdr = static_cast<Elf64_Ehdr*>(map);
    auto shstrtab_hdr = visit<Elf64_Shdr>(map, elf_hdr->e_shoff) +
        elf_hdr->e_shstrndx;
    auto shstrtab = visit<const char>(map, shstrtab_hdr->sh_offset);
    for (size_t i = 0; i < elf_hdr->e_shnum; ++ i) {
        auto sec_hdr = visit<Elf64_Shdr>(map, elf_hdr->e_shoff) + i;
        const char *name = shstrtab + sec_hdr->sh_name;
        if (sec_hdr->sh_type == SHT_INIT_ARRAY ||
                sec_hdr->sh_type == SHT_FINI_ARRAY) {
            printf("section %zu: %s type=%d size=%d\n",
                    i, name,
                    static_cast<int>(sec_hdr->sh_type),
                    static_cast<int>(sec_hdr->sh_size));
            sec_hdr->sh_type = SHT_PROGBITS;
            // might be modified in reallocation so it has WRITE flag
            assert(sec_hdr->sh_flags == (SHF_ALLOC | SHF_WRITE));
        }
    }
}

int main(int argc, char **argv) {
    bool change_target1 = getenv("FIXELF_TARGET1");
    if (argc != 2) {
        fprintf(stderr, "usage: %s <.o file>\n", argv[0]);
        return -1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "failed to open %s: %s", argv[1], strerror(errno));
        return 2;
    }
    struct stat finfo;
    if (fstat(fd, &finfo) < 0) {
        perror("fstat");
        return 2;
    }
    void *map = mmap(nullptr, finfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
            fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        return 2;
    }

    auto elf_hdr = static_cast<Elf32_Ehdr*>(map);
    if (strncmp(reinterpret_cast<char*>(elf_hdr->e_ident), ELFMAG, 4)) {
        printf("bad magic: %s", elf_hdr->e_ident);
        return 3;
    }

    if (elf_hdr->e_ident[EI_CLASS] == ELFCLASS32) {
        work_elf32(map, change_target1);
    } else if (elf_hdr->e_ident[EI_CLASS] == ELFCLASS64) {
        work_elf64(map, change_target1);
    } else {
        printf("bad EI_CLASS\n");
        return 3;
    }

    if (munmap(map, finfo.st_size)) {
        perror("munmap");
        return 3;
    }
    if (close(fd)) {
        perror("close");
        return 3;
    }
}

// vim: syntax=cpp.doxygen foldmethod=marker foldmarker=f{{{,f}}}
