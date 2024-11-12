#pragma once

namespace Pad
{
	// パッドの更新処理 1フレームに1回行う
	void Update();

	// 押されているかを取得
	bool IsPress(int button);
	// 押された瞬間を取得
	bool IsTrigger(int button);
	// 離した瞬間を取得
//	bool IsRelase(int button);

}
