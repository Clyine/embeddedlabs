cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(LabManual)
set(PICO_BOARD pico_w)

pico_sdk_init()

add_executable(lab2_student lab2_student.c)
pico_add_extra_outputs(lab2_student)

pico_enable_stdio_usb(lab2_student 1)
pico_enable_stdio_uart(lab2_student 1)


target_link_libraries(lab2_student
	pico_stdlib
	pico_cyw43_arch_none
	)
