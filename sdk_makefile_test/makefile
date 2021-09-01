override OPTLEVEL ?= -O0
override V ?= @
override ARCH ?= android-armv7
override VENDOR_NAME ?= megvii
override BUILD_DIR ?= build/$(ARCH)$(OPTLEVEL)$(VENDOR_NAME)
ifeq (, $(findstring aarch64, $(ARCH)))
	ARCH_SUFFIX=armv7
else
	ARCH_SUFFIX=aarch64
endif
$(warning "arch=$(ARCH) suffix=$(ARCH_SUFFIX)")
# clang toolchain suffix
TARGET := anctee_${VENDOR_NAME}_${ARCH_SUFFIX}.o
all: $(TARGET)

SUFFIX := 

PUBLIC_API := $(VENDOR_API)


ifeq ($(ARCH),huawei)
    NEED_MANGLE := 1
    MACHINE := arm-none-eabi
    COMMONFLAGS := -g -mfpu=neon -mfloat-abi=hard -march=armv7-a
    FIX_ELF_ARGS := FIXELF_TARGET1=1
else ifeq ($(ARCH),op-tee-armv7)
    MACHINE := arm-linux-gnueabihf
    COMMONFLAGS := -fpie -fPIC \
		-mfpu=neon -mfloat-abi=hard -march=armv7-a
    OPTFLAGS := -float-abi=hard -relocation-model=pic
else ifeq ($(ARCH),android-armv7)
    MACHINE := arm-linux-androideabi
    COMMONFLAGS := -g -mfpu=neon -mfloat-abi=hard -march=armv7-a -fPIC -fpie
    OPTFLAGS := -relocation-model=pic
else ifeq ($(ARCH),qsee-armv7)
	MACHINE := arm-linux-gnueabi
	COMMONFLAGS := -g -mfpu=neon -mfloat-abi=hard -march=armv7-a -fPIC -fpie
	OPTFLAGS := -relocation-model=pic
else ifeq ($(ARCH),android-aarch64)
    MACHINE := aarch64-linux-android
    COMMONFLAGS := -g -fPIC -fpie
    OPTFLAGS := -relocation-model=pic
    IS_AARCH64 := 1
else ifeq ($(ARCH),qsee-aarch64)
    MACHINE := aarch64-linux-gnu
    COMMONFLAGS := -fPIC -fpie -march=armv8.2-a+fp16+dotprod -DMEGDNN_DISABLE_FLOAT16
    OPTFLAGS := -relocation-model=pic
    IS_AARCH64 := 1
else
    $(error "unkown $(ARCH)")
endif
ifeq ($(IS_AARCH64),1)
    PUBLIC_API_INTERNAL := $(PUBLIC_API),__addtf3,__eqtf2,__extenddftf2,__fixtfsi,__fixunstfsi,__floatsitf,__floatunsitf,__multf3,__netf2,__subtf3,__unordtf2,__getf2,__divtf3,__letf2,__extendsftf2,__trunctfsf2,__trunctfdf2
else
    PUBLIC_API_INTERNAL := $(PUBLIC_API),__aeabi_memclr4,__aeabi_memclr8,__aeabi_memcpy,__aeabi_memcpy4,__aeabi_memcpy8,memset,__aeabi_idiv,__aeabi_idivmod,__aeabi_uidiv,__aeabi_uidivmod,__aeabi_uldivmod
endif

COMMONFLAGS := -emit-llvm $(OPTLEVEL)  \
    --target=aarch64-none-linux-android28 \
	-fvisibility=hidden \
	-fvisibility-inlines-hidden -fomit-frame-pointer \
	-DNDEBUG -Wall -Wextra -Wwrite-strings   \
	-D_XOPEN_SOURCE=700 $(COMMONFLAGS) -Isrc/sys/include -Isrc -IFingerprintUnlock/tee_sdk/vendor/$(VENDOR_NAME)/include/
ifeq ($(LIMIT_TIME),1)
	COMMONFLAGS := $(COMMONFLAGS) -D__SDK_DEMO_RELEASE__
endif

COMMONFLAGS := $(COMMONFLAGS) $(VENDOR_FLAGS)
ifeq ($(IS_AARCH64),1)
	COMMONFLAGS := $(COMMONFLAGS) -DIS_AARCH64
endif
# note: -disable-simplify-libcalls (handled in llvm/tools/opt/opt.cpp) is
# equivalent to -fno-builtin.
# See disableAllFunctions() in llvm/include/llvm/Analysis/TargetLibraryInfo.h
ifeq ($(OPTLEVEL),-Ofast)
    OPTFLAGS := -O3 $(OPTFLAGS)  -ffast-math
    COMMONFLAGS := $(COMMONFLAGS) -ffast-math
else
    OPTFLAGS := $(OPTLEVEL) $(OPTFLAGS)
endif
OPTFLAGS := $(OPTFLAGS) -thread-model=single -disable-simplify-libcalls

MUSL := third-party/musl
MUSL_INSTALL := third-party/install

LIBCXX := third-party/libcxx
LIBCXXABI := third-party/libcxxabi

# remember to check flags when musl library is updated
CFLAGS_MUSL := $(COMMONFLAGS)
ifeq ($(IS_AARCH64),1)
    CFLAGS_MUSL := $(CFLAGS_MUSL) -I$(MUSL)/arch/aarch64 -Isrc/sys/musl_aarch64/internal
	MUSL_INSTALL := third-party/install_aarch64
else
    CFLAGS_MUSL := $(CFLAGS_MUSL) -I$(MUSL)/arch/arm -DBROKEN_VFP_ASM -Isrc/sys/musl_armv7/internal
	MUSL_INSTALL := third-party/install_armv7
endif
CFLAGS_MUSL := $(CFLAGS_MUSL) -I$(MUSL)/arch/generic \
	-I$(MUSL_INSTALL)/include $(MEGDEBASE_FLAGS)

# CFLAGS_MUSL += -v

CFLAGS_MEGDNN := $(COMMONFLAGS) $(MEGDNN_FLAGS)
CFLAGS_MEGDNN := $(filter-out -emit-llvm,$(CFLAGS_MEGDNN))

CXXFLAGS := $(COMMONFLAGS) -std=c++14  \
	-I$(LIBCXX)/include -I$(LIBCXXABI)/include \
	-isystem $(MUSL_INSTALL)/include $(DEP_LIB_FLAGS)

# CXXFLAGS += -v

CXX := clang++$(SUFFIX)
CC := clang$(SUFFIX)
OPT := opt$(SUFFIX)
LLC := llc$(SUFFIX)
LLD := ld.lld$(SUFFIX)
LLVM_LINK := llvm-link$(SUFFIX)
LLVM_NM := llvm-nm$(SUFFIX)

CXXSOURCES += $(shell find -L . -name '*.cpp' ! -path './elfmanip/*' | sort)
CSOURCES := $(shell find -L . -name '*.c' ! -path 'src/sys/musl_aarch64/*' ! -path 'src/sys/musl_armv7/*' ! -path 'src/sys/compiler-rt-builtins-aarch64/*' ! -path 'src/sys/optee_os_arm/*' ! -path "src/libjpeg/*" | sort)

ASMSOURCES := $(shell find -L . -name '*.S')

BYTECODE := $(addprefix $(BUILD_DIR)/,$(CXXSOURCES:.cpp=.cpp.bc)) \
	    $(addprefix $(BUILD_DIR)/,$(CSOURCES:.c=.c.bc))
ASMOBJS := $(addprefix $(BUILD_DIR)/,$(ASMSOURCES:.S=.S.o))
DEPFILES := $(BYTECODE:.bc=.d)
DEPFILES += $(STATICLINKSOURCES)
MERGE_BYTECODE := $(BUILD_DIR)/merged.bc
-include $(DEPFILES)

$(BUILD_DIR)/%.cpp.bc: %.cpp
	@echo "[cxx] $< ..."
	@mkdir -pv $(dir $@)
	@$(CXX) $(CXXFLAGS) -MM -MT "$@" "$<"  > "$(@:.bc=.d)"
	$(V)$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.S.o: %.S
	@echo "[asm] $< ..."
	@mkdir -pv $(dir $@)
	@$(CC) $(CFLAGS_MEGDNN) -MM -MT "$@" "$<"  > "$(@:.bc=.d)"
	$(V)$(CC) -c $< -o $@ $(CFLAGS_MEGDNN)

$(BUILD_DIR)/%.c.bc: %.c
	@echo "[c] $< ..."
	@mkdir -pv $(dir $@)
	@$(CC) $(CFLAGS_MUSL) -MM -MT "$@" "$<"  > "$(@:.bc=.d)"
	$(V)$(CC) -c $< -o $@ $(CFLAGS_MUSL)

# see https://llvm.org/devmtg/2013-11/slides/Gao-LTO.pdf
$(MERGE_BYTECODE): $(BYTECODE)
	@echo "Merging bitcode files ..."
	$(V)$(LLVM_LINK) -o $@.nonopt0 $^
	$(V)$(OPT) -internalize \
		-internalize-public-api-list=$(PUBLIC_API_INTERNAL) \
		-o $@.nonopt1 $@.nonopt0
	$(V)$(OPT) $(OPTFLAGS) -mergefunc -std-link-opts -o $@ $@.nonopt1

$(BUILD_DIR)/main-orig.o: $(MERGE_BYTECODE)
	@echo "Linking ..."
	$(V)$(LLC) $(OPTFLAGS) -filetype=obj -o $@ $<

$(BUILD_DIR)/main-withasm.o: $(BUILD_DIR)/main-orig.o $(ASMOBJS)
#	@$(V)$(V)$(LLD) --script link-ia.ld --relocatable --define-common $< $(ASMOBJS) -o $@
#	lld seems slow; use gnu linker
	$(V)$(MACHINE)-ld -r -d $< $(ASMOBJS) -o $@

$(BUILD_DIR)/main-ia.o: $(BUILD_DIR)/main-withasm.o elfmanip/*.cpp
	@echo "Fix init/fini array ..."
	cp $< $@.tmp
	$(V) $(FIX_ELF_ARGS) ./elfmanip/prepare_merge.sh $@.tmp
	$(V)$(MACHINE)-ld -T link-ia.ld -r -d $@.tmp -o $@
	$(V) $(FIX_ELF_ARGS) ./elfmanip/fix_init_fini.sh $@

$(BUILD_DIR)/main.o: $(BUILD_DIR)/main-ia.o link-merge.ld
	@echo "Merge sections ..."
	@$(V)$(MACHINE)-ld -T link-merge.ld -r -d $< -o $@


$(BUILD_DIR)/main-pub.o: $(BUILD_DIR)/main.o
	@echo "[objcopy] $@"
	$(V)$(MACHINE)-objcopy \
		$(addprefix --keep-global-symbol=,$(subst $(comma), ,$(PUBLIC_API))) \
		$< $@

# for deleted headers
%.h: ;

$(BUILD_DIR)/main-mangle.o: $(BUILD_DIR)/main-pub.o elfmanip/mangle_sym.py
ifeq ($(NEED_MANGLE),1)
	@echo "Mangling ..."
	$(V)./elfmanip/mangle_sym.py $< $@ --objcopy $(MACHINE)-objcopy --nm $(LLVM_NM)
else
	$(V)cp -a $< $@
endif

comma := ,
$(TARGET): $(BUILD_DIR)/main-mangle.o always_copy
	$(V)cp -a $< $@
	$(LLVM_NM) $@ | grep ' [A-Z] '

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

always_copy:

.PHONY: all clean always_copy

# vim: ft=make

