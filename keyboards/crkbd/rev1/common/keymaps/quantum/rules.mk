SPLIT_KEYBOARD = yes
OLED_DRIVER_ENABLE = yes
LOC_OPTIMIZATION = yes
NKRO_ENABLE=yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c
