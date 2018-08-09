#ifndef exixe_h
#define exixe_h

#include "Arduino.h"

#define EXIXE_SPI_BUF_SIZE (16)
#define EXIXE_SPI_HEADER (0xaa)
#define EXIXE_SPI_HEADER_OD (0xab)
#define EXIXE_ANIMATION_FRAME_DURATION_MS (33)
#define EXIXE_ANIMATION_IN_PROGRESS (1)
#define EXIXE_ANIMATION_FINISHED (0)

class exixe
{
  public:
    enum symbol
    {
        IN_19A_K = 1,     IN_19A_n = 2,       IN_19A_MU = 3,    IN_19A_DEGREE_CELSIUS = 5, IN_19A_PERCENT = 7, IN_19A_M = 8,       IN_19A_P = 9,     IN_19A_m = 0,
        IN_19B_T = 1,     IN_19B_A = 2,       IN_19B_OMEGA = 3, IN_19B_Hz = 5,             IN_19B_S = 7,       IN_19B_F = 8,       IN_19B_H = 9,     IN_19B_V = 0,
        IN_19V_MINUS = 1, IN_19V_GREATER = 2, IN_19V_PLUS = 3,  IN_19V_dB = 5,             IN_19V_PI = 7,      IN_19V_A_DIV_B = 8, IN_19V_TILDE = 9, IN_19V_LESS = 0
    };

    exixe(int my_cs);
    void spi_init();
    void show_digit(unsigned char digit, unsigned char brightness, unsigned char overdrive);
    void show_symbol(symbol symb, unsigned char brightness, unsigned char overdrive);
    void set_led(unsigned char red, unsigned char green, unsigned char blue);
    void set_dots(unsigned char left_brightness, unsigned char right_brightness);
    void crossfade_init(unsigned char digit, unsigned int duration_frames, unsigned char brightness, unsigned char overdrive);
    unsigned char crossfade_run();
    void clear();
  private:
    unsigned char cs_pin;
    unsigned char spi_buf[EXIXE_SPI_BUF_SIZE];
    unsigned char cap_digit(unsigned char digit);
    unsigned char cap_float(float temp);
    void spi_write();

    //------- crossfade animation variables -------
    unsigned char animation_src_digit;
    unsigned char animation_dest_digit;
    unsigned long animation_start_frame;
    unsigned long animation_duration;
    unsigned char animation_brightness;
    unsigned char animation_overdrive;
    float animation_step;
};

#endif

