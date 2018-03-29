
template<class Type, class ...Param>
inline std::shared_ptr<Type>
Object::AddComponent(Param && ..._param)
{
	//コンポーネントは第一引数にOwnerを必ず持つ
	auto spCom =
		std::make_shared<Type>(*this, std::forward<Param>(_param)...);

	components.push_back(spCom);

	return spCom;
}

template<class Type>
inline void Object::RemoveComponents()
{
	if (!components.size())
	{
		return;
	}

	auto removes = GetComponents<Type>();
	std::copy(removes.begin(), removes.end(), std::back_inserter(deletableComponents));
}

template<class Type>
inline std::shared_ptr<Type>
Object::GetComponent()
{
	if (!components.size())
	{
		return std::shared_ptr<Type>();
	}

	for (auto& _ : components)
	{
		if (_->IsSame<Type>())
		{
			return std::dynamic_pointer_cast<Type>(_);
		}
	}
	return std::shared_ptr<Type>();
}


template<class Type>
inline
std::shared_ptr<Type>
Object::GetComponentFromName
(std::string _name)
{
	auto searched = GetComponents<Type>();

	if (!searched.size())
	{
		return std::shared_ptr<Type>();
	}

	auto result =
		Utility::Estd::find_if(
			searched,
			[_name](std::shared_ptr<Type>& _spCom)
	{
		return _spCom->Name == _name;
	});

	if (std::end(searched) == result)
	{
		return std::shared_ptr<Type>();
	}

	return *result;
}

template<class Type>
inline std::vector<std::shared_ptr<Type>>
Object::GetComponents()
{
	if (!components.size())
	{
		return std::vector<std::shared_ptr<Type>>();
	}

	std::vector<std::shared_ptr<Type>> result;
	for (auto& _ : components)
	{
		if (_->IsSame<Type>())
		{
			result.push_back(std::dynamic_pointer_cast<Type>(_));
		}
	}
	return std::vector<std::shared_ptr<Type>>(result);
}


template<class Type>
inline bool Object::HasComponent()
{
	if (!components.size())
	{
		return false;
	}

	for (auto& _ : components)
	{
		if (_->IsSame<Type>())
		{
			return true;
		}
	}
	return false;
}


