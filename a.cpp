#include <iostream>
#include <windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>



namespace {
    const bool    IS_FULL_SCREEN  = false;  // フルスクリーンかどうか 
    const GLint   FORM_WIDTH      = 1024;   // 画面サイズ。フルスクリーンの場合は解像度
    const GLint   FORM_HEIGHT     = 768;
    const int64_t WAIT_TIME       = 33;     // 1ループのウェイト（ms）

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
}



void doWait(int64_t elapse_ms, int64_t wait_ms);
bool checkControllerEvent(GLFWwindow *window);





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 【関数】
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void
doWait(int64_t elapse_ms, int64_t wait_ms)
{
    // 【関数】処理時間に応じたウェイト
    // ＜引数＞elapse_msは計測開始からの経過時間。wait_msは最低ウェイトする時間。
    // 単位はすべてミリ秒。計測開始点でglfwSetTime(0.0)を実行して使用する。Windows依存。
    // 式。実際にウェイトする時間 = wait_ms - elapse_ms
    int64_t ms = wait_ms - elapse_ms;

    if (ms > 0) {
        if (ms > wait_ms) ms = wait_ms;
        Sleep(static_cast<DWORD>(ms));
    }

    return;
}





bool
checkControllerEvent(GLFWwindow *window)
{
    // 【関数】入力操作の判定
    // ＜戻り値＞アプリ終了の操作ならtrue、それ以外false
    static bool flgMouseBtn[GLFW_MOUSE_BUTTON_LAST+1];  // 初期化不要。C++のstatic変数は自動で初期化
    // static bool flgKey[GLFW_KEY_LAST+1];

    // @ アプリ終了操作
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            return true;
    
    // @ ボタンのプッシュ処理
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!flgMouseBtn[GLFW_MOUSE_BUTTON_RIGHT]) {
            return false;
        }
        flgMouseBtn[GLFW_MOUSE_BUTTON_RIGHT] = true;
    }
    else {
        flgMouseBtn[GLFW_MOUSE_BUTTON_RIGHT] = false;
    }


    return false;
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 【メイン】
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int
main()
{
    // @@@ OpenGLの初期設定
    // GLFWを初期化
    if (!glfwInit()) return -1;
    // 生成するウィンドウの特性
    glfwWindowHint(GLFW_SAMPLES, 4);
    // ウィンドウを生成し、識別子を取得
    // glfwCreateWindowの第4引数に、glfwGetPrimaryMonitor()を渡すと、フルスクリーンになる。
    // この際、widthとheightは解像度となる。
    GLFWmonitor *monitor = IS_FULL_SCREEN ? glfwGetPrimaryMonitor() : NULL;
    GLFWwindow *window = glfwCreateWindow(FORM_WIDTH, FORM_HEIGHT, "App. name", monitor , NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // カレントウィンドウに指定
    glfwMakeContextCurrent(window);
    // GLEWを初期化
    if(glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    // デフォルトのフレームバッファ識別子を取得（後で使用）
    GLint showFrameBuffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &showFrameBuffer);
    // 垂直同期
    glfwSwapInterval(1);  // 最近はOS自体がダブルバッファを使うため、無視される可能性あり
    // その他
    glfwSetTime(0.0);



    // @@@ ImGuiの初期設定
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // @ フォント
    ImGuiIO &guiIO = ImGui::GetIO();
    // 1バイト文字と全角文字、それぞれフォントを読み込んで混在できるようにする
    ImFontConfig guiFontConfig;
    guiFontConfig.MergeMode = true;
    // 1バイト文字用のフォント（文字列リテラルは "" で記述）
    // guiIO.Fonts->AddFontDefault();
    guiIO.Fonts->AddFontFromFileTTF("imgui/fonts/Roboto-Medium.ttf", 21.0f);
    // guiIO.Fonts->AddFontFromFileTTF("imgui/fonts/Cousine-Regular.ttf", 21.0f);
    // guiIO.Fonts->AddFontFromFileTTF("imgui/fonts/DroidSans.ttf", 21.0f);
    // guiIO.Fonts->AddFontFromFileTTF("imgui/fonts/ProggyTiny.ttf", 21.0f);
    // 全角文字用のフォント（文字列リテラルは u8"" で記述）
    guiIO.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 26.0f,
                                    &guiFontConfig, guiIO.Fonts->GetGlyphRangesJapanese());

    // @ キーボード操作を有効化
    // guiIO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // @ スタイル
    ImGuiStyle &guiStyle = ImGui::GetStyle();
    // 元となるスタイル（プリセット）を読み込む
    ImGui::StyleColorsClassic(&guiStyle);
    // ImGui全体の属性
    guiStyle.Alpha             = 0.9f;
    guiStyle.WindowRounding    = 7.0f;
    guiStyle.FrameRounding     = 5.0f;
    guiStyle.GrabRounding      = 7.0f;
    guiStyle.ScrollbarRounding = 1.0f;
    guiStyle.WindowBorderSize  = 0.0f;
    guiStyle.FrameBorderSize   = 0.0f;
    guiStyle.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    // Beginするウィンドウの属性
    ImGuiWindowFlags flgGuiAttr = 0;
    // flgGuiAttr |= ImGuiWindowFlags_NoTitleBar;            // タイトルバー非表示
    // flgGuiAttr |= ImGuiWindowFlags_MenuBar;               // メニュー非表示
    // flgGuiAttr |= ImGuiWindowFlags_NoScrollbar;           // スクロールバー非表示
    flgGuiAttr |= ImGuiWindowFlags_NoMove;                // ウィンドウのドラッグ移動無し
    flgGuiAttr |= ImGuiWindowFlags_NoResize;              // リサイズ無し
    // flgGuiAttr |= ImGuiWindowFlags_NoCollapse;            // 最小化無し
    // flgGuiAttr |= ImGuiWindowFlags_NoNav;                 // ナビ無し
    // flgGuiAttr |= ImGuiWindowFlags_NoBackground;          // ウィンドウの背景を非表示
    // flgGuiAttr |= ImGuiWindowFlags_NoBringToFrontOnFocus; // 最前面に表示しない
    // 次にBeginするウィンドウの座標とサイズ。及び「いつ設定するか」の指定
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_FirstUseEver);
    


	// @@@ 座標変換（モデルの実寸表示。左上基準。簡易2d用）
	// @ プロジェクション座標変換
	// ワールド座標に直に描画するため、「モデルビュー座標変換」は省略。
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  // 初期化（単位行列）
	// 正投影行列を作り、行列に掛け合わせる
	// void glOrtho( 左x, 右x, 下y, 上y, 手前z, 奥z );
	glOrtho(0.0, static_cast<GLdouble>(FORM_WIDTH),
            static_cast<GLdouble>(FORM_HEIGHT), 0.0,
            -1.0, 1.0);
        


    // @@@ GLFWループ ----------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        static double startTime;
        startTime = glfwGetTime();
        glfwPollEvents();
        if (checkControllerEvent(window)) break;



        // @@ ImGui
        // @ ImGuiの内容を刷新
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        static float val     = 0.0f;
        static int   cnt     = 0;
        static float rgba[4] = {0.0f, 0.5f, 1.0f, 0.5f};
        static bool isShowGui2 = false;


        // @ ImGuiの操作子サンプル
        ImGui::Begin("Hello world!", NULL, flgGuiAttr);

        ImGui::Text(u8"日本語の表示は、文字列リテラルの前にu8を付加。");

        if (ImGui::SliderFloat("SliderFloat", &val, 0.0f, 1.0f))
            printf("Slider Moved.");

        ImGui::ColorEdit4("B.G. Color", rgba);

        ImGui::NewLine();

        if (ImGui::Button("Button")) cnt++;
        ImGui::SameLine();  // 改行しない
        ImGui::Text(" cnt: %d", cnt);

        ImGui::Checkbox("Show GUI2", &isShowGui2);

        ImGui::NewLine();
        ImGui::Separator();

        ImGui::Text("Avg. %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();


        // @ 複数のGUIを表示
        // 表示されるかどうかは下のブロックが実行されるかどうか。閉じる方法は3つ
        // あることに意識すること（上記Checkbox, GUI2のButton, GUI2の右上の閉じるボタン）
        if (isShowGui2) {
            ImGui::Begin("GUI2", &isShowGui2);
            if (ImGui::Button("Close"))
                isShowGui2 = false;
            ImGui::End();
        }

        // @ ImGuiの内容を生成
        ImGui::Render();



        // @@ 描画
        static int w, h;
        glfwGetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // ここにメインの描画処理を記述...

        // @ ImGuiを描画
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());



        // @@ 後処理
        // printf("Time(s):%f\n", glfwGetTime());  // 1ループの純粋な処理時間
        int64_t elapseTime = static_cast<int64_t>(glfwGetTime() - startTime) * 1000;
        doWait(elapseTime, WAIT_TIME);
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }



    // @@@ 終了処理
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
