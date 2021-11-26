
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(task3 Validator.cpp Translator.cpp MathExpression.cpp TextParser.cpp main.cpp)