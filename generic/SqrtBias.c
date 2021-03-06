#ifndef TH_GENERIC_FILE
#define TH_GENERIC_FILE "generic/SqrtBias.c"
#else

static int nn_(SqrtBias_updateOutput)(lua_State *L)
{
  THTensor *input = luaT_checkudata(L, 2, torch_Tensor);
  real bias = luaT_getfieldchecknumber(L,1,"bias");
  THTensor *output = luaT_getfieldcheckudata(L, 1, "output", torch_Tensor);

  THTensor_(resizeAs)(output, input);

  TH_TENSOR_APPLY2(real, output, real, input,			\
		   *output_data = sqrt(*input_data + bias););
  
  return 1;
}

static int nn_(SqrtBias_updateGradInput)(lua_State *L)
{
  THTensor *input = luaT_checkudata(L, 2, torch_Tensor);
  THTensor *gradOutput = luaT_checkudata(L, 3, torch_Tensor);
  THTensor *output = luaT_getfieldcheckudata(L, 1, "output", torch_Tensor);
  THTensor *gradInput = luaT_getfieldcheckudata(L, 1, "gradInput", torch_Tensor);

  THTensor_(resizeAs)(gradInput, input);

  TH_TENSOR_APPLY3(real, gradInput, real, gradOutput, real, output,	\
		   *gradInput_data  = 0.5 * (*gradOutput_data / *output_data););
  
  return 1;
}

static const struct luaL_Reg nn_(SqrtBias__) [] = {
  {"SqrtBias_updateOutput", nn_(SqrtBias_updateOutput)},
  {"SqrtBias_updateGradInput", nn_(SqrtBias_updateGradInput)},
  {NULL, NULL}
};

static void nn_(SqrtBias_init)(lua_State *L)
{
  luaT_pushmetatable(L, torch_Tensor);
  luaT_registeratname(L, nn_(SqrtBias__), "nn");
  lua_pop(L,1);
}

#endif
