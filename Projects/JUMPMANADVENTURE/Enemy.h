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

/// <summary>
/// �G�N���X
/// </summary>
class Enemy
{
public:
	Enemy();
	 ~Enemy();

	void Init(Camera* camera);
	void Update();
	void Draw();

	/*�G�̏㉺���E���擾*/
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// ���݂̓G�̋�`���
	Rect GetRect();

	// �G�̈ʒu�����擾
	Vec2 GetPos() const { return m_pos; }

	/// <summary>
	///  �G�̈ړ������𔽓]
	/// </summary>
	void ReverseDirection();

	/// <summary>
	///  �G�̐����t���O 
	/// </summary>
	/// <param name="isAlive">true:�����Ă��� false:����ł���</param>
	void SetAlive(bool isAlive);

	/// <summary>
	///  �G�̈ʒu��ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPos(float x, float y);

	/// <summary>
	/// �G�������Ă��邩�ǂ����̃t���O
	/// </summary>
	/// <returns> true:�����Ă��� false:����ł���</returns>
	bool IsAlive() const;

	/// <summary>
	///	�v���C���[���͈͓��ɂ��邩�`�F�b�N���� 
	/// </summary>
	/// <param name="playerPos">�v���C���[�̈ʒu</param>
	/// <param name="range">�͈�</param>
	/// <returns>�͈͓��ɂ��邩�ǂ���</returns>
	bool IsPlayerInRange(const Vec2& playerPos, float range); 

	/// <summary>
	///  �G���A�N�e�B�u�ɂ���
	/// </summary>
	void Activate(); 
	
	/// <summary>
	/// �G���A�N�e�B�u���ǂ������`�F�b�N����
	/// </summary>
	/// <returns>true:�A�N�e�B�u false:��A�N�e�B�u</returns>
	bool IsActive() const;

private:
  	Camera* m_pCamera;

	std::shared_ptr<BgStage> m_pBgStage;
	std::shared_ptr<Player> m_pPlayer;

	// �G�̈ʒu
	Vec2 m_pos;
	// �G�̉����x
	Vec2 m_move; 

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
};
