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
		void OnLevelExplode(const std::string& title,const std::string& player_name,int dimension_1,int x1,int y1,int z1,const std::string& operation,int explodepower,int dimension_2,int x2,int y2,int z2)
		{
			if (dimension_1 == dimension_2)
			{
				int X = pow(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2), 0.5);//欧氏距离
				if (X <= 6)
				{
					std::ofstream File;
					File.open("Plugin/Log/All/OnLevelExplode.log", std::ofstream::app);
					File << Log::Helper::Title(title) << " " << player_name << u8" 在 " << Log::Helper::Dimension(dimension_1) << "(" << x1 << "," << y1 << "," << z1 << ")" << operation << Log::Helper::Dimension(dimension_2) << "(" << x2 << "," << y2 << "," << z2 << u8")的 " << Log::Helper::ExplodePower(explodepower) << std::endl;
				}
			}	
		}
	}
}

THook(bool, MSSYM_B1QA7explodeB1AA5LevelB2AAE20UEAAXAEAVBlockSourceB2AAA9PEAVActorB2AAA8AEBVVec3B2AAA1MB1UA4N3M3B1AA1Z, Level* _this, BlockSource* bs, Actor* a3, Vec3 pos, float a5, bool a6, bool a7, float a8, bool a9)
{
	for (auto& it : _this->getAllPlayers())
	{
		Log::Player::OnLevelExplode("", it->getNameTag()->c_str(), it->getDimensionId(), it->getPos()->x, it->getPos()->y, it->getPos()->z, u8" 引爆位于 ", a5, a3->getDimensionId(), a3->getPos()->x, a3->getPos()->y, a3->getPos()->z);
	}
	return original(_this, bs, a3, pos, a5, a6, a7, a8, a9);
}

void init() 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	std::cout << "[TwOnEnd-1.17.10.04] ExplodeLog Load ..." << std::endl;
}

void exit() {}

