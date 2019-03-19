///////////////////////////////////////////////////////////////////////////////////////////////
// 【モジュール実装】module_gl
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

#include <windows.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "module_gl.h"



namespace {
    // モジュール変数
    GLFWwindow *m_window    = nullptr;
    double      m_startTime = 0.0;
}





namespace module_gl {


// 【関数】GLFWとGLEWを初期化してウィンドウを生成
// ＜戻り値＞GLFWウィンドウ識別子。失敗でnullptr
GLFWwindow *setupWindow(const char *title,
                        int formWidth, int formHeight,
                        bool isFullScreen)
{
    // @ GLFWを初期化
    if (!glfwInit()) return nullptr;

    // これから生成するウィンドウの属性
    glfwWindowHint(GLFW_SAMPLES, 4);

    // ウィンドウを生成し、識別子を取得
    // glfwCreateWindowの第4引数に、glfwGetPrimaryMonitor()を渡すと、フルスクリーンになる。
    // この際、widthとheightは解像度となる。
    GLFWmonitor *monitor = isFullScreen ? glfwGetPrimaryMonitor() : nullptr;
    m_window = glfwCreateWindow(formWidth, formHeight, title, monitor , NULL);
    if (!m_window) {
        glfwTerminate();
        return nullptr;
    }

    // カレントウィンドウに指定
    glfwMakeContextCurrent(m_window);

    // @ GLEWを初期化
    if(glewInit() != GLEW_OK) {
        glfwTerminate();
        return nullptr;
    }

    // @ その他
    glfwSwapInterval(1);  // 垂直同期。最近はOS自体がダブルバッファを使うため、無視される可能性あり
    glfwSetTime(0.0);     // GLFWのタイマーをリセット


    return m_window;
}





// 【関数】キーが押されていたら、真を「1度だけ」返す
bool pressedKey(int key)
{
    static bool flgKey[GLFW_KEY_LAST+1];  // 初期化不要。C++のstatic変数は自動で初期化

    if (glfwGetKey(m_window, key) == GLFW_PRESS) {
        if (!flgKey[key]) {
            flgKey[key] = true;   
            return true;
        }
    }
    else
        flgKey[key] = false;
    
    return false;
}





// 【関数】マウスボタンが押されていたら、真を「1度だけ」返す
bool pressedMouse(int button)
{
    static bool flgMouseBtn[GLFW_MOUSE_BUTTON_LAST+1];  // 初期化不要。C++のstatic変数は自動で初期化

    if (glfwGetMouseButton(m_window, button) == GLFW_PRESS) {
        if (!flgMouseBtn[button]) {
            flgMouseBtn[button] = true;   
            return true;
        }
    }
    else
        flgMouseBtn[button] = false;
    
    return false;
}





// 【関数】2D座標変換を設定（モデルの実寸表示。左上基準。簡易2d用）
void setView2D(int topLeftX,     int topLeftY,
               int bottomRightX, int bottomRightY )
{
    // @ プロジェクション座標変換
    // ワールド座標に直に描画するため、「モデルビュー座標変換」は省略。
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // 初期化（単位行列）

    // @ 正投影行列を作り、行列に掛け合わせる
    // void glOrtho( 左x, 右x, 下y, 上y, 手前z, 奥z );
    glOrtho(static_cast<GLdouble>(topLeftX)    , static_cast<GLdouble>(bottomRightX),
            static_cast<GLdouble>(bottomRightY), static_cast<GLdouble>(topLeftY),
            -1.0, 1.0);
    
    return;
}





// 【関数】時間計測開始
void startTimer()
{
    m_startTime = glfwGetTime();
    return;
}





// 【関数】経過時間を返す（ms）
int64_t getElapseTime()
{
    return static_cast<int64_t>(glfwGetTime() - m_startTime) * 1000;
}





// 【関数】処理時間に応じたウェイト
// ＜引数＞最低ウェイトする時間
// ＜補足＞単位はミリ秒。計測開始点でstartTimer()を実行して使用する。Windows依存
// ＜式＞実際にウェイトする時間 = wait_ms - elapse_ms
void doWait(int64_t wait_ms)
{
    int64_t ms = wait_ms - getElapseTime();

    if (ms > 0) {
        if (ms > wait_ms) ms = wait_ms;
        Sleep(static_cast<DWORD>(ms));
    }

    return;
}





// 【関数】GLFWウィンドウを破棄
void teardownWindow()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
    return;
}
}