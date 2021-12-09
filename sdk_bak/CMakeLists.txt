if(CMAKE_TOOLCHAIN_FILE)
    set(LIBRARY_OUTPUT_PATH_ROOT ${CMAKE_BINARY_DIR} CACHE PATH "root for library output, set this to change where android libs are compiled to")
    # get absolute path, but get_filename_component ABSOLUTE only refer with source dir, so find_file here :(
    get_filename_component(CMAKE_TOOLCHAIN_FILE_NAME ${CMAKE_TOOLCHAIN_FILE} NAME)
    find_file(CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE_NAME} PATHS ${CMAKE_SOURCE_DIR} NO_DEFAULT_PATH)
    message(STATUS "CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
endif()

ENABLE_LANGUAGE(ASM)

cmake_minimum_required(VERSION 2.8.12)

project(megtee)

set(VENDOR_NAME "anc")

set(CMAKE_CXX_FLAGS 
"-O3 \
-ffunction-sections -fdata-sections \
-fvisibility=hidden \
-fno-stack-protector \
-fvisibility-inlines-hidden \
-fno-asynchronous-unwind-tables \
-fno-unwind-tables \
-fomit-frame-pointer \
-DNDEBUG \
-Wall \
-Wextra \
-Wwrite-strings \
-Wno-unused-parameter \
-D_XOPEN_SOURCE=700 \
-fPIC \
-fpie \
-march=armv8.2-a+fp16+dotprod \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/sys/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/src \
-I${CMAKE_CURRENT_SOURCE_DIR}/FingerprintUnlock/tee_sdk/vendor/vendor/include \
-DSUPPORT_SHARE_MODEL_MEMORY \
-DSDK_ALGO_MOSAICKING \
-DIS_AARCH64 \
-fno-exceptions \
-fno-rtti \
-nostdinc++ \
-Wno-user-defined-literals \
-D_LIBCPP_BUILDING_LIBRARY -D_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER \
-D_LIBCPP_NO_EXCEPTIONS -D_LIBCPP_NO_RTTI -D_LIBCPP_HAS_NO_THREADS \
-D_LIBCXXABI_BUILDING_LIBRARY -D_LIBCXXABI_HAS_NO_PRAGMA_SYSTEM_HEADER \
-D_LIBCXXABI_NO_EXCEPTIONS -D_LIBCXXABI_NO_RTTI -D_LIBCXXABI_HAS_NO_THREADS \
-I${CMAKE_CURRENT_SOURCE_DIR}/third-party/libcxx/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/third-party/libcxxabi/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/third-party/install_aarch64/include \
-Wno-user-defined-literals \
-DMEGTEE_INTERNAL_BUILD=1 \
-DMGB_HAVE_THREAD=0 \
-DANDROID=1 \
-D__ANDROID__=1 \
-DMGB_EXTERN_API_TIME=1 \
-DMGB_EXTERN_API_MEMSTAT=1 \
-DMGB_ENABLE_ANDROID_NN=0 \
-DMGB_ENABLE_CPUINFO=0 \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/sdk/build_config \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/src/core/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/src/opr/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/src/gopt/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/src/plugin/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/src/serialization/include \
-DMEGDNN_ENABLE_MANGLING=1 \
-DMEGDNN_ANDROID=1 \
-DMEGDNN_NO_THREAD=1 \
-funsafe-math-optimizations \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/dnn/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/dnn/ \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegBrain/third_party/midout/src \
-DMGF_PLATFORM_ARM32=0 \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/megdnn \
-I${CMAKE_CURRENT_SOURCE_DIR}/FingerprintUnlock/models/cache/aarch64 \
-DMGF_NO_TIME_API=1 \
-D__MGF_TEE__ \
-DMGF_FEAT_KEY_FOR_VIVO=1 \
-DMGF_PLATFORM_ANDROID=1 \
-I${CMAKE_CURRENT_SOURCE_DIR}/megface-v2/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/MegCV2/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/megface-bucket \
-I${CMAKE_CURRENT_SOURCE_DIR}/megface-v2/include/nlohmann/single_include \
-D__ARM_NEON__ \
-I${CMAKE_CURRENT_SOURCE_DIR}/FingerprintUnlock/models \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/fingerprint-unlock/vendor/vendor/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/fingerprint-unlock/vendor/vendor/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/fingerprint-unlock/src/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/fingerprint-unlock/src/include/mgulk \
-I${CMAKE_CURRENT_SOURCE_DIR}/src/libjpeg \
-DMGULK_USE_MGB_TIMER=1 \
-DMGULK_IN_TEE=1 \
-DMGULK_USE_DEPTH=1 \
-DMGULK_USE_PATTERN=1 \
-DMEM_PROFILE=1 \
-DPROJECT_NAME=\\\"LUNA_A\\\" \
-DSDK_VERSION=\\\"2021081003\\\" \
-DMEGTEE_VERSION=\\\"959f752\\\" \
-DBUILD_NUMBER=0 \
-DBUILD_NUMBER_STR=\\\"0\\\" \
-DFAST_COMPARE_RET \
-I${CMAKE_CURRENT_SOURCE_DIR}/libdebase/include \
-I${CMAKE_CURRENT_SOURCE_DIR}/libdebase/src \
-I${CMAKE_CURRENT_SOURCE_DIR}/libdebase/src/include"
)

set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})

set(CXXSOURCES
    src/fingerprint-unlock/src/common.cpp 
    src/fingerprint-unlock/src/finger_algo_strategy.cpp 
    src/fingerprint-unlock/src/finger_handler.cpp 
    src/fingerprint-unlock/src/finger_sensor_evaluation.cpp 
    src/fingerprint-unlock/src/finger_sensor_handler.cpp 
    src/fingerprint-unlock/src/fp_debase.cpp 
    src/fingerprint-unlock/src/fp_mosaicking.cpp 
    src/fingerprint-unlock/src/light_checker.cpp 
    src/fingerprint-unlock/src/mat.cpp 
    src/fingerprint-unlock/src/sensor-distortion.cpp 
    src/fingerprint-unlock/vendor/vendor/src/AncAdapter.cpp 
    src/fingerprint-unlock/vendor/vendor/src/c_api_adapter.cpp 
    src/fingerprint-unlock/vendor/vendor/src/feature_set_manager.cpp 
    src/libjpeg/jaricom.c 
    src/libjpeg/jcapimin.c 
    src/libjpeg/jcapistd.c 
    src/libjpeg/jcarith.c 
    src/libjpeg/jccoefct.c 
    src/libjpeg/jccolor.c 
    src/libjpeg/jcdctmgr.c 
    src/libjpeg/jchuff.c 
    src/libjpeg/jcinit.c 
    src/libjpeg/jcmainct.c 
    src/libjpeg/jcmarker.c 
    src/libjpeg/jcmaster.c 
    src/libjpeg/jcomapi.c 
    src/libjpeg/jcparam.c 
    src/libjpeg/jcphuff.c 
    src/libjpeg/jcprepct.c 
    src/libjpeg/jcsample.c 
    src/libjpeg/jctrans.c 
    src/libjpeg/jdapimin.c 
    src/libjpeg/jdapistd.c 
    src/libjpeg/jdarith.c 
    src/libjpeg/jdatadst-tj.c 
    src/libjpeg/jdatadst.c 
    src/libjpeg/jdatasrc-tj.c 
    src/libjpeg/jdatasrc.c 
    src/libjpeg/jdcoefct.c 
    src/libjpeg/jdcolor.c 
    src/libjpeg/jddctmgr.c 
    src/libjpeg/jdhuff.c 
    src/libjpeg/jdinput.c 
    src/libjpeg/jdmainct.c 
    src/libjpeg/jdmarker.c 
    src/libjpeg/jdmaster.c 
    src/libjpeg/jdmerge.c 
    src/libjpeg/jdphuff.c 
    src/libjpeg/jdpostct.c 
    src/libjpeg/jdsample.c 
    src/libjpeg/jdtrans.c 
    src/libjpeg/jerror.c 
    src/libjpeg/jfdctflt.c 
    src/libjpeg/jfdctfst.c 
    src/libjpeg/jfdctint.c 
    src/libjpeg/jidctflt.c 
    src/libjpeg/jidctfst.c 
    src/libjpeg/jidctint.c 
    src/libjpeg/jidctred.c 
    src/libjpeg/jmemmgr.c 
    src/libjpeg/jmemnobs.c 
    src/libjpeg/jquant1.c 
    src/libjpeg/jquant2.c 
    src/libjpeg/jutils.c 
    src/libjpeg/simd/jsimd_arm64.c 
    src/libjpeg/simd/jsimd_arm64_neon.S
    src/libjpeg/transupp.c 
    src/libjpeg/turbojpeg.c 
    src/megbrain/core/common.cpp 
    src/megbrain/core/comp_node/atlas/comp_node.cpp 
    src/megbrain/core/comp_node/cadence/comp_node.cpp 
    src/megbrain/core/comp_node/cambricon/comp_node.cpp 
    src/megbrain/core/comp_node/comp_node.cpp 
    src/megbrain/core/comp_node/cpu/comp_node.cpp 
    src/megbrain/core/comp_node/cuda/comp_node.cpp 
    src/megbrain/core/comp_node/fpga/comp_node.cpp 
    src/megbrain/core/comp_node/fpga/driver/driver.cpp 
    src/megbrain/core/comp_node/fpga/driver/fake_driver.cpp 
    src/megbrain/core/comp_node/hexagon/comp_node.cpp 
    src/megbrain/core/comp_node/impl_helper.cpp 
    src/megbrain/core/comp_node/mem_alloc/alloc.cpp 
    src/megbrain/core/comp_node/mem_alloc/impl.cpp 
    src/megbrain/core/comp_node/opencl/command_queue.cpp 
    src/megbrain/core/comp_node/opencl/comp_node.cpp 
    src/megbrain/core/comp_node/rocm/comp_node.cpp 
    src/megbrain/core/comp_node_env.cpp 
    src/megbrain/core/dtype.cpp 
    src/megbrain/core/exception.cpp 
    src/megbrain/core/graph/bases.cpp             
    src/megbrain/core/graph/cg_impl.cpp                                                          
    src/megbrain/core/graph/cg_impl_partial.cpp    
    src/megbrain/core/graph/cg_impl_seq.cpp      
    src/megbrain/core/graph/eager_eval.cpp                      
    src/megbrain/core/graph/event.cpp       
    src/megbrain/core/graph/execution_mask.cpp                        
    src/megbrain/core/graph/grad_manager.cpp  
    src/megbrain/core/graph/graph_opt.cpp             
    src/megbrain/core/graph/helper.cpp                        
    src/megbrain/core/graph/memory_optimizer.cpp                                           
    src/megbrain/core/graph/normal_exec_env.cpp   
    src/megbrain/core/graph/operator_node.cpp                     
    src/megbrain/core/graph/seq_comp_node_opt_impl.cpp       
    src/megbrain/core/graph/seq_sublinear_memory.cpp                                                   
    src/megbrain/core/graph/static_infer_impl.cpp       
    src/megbrain/core/graph/swap/memory_swap.cpp            
    src/megbrain/core/graph/swap/swap_helper.cpp     
    src/megbrain/core/graph/swap/swap_opr.cpp                
    src/megbrain/core/graph/symbol_var.cpp 
    src/megbrain/core/graph/topo_sort.cpp                                                                                           
    src/megbrain/core/graph/var_node.cpp               
    src/megbrain/core/graph/var_node_mem_mgr.cpp  
    src/megbrain/core/graph/var_node_mem_mgr/defrag.cpp                               
    src/megbrain/core/graph/var_node_mem_mgr/seq_mem_opt.cpp 
    src/megbrain/core/graph/var_node_mem_mgr/static_mem_alloc/best_fit.cpp 
    src/megbrain/core/graph/var_node_mem_mgr/static_mem_alloc/best_fit_helper.cpp 
    src/megbrain/core/graph/var_node_mem_mgr/static_mem_alloc/impl.cpp 
    src/megbrain/core/graph/var_node_mem_mgr/static_mem_alloc/interval_move.cpp 
    src/megbrain/core/graph/var_node_mem_mgr/static_mem_alloc/pushdown.cpp 
    src/megbrain/core/system.cpp 
    src/megbrain/core/tensor.cpp 
    src/megbrain/core/utils/async_worker.cpp 
    src/megbrain/core/utils/comp_node_sync_manager.cpp 
    src/megbrain/core/utils/debug.cpp 
    src/megbrain/core/utils/event.cpp 
    src/megbrain/core/utils/hash.cpp 
    src/megbrain/core/utils/hashable.cpp 
    src/megbrain/core/utils/json.cpp 
    src/megbrain/core/utils/mempool.cpp 
    src/megbrain/core/utils/metahelper.cpp 
    src/megbrain/core/utils/persistent_cache.cpp 
    src/megbrain/core/utils/thread.cpp 
    src/megbrain/core/utils/thread_pool.cpp 
    src/megbrain/core/utils/timer.cpp 
    src/megbrain/core/utils/xxhash/xxhash.cpp 
    src/megbrain/core/version.cpp 
    src/megbrain/gopt/basic_arith/chain.cpp 
    src/megbrain/gopt/basic_arith/inplace.cpp 
    src/megbrain/gopt/basic_arith/trans.cpp 
    src/megbrain/gopt/framework.cpp 
    src/megbrain/gopt/gtrans.cpp 
    src/megbrain/gopt/inference.cpp 
    src/megbrain/gopt/misc.cpp 
    src/megbrain/gopt/tensor_reformat.cpp 
    src/megbrain/gopt/weights_preprocess.cpp 
    src/megbrain/opr/atlas_runtime_op.cpp 
    src/megbrain/opr/basic_arith.cpp 
    src/megbrain/opr/blas.cpp 
    src/megbrain/opr/cond.cpp 
    src/megbrain/opr/dnn/adaptive_pooling.cpp 
    src/megbrain/opr/dnn/batch_norm.cpp 
    src/megbrain/opr/dnn/convolution.cpp 
    src/megbrain/opr/dnn/images2neibs.cpp 
    src/megbrain/opr/dnn/local.cpp 
    src/megbrain/opr/dnn/lrn.cpp 
    src/megbrain/opr/dnn/pooling.cpp 
    src/megbrain/opr/dnn/roi_align.cpp 
    src/megbrain/opr/dnn/roi_pooling.cpp 
    src/megbrain/opr/fpga.cpp 
    src/megbrain/opr/hexagon.cpp 
    src/megbrain/opr/imgproc.cpp 
    src/megbrain/opr/indexing.cpp 
    src/megbrain/opr/internal/identical_fwd.cpp 
    src/megbrain/opr/internal/indexing_helper.cpp 
    src/megbrain/opr/internal/megdnn_opr_wrapper.cpp 
    src/megbrain/opr/internal/out_shape_by_sym_var.cpp 
    src/megbrain/opr/io.cpp 
    src/megbrain/opr/loop/forward.cpp 
    src/megbrain/opr/loop/forward_sereg.cpp 
    src/megbrain/opr/loop/grad.cpp 
    src/megbrain/opr/loop/grad_sereg.cpp 
    src/megbrain/opr/loop/impl.cpp 
    src/megbrain/opr/loop/output_recorder.cpp 
    src/megbrain/opr/misc.cpp 
    src/megbrain/opr/muxing.cpp 
    src/megbrain/opr/nn_int.cpp 
    src/megbrain/opr/nvof/denseflownvidia.cpp 
    src/megbrain/opr/nvof/NvOF.cpp 
    src/megbrain/opr/nvof/NvOFCuda.cpp 
    src/megbrain/opr/rand.cpp 
    src/megbrain/opr/standalone/nms_cpu.cpp 
    src/megbrain/opr/standalone/nms_opr.cpp 
    src/megbrain/opr/tensor_gen.cpp 
    src/megbrain/opr/tensor_manip.cpp 
    src/megbrain/opr/utility.cpp 
    src/megbrain/plugin/cpu_dispatch_checker.cpp 
    src/megbrain/plugin/infkern_finder.cpp 
    src/megbrain/plugin/num_range_checker.cpp 
    src/megbrain/plugin/opr_footprint.cpp 
    src/megbrain/plugin/opr_io_dump.cpp 
    src/megbrain/plugin/profiler.cpp 
    src/megbrain/plugin/var_sanity_check.cpp 
    src/megbrain/plugin/var_value_checker.cpp 
    src/megbrain/serialization/batched_device_value_loader.cpp 
    src/megbrain/serialization/extern_c_opr.cpp 
    src/megbrain/serialization/file.cpp 
    src/megbrain/serialization/flatbuffers_helper.cpp 
    src/megbrain/serialization/helper.cpp 
    src/megbrain/serialization/opr_load_dump.cpp 
    src/megbrain/serialization/opr_registry.cpp 
    src/megbrain/serialization/opr_shallow_copy.cpp 
    src/megbrain/serialization/sereg_caller.cpp 
    src/megbrain/serialization/serializer.cpp
    src/megbrain/serialization/serializer_mdl.cpp 
    src/megbrain/serialization/serializer_oss.cpp 
    src/megcv/src/get_perspective.cpp 
    src/megcv/src/mat.cpp 
    src/megcv/src/megcv.cpp 
    src/megdebase/src/debase.c 
    src/megdebase/src/fft.c 
    src/megdebase/src/ImageCheck.c 
    src/megdebase/src/ImageDeal.cpp 
    src/megdebase/src/ImageFeature.c 
    src/megdebase/src/pocketfft.c 
    src/megdebase/src/Variance2.c 
    src/megdebase/src/wt_src/conv.c 
    src/megdebase/src/wt_src/cwt.c 
    src/megdebase/src/wt_src/cwtmath.c 
    src/megdebase/src/wt_src/hsfft.c 
    src/megdebase/src/wt_src/real.c 
    src/megdebase/src/wt_src/wavefilt.c 
    src/megdebase/src/wt_src/wavefunc.c 
    src/megdebase/src/wt_src/wavelib.c 
    src/megdebase/src/wt_src/wtmath.c 
    src/megdnn/aarch64/conv_bias/fp16/algos.cpp 
    src/megdnn/aarch64/conv_bias/fp32/algos.cpp 
    src/megdnn/aarch64/conv_bias/int8/algos.cpp 
    src/megdnn/aarch64/conv_bias/int8/strategy.cpp 
    src/megdnn/aarch64/conv_bias/opr_impl.cpp 
    src/megdnn/aarch64/conv_bias/quint8/algos.cpp 
    src/megdnn/aarch64/conv_bias/quint8/strategy.cpp 
    src/megdnn/aarch64/handle.cpp 
    src/megdnn/aarch64/matrix_mul/algos.cpp 
    src/megdnn/aarch64/matrix_mul/fp16/strategy.cpp 
    src/megdnn/aarch64/matrix_mul/fp16/strategy_mk8_8x8.cpp 
    src/megdnn/aarch64/matrix_mul/fp32/strategy.cpp 
    src/megdnn/aarch64/matrix_mul/fp32/strategy_mk4_4x16.cpp 
    src/megdnn/aarch64/matrix_mul/int16/strategy.cpp 
    src/megdnn/aarch64/matrix_mul/int16/strategy_mk8_8x8.cpp 
    src/megdnn/aarch64/matrix_mul/int8/strategy.cpp 
    src/megdnn/aarch64/matrix_mul/int8_dot/strategy.cpp 
    src/megdnn/aarch64/matrix_mul/int8x8x16/strategy.cpp 
    src/megdnn/aarch64/matrix_mul/opr_impl.cpp 
    src/megdnn/aarch64/matrix_mul/quint8/strategy.cpp 
    src/megdnn/aarch64/matrix_mul/quint8_dot/gemv.cpp 
    src/megdnn/aarch64/matrix_mul/quint8_dot/strategy.cpp 
    src/megdnn/aarch64/relayout/opr_impl.cpp 
    src/megdnn/aarch64/rotate/opr_impl.cpp 
    src/megdnn/aarch64/warp_perspective/opr_impl.cpp 
    src/megdnn/aarch64/warp_perspective/warp_perspective_cv.cpp 
    src/megdnn/arm_common/conv_bias/direct/multi_thread_common.cpp 
    src/megdnn/arm_common/conv_bias/f16/algos.cpp 
    src/megdnn/arm_common/conv_bias/f16/direct.cpp 
    src/megdnn/arm_common/conv_bias/f16/do_conv_stride1.cpp 
    src/megdnn/arm_common/conv_bias/f16/strategy_2x3.cpp 
    src/megdnn/arm_common/conv_bias/f16/strategy_2x3_8x8.cpp 
    src/megdnn/arm_common/conv_bias/f16/strategy_4x5.cpp 
    src/megdnn/arm_common/conv_bias/f16/strategy_6x3.cpp 
    src/megdnn/arm_common/conv_bias/fp32/algos.cpp 
    src/megdnn/arm_common/conv_bias/fp32/channel_wise_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/fp32/channel_wise_nchw44_kern.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_2x2s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_2x2s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_3x3s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_3x3s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_5x5s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_5x5s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_7x7s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw44_kern_7x7s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_2x2s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_2x2s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_3x3s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_3x3s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_5x5s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_5x5s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_7x7s1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/direct_kernels/f32_direct_nchw_nchw44_kern_7x7s2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/do_conv_stride1.cpp 
    src/megdnn/arm_common/conv_bias/fp32/do_conv_stride2.cpp 
    src/megdnn/arm_common/conv_bias/fp32/f32_direct_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/fp32/f32_direct_nchw_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_2x3_4x4.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_4x5.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_5x4.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_6x3.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_6x3_4x4.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_f23_mk4_nchw44.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_f63_mk4_nchw44.cpp 
    src/megdnn/arm_common/conv_bias/fp32/strategy_f73_mk4_nchw44.cpp 
    src/megdnn/arm_common/conv_bias/int8/algos.cpp 
    src/megdnn/arm_common/conv_bias/int8/channel_wise_kernel.cpp 
    src/megdnn/arm_common/conv_bias/int8/channel_wise_nchw44.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_dotprod.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_dotprod_nchw44.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_dotprod_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/dot_direct_nchw44_s1.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/dot_direct_nchw44_s2.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/dot_direct_nchw_nchw44_s1.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/dot_direct_nchw_nchw44_s2.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/int8_direct_nchw44_s1.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/int8_direct_nchw44_s2.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/int8_direct_nchw_nchw44_s1.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_kernels/int8_direct_nchw_nchw44_s2.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/int8/direct_nchw_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/int8/dot_direct_nchw_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/int8/strategy_2x3_8x8.cpp 
    src/megdnn/arm_common/conv_bias/int8/strategy_nchw44_2x3_4x4.cpp 
    src/megdnn/arm_common/conv_bias/int8/strategy_nchw44_2x3_8x8.cpp 
    src/megdnn/arm_common/conv_bias/int8/stride1.cpp 
    src/megdnn/arm_common/conv_bias/int8/stride1_dotprod.cpp 
    src/megdnn/arm_common/conv_bias/int8/stride2.cpp 
    src/megdnn/arm_common/conv_bias/int8/stride2_dotprod.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/algos.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/channel_wise_kernel_int8x8x16_nchw44.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/channel_wise_nchw44_8x8x16.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/conv_direct.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/conv_stride2.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/direct_8x8x16_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/direct_kernels/int8x8x16_direct_nchw44_s1_aarch64.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/direct_kernels/int8x8x16_direct_nchw44_s1_armv7.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/direct_kernels/int8x8x16_direct_nchw44_s2.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/direct_nchw_nchw44_algo.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/kernel/direct_nchw_nchw44_kern_impl_s1.cpp 
    src/megdnn/arm_common/conv_bias/int8x8x16/kernel/direct_nchw_nchw44_kern_impl_s2.cpp 
    src/megdnn/arm_common/conv_bias/opr_impl.cpp 
    src/megdnn/arm_common/conv_bias/quint8/algos.cpp 
    src/megdnn/arm_common/conv_bias/quint8/direct.cpp 
    src/megdnn/arm_common/conv_bias/quint8/direct_dotprod.cpp 
    src/megdnn/arm_common/conv_bias/quint8/stride1.cpp 
    src/megdnn/arm_common/conv_bias/quint8/stride1_dotprod.cpp 
    src/megdnn/arm_common/conv_bias/quint8/stride2.cpp 
    src/megdnn/arm_common/conv_bias/quint8/stride2_dotprod.cpp 
    src/megdnn/arm_common/convolution/int8x8x32/algos.cpp 
    src/megdnn/arm_common/convolution/int8x8x32/conv_backdata_stride1.cpp 
    src/megdnn/arm_common/convolution/int8x8x32/conv_backdata_stride2.cpp 
    src/megdnn/arm_common/convolution/opr_impl.cpp 
    src/megdnn/arm_common/convolution/quint8/algos.cpp 
    src/megdnn/arm_common/convolution/quint8/conv_backdata_stride1.cpp 
    src/megdnn/arm_common/convolution/quint8/conv_backdata_stride2.cpp 
    src/megdnn/arm_common/cvt_color/opr_impl.cpp 
    src/megdnn/arm_common/elemwise/binary/algo.cpp 
    src/megdnn/arm_common/elemwise/neon_mathfun.cpp 
    src/megdnn/arm_common/elemwise/opr_impl.cpp 
    src/megdnn/arm_common/elemwise/ternary/algo.cpp 
    src/megdnn/arm_common/elemwise/unary/algo.cpp 
    src/megdnn/arm_common/elemwise_multi_type/opr_impl.cpp 
    src/megdnn/arm_common/handle.cpp 
    src/megdnn/arm_common/local/opr_impl.cpp 
    src/megdnn/arm_common/matrix_mul/algos.cpp 
    src/megdnn/arm_common/matrix_mul/exec_gemm_int8_int8_int16.cpp 
    src/megdnn/arm_common/matrix_mul/fp16/hgemv.cpp 
    src/megdnn/arm_common/matrix_mul/fp32/exec_sgemv.cpp 
    src/megdnn/arm_common/matrix_mul/int8/gemv.cpp 
    src/megdnn/arm_common/matrix_mul/opr_impl.cpp 
    src/megdnn/arm_common/pooling/algo.cpp 
    src/megdnn/arm_common/pooling/algo_fp32_pooling_nchw44.cpp 
    src/megdnn/arm_common/pooling/do_max_pooling_3x3_s2x2_float.cpp 
    src/megdnn/arm_common/pooling/do_max_pooling_3x3_s2x2_float16.cpp 
    src/megdnn/arm_common/pooling/do_max_pooling_3x3_s2x2_int8.cpp 
    src/megdnn/arm_common/pooling/do_max_pooling_w2x2_s2x2.cpp 
    src/megdnn/arm_common/pooling/do_max_pooling_w4x4_s2x2.cpp 
    src/megdnn/arm_common/pooling/do_pooling_2x2_nchw44.cpp 
    src/megdnn/arm_common/pooling/do_pooling_3x3_nchw44.cpp 
    src/megdnn/arm_common/pooling/do_pooling_4x4_nchw44.cpp 
    src/megdnn/arm_common/pooling/do_pooling_5x5_nchw44.cpp 
    src/megdnn/arm_common/pooling/opr_impl.cpp 
    src/megdnn/arm_common/reduce/opr_impl.cpp 
    src/megdnn/arm_common/resize/opr_impl.cpp 
    src/megdnn/arm_common/resize/resize_cv.cpp 
    src/megdnn/arm_common/separable_conv/opr_impl.cpp 
    src/megdnn/arm_common/separable_conv/sep_conv_filter_engine.cpp 
    src/megdnn/arm_common/separable_filter/opr_impl.cpp 
    src/megdnn/arm_common/simd_macro/marm_neon.cpp 
    src/megdnn/arm_common/type_cvt/opr_impl.cpp 
    src/megdnn/arm_common/utils.cpp 
    src/megdnn/arm_common/warp_affine/opr_impl.cpp 
    src/megdnn/arm_common/warp_affine/warp_affine_cv.cpp 
    src/megdnn/arm_common/warp_perspective/opr_impl.cpp 
    src/megdnn/arm_common/warp_perspective/warp_perspective_cv.cpp 
    src/megdnn/arm_common/winograd_filter_preprocess/opr_impl.cpp 
    src/megdnn/common/adaptive_pooling.cpp 
    src/megdnn/common/add_update.cpp 
    src/megdnn/common/argmxx/base_impl.cpp 
    src/megdnn/common/argsort.cpp 
    src/megdnn/common/basic_types.cpp 
    src/megdnn/common/batch_conv_bias.cpp 
    src/megdnn/common/batch_normalization.cpp 
    src/megdnn/common/batched_matrix_mul.cpp 
    src/megdnn/common/checksum.cpp 
    src/megdnn/common/concat_split.cpp 
    src/megdnn/common/cond_take/opr_impl.cpp 
    src/megdnn/common/conv_bias.cpp 
    src/megdnn/common/conv_pooling.cpp 
    src/megdnn/common/convolution.cpp 
    src/megdnn/common/convolution3d.cpp 
    src/megdnn/common/cpuinfo_arch_vendor.cpp 
    src/megdnn/common/cumsum.cpp 
    src/megdnn/common/cv/filter.cpp 
    src/megdnn/common/cv/interp_helper.cpp 
    src/megdnn/common/cv/mat.cpp 
    src/megdnn/common/cvt_color.cpp 
    src/megdnn/common/deformable_conv.cpp 
    src/megdnn/common/deformable_ps_roi_pooling.cpp 
    src/megdnn/common/dot.cpp 
    src/megdnn/common/dtype.cpp 
    src/megdnn/common/elemwise/opr_impl.cpp 
    src/megdnn/common/elemwise/opr_impl_helper.cpp 
    src/megdnn/common/elemwise_helper.cpp 
    src/megdnn/common/elemwise_multi_type/opr_impl.cpp 
    src/megdnn/common/elemwise_multi_type/opr_impl_helper.cpp 
    src/megdnn/common/eye.cpp 
    src/megdnn/common/flag_warn.cpp 
    src/megdnn/common/flip.cpp 
    src/megdnn/common/gaussian_blur.cpp 
    src/megdnn/common/group_local.cpp 
    src/megdnn/common/handle.cpp 
    src/megdnn/common/images2neibs.cpp 
    src/megdnn/common/indexing_multi_axis_vec.cpp 
    src/megdnn/common/indexing_one_hot.cpp 
    src/megdnn/common/linspace.cpp 
    src/megdnn/common/local/opr_impl.cpp 
    src/megdnn/common/local_share/opr_impl.cpp 
    src/megdnn/common/lrn.cpp 
    src/megdnn/common/mask_conv.cpp 
    src/megdnn/common/matrix_inverse.cpp 
    src/megdnn/common/matrix_mul.cpp 
    src/megdnn/common/max_tensor_diff.cpp 
    src/megdnn/common/megcore/common/computing_context.cpp 
    src/megdnn/common/megcore/common/device_context.cpp 
    src/megdnn/common/megcore/cpu/api.cpp 
    src/megdnn/common/megcore/cpu/default_computing_context.cpp 
    src/megdnn/common/megcore/cpu/default_device_context.cpp 
    src/megdnn/common/megcore/public_api/computing.cpp 
    src/megdnn/common/megcore/public_api/device.cpp 
    src/megdnn/common/megcore/public_api/misc.cpp 
    src/megdnn/common/mesh_indexing.cpp 
    src/megdnn/common/nchw_nchwxx_valid.cpp 
    src/megdnn/common/opr_delegate.cpp 
    src/megdnn/common/param_pack.cpp 
    src/megdnn/common/pooling.cpp 
    src/megdnn/common/powc.cpp 
    src/megdnn/common/reduce.cpp 
    src/megdnn/common/reduce_helper.cpp 
    src/megdnn/common/relayout.cpp 
    src/megdnn/common/relayout_format.cpp 
    src/megdnn/common/remap.cpp 
    src/megdnn/common/resize.cpp 
    src/megdnn/common/rng.cpp 
    src/megdnn/common/roi_align.cpp 
    src/megdnn/common/roi_copy.cpp 
    src/megdnn/common/roi_pooling.cpp 
    src/megdnn/common/rotate.cpp 
    src/megdnn/common/separableConv.cpp 
    src/megdnn/common/separableFilter.cpp 
    src/megdnn/common/small_vector.cpp 
    src/megdnn/common/svd.cpp 
    src/megdnn/common/tensor_format.cpp 
    src/megdnn/common/tensor_iter.cpp 
    src/megdnn/common/tensor_remap.cpp 
    src/megdnn/common/tile_repeat.cpp 
    src/megdnn/common/tile_repeat_helper.cpp 
    src/megdnn/common/topk.cpp 
    src/megdnn/common/transpose.cpp 
    src/megdnn/common/type_cvt.cpp 
    src/megdnn/common/utils.cpp 
    src/megdnn/common/version.cpp 
    src/megdnn/common/warp_affine.cpp 
    src/megdnn/common/warp_common.cpp 
    src/megdnn/common/warp_perspective.cpp 
    src/megdnn/common/warp_perspective_helper.cpp 
    src/megdnn/common/winograd/winograd_generator.cpp 
    src/megdnn/common/winograd/winograd_helper.cpp 
    src/megdnn/common/winograd_filter_preprocess.cpp 
    src/megdnn/fallback/add_update/opr_impl.cpp 
    src/megdnn/fallback/batched_matrix_mul/opr_impl.cpp 
    src/megdnn/fallback/concat/opr_impl.cpp 
    src/megdnn/fallback/conv_bias/algos.cpp 
    src/megdnn/fallback/conv_bias/conv1x1/algos.cpp 
    src/megdnn/fallback/conv_bias/conv1x1/algos_conv1x1_gemv.cpp 
    src/megdnn/fallback/conv_bias/conv1x1/conv1x1_strategy.cpp 
    src/megdnn/fallback/conv_bias/conv1x1/conv1x1_utils.cpp 
    src/megdnn/fallback/conv_bias/im2col/algos.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_default.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_default_nchw44.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_fuse_nchw44.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_fuse_nchw44_dot.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_fuse_nchw44_dot_s2.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_fuse_nchw44_fp32_s2.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_nopack.cpp 
    src/megdnn/fallback/conv_bias/im2col/strategy_onlypacka.cpp 
    src/megdnn/fallback/conv_bias/opr_impl.cpp 
    src/megdnn/fallback/conv_bias/winograd/strategy.cpp 
    src/megdnn/fallback/convolution/algos.cpp 
    src/megdnn/fallback/convolution/opr_impl.cpp 
    src/megdnn/fallback/convolution/run_conv.cpp 
    src/megdnn/fallback/elemwise/opr_impl.cpp 
    src/megdnn/fallback/elemwise_multi_type/opr_impl.cpp 
    src/megdnn/fallback/flip/opr_impl.cpp 
    src/megdnn/fallback/gaussian_blur/opr_impl.cpp 
    src/megdnn/fallback/group_local/opr_impl.cpp 
    src/megdnn/fallback/handle.cpp 
    src/megdnn/fallback/mask_conv/opr_impl.cpp 
    src/megdnn/fallback/matrix_mul/algos.cpp 
    src/megdnn/fallback/matrix_mul/generic_strategy.cpp 
    src/megdnn/fallback/matrix_mul/opr_impl.cpp 
    src/megdnn/fallback/pooling/opr_impl.cpp 
    src/megdnn/fallback/powc/opr_impl.cpp 
    src/megdnn/fallback/reduce/opr_impl.cpp 
    src/megdnn/fallback/relayout/opr_impl.cpp 
    src/megdnn/fallback/repeat/opr_impl.cpp 
    src/megdnn/fallback/resize/opr_impl.cpp 
    src/megdnn/fallback/roi_copy/opr_impl.cpp 
    src/megdnn/fallback/rotate/opr_impl.cpp 
    src/megdnn/fallback/split/opr_impl.cpp 
    src/megdnn/fallback/tile/opr_impl.cpp 
    src/megdnn/fallback/type_cvt/opr_impl.cpp 
    src/megdnn/fallback/warp_perspective/opr_impl.cpp 
    src/megdnn/megcore_opencl.cpp 
    src/megdnn/naive/adaptive_pooling/opr_impl.cpp 
    src/megdnn/naive/add_update/opr_impl.cpp 
    src/megdnn/naive/argmxx/opr_impl.cpp 
    src/megdnn/naive/argsort/opr_impl.cpp 
    src/megdnn/naive/batch_conv_bias/opr_impl.cpp 
    src/megdnn/naive/batch_normalization/opr_impl.cpp 
    src/megdnn/naive/batched_matrix_mul/opr_impl.cpp 
    src/megdnn/naive/checksum/opr_impl.cpp 
    src/megdnn/naive/concat/concat.cpp 
    src/megdnn/naive/cond_take/opr_impl.cpp 
    src/megdnn/naive/conv_bias/opr_impl.cpp 
    src/megdnn/naive/convolution/convolution.cpp 
    src/megdnn/naive/convolution3d/convolution3d.cpp 
    src/megdnn/naive/convpooling/conv_pooling.cpp 
    src/megdnn/naive/cumsum/opr_impl.cpp 
    src/megdnn/naive/cvt_color/opr_impl.cpp 
    src/megdnn/naive/deformable_conv/opr_impl.cpp 
    src/megdnn/naive/deformable_ps_roi_pooling/opr_impl.cpp 
    src/megdnn/naive/dot/opr_impl.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_GRAD_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_GRAD_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_GRAD_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_GRAD_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_GRAD_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_GRAD_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/ABS_GRAD_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/ACOS_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ACOS_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ACOS_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ADD_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ADD_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ADD_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ADD_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/ADD_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/ADD_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/ADD_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/AND_dt_bool.cpp 
    src/megdnn/naive/elemwise/kimpl/ASIN_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ASIN_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ASIN_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ATAN2_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ATAN2_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ATAN2_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/CEIL_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/CEIL_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/CEIL_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/COND_LEQ_MOV_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/COND_LEQ_MOV_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/COND_LEQ_MOV_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/COND_LEQ_MOV_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/COND_LEQ_MOV_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/COND_LEQ_MOV_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/COND_LEQ_MOV_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/COS_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/COS_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/COS_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_bool.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/EQ_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/ERF_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERF_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERF_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFC_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFC_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFC_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFCINV_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFCINV_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFCINV_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFINV_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFINV_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ERFINV_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/EXP_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/EXP_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/EXP_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/EXPM1_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/EXPM1_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/EXPM1_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FAST_TANH_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FAST_TANH_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FAST_TANH_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FAST_TANH_GRAD_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FAST_TANH_GRAD_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FAST_TANH_GRAD_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_DIV_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_DIV_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_DIV_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_DIV_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_DIV_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_DIV_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_DIV_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FLOOR_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_H_SWISH_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_H_SWISH_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_H_SWISH_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_RELU_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_RELU_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_RELU_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_RELU_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_RELU_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_RELU_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_RELU_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_SIGMOID_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_SIGMOID_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_SIGMOID_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_TANH_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_TANH_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_ADD_TANH_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_MUL_ADD3_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_MUL_ADD3_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/FUSE_MUL_ADD3_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/H_SWISH_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/H_SWISH_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/H_SWISH_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/H_SWISH_GRAD_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/H_SWISH_GRAD_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/H_SWISH_GRAD_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_bool.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/LEQ_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG1P_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG1P_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG1P_dt_float32.cpp
    src/megdnn/naive/elemwise/kimpl/LOG_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG_SUM_EXP_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG_SUM_EXP_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/LOG_SUM_EXP_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_bool.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/LT_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/MAX_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/MAX_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/MAX_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/MAX_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/MAX_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/MAX_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/MAX_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/MIN_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/MIN_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/MIN_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/MIN_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/MIN_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/MIN_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/MIN_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/MOD_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/MOD_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/MOD_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/MOD_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/MOD_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/MOD_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/MOD_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/MUL_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/MUL_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/MUL_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/MUL_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/MUL_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/MUL_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/MUL_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/NEGATE_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/NEGATE_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/NEGATE_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/NEGATE_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/NEGATE_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/NEGATE_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/NEGATE_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/NOT_dt_bool.cpp 
    src/megdnn/naive/elemwise/kimpl/OR_dt_bool.cpp 
    src/megdnn/naive/elemwise/kimpl/POW_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/POW_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/POW_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/RELU_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/RELU_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/RELU_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/RELU_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/RELU_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/RELU_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/RELU_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/RMULH_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/RMULH_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/RMULH_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/RMULH_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/ROUND_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/ROUND_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/ROUND_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/SHL_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/SHL_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/SHL_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/SHL_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/SHR_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/SHR_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/SHR_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/SHR_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_GRAD_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_GRAD_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_GRAD_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_GRAD_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_GRAD_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_GRAD_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/SIGMOID_GRAD_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/SIN_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/SIN_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/SIN_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/SUB_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/SUB_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/SUB_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/SUB_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/SUB_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/SUB_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/SUB_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/SWITCH_GT0_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/SWITCH_GT0_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/SWITCH_GT0_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/SWITCH_GT0_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/SWITCH_GT0_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/SWITCH_GT0_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/SWITCH_GT0_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_GRAD_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_GRAD_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_GRAD_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_GRAD_dt_int16.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_GRAD_dt_int32.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_GRAD_dt_int8.cpp 
    src/megdnn/naive/elemwise/kimpl/TANH_GRAD_dt_uint8.cpp 
    src/megdnn/naive/elemwise/kimpl/TRUE_DIV_dt_bfloat16.cpp 
    src/megdnn/naive/elemwise/kimpl/TRUE_DIV_dt_float16.cpp 
    src/megdnn/naive/elemwise/kimpl/TRUE_DIV_dt_float32.cpp 
    src/megdnn/naive/elemwise/kimpl/XOR_dt_bool.cpp 
    src/megdnn/naive/elemwise/opr_impl.cpp 
    src/megdnn/naive/elemwise_multi_type/opr_impl.cpp 
    src/megdnn/naive/eye/opr_impl.cpp 
    src/megdnn/naive/flip/opr_impl.cpp 
    src/megdnn/naive/gaussian_blur/opr_impl.cpp 
    src/megdnn/naive/group_local/opr_impl.cpp 
    src/megdnn/naive/handle.cpp 
    src/megdnn/naive/images2neibs/opr_impl.cpp 
    src/megdnn/naive/indexing_multi_axis_vec/opr_impl.cpp 
    src/megdnn/naive/indexing_one_hot/opr_impl.cpp 
    src/megdnn/naive/linspace/opr_impl.cpp 
    src/megdnn/naive/local/local.cpp 
    src/megdnn/naive/local_share/opr_impl.cpp 
    src/megdnn/naive/lowbit_utils.cpp 
    src/megdnn/naive/lrn/opr_impl.cpp 
    src/megdnn/naive/mask_conv/opr_impl.cpp 
    src/megdnn/naive/matrix_inverse/opr_impl.cpp 
    src/megdnn/naive/matrix_mul/opr_impl.cpp 
    src/megdnn/naive/max_tensor_diff/opr_impl.cpp 
    src/megdnn/naive/mesh_indexing/opr_impl.cpp 
    src/megdnn/naive/param_pack/opr_impl.cpp 
    src/megdnn/naive/pooling/opr_impl.cpp 
    src/megdnn/naive/powc/opr_impl.cpp 
    src/megdnn/naive/reduce/opr_impl.cpp 
    src/megdnn/naive/relayout/opr_impl.cpp 
    src/megdnn/naive/relayout_format/opr_impl.cpp 
    src/megdnn/naive/remap/opr_impl.cpp 
    src/megdnn/naive/repeat/repeat.cpp 
    src/megdnn/naive/resize/opr_impl.cpp 
    src/megdnn/naive/resize/resize_cv.cpp 
    src/megdnn/naive/rng/opr_impl.cpp 
    src/megdnn/naive/roi_align/opr_impl.cpp 
    src/megdnn/naive/roi_copy/opr_impl.cpp 
    src/megdnn/naive/roi_pooling/opr_impl.cpp 
    src/megdnn/naive/rotate/opr_impl.cpp 
    src/megdnn/naive/separable_conv/opr_impl.cpp 
    src/megdnn/naive/separable_filter/opr_impl.cpp 
    src/megdnn/naive/sleep/opr_impl.cpp 
    src/megdnn/naive/split/split.cpp 
    src/megdnn/naive/svd/opr_impl.cpp 
    src/megdnn/naive/tensor_remap/opr_impl.cpp 
    src/megdnn/naive/tile/tile.cpp 
    src/megdnn/naive/topk/opr_impl.cpp 
    src/megdnn/naive/transpose/opr_impl.cpp 
    src/megdnn/naive/type_cvt/opr_impl.cpp 
    src/megdnn/naive/warp_affine/opr_impl.cpp 
    src/megdnn/naive/warp_affine/warp_affine_cv.cpp 
    src/megdnn/naive/warp_perspective/opr_impl.cpp 
    src/megdnn/naive/warp_perspective/warp_perspective_cv.cpp 
    src/megdnn/naive/winograd_filter_preprocess/opr_impl.cpp 
    src/megface-bucket/megcommon/affine.cpp
    src/megface-bucket/megcommon/allocator.cpp
    src/megface-bucket/megcommon/assert.cpp
    src/megface-bucket/megcommon/cadence.cpp
    src/megface-bucket/megcommon/common.cpp
    src/megface-bucket/megcommon/comp_node.cpp 
    src/megface-bucket/megcommon/compression.cpp
    src/megface-bucket/megcommon/config_loader.cpp 
    src/megface-bucket/megcommon/context.cpp
    src/megface-bucket/megcommon/device_handler.cpp 
    src/megface-bucket/megcommon/encryption_info.cpp
    src/megface-bucket/megcommon/fastrun.cpp
    src/megface-bucket/megcommon/global_option.cpp
    src/megface-bucket/megcommon/image.cpp 
    src/megface-bucket/megcommon/infile_persistent_cache.cpp 
    src/megface-bucket/megcommon/keypoint_tags.cpp
    src/megface-bucket/megcommon/logging.cpp
    src/megface-bucket/megcommon/model.cpp 
    src/megface-bucket/megcommon/opencl.cpp
    src/megface-bucket/megcommon/release.cpp
    src/megface-bucket/megcommon/stream_impl.cpp
    src/megface-bucket/megcommon/string.cpp
    src/megface-bucket/megcommon/super_log.cpp
    src/megface-bucket/megcommon/tags.cpp 
    src/megface-bucket/megcommon/tensor.cpp
    src/megface-bucket/megcommon/utils.cpp 
    src/megface-bucket/megfinger/context/finger_align_context.cpp 
    src/megface-bucket/megfinger/context/finger_global_context.cpp 
    src/megface-bucket/megfinger/context/finger_live_context.cpp 
    src/megface-bucket/megfinger/context/finger_live_feat_context.cpp 
    src/megface-bucket/megfinger/context/finger_segmentation_context.cpp 
    src/megface-bucket/megfinger/context/mosaicking_context.cpp 
    src/megface-bucket/megfinger/driver/bal_sobel.cpp 
    src/megface-bucket/megfinger/driver/circleM.cpp 
    src/megface-bucket/megfinger/driver/circleM_fast.cpp 
    src/megface-bucket/megfinger/driver/contour_overlap.cpp 
    src/megface-bucket/megfinger/driver/feature_matcher.cpp 
    src/megface-bucket/megfinger/driver/finger_align.cpp 
    src/megface-bucket/megfinger/driver/finger_align_classic_enhance.cpp
    src/megface-bucket/megfinger/driver/finger_classifier_driver.cpp 
    src/megface-bucket/megfinger/driver/finger_global_driver.cpp 
    src/megface-bucket/megfinger/driver/finger_live_driver.cpp 
    src/megface-bucket/megfinger/driver/finger_live_feat_driver.cpp 
    src/megface-bucket/megfinger/driver/finger_local_feature_driver.cpp 
    src/megface-bucket/megfinger/driver/finger_model.cpp
    src/megface-bucket/megfinger/driver/finger_model_factory.cpp  
    src/megface-bucket/megfinger/driver/finger_segmentation_driver.cpp 
    src/megface-bucket/megfinger/driver/finger_struct.cpp 
    src/megface-bucket/megfinger/driver/ghost_classifier_driver.cpp 
    src/megface-bucket/megfinger/driver/lsq.cpp 
    src/megface-bucket/megfinger/driver/mosaicking_common.cpp 
    src/megface-bucket/megfinger/driver/mosaicking_core.cpp 
    src/megface-bucket/megfinger/driver/mosaicking_strategy.cpp 
    src/megface-bucket/megfinger/driver/neon_opr.cpp 
    src/megface-bucket/megfinger/driver/orb.cpp 
    src/megface-bucket/megfinger/driver/param_impl.cpp 
    src/megface-bucket/megfinger/driver/ransac.cpp 
    src/megface-bucket/megfinger/driver/serialize.cpp 
    src/megface-bucket/mgfutils/dl_trace.cpp 
    src/megface-bucket/mgfutils/main.cpp 
    src/megface-bucket/mgfutils/trace.cpp 
    src/megtee_common.cpp
    src/megvii_full_tee.cpp
    src/megvii_tee.cpp 
    src/model_load_impl.cpp
    # src/sys/dlmalloc.c 
    # src/sys/heapoverflow/heapoverflow.cpp 
    # src/sys/memory.cpp 
    # src/sys/sysinit.cpp 
    src/system_api_impl.cpp
    src/sys/memory_new.cpp
    src/sys/libcxxabi/abort_message.cpp
    src/sys/libcxxabi/cxa_guard.cpp
    src/sys/libcxxabi/cxa_virtual.cpp
    src/sys/libcxx/exception.cpp
    src/sys/libcxx/hash.cpp
    src/sys/libcxx/memory.cpp
    src/sys/libcxx/string.cpp
    src/sys/libcxx/utility.cpp
    src/sys/libcxx/vector.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${CXXSOURCES}
)

# add_library(${PROJECT_NAME} SHARED 
#     ${CXXSOURCES}
# )
