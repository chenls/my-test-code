#ifndef __ANC_ERROR_H__
#define __ANC_ERROR_H__

typedef enum {
    ANC_OK = 0,
    ANC_FAIL = 1,
    ANC_FAIL_MEMORY = 2,
    ANC_FAIL_BUFFER_TOO_SMALL = 3,
    ANC_FAIL_OPEN_FILE = 4,
    ANC_FAIL_FSTAT_FILE = 5,
    ANC_FAIL_READ_FILE = 6,
    ANC_FAIL_CLOSE_FILE = 7,
    ANC_FAIL_NO_DIR = 8,
    ANC_FAIL_SPI_OPEN = 9,
    ANC_FAIL_SPI_CLOSE = 10,
    ANC_FAIL_SPI_READ = 11,
    ANC_FAIL_SPI_WRITE = 12,
    ANC_FAIL_SPI_WRITE_READ = 13,
    ANC_FAIL_HMAC_KEY = 14,
    ANC_FAIL_LOAD_TA = 15,
    ANC_FAIL_HW_UNAVALABLE = 16,
    ANC_FAIL_REGISTER_SB = 17,
    ANC_FAIL_PREP_SB_SECURE_READ = 18,
    ANC_FAIL_PREP_SB_NON_SECURE_READ = 19,
    ANC_FAIL_DEREGISTER_SB = 20,
    ANC_FAIL_WAIT_TIME_OUT = 21,
    ANC_FAIL_CANCEL = 22,
    ANC_FAIL_INVALID_COMMAND = 23,
    ANC_FAIL_EFUSE_READ_BYTE = 24,
    ANC_FAIL_EFUSE_WRITE_BYTE = 25,
    ANC_FAIL_NO_CALIBRATION = 26,
    ANC_FAIL_EFUSE_EMPTY = 27,
    ANC_FAIL_EFUSE_INVALID = 28,
    ANC_FAIL_CRC_CHECK = 29,
    ANC_FAIL_INVALID_PARAM = 30,
    ANC_FAIL_TA_TRANSMIT = 31,
    ANC_FAIL_CAP_OCP_TRIGER = 32,
    ANC_FAIL_CAP_OCP_CHECK_ID = 33,
    ANC_FAIL_LOAD_OTP_DATA = 34,
    ANC_FAIL_WAIT_HBM_TIMEOUT = 35,
    ANC_FAIL_TOUCH_BY_MISTAKE = 36,

    ANC_CAPTURE_FRAME_ERROR = 100,
    ANC_CAPTURE_PACKET_ERROR = 101,
    ANC_CAPTURE_FRAME_SIZE_NOT_MATCH = 102,
    ANC_CAPTURE_READ_SIZE_TOO_LARGE = 103,
    ANC_CAPTURE_BUFFER_NOT_ENOUGH = 104,
    ANC_CAPTURE_FINGER_MOVE_TOO_FAST = 105,
    ANC_CAPTURE_ABNORMAL_EXP = 106,
    ANC_CAPTURE_LOW_AUTO_EXP = 107,
    ANC_CAPTURE_LOW_ENV_LIGHT = 108,
    ANC_CAPTURE_HIGH_ENV_LIGHT = 109,
    ANC_CAPTURE_WAIT_IMAGE_TIMEOUT = 110,
    ANC_CAPTURE_IMAGE_CRC_ERROR = 111,
    ANC_CAPTURE_RD_UNDERFLOW = 112,
    ANC_CAPTURE_FINGER_UP = 113,
    ANC_CAPTURE_IMAGE_CHECK_FAIL = 114,

    ANC_ALGO_NO_ERROR = 200,
    ANC_ALGO_INVALID_PARAMETER = 201,
    ANC_ALGO_STATE_ERR = 202,
    ANC_ALGO_ALLOC_MEM_FAIL = 203,
    ANC_ALGO_SDK_TIMEOUT = 204,
    ANC_ALGO_LOAD_MODEL_FAIL = 205,
    ANC_ALGO_PALM = 206,

    ANC_ALGO_EXTRACT_OK = 300,
    ANC_ALGO_BAD_IMG = 301,
    ANC_ALGO_LOW_QTY = 302,
    ANC_ALGO_PARITAL = 303,
    ANC_ALGO_FAKE_FINGER = 304,
    ANC_ALGO_GHOST_FINGER = 305,
    ANC_ALGO_EXTRACT_RETRY_FAST_RET = 306,
    ANC_ALGO_EXTRACT_FAIL = 307,

    ANC_ALGO_ENROLL_FINISH = 400,
    ANC_ALGO_ENROLL_OK_CONTINUE = 401,
    ANC_ALGO_ENROLL_SAME_FINGER = 402,
    ANC_ALGO_ENROLL_DUPLICATE = 403,
    ANC_ALGO_ENROLL_FAIL = 404,
    ANC_ALGO_ENROLL_LOW_QTY = 406,
    ANC_ALGO_ENROLL_GET_TEMPLATE_FAIL = 407,
    ANC_ENROLL_TIME_OUT = 408,
    ANC_ENROLL_FAIL = 409,

    // 比对流程返回值
    ANC_ALGO_MATCH_OK = 500,
    ANC_ALGO_MATCH_FAIL = 501,
    ANC_ALGO_MATCH_FAIL_STOP_RETRY = 502,
    // 比对算法返回值
    ANC_ALGO_MATCH_ALGO_PASS = 550,
    ANC_ALGO_MATCH_ALGO_FAIL = 551,
    ANC_ALGO_MATCH_ALGO_PASS_AND_LIVE_FAILED = 552,
    ANC_ALGO_MATCH_ALGO_FAIL_AND_LIVE_FAILED = 553,
    ANC_ALGO_MATCH_ALGO_PASS_AND_GHOST_FAILED = 554,
    ANC_ALGO_MATCH_ALGO_FAIL_AND_GHOST_FAILED = 555,
    ANC_ALGO_MATCH_ALGO_FAIL_PARTIAL = 556,
    ANC_ALGO_MATCH_ALGO_FAIL_STRANGE = 557,
    ANC_ALGO_MATCH_ALGO_FAIL_LOW_EXPO = 558,
    ANC_ALGO_MATCH_ALGO_FAIL_HIGH_EXPO = 559,
    ANC_ALGO_MATCH_ALGO_FAIL_PATTERN = 560,

    ANC_DB_FINGER_ID_INVALID = 600,
    ANC_DB_CACHE_INCOMPLETE = 601,
    ANC_DB_FILE_INCOMPLETE = 602,
    ANC_DB_CRC32_DISMATCH = 603,
    ANC_DB_ENROLL_ALREADY_FULL = 604,

    ANC_FT_ALGO_VERSION_DISMATCH = 700,
    ANC_FT_TRANSMIT_IMAGE_FAIL = 701,
    ANC_FT_SAVE_IMAGE_FAIL = 702,
    ANC_FT_LENS_HIGH_FREQ_SINAL_TEST_FAIL = 703,
    ANC_FT_LENS_CENTER_OFFSET_TEST_FAIL = 704,
    ANC_FT_LENS_CORNER_SHADING_TEST_FAIL = 705,
    ANC_FT_LENS_FOR_AREA_TEST_FAIL = 706,
    ANC_FT_DEFECT_TEST_FAIL = 707,
    ANC_FT_INSTALL_OFFSET_TEST_FAIL = 708,
    ANC_FT_PREVENT_CHECK_FAIL = 709,
    ANC_FT_SCREEN_SIGNAL_CHECK_FAIL = 710,
    ANC_FT_SCREEN_LEAK_RATIO_CHECK_FAIL = 711,
    ANC_FT_BLACK_EXP_TIME_TEST_FAIL = 712,
    ANC_FT_SIGNAL_NOISE_TEST_FAIL = 713,
    ANC_FT_REQ_MFACTOR_TEST_FAIL = 714,
    ANC_FT_MODULE_TEST_FAIL = 715,
    ANC_FT_CALIBRATION_TEST_FAIL = 716,
    ANC_FT_SAVE_CALIBRATION_DATA_FAIL = 717,
    ANC_FT_INSTALL_ANGLE_TEST_FAIL = 718,
    ANC_FT_CHART_ANGLE_CHECK_FAIL = 719,
    ANC_FT_CHART_POSITION_CHECK_FAIL = 720,
    ANC_FT_SW_HW_VERSION_MATCH_FAIL = 721,
    ANC_FT_READ_CHIP_VERSION_FAIL = 722,
    ANC_FT_EXPO_CALIBRATION_FAIL = 723,
    ANC_FT_DETECT_DISTORTION_FAIL = 724,
    ANC_FT_INSTALL_TILT_TEST_FAIL = 725,
    ANC_FT_LENS_ID_TEST_FAIL = 726,

    ANC_ALGO_TEMPLATE_LOAD_FAIL = 800,
    ANC_ALGO_TEMPLATE_SAVE_IMAGE_FAIL = 801,
    ANC_ALGO_TEMPLATE_SAVE_FEATURE_FAIL = 802,
    ANC_ALGO_TEMPLATE_ENROLL_FULL = 803,
    ANC_ALGO_TEMPLATE_STATE_ERR = 804,
    ANC_ALGO_TEMPLATE_UPGRADE_FAIL = 805,

    ANC_HB_FAIL = 2000,
    ANC_HB_BAD_QUALITY = 2001,

    ANC_MAX
} ANC_RETURN_TYPE;

#endif