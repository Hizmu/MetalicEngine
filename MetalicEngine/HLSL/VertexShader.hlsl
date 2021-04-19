/*
cbuffer VS_CONSTANT_BUFFER : register(b0) {
    matrix projectionMat;
    matrix viewMat;
    matrix worldMat;
};*/

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
  //  float2 tex : TEXCOORD0;
};

VOut VShader(float4 position : SV_POSITION, float4 color : COLOR)
{
    VOut output;
    position.w = 1.0f;
//   output.position = mul(position, worldMat);
 //  output.position = mul(output.position, viewMat);
 //  output.position = mul(output.position, projectionMat);

   // output.position = mul(worldMat, position);
  //  output.position = mul(viewMat,output.position);
  //  output.position = mul(projectionMat, output.position);

    output.position = position;
    output.color = color;

    return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}