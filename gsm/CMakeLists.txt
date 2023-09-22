add_library(gsm INTERFACE)

target_sources(gsm
    INTERFACE
      ${CMAKE_CURRENT_LIST_DIR}/gsm.c
      )
target_link_libraries(gsm # link the libraries to the executable
	INTERFACE
    	hardware_uart
        hardware_gpio
    	pico_stdlib
    )
