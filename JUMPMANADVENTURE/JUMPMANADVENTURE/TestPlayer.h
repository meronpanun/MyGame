//#pragma once
//#include <memory>
//#include "TestRect.h"
//
//class TestMap;
//class TestPlayer
//{
//public:
//	TestPlayer();
//	virtual ~TestPlayer();
//
//	void SetMap(std::shared_ptr<TestMap> pTestMap) { m_pTestMap = pTestMap; }
//
//	void Init();
//	void Update();
//	void Draw();
//
//	float GetX() const { return m_posX; }
//	float GetY() const { return m_posY; }
//
//	float GetRadius();
//
//	// �v���C���[�̏㉺���E���擾
//	float GetLeft() const;
//	float GetTop() const;
//	float GetRigth() const;
//	float GetBottom() const;
//
//	TestRect getRect();
//
//private:
//	enum Dir
//	{
//		kNutral,
//		kWalk,
//		kNo,
//		kFall,
//		kDash
//	};
//	std::shared_ptr<TestMap> m_pTestMap;
//
//	Vec2 m_pos;
//
//	int m_playerHandle01;
//	int m_playerHandle02;
//
//	int m_jumpCount = 0;
//
//	bool m_isJump;
//
//	bool m_isRight;
//
//	bool m_isLeft;
//
//	bool m_isCommand;
//
//	float m_posX;
//	float m_posY;
//
//	float m_moveX;
//	float m_moveY;
//
//	Dir m_dir;
//
//	bool m_isAnimTurn;
//
//	bool m_isAnimJump;
//
//	int m_animationFrame;
//
//	int m_animFrame;
//	int m_animCount;
//};
//