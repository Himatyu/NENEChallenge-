
cbuffer global
{
	matrix g_mWVP; //���[���h�A�r���[�A�ˉe�̍����ϊ��s��
};

float4 VS(float4 Pos : POSITION) : SV_POSITION
{
	Pos = mul(Pos,g_mWVP);
	return Pos;
}

float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
	float4 color = float4(1,0,0,0);
	return color;
}