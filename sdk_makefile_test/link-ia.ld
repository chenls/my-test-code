SECTIONS
{
    .megtee_init_array : {
        *(.megtee_init_array_begin_marker)
        *(SORT(.init_array.*))
        *(.init_array)
        *(.megtee_init_array_end_marker)
    }

    .megtee_fini_array : {
        *(.megtee_fini_array_begin_marker)
        *(SORT(.fini_array.*))
        *(.fini_array)
        *(.megtee_fini_array_end_marker)
    }

    .data : {
        *(.megtee_data_begin_marker)
        *(.data .data.*)
        *(.megtee_data_end_marker)
    }

    .bss : {
        *(.megtee_bss_begin_marker)
        *(.bss .bss.*)
        *(.megtee_bss_end_marker)
    }
}
