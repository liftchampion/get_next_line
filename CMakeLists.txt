cmake_minimum_required(VERSION 3.12)
project(getNextLine C)

set(CMAKE_C_STANDARD 11)

FILE(GLOB LIBFT ./libft/*.c)

FILE(GLOB LIBFT_MAP ./libft/ft_map/*.c)

add_executable(getNextLine
        get_next_line.c main.c ${LIBFT} ${LIBFT_MAP})
