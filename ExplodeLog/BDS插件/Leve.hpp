
#define FETCH(type, ptr) (*reinterpret_cast<type*>(ptr))

struct Level 
{
  std::vector<Actor*> getAllPlayers()
  {
		return FETCH(std::vector<Actor*>, this + 112);//IDA Level::forEachPlayer
	}
};
