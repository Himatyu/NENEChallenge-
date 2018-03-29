#pragma once
#include<algorithm>
#include<functional>
#include<numeric>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace NeneLabyrinth
{
	namespace Utility
	{
		namespace Estd
		{

			/// <summary>
			/// コンテナ指定のfind
			/// </summary>
			template<typename Container, class Ty>
			inline
				auto find(Container& _cont, const Ty& _Val)
			{
				return std::find(_cont.begin(), _cont.end(), _Val);
			}

			/// <summary>
			/// コンテナ指定のfind_if
			/// </summary>
			template<typename Container, class Pred>
			inline
				auto find_if(Container& _cont, Pred _pred)
			{
				return std::find_if(_cont.begin(), _cont.end(), _pred);
			}

			/// <summary>
			/// コンテナと条件を指定して射影する
			/// </summary>
			template<typename Container, class Pred>
			inline
				auto find_all(const Container& _cont, Pred _pred)
			{
				Container result;
				for (auto& _ : _cont)
				{
					if (!_pred(_))
					{
						continue;
					}
					result.push_back(_);
				}
				return std::move(result);
			}

			/// <summary>
			/// コンテナ指定のsort
			/// </summary>
			template<class Container>
			inline
				void sort(Container& _cont)
			{
				std::sort(_cont.begin(), _cont.end());
			}

			/// <summary>
			/// コンテナ指定の条件指定sort
			/// </summary>
			template<class Container, class Pred>
			inline
				void sort(Container& _cont, Pred _pred)
			{
				std::sort(_cont.begin(), _cont.end(), _pred);
			}

			/// <summary>
			/// コンテナ指定の条件指定remove_if
			/// </summary>
			template<class Container, class Pred>
			inline
				void remove_if(Container& _cont, Pred _pred)
			{
				std::remove_if(_cont.begin(), _cont.end(), _pred);
			}

			/// <summary>
			/// コンテナ指定のtransform
			/// </summary>
			template<class Container, class ResultIt, class Pred>
			inline
				void transform(Container& _cont, ResultIt _result, Pred _pred)
			{
				std::transform(_cont.begin(), _cont.end(), _result, _pred);
			}

			/// <summary>
			/// コンテナ指定のtransform
			/// </summary>
			template<class Container, class Counter, class ResultIt, class Pred>
			inline
				void transform(Container& _cont, Counter _counter, ResultIt _result, Pred _pred)
			{
				std::transform(_cont.begin(), _cont.end(), _counter, _result, _pred);
			}

			/// <summary>
			/// コンテナ指定のany_of
			/// </summary>
			template<class Container, class Pred>
			inline
				bool any_of(Container& _cont, Pred _pred)
			{
				return std::any_of(_cont.begin(), _cont.end(), _pred);
			}

			/// <summary>
			/// コンテナ指定のfor_each
			/// </summary>
			template<class Container, class Pred>
			inline
				Pred for_each(Container& _cont, Pred _pred)
			{
				return std::for_each(_cont.begin(), _cont.end(), _pred);
			}

			/// <summary>
			/// コンテナ指定のreverse
			/// </summary>
			template<typename Container>
			inline
				void reverse(Container& _cont)
			{
				std::reverse(_cont.begin(), _cont.end());
			}

			/// <summary>
			/// コンテナ指定のaccumulate
			/// </summary>
			template<typename Container, typename T>
			inline
				T accumulate(Container& _cont, T _init)
			{
				return std::accumulate(_cont.begin(), _cont.end(), _init);
			}

			/// <summary>
			/// リストを追加する
			/// </summary>
			template<typename Container>
			inline
				void combineList(Container& _source, Container _target)
			{
				_source.splice(_source.begin(), std::move(_target));
			}

			/// <summary>
			/// コンテナ指定のcopy
			/// </summary>
			template<class Container>
			inline
				void copy(Container& _source, Container& _target)
			{
				std::copy(
					_target.begin(),
					_target.end(),
					std::back_inserter(_source));
			}

			/// <summary>
			/// 要素をremove
			/// </summary>
			template<class Container, class Pred>
			inline
				void RemoveOfAssociativeArray(Container& _cont, Pred _pred)
			{
				for (auto it = _cont.begin(); it != _cont.end();)
				{
					if (_pred(*it))
					{
						it = _cont.erase(it);
					}
					else
					{
						++it;
					}
				}
			}

			std::vector<std::string> Split(const std::string& _input, char _delimiter);
		}
	}
}