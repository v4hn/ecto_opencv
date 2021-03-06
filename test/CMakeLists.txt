#testing macros
macro(pytest pyfile)
  string(REPLACE ";" " " args "${ARGN}")
  add_test(opencv_${pyfile}
    ${CATKIN_ENV} ${CMAKE_CURRENT_SOURCE_DIR}/${pyfile}.py ${args}
    )
endmacro()

macro(data_download PATH_VAR DATA_FILE)
  set(data_base_url http://vault.willowgarage.com/wgdata1/vol1/ecto_data)
  set(${PATH_VAR} ${PROJECT_BINARY_DIR}/data/${DATA_FILE})
  if(NOT EXISTS ${${PATH_VAR}})
    message(STATUS "Data fetch.\n** Downloading:\n** ${data_base_url}/${DATA_FILE}\n** to:\n** ${${PATH_VAR}}")
    file(DOWNLOAD ${data_base_url}/${DATA_FILE} ${${PATH_VAR}})
  endif()
endmacro()

pytest(test_import)
pytest(doc_opencv)
pytest(test_image_saver)

add_subdirectory(cells)
