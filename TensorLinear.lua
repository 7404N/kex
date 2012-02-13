local TensorLinear,parent = torch.class('nn.TensorLinear','nn.Module')

function TensorLinear:__init(in1,in2,out)
    parent.__init(self)
    self.weight = torch.Tensor(out,in1,in2)
    self.gradWeight = torch.Tensor(out,in1,in2)
    self.bias = torch.Tensor(out)
    self.gradBias = torch.Tensor(out)

    self.gradInput = {torch.Tensor(), torch.Tensor()}
    self:reset()
end

function TensorLinear:reset( stdv )
    if stdv then
        stdv = stdv * math.sqrt(3)
    else
        stdv = 1./math.sqrt(self.weight:size(2)+self.weight:size(3))
    end

    -- we do this so the initialization is exactly
    -- the same than in previous torch versions
    for i=1,self.weight:size(1) do
        self.weight:select(1, i):apply(function()
                                        return torch.uniform(-stdv, stdv)
                                        end)
        self.bias[i] = torch.uniform(-stdv, stdv)
    end
end

function TensorLinear:updateOutput( input )
    local in1,in2 = input[1],input[2]
    local iout = torch.ger(in1,in2)
    local i1 = torch.Tensor(iout):resize(in1:size(1)*in2:size(1))
    local w2 = torch.Tensor(self.weight):resize(self.weight:size(1),in1:size(1)*in2:size(1))
    self.output:resize(self.weight:size(1))
    torch.mv(self.output,w2,i1)
    self.output:add(self.bias)
    return self.output
end

function TensorLinear:updateGradInput(input, gradOutput)
    local in1,in2 = input[1],input[2]
    local w2 = torch.Tensor(self.weight):resize(self.weight:size(1),in1:size(1)*in2:size(1))
    local gin = torch.mv(w2:t(),gradOutput)
    gin:resize(in1:size(1),in2:size(1))

    gin1 = self.gradInput[1]
    gin2 = self.gradInput[2]
    gin1:resizeAs(in1)
    gin2:resizeAs(in2)
    torch.mv(gin1,gin,in2)
    torch.mv(gin2,gin:t(),in1)
    return self.gradInput
end

function TensorLinear:accGradParameters( input, gradOutput, scale)
    scale = scale or 1
    local in1,in2 = input[1],input[2]
    local iout = torch.ger(in1,in2)
    local i1 = torch.Tensor(iout):resize(in1:size(1)*in2:size(1))
    local gw2 = torch.Tensor(self.gradWeight):resize(self.gradWeight:size(1),in1:size(1)*in2:size(1))
    local w2 = torch.Tensor(self.weight):resize(self.weight:size(1),in1:size(1)*in2:size(1))
    torch.addr(gw2,1,gw2,scale,gradOutput,i1)
    self.gradBias:add(scale, gradOutput)
end
