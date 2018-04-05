#include "CollisionProvider.h"

namespace NeneLabyrinth
{
	namespace Collision
	{
		void CollisionProvider::Dispatch()
		{
			for (auto& record : records)
			{
				record.swap(
					std::make_tuple(
						std::get<0>(record),
						std::get<1>(record), std::get<2>(record), false, D3DXVECTOR3(0, 0, 0)));
			}

			Component::IColldee* pColldee;
			Component::IColldee* pOpp;
			auto& find =
				[&pColldee, &pOpp](RegisterRecord& _record)
			{
				auto pColldeeR = std::get<0>(_record);
				auto pColldeeL = std::get<1>(_record);

				if (pColldee == pColldeeR && pOpp == pColldeeL)
				{
					return true;
				}

				if (pOpp == pColldeeR && pColldee == pColldeeL)
				{
					return true;
				}
				return false;

			};

			std::vector<RegisterRecord> uniquePiar;

			for (auto& colldee : receivers)
			{
				for (auto& opp : receivers)
				{
					pColldee = colldee;
					pOpp = opp;
					if (pColldee == pOpp)
					{
						continue;
					}

					auto result = Utility::Estd::find_if(uniquePiar, find);
					if (result != uniquePiar.end())
					{
						continue;
					}
					uniquePiar.push_back(
						std::make_tuple(
							colldee, opp, State::Enter, true, D3DXVECTOR3(0, 0, 0)));
				}
			}

			//ÉiÉçÅ[ñ≥éã
			for (auto& piar : uniquePiar)
			{
				pColldee = std::get<0>(piar);
				pOpp = std::get<1>(piar);

				auto isAppropriate = collider.IsAppropriate(pColldee->pShape, pOpp->pShape);

				if (!isAppropriate)
				{
					continue;
				}

				auto isCollision = collider.Execution(pColldee->pShape, pOpp->pShape);

				if (isCollision == D3DXVECTOR3(0, 0, 0))
				{
					continue;
				}

				auto result = Utility::Estd::find_if(records, find);

				if (result == records.end())
				{
					records.push_back(
						std::make_tuple(
							pColldee, pOpp, State::Enter, true, isCollision));
				}
				else
				{
					result->swap(
						std::make_tuple(
							pColldee, pOpp, State::Stay, true, isCollision));
				}

			}

			std::vector<RegisterRecord> removes;
			for (auto& record : records)
			{
				auto pColldeL = std::get<0>(record);
				auto pColldeR = std::get<1>(record);

				bool isRigidbodyL = pColldeL->IsRigidbody();
				bool isRigidbodyR = pColldeR->IsRigidbody();

				if (isRigidbodyL == isRigidbodyR)
				{
					if (!isRigidbodyR)
					{
						if (!std::get<3>(record))
						{
							pColldeL->OnTriggerExit(&pColldeR->Owner);
							pColldeR->OnTriggerExit(&pColldeL->Owner);
							removes.push_back(record);
							continue;
						}
						if (std::get<2>(record) == State::Enter)
						{
							pColldeL->OnTriggerEnter(&pColldeR->Owner);
							pColldeR->OnTriggerEnter(&pColldeL->Owner);
							continue;
						}
						if (std::get<2>(record) == State::Stay)
						{
							pColldeL->OnTriggerStay(&pColldeR->Owner);
							pColldeR->OnTriggerStay(&pColldeL->Owner);
							continue;
						}
						continue;
					}

					if (!std::get<3>(record))
					{
						pColldeL->OnCollisionExit(&pColldeR->Owner);
						pColldeR->OnCollisionExit(&pColldeL->Owner);
						removes.push_back(record);
						continue;
					}
					if (std::get<2>(record) == State::Enter)
					{
						pColldeL->OnCollisionEnter(&pColldeR->Owner);
						pColldeR->OnCollisionEnter(&pColldeL->Owner);
					}
					if (std::get<2>(record) == State::Stay)
					{
						pColldeL->OnCollisionStay(&pColldeR->Owner);
						pColldeR->OnCollisionStay(&pColldeL->Owner);
					}

					auto exForce = std::get<4>(record);
					pColldeL->Body->AddForceImpulse(-exForce*pColldeL->Body->Bound);
					pColldeR->Body->AddForceImpulse(exForce*pColldeR->Body->Bound);
					auto txt = std::to_string(exForce.x) + " : " + std::to_string(exForce.y) + " : " + std::to_string(exForce.z);
					___D_LOG(txt);
				}
			}

			for (auto& removeRecoord : removes)
			{
				pColldee = std::get<0>(removeRecoord);
				pOpp = std::get<1>(removeRecoord);
				Utility::Estd::RemoveOfAssociativeArray(records, find);
			}

		}

	}
}
