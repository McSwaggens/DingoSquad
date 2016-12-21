#pragma once
class CResolver
{
public:
	void Resolver(ClientFrameStage_t curStage);
private:
	void Lispfix(Vector* &Angle, CPlayer* Player);
	void XResolver(Vector* &Angle, CPlayer* Player);
	void YResolver(Vector* &Angle, CPlayer* Player);
	void TargetsResolver();
	void Reset();
	void AutoResolver(Vector* &Angle, CPlayer* Player);
	void AAID(Vector* &Angle, CPlayer* Player);

};

extern CResolver Resolver;