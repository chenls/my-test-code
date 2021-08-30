#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

template <typename T>
T* visit(void* base, size_t offset) {
    return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(base) + offset);
}

bool startswith(const char* whole, const char* prefix) {
    return !strncmp(whole, prefix, strlen(prefix));
}

template <typename T>
void set_sec_type(T* hdr, const char* name) {
    if (startswith(name, ".megtee_init_array")) {
        hdr->sh_type = SHT_INIT_ARRAY;
    } else if (startswith(name, ".megtee_fini_array")) {
        hdr->sh_type = SHT_FINI_ARRAY;
    } else if (startswith(name, ".megtee_data")) {
        hdr->sh_type = SHT_PROGBITS;
    } else if (startswith(name, ".megtee_bss")) {
        hdr->sh_type = SHT_NOBITS;
    }
}

void work_elf32(void* map) {
    auto elf_hdr = static_cast<Elf32_Ehdr*>(map);
    auto shstrtab_hdr =
            visit<Elf32_Shdr>(map, elf_hdr->e_shoff) + elf_hdr->e_shstrndx;
    auto shstrtab = visit<const char>(map, shstrtab_hdr->sh_offset);
    for (size_t i = 0; i < elf_hdr->e_shnum; ++i) {
        auto sec_hdr = visit<Elf32_Shdr>(map, elf_hdr->e_shoff) + i;
        const char* name = shstrtab + sec_hdr->sh_name;
        set_sec_type(sec_hdr, name);
        if (sec_hdr->sh_flags & SHF_GROUP) {
            // group sections would be removed
            sec_hdr->sh_flags ^= SHF_GROUP;
            printf("!! warning remove group flag for section %zu: %s\n", i,
                   name);
        }
        if (sec_hdr->sh_type == SHT_GROUP) {
            printf("!! warning remove group section %zu: %s\n", i, name);
            sec_hdr->sh_type = SHT_NULL;
        }
    }
}

void work_elf64(void* map) {
    auto elf_hdr = static_cast<Elf64_Ehdr*>(map);
    auto shstrtab_hdr =
            visit<Elf64_Shdr>(map, elf_hdr->e_shoff) + elf_hdr->e_shstrndx;
    auto shstrtab = visit<const char>(map, shstrtab_hdr->sh_offset);
    for (size_t i = 0; i < elf_hdr->e_shnum; ++i) {
        auto sec_hdr = visit<Elf64_Shdr>(map, elf_hdr->e_shoff) + i;
        const char* name = shstrtab + sec_hdr->sh_name;
        set_sec_type(sec_hdr, name);
        if (sec_hdr->sh_flags & SHF_GROUP) {
            // group sections would be removed
            sec_hdr->sh_flags ^= SHF_GROUP;
            printf("!! warning remove group flag for section %zu: %s\n", i,
                   name);
        }
        if (sec_hdr->sh_type == SHT_GROUP) {
            printf("!! warning remove group section %zu: %s\n", i, name);
            sec_hdr->sh_type = SHT_NULL;
        }
    }
}

int main(int argc, char** argv) {
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
    void* map = mmap(nullptr, finfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                     fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        return 2;
    }

    auto elf_hdr = static_cast<Elf32_Ehdr*>(map);
    if (elf_hdr->e_ident[EI_CLASS] == ELFCLASS32) {
        work_elf32(map);
    } else if (elf_hdr->e_ident[EI_CLASS] == ELFCLASS64) {
        work_elf64(map);
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
