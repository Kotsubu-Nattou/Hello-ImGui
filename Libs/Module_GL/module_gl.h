///////////////////////////////////////////////////////////////////////////////////////////////
// 【モジュール定義】module_gl
//
// ・概要
//   OpenGL関係のよく使う定型処理を、メインソースから切り離すことを目的とする。
//   対応：Windows, GLFW, GLEW
//   想定：GLFWでウィンドウを1つしか使わない。GLFWループや細かなメソッドは、
//        メインソースから直接gl*命令をコールする。
//
// ・内容
//   グローバルで使えるテンプレート構造体、VEC2～VEC4を用意（主な算術オペレーションに対応）
//   下記のようなOpenGL関係の定型処理関数
//       module_gl::setupWindow()    --- GLFWとGLEWを初期化してウィンドウを生成
//       module_gl::teardownWindow() --- GLFWの終了処理
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "struct_vec.h"



namespace module_gl {
    // 【関数】GLFWとGLEWを初期化してウィンドウを生成
    // ＜戻り値＞GLFWウィンドウ識別子。失敗でnullptr
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