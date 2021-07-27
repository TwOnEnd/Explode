#include "Block.hpp"

#define FETCH(type, ptr) (*reinterpret_cast<type*>(ptr))

struct Vec3
{
	float x;
	float y;
	float z;
};

struct Actor 
{
	//获取生物名称信息
	const std::string* getNameTag() const
	{
		return SYMCALL(std::string*, MSSYM_MD5_7044ab83168b0fd345329e6566fd47fd, this);
	}
	//获取生物当前所处维度ID
	int getDimensionId()
	{//IDA Actor::getDimensionId
		/*int did;
		SYMCALL(int, MSSYM_B1QE14getDimensionIdB1AE11BlockSourceB2AAA4QEBAB1QA2AVB2QDE11AutomaticIDB1AE10VDimensionB2AAA1HB2AAA2XZ, this, &did);
		return did;*/
		return FETCH(int, this + 236);
	}
	//获取生物当前所在坐标
	Vec3* getPos()
	{//IDA Actor::getPos
		return (Vec3*)(this + 1268);
	}
};

struct Mob : Actor {};
