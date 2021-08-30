SECTIONS
{
    .data : {
        *(.data*)

        /* generated in link-ia.ld */
        *(.megtee_init_array)
        *(.megtee_fini_array)
    }

    .rodata : {
        *(.rodata*)
    }
}
