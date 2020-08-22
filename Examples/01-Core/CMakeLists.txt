PROJECT(Example01)

ADD_EXECUTABLE(Example01
    "Sandbox.cpp"
)

TARGET_LINK_LIBRARIES(Example01 PUBLIC void dl)
