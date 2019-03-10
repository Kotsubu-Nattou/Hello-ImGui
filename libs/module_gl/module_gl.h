#pragma once

template <typename T>
struct VEC2 {
    T x;
    T y;
};

template <typename T>
struct VEC3 {
    T x;
    T y;
    T z;
};

template <typename T>
struct VEC4 {
    T x;
    T y;
    T z;
    T w;
};





namespace module_gl {
    // 【関数】GLFWウィンドウを生成（GLEW対応）
    GLFWwindow* setupWindow(const char *title = "App. name",
                            int formWidth = 100, int formHeight = 100,
                            bool isFullScreen = false);

    // 【関数】キーが押されていたら、真を「1度だけ」返す
    bool pressedKey(int key);

    // 【関数】マウスボタンが押されていたら、真を「1度だけ」返す
    bool pressedMouse(int button);

    // 【関数】2D座標変換を設定（モデルの実寸表示。左上基準。簡易2d用）
    void setView2D(int topLeftX,     int topLeftY,
                   int bottomRightX, int bottomRightY );

    // 【関数】時間計測開始
    void startTimer();

    // 【関数】経過時間を返す（ms）
    int64_t getElapseTime();

    // 【関数】処理時間に応じたウェイト
    // ＜引数＞最低ウェイトする時間
    // ＜補足＞単位はミリ秒。計測開始点でstartTimer()を実行して使用する。Windows依存
    // ＜式＞実際にウェイトする時間 = wait_ms - elapse_ms
    void doWait(int64_t wait_ms);

    // 【関数】GLFWウィンドウを破棄
    void teardownWindow();
}