
cbuffer global
{
	matrix g_mWVP; //���[���h�A�r���[�A�ˉe�̍����ϊ��s��
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