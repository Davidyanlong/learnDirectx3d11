cbuffer CBuf
{
    float4 face_colors[6];
};

// If you get following error Error X4583 semantic 'SV_PrimitiveID' unsupported on ps_4_0_level_9_3 Please specify pixelShader properties -> HLSL compiler -> General -> Shader model -> Shader Model 4 (/4_0)
float4 main(uint tid : SV_PrimitiveID) : SV_Target
{
    return face_colors[(tid / 2) % 6];
}