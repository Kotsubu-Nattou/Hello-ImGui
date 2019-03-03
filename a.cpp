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
    const GLint   FORM_HEIGHT     = 800;
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
    guiStyle.Alpha             = 1.0f;
    guiStyle.WindowRounding    = 7.0f;
    guiStyle.FrameRounding     = 5.0f;
    guiStyle.GrabRounding      = 7.0f;
    guiStyle.ScrollbarRounding = 1.0f;
    guiStyle.WindowBorderSize  = 0.0f;
    guiStyle.FrameBorderSize   = 0.0f;
    guiStyle.Colors[ImGuiCol_WindowBg]         = ImVec4(0.2f, 0.2f, 0.2f, 0.7f); // ImVec4(0.0f, 0.0f, 0.0f, 0.7f);
    guiStyle.Colors[ImGuiCol_MenuBarBg]        = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // ImVec4(0.4f , 0.4f , 0.55f, 0.8f);
    guiStyle.Colors[ImGuiCol_TitleBg]          = ImVec4(0.5f, 0.5f, 0.5f, 0.5f); // ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
    guiStyle.Colors[ImGuiCol_TitleBgActive]    = ImVec4(0.5f, 0.5f, 0.5f, 0.7f); // ImVec4(0.32f, 0.32f, 0.63f, 0.87f);
    guiStyle.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.5f, 0.5f, 0.5f, 0.3f); // ImVec4(0.4f , 0.4f , 0.8f , 0.2f);
    // ウィンドウの属性：メインのGUI
    ImGuiWindowFlags flgGuiAttrMain = 0;
    // flgGuiAttrMain |= ImGuiWindowFlags_NoTitleBar;            // タイトルバー非表示
    flgGuiAttrMain |= ImGuiWindowFlags_MenuBar;               // メニューを使用する
    flgGuiAttrMain |= ImGuiWindowFlags_NoMove;                // ウィンドウのドラッグ移動無し
    flgGuiAttrMain |= ImGuiWindowFlags_AlwaysAutoResize;      // 自動リサイズする（手動リサイズ無し）
    // flgGuiAttrMain |= ImGuiWindowFlags_NoResize;              // 手動リサイズ無し
    // flgGuiAttrMain |= ImGuiWindowFlags_NoBackground;          // ウィンドウの背景を非表示
    // flgGuiAttrMain |= ImGuiWindowFlags_NoScrollbar;           // スクロールバー非表示
    // flgGuiAttrMain |= ImGuiWindowFlags_NoCollapse;            // 最小化無し
    // flgGuiAttrMain |= ImGuiWindowFlags_NoNav;                 // ナビ無し
    // flgGuiAttrMain |= ImGuiWindowFlags_NoBringToFrontOnFocus; // 最前面に表示しない
    // ウィンドウの属性：サブのGUI
    ImGuiWindowFlags flgGuiAttrSub = 0;
    // ウィンドウの属性：オーバーレイ
    ImGuiWindowFlags flgGuiAttrOverlay = 0;
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoTitleBar;            // タイトルバー非表示
    // flgGuiAttrOverlay |= ImGuiWindowFlags_MenuBar;               // メニューを使用する
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoMove;                // ウィンドウのドラッグ移動無し
    flgGuiAttrOverlay |= ImGuiWindowFlags_AlwaysAutoResize;      // 自動リサイズする（手動リサイズ無し）
    // flgGuiAttrOverlay |= ImGuiWindowFlags_NoResize;              // 手動リサイズ無し
    // flgGuiAttrOverlay |= ImGuiWindowFlags_NoBackground;          // ウィンドウの背景を非表示
    // flgGuiAttrOverlay |= ImGuiWindowFlags_NoScrollbar;           // スクロールバー非表示
    // flgGuiAttrOverlay |= ImGuiWindowFlags_NoCollapse;            // 最小化無し
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoNav;                 // ナビ無し
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoBringToFrontOnFocus; // 最前面に表示しない
    


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



        // @@ ImGui ウィジェットサンプル
        // ・ImGuiの各操作子のことを、ウィジェットと言う
        // ・ImGuiはステート駆動方式
        // ・フロー
        //     1. ImGuiを初期化。フォントなどImGui全体の設定を行う
        //    （GLFWループ開始）
        //       2. ImGuiバッファをクリア
        //       3. ウィジェットの内容を定義
        //       4. ImGuiバッファにレンダリング
        //       5. クライアントの処理、及びドロー
        //       6. ImGuiバッファをドロー（最前面に来る）
        //    （GLFWループ終了）
        //     7. ImGuiを解放
        // ・ウィジェットの表示は「そのメソッドが実行された」かどうかで決まる
        // ・主に各ウィジェットの戻り値はbool。操作したときtrueが返る
        // ・if (ImGui::InputInt("Value", &val)) {/*処理*/}
        //   これで、ウィジェットの「表示」と「イベント処理」を兼ねている。
        //   if文を無くせば、「非イベント型のウィジェット」となる。
        // ・注意。glfwSetTime() を実行するとImGuiがエラーする

        // @ ImGuiの内容を刷新
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

  
        // @ ウィンドウ：Hello ImGui!
        static const float GUI_MARGIN_MAIN = 30.0f;
        // ウィンドウの座標（次のBeginが対象）
        ImGui::SetNextWindowPos(ImVec2(guiIO.DisplaySize.x - GUI_MARGIN_MAIN, GUI_MARGIN_MAIN),  // 座標
                                ImGuiSetCond_Always,       // いつ設定するか
                                ImVec2(1.0f, 0.0f));       // 基準の位置（Pivot）
        // ImGui::SetNextWindowSize(ImVec2(100, 300), ImGuiSetCond_Once); // サイズは自動リサイズに任せる
        ImGui::Begin("Hello ImGui!", nullptr, flgGuiAttrMain);

        // メニューバー
        if (ImGui::BeginMenuBar()) {
            // Menu
            if (ImGui::BeginMenu("Menu")) {
                if (ImGui::MenuItem("dummy")) {/*処理を記述*/}
                ImGui::Separator();
                if (ImGui::MenuItem("Quit", "Alt+F4")) break;
                ImGui::EndMenu();
            }
            // Edit
            if (ImGui::BeginMenu("Edit")) {
                ImGui::MenuItem("Disabled item.", nullptr, false, false); 
                ImGui::MenuItem("Checked item.", nullptr, true); 
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // 日本語テキストを表示（UTF-8）
        // ・文字列リテラルが、内部でどう扱われるかはコンパイラ依存。
        // ・明示的に文字コードを指定するには、文字列リテラルの接頭辞にu8を付加。
        //   これで、仮引数の直接指定や、変数での運用も可能。
        // ・ちなみに、現開発環境（GCC、ソースコードUTF-8）では、u8を付けなくても良い。
        // ・型について
        //   UTF-8はマルチバイト文字でありバイト数可変である。それに対し、
        //   ワイド文字（wchar_t）は、2バイト固定で扱いは楽であるが、UTF-8と互換性がない。
        //   よってリテラルの型は、const char* を使用する（constが無いとコンパイラワーニング）
        ImGui::Text(u8"日本語を表示するには、文字列リテラルの接頭辞にu8を付加。");
        static const char *str = u8"変数での運用も可能。";
        ImGui::Text(str);
        ImGui::NewLine();

        // 各数値入力（ノブ、ドラッグ、ボタン、レンジ）
        static float val1 = 0.0f, angle = 0.0f;
        static int val2 = 30, val3 = 55, valMin = 40, valMax = 50;
        if (ImGui::SliderFloat("SliderFloat", &val1, 0.0f, 1.0f))
            printf("Slider Moved.");
        ImGui::SliderAngle("SliderAngle", &angle);
        ImGui::DragInt("DragInt 0..100", &val2, 1, 0, 100, "%d%%");
        ImGui::InputInt("InputInt", &val3, 10, 100);
        ImGui::DragIntRange2("DragIntRange2", &valMin, &valMax, 1.0f,
                             20, 100, "%dunit");  // 範囲超えバグあり（後で変数を修正するかDragIntなどで代用すること）
        ImGui::NewLine();
        ImGui::Separator();

        // コマンドボタン
        static int cnt = 0;
        if (ImGui::Button("Button")) cnt++;
        ImGui::SameLine();  // 改行しない
        ImGui::Text(" cnt: %d", cnt);

        // チェックボックス
        static bool isShowGui2 = false;
        ImGui::Checkbox("Show GUI2", &isShowGui2);
        ImGui::NewLine();

        // カラーセレクター
        static float rgba[4] = {0.4f, 0.6f, 0.2f, 0.8f};
        ImGui::ColorEdit4("B.G. Color", rgba);
        ImGui::NewLine();
        ImGui::Separator();

        // ラジオボタン
        static int radioId = 1;
        ImGui::RadioButton("foo", &radioId, 0); ImGui::SameLine();
        ImGui::RadioButton("bar", &radioId, 1); ImGui::SameLine();
        ImGui::RadioButton("hoge", &radioId, 2);
        ImGui::NewLine();

        // コンボボックス
        static int comboId = 2;
        ImGui::Combo("Combo", &comboId, "aaa\0bbb\0ccc\0ddd\0eee\0");
        ImGui::NewLine();

        // リストボックス
        static const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange"};
        static int listBoxId = 0;
        ImGui::ListBox("ListBox", &listBoxId, items, IM_ARRAYSIZE(items), 3);
        ImGui::NewLine();

        // セレクタブル
        static bool isSelected[8] = {};
        ImGui::Separator();
        ImGui::Columns(4, nullptr, false);  // 1セットのカラム数（並びは右方向）

        for (int i = 0; i < 8; ++i) {
            char str[32];
            sprintf(str, "Item%d", i);
            if (ImGui::Selectable(str, &isSelected[i])) {/*処理を記述*/}
            ImGui::NextColumn();  // カラムを進める（これが無いとSelectableが縦に連なる）
        }
        ImGui::Columns(1);  // カラムを初期化（以降全てに適応してしまうため）
        ImGui::Separator();

        ImGui::End();


        // @ ウィンドウ：GUI2
        // 表示されるかどうかは下のブロックが実行されるかどうか。閉じる方法は3つ
        // あることに意識すること（上記Checkbox, GUI2のButton, GUI2の右上の閉じるボタン）
        if (isShowGui2) {
            ImGui::Begin("GUI2", &isShowGui2, flgGuiAttrSub);
            if (ImGui::Button("Close"))
                isShowGui2 = false;
            ImGui::End();
        }


        // @ ウィンドウ：オーバーレイ
        enum {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
        static const float GUI_MARGIN_OVERLAY = 20.0f;
        static int overlayCorner = BOTTOM_LEFT;
        // 表示する座標
        ImVec2 guiOverlayPos = ImVec2(GUI_MARGIN_OVERLAY, GUI_MARGIN_OVERLAY);
        ImVec2 guiOverlayPivot = ImVec2(0.0f, 0.0f);
        switch (overlayCorner) {
            case TOP_RIGHT:
                guiOverlayPos.x = guiIO.DisplaySize.x - GUI_MARGIN_OVERLAY;
                guiOverlayPivot.x = 1.0f;
                break;

            case BOTTOM_LEFT:
                guiOverlayPos.y = guiIO.DisplaySize.y - GUI_MARGIN_OVERLAY;
                guiOverlayPivot.y = 1.0f;
                break;

            case BOTTOM_RIGHT:
                guiOverlayPos.x = guiIO.DisplaySize.x - GUI_MARGIN_OVERLAY;
                guiOverlayPos.y = guiIO.DisplaySize.y - GUI_MARGIN_OVERLAY;
                guiOverlayPivot.x = guiOverlayPivot.y = 1.0f;
                break;
        }
        ImGui::SetNextWindowPos(guiOverlayPos, ImGuiSetCond_Always, guiOverlayPivot);
        ImGui::SetNextWindowBgAlpha(0.2f);
        ImGui::Begin("Overlay", nullptr, flgGuiAttrOverlay);

        // FPSを取得して表示
        ImGui::Text("FPS: %.1f",
                    ImGui::GetIO().Framerate);
        ImGui::Text("Avg: %.2f ms/frame",
                    1000.0f / ImGui::GetIO().Framerate);
        
        // ポップアップ
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Top-Left"))     overlayCorner = TOP_LEFT;
            if (ImGui::MenuItem("Top-Right"))    overlayCorner = TOP_RIGHT;
            if (ImGui::MenuItem("Bottom-Left"))  overlayCorner = BOTTOM_LEFT;
            if (ImGui::MenuItem("Bottom-Right")) overlayCorner = BOTTOM_RIGHT;
            ImGui::EndPopup();
        }
        ImGui::End();


        // @ ImGuiの内容を生成
        ImGui::Render();



        // @@ 描画
        static int w, h;
        glfwGetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // ここにメインの描画処理を記述...

        // @ ImGuiを描画（最前面にするため最後に描画）
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
