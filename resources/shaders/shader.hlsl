cbuffer cb : register(b0)
{
    matrix mvp;
};

struct VSInput
{
	float4 pos : POSITION;
    float4 color : COLOR;
	
};
struct FSInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};



FSInput mainVS(VSInput input)
{
    FSInput output;
    output.color = input.color;
    output.pos = mul(mvp, input.pos);
	return output;
}

float4 mainFS(FSInput input) : SV_TARGET
{
    return input.color;

}