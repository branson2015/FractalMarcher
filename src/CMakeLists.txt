FILE (GLOB SOURCES *.cpp)

target_sources(FractalMarcher PUBLIC ${SOURCES})




if (OPENGL_FOUND)
  add_library(vkl_opengl INTERFACE)
  target_compile_definitions(vkl_opengl INTERFACE GL_SILENCE_DEPRECATION)
  if (TARGET OpenGL::GL)
    target_link_libraries(vkl_opengl INTERFACE OpenGL::GL)
  else ()
    # Old versions of cmake do not create the GL targets.
    target_link_libraries(vkl_opengl INTERFACE ${OPENGL_LIBRARIES})
    target_include_directories(vkl_opengl INTERFACE ${OPENGL_INCLUDE_DIR})
  endif ()

  # set(OPENVKL_IMGUI_ROOT "${CMAKE_CURRENT_LIST_DIR}/imgui-1.83"
  #   CACHE PATH "Path to imgui.")
  # 
  # add_library(imgui STATIC
  #   ${OPENVKL_IMGUI_ROOT}/imgui.cpp
  #   ${OPENVKL_IMGUI_ROOT}/imgui_draw.cpp
  #   ${OPENVKL_IMGUI_ROOT}/imgui_tables.cpp
  #   ${OPENVKL_IMGUI_ROOT}/imgui_widgets.cpp
  #   ${OPENVKL_IMGUI_ROOT}/backends/imgui_impl_glfw.cpp
  #   ${OPENVKL_IMGUI_ROOT}/backends/imgui_impl_opengl2.cpp)
  # 
  # target_include_directories(imgui PUBLIC ${OPENVKL_IMGUI_ROOT})
  # target_link_libraries(imgui PUBLIC glfw vkl_opengl)
  # target_compile_definitions(imgui PUBLIC VKL_HAVE_IMGUI)
endif()

if (TARGET imgui)
  add_executable(vklExamples
    vklExamples.cpp
    BatchApplication.cpp
    InteractiveApplication.cpp
    ParameterGui.cpp
    RenderView.cpp
    TransferFunctionWidget.cpp
    ${VKL_RESOURCE}
  )

  target_link_libraries(vklExamples
    PRIVATE
      imgui
      vkl_example_renderers
  )

  install(TARGETS vklExamples
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif()