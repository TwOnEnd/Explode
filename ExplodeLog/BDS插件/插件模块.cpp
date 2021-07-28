//正经人谁认真写注释
#include "预编译头.h"
#include "BDS内容.hpp"
#include <fstream>
#include<direct.h>
#include <io.h>
#include <math.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)

namespace Log
{
	namespace Helper
	{
		template<size_t size>
		void UtoA_Fill(char(&buf)[size], int num)
		{
			int nt = size - 1;
			buf[nt] = 0;
			for (auto i = nt - 1; i >= 0; --i)
			{
				char d = '0' + (num % 10);
				num /= 10;
				buf[i] = d;
			}
		}

		auto TimeNow() {
			auto timet = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			tm time;
			char buf[3] = { 0 };
			localtime_s(&time, &timet);
			std::string str(std::to_string((time.tm_year + 1900)));
			str += "-";
			UtoA_Fill(buf, time.tm_mon + 1);
			str += buf; str += "-";
			UtoA_Fill(buf, time.tm_mday);
			str += buf; str += " ";
			UtoA_Fill(buf, time.tm_hour);
			str += buf; str += ":";
			UtoA_Fill(buf, time.tm_min);
			str += buf; str += ":";
			UtoA_Fill(buf, time.tm_sec);
			str += buf;
			return str;
		}

		auto Title(const std::string& content)
		{
			return std::string("[") + TimeNow() + " " + "INFO" + content + "]";
		}

		auto Pos(Vec3* v)
		{
			return "(" + std::to_string(int(v->x)) + "," + std::to_string(int(v->y)) + "," + std::to_string(int(v->z)) + ")";
		}

		auto Dimension(int v)
		{
			switch (v)
			{
			case 0: return u8"主世界";
			case 1: return u8"地狱";
			case 2: return u8"末地";
			}
			return u8"未知维度";
		}

		auto ExplodePower(int v)
		{ 			
			switch (v)
			{
			case 3:return u8"苦力怕";
			case 4:return u8"TNT";
		//	case 5:return "";
			case 6:return u8"水晶或闪电苦力怕";
			}
			return "unknow";
		}
	}

	namespace Player
	{
		void OnLevelExplode(const std::string& title, const std::string& player_name, int dimension_1, Vec3* v, const std::string& operation, int explodepower,int dimension_2,int x, int y,int z)
		{
			std::ofstream File;
			File.open("Plugin/Log/All/OnLevelExplode.log", std::ofstream::app);	
			File << Log::Helper::Title(title) << " " << player_name << u8" 在 " << Log::Helper::Dimension(dimension_1) << Log::Helper::Pos(v) << operation << Log::Helper::Dimension(dimension_2) << "(" << x << "," << y << "," << z << u8") 的 " << Log::Helper::ExplodePower(explodepower) << u8" 并受到伤害" << std::endl;
		}

	}

}

int explode_flag = 0;
int explode_power = 0;
int explode_dimensionid = 0;
float explode_pos_x = 0;
float explode_pos_y = 0;
float explode_pos_z = 0;
THook(bool, MSSYM_B1QA7explodeB1AA5LevelB2AAE20UEAAXAEAVBlockSourceB2AAA9PEAVActorB2AAA8AEBVVec3B2AAA1MB1UA4N3M3B1AA1Z, Level* _this, BlockSource* bs, Actor* a3, Vec3 pos, float a5, bool a6, bool a7, float a8, bool a9)
{
	explode_flag = 1;
	explode_dimensionid = a3->getDimensionId();
	//↓又不是不能用
	explode_power = a5;
	explode_pos_x = a3->getPos()->x;
	explode_pos_y = a3->getPos()->y;
	explode_pos_z = a3->getPos()->z;
	int x = a3->getPos()->x;
	int y = a3->getPos()->y;
	int z = a3->getPos()->z;

	const std::string& title = "";
	std::ofstream File;
	File.open("Plugin/Log/All/OnLevelExplode.log", std::ofstream::app);
	File << Log::Helper::Title(title) << " " << Log::Helper::ExplodePower(a5) << u8" 在 " << Log::Helper::Dimension(a3->getDimensionId()) << "(" << x << "," << y << "," << z << u8") 爆炸" << std::endl;
	return original(_this, bs, a3, pos, a5, a6, a7, a8, a9);
}

THook(bool, MSSYM_B2QUA4hurtB1AA3MobB2AAA4MEAAB1UE22NAEBVActorDamageSourceB2AAA1HB1UA2N1B1AA1Z, Mob* _this, VA dmsg, int a3, bool a4, bool a5)
{
	std::string player_name = _this->getNameTag()->c_str();
	if (player_name != "" && explode_flag == 1)
	{
		float x1 = _this->getPos()->x, y1 = _this->getPos()->y, z1 = _this->getPos()->z;
		float x2 = explode_pos_x, y2 = explode_pos_y, z2 = explode_pos_z;
		int X = pow(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2), 0.5);//欧氏距离
		if (X <= 5)
		{
			Log::Player::OnLevelExplode("", player_name, _this->getDimensionId(), _this->getPos(), u8" 引爆位于 ", explode_power, explode_dimensionid, explode_pos_x, explode_pos_y, explode_pos_z);
		}
		
	}	explode_flag = 0, explode_power = 0, explode_dimensionid = 0, explode_pos_x = 0, explode_pos_y = 0, explode_pos_z = 0;
	return original(_this, dmsg, a3, a4, a5);				  
}

void init() 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << "[TwOnEnd-1.17.10.04] ExplodeLog Load ..." << std::endl;
}

void exit() {}

