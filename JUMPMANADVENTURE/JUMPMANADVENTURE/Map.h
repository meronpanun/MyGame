#pragma once
class Map
{
public:
	Map();
	~Map();

	void Inti();
	void Update();
	void Draw();

private:
	// グラフィックのハンドル
	int m_handle;
	// グラフィックにチップがいくつ含まれているか
	int m_graphChipNumX;
	int m_graphChipNumY;

};

