
template<class T, class U>
bool ICollider<T, U>::IsAppropriate(IShape* _pShapeL, IShape* _pShapeR)
{
	auto pTL = dynamic_cast<TPointer>(_pShapeL);
	auto pUR = dynamic_cast<UPointer>(_pShapeR);

	if (pTL != nullptr && pUR != nullptr)
	{
		return true;
	}

	auto pTR = dynamic_cast<TPointer>(_pShapeR);
	auto pUL = dynamic_cast<UPointer>(_pShapeL);

	if (pTR != nullptr && pUL != nullptr)
	{
		return true;
	}

	return false;

}
//
//template<class T, class U>
//inline ShpaePair ICollider<T, U>::CastShpaes(IShape * _pShapeL, IShape * _pShapeR)
//{
//	auto pTL = dynamic_cast<TPointer>(_pShapeL);
//	auto pUR = dynamic_cast<UPointer>(_pShapeR);
//
//	if (pTL != nullptr && pUR != nullptr)
//	{
//		return std::make_pair(pTL, pUR);
//	}
//
//	auto pTR = dynamic_cast<TPointer>(_pShapeR);
//	auto pUL = dynamic_cast<UPointer>(_pShapeL);
//
//	if (pTR != nullptr && pUL != nullptr)
//	{
//		return std::make_pair(pTR, pUL);
//	}
//
//	return std::make_pair(nullptr, nullptr);
//
//}

