#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>
#include <vector>
#include <string> 

class FontManager;
class Camera;
class Player;
class BgStage;
class Enemy
{
public:
	Enemy();
	 ~Enemy();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// �G�̏㉺���E���擾
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// ���݂̓G�̋�`���
	Rect GetRect();

	// �G�̈ʒu�����擾
	Vec2 GetPos() const { return m_pos; }

	// �G�̈ړ������𔽓]
	void ReverseDirection();

	// �G�̐����t���O
	void SetAlive(bool isAlive);

	// �G�̈ʒu��ݒ�
	void SetPos(float x, float y);

	// �G�������Ă��邩�ǂ����̃t���O
	bool IsAlive() const;

	// �v���C���[���͈͓��ɂ��邩�`�F�b�N����
	bool IsPlayerInRange(const Vec2& playerPos, float range); 

	// �G���A�N�e�B�u�ɂ���
	void Activate(); 
	// �G���A�N�e�B�u���ǂ������`�F�b�N����
	bool IsActive() const;

private:
  	Camera* m_pCamera;

	std::shared_ptr<BgStage> m_pBgStage;
	std::shared_ptr<Player> m_pPlayer;

	// �G�̈ʒu
	Vec2 m_pos;
	// �G�̉����x
	Vec2 m_move; 

	bool m_isTurnFlag;

	// �G�l�~�[�������Ă��邩�ǂ����̃t���O
	bool m_isAlive;

	// �����Ă������
	bool m_isAnimRight;
	bool m_isAnimLeft;
	bool m_isFacingRight; // �G���E�������Ă��邩�ǂ���

	// �G���A�N�e�B�u���ǂ������Ǘ�����t���O
	bool m_isActive; 

	// �A�j���[�V�����̃t���[��
	int m_animFrame;
	// �A�j���[�V�����̃J�E���g
	int m_animCount;
	// �G�̃O���t�B�b�N�n���h��
	int m_handle;
	int m_hitHandle;

	// ����n���h��
	int m_videoHandle;
	// ����̍Đ����
	bool m_isVideoPlaying;
	// �t�F�[�h�A�E�g�t���[���J�E���g
	int m_videoFadeFrameCount;
	// �t�F�[�h�C���t���[���J�E���g
	int m_videoFadeInFrameCount;

	int m_hitFrame;
};
