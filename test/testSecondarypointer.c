#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    uint32_t image_size;
    uint32_t width;
    uint32_t height;
    int32_t exposure_time;
    uint32_t exposure_reg_val;
    uint32_t image_serial_number;
    uint32_t env_light_value;
    uint8_t *p_image_data;
} __attribute__((packed)) AncExtensionImage;

int main(int argc, char const *argv[])
{
    uint8_t *p_share_buffer = malloc(800 * 1024);
    AncExtensionImage *p_image = (AncExtensionImage *)p_share_buffer;
    p_image->image_size = 51200;
    uint8_t *p_image_data = p_share_buffer + offsetof(AncExtensionImage, p_image_data);
    
    uint8_t *temp = malloc(51200);
    for (int i = 0; i < 51200; i++)
    {
        temp[i] = i % 100;
    }
    memcpy(p_image_data, temp, 51200);
    free(temp);
    p_image->p_image_data = p_image_data;
    printf("p_image->image_size %p\n", &p_image->image_size);
    printf("p_share_buffer %p\n", p_share_buffer);
    printf("p_image->image_size int %d\n", (uint32_t)p_image->image_size);
    printf("p_share_buffer int %d\n", *(uint32_t *)p_share_buffer);

    printf("p_image %p\n", p_image);

    printf("p_share_buffer 2 %p\n", p_share_buffer + offsetof(AncExtensionImage, p_image_data));

    printf("p_image 2 %p\n", (void *)p_image + offsetof(AncExtensionImage, p_image_data));

    printf("p_image 3 %p\n", (void *)p_image + 28);
    printf("%p %p\n", p_image_data, p_image);
    printf("%p %p\n", p_image_data, &p_image->width);
    printf("%p %p\n", p_image_data, p_image->p_image_data);
    printf("%p %p\n", p_image_data, &p_image->p_image_data);

    printf("%d\n", p_image_data[13]);
    printf("%d\n", p_image->p_image_data[13]);
    p_image->p_image_data = (uint8_t *)&p_image->p_image_data;
    printf("%d\n", p_image->p_image_data[13]);

    return 0;
}
