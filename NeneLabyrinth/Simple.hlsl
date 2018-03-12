
cbuffer global
{
	matrix g_mWVP; //ワールド、ビュー、射影の合成変換行列
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
};

float4 VS(float4 Pos : POSITION ,float4 Normal : NORMAL) : SV_POSITION
{
	VS_OUTPUT vo;
	vo.Pos = mul(Pos,g_mWVP);
	return vo.Pos;
}

float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
	float4 color = float4(1,0,0,0);
	return color;
}