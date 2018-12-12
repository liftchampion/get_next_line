cmake_minimum_required(VERSION 3.12)
project(getNextLine C)

set(CMAKE_C_STANDARD 11)

FILE(GLOB LIBFT ./libft/*.c)

FILE(GLOB LIBFT_MAP ./libft/ft_map/*.c)

FILE(GLOB LIBFT_STRING ./libft/ft_string/*.c)

FILE(GLOB HEADERS ./libft/includes/*.h)

include_directories(./libft/includes)

add_executable(getNextLine
        get_next_line.c main.c ${LIBFT} ${LIBFT_MAP} ${LIBFT_STRING} ${HEADERS})
