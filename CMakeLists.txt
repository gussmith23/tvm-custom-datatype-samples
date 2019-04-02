cmake_minimum_required(VERSION 3.0)
project(TVMCustomDatatypeSamples)

# TODO(gus) we need to specify the working directory here, as these scripts
# contain relative paths.

add_test(
  NAME bfloat
  COMMAND python mybfloat16.py
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

add_test(
  NAME posit
  COMMAND python universal-posit.py
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

enable_testing()
