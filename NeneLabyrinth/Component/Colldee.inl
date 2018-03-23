#include "Colldee.h"
template<class T>
inline Colldee<T>::Colldee(Behavior & _owner, std::type_index _type) :
	IColldee(_owner, _type, &BounsVolume)
{

}
template<class T>
inline Colldee<T>::~Colldee()
{
}

template<class T>
inline void NeneLabyrinth::Component::Colldee<T>::Update()
{
	auto spTransform = Owner.GetComponent<Component::Transform>();
	BounsVolume.Updata(spTransform);
}

template<class T>
inline MeshColldee<T>::MeshColldee(
	Behavior & _owner, std::type_index _type, std::string _path) :
	Colldee(_owner, _type)
{
	auto& service = Service::Instantiate();
	entity = service.CreateEntity<Entity::Mesh>("box.object");
	BounsVolume.FormEntity(*entity);
}
