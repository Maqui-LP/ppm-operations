#ifndef __PPM_OPERATIONS_H
#define __PPM_OPERATIONS_H

t_ppm ppm_operation_rotate90(t_ppm );
t_ppm ppm_operation_flip_horizontal(t_ppm );
t_ppm ppm_operation_flip_vertical(t_ppm );
t_ppm ppm_operation_negative(t_ppm );
t_ppm ppm_operation_blur(t_ppm , unsigned char);
t_ppm ppm_operation_sepia(t_ppm);
t_ppm ppm_operation_grayscale(t_ppm);
t_ppm ppm_operation_black_and_white(t_ppm);

#endif

