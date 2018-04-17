add_library (readwrite
    log.cpp
    readwrite.cpp
)

install (TARGETS readwrite DESTINATION /lib)
install (FILES "${PROJECT_SOURCE_DIR}/src/readwrite.h" DESTINATION /include)