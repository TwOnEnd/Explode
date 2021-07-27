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
	//��ȡ����������Ϣ
	const std::string* getNameTag() const
	{
		return SYMCALL(std::string*, MSSYM_MD5_7044ab83168b0fd345329e6566fd47fd, this);
	}
	//��ȡ���ﵱǰ����ά��ID
	int getDimensionId()
	{//IDA Actor::getDimensionId
		/*int did;
		SYMCALL(int, MSSYM_B1QE14getDimensionIdB1AE11BlockSourceB2AAA4QEBAB1QA2AVB2QDE11AutomaticIDB1AE10VDimensionB2AAA1HB2AAA2XZ, this, &did);
		return did;*/
		return FETCH(int, this + 236);
	}
	//��ȡ���ﵱǰ��������
	Vec3* getPos()
	{//IDA Actor::getPos
		return (Vec3*)(this + 1268);
	}
};

struct Mob : Actor {};
