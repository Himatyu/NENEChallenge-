
namespace NeneLabyrinth
{
	namespace Component
	{
		class IBehavior
		{
		public:
			virtual ~IBehavior();
			virtual void Update() = 0;

		};
	}
}