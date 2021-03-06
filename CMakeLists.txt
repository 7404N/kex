CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
CMAKE_POLICY(VERSION 2.6)
FIND_PACKAGE(Torch REQUIRED)

SET(src init.c)

SET(luasrc init.lua 
  lushio.lua
  CriterionModule.lua
  SpatialFullConvolution.lua 
  SpatialFullConvolutionMap.lua 
  WeightedMSECriterion.lua
  L1Cost.lua
  Diag.lua
  SpatialMaxPyramid.lua
  SpatialMaxPooling2.lua
  Vectorize.lua
  TanhShrink.lua
  Crop.lua
  SqrtBias.lua
  stochasticrates.lua
  TensorLinear.lua
  DivisiveNormalization.lua
  cudahacks.lua
  test/test.lua
  test/test_module.lua
  hessian.lua
  )

IF (WITH_OPENMP)
  FIND_PACKAGE(OpenMP)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
ENDIF(WITH_OPENMP)

INCLUDE_DIRECTORIES(${Torch_SOURCE_INCLUDES})
ADD_TORCH_PACKAGE(kex "${src}"  "${luasrc}" "Extra Tools")
ADD_TORCH_DOK(dok kex "3rd Party" "Extensions from Koray" 111111.)

TARGET_LINK_LIBRARIES(kex luaT TH)
