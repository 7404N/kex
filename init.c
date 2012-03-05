#include "TH.h"
#include "luaT.h"

#define torch_(NAME) TH_CONCAT_3(torch_, Real, NAME)
#define torch_string_(NAME) TH_CONCAT_STRING_3(torch., Real, NAME)
#define nn_(NAME) TH_CONCAT_3(nn_, Real, NAME)
#define kex_(NAME) TH_CONCAT_3(kex_, Real, NAME)
#define THOmpTensor_(NAME)   TH_CONCAT_4(THOmp,Real,Tensor_,NAME)

static const void* torch_FloatTensor_id = NULL;
static const void* torch_DoubleTensor_id = NULL;
static const void* torch_LongTensor_id = NULL;

#include "generic/SpatialFullConvolution.c"
#include "THGenerateFloatTypes.h"

#include "generic/SpatialFullConvolutionMap.c"
#include "THGenerateFloatTypes.h"

#include "generic/L1Cost.c"
#include "THGenerateFloatTypes.h"

#include "generic/SpatialMaxPooling2.c"
#include "THGenerateFloatTypes.h"

#include "generic/util.c"
#include "THGenerateFloatTypes.h"

#include "generic/SqrtBias.c"
#include "THGenerateFloatTypes.h"

DLL_EXPORT int luaopen_libkex(lua_State *L)
{
  torch_FloatTensor_id = luaT_checktypename2id(L, "torch.FloatTensor");
  torch_DoubleTensor_id = luaT_checktypename2id(L, "torch.DoubleTensor");
  torch_LongTensor_id = luaT_checktypename2id(L, "torch.LongTensor");

  lua_newtable(L);
  lua_pushvalue(L, -1);
  lua_setfield(L, LUA_GLOBALSINDEX, "kex");

  kex_Floatutil_init(L);
  kex_Doubleutil_init(L);

  nn_FloatSpatialFullConvolution_init(L);
  nn_DoubleSpatialFullConvolution_init(L);

  nn_FloatSpatialFullConvolutionMap_init(L);
  nn_DoubleSpatialFullConvolutionMap_init(L);

  nn_FloatL1Cost_init(L);
  nn_DoubleL1Cost_init(L);

  nn_FloatSpatialMaxPooling2_init(L);
  nn_DoubleSpatialMaxPooling2_init(L);

  nn_FloatSqrtBias_init(L);
  nn_DoubleSqrtBias_init(L);

  return 1;
}


