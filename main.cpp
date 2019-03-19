#include <iostream>
#include <windows.h>
#include "Libs/ImGui/imgui.h"
#include "Libs/ImGui/imgui_impl_glfw.h"
#include "Libs/ImGui/imgui_impl_opengl2.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Libs/Module_GL/module_gl.h"

namespace {
    const bool    IS_FULL_SCREEN  = false;  // フルスクリーンかどうか 
    const int     FORM_WIDTH      = 1024;   // 画面サイズ。フルスクリーンの場合は解像度
    const int     FORM_HEIGHT     = 800;
    const int64_t WAIT_TIME       = 33;     // 1ループのウェイト（ms）
}



bool checkControllerEvent(GLFWwindow *window);





// 【関数】入力操作の判定
// ＜戻り値＞アプリ終了の操作ならtrue、それ以外false
bool checkControllerEvent(GLFWwindow *window)
{
    // static bool flgMouseBtn[GLFW_MOUSE_BUTTON_LAST+1];  // 初期化不要。C++のstatic変数は自動で初期化
    // static bool flgKey[GLFW_KEY_LAST+1];

    // @ アプリ終了操作
    if (module_gl::pressedKey(GLFW_KEY_ESCAPE) ||
        module_gl::pressedMouse(GLFW_MOUSE_BUTTON_RIGHT))
        return true;


    return false;
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 【メイン】
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int main()
{
    // @@@ OpenGLの初期設定
    GLFWwindow *window = module_gl::setupWindow("Hello ImGui!",
                                                FORM_WIDTH, FORM_HEIGHT,
                                                IS_FULL_SCREEN);
    if (!window) return -1;

    // @@@ ImGuiの初期設定
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // @ フォント
    // ASCII文字用フォントと日本語用フォントを、混在利用できるように設定
    ImGuiIO &guiIO = ImGui::GetIO();
    ImFontConfig guiFontConfig;
    guiFontConfig.MergeMode = true;
    // ASCII文字用のフォント
    // guiIO.Fonts->AddFontDefault();
    guiIO.Fonts->AddFontFromFileTTF("Libs/ImGui/fonts/Roboto-Medium.ttf", 21.0f);
    // guiIO.Fonts->AddFontFromFileTTF("Libs/ImGui/fonts/Cousine-Regular.ttf", 21.0f);
    // guiIO.Fonts->AddFontFromFileTTF("Libs/ImGui/fonts/DroidSans.ttf", 21.0f);
    // guiIO.Fonts->AddFontFromFileTTF("Libs/ImGui/fonts/ProggyTiny.ttf", 21.0f);
    // 日本語用のフォント
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
    // flgGuiAttrMain |= ImGuiWindowFlags_NoDecoration;          // NoTitleBar | NoResize | NoScrollbar | NoCollapse
    // flgGuiAttrMain |= ImGuiWindowFlags_NoSavedSettings;       // imgui.iniの保存無し
    // flgGuiAttrMain |= ImGuiWindowFlags_NoInputs;              // 操作無し
    // ウィンドウの属性：サブのGUI
    ImGuiWindowFlags flgGuiAttrSub = 0;
    // ウィンドウの属性：オーバーレイ
    ImGuiWindowFlags flgGuiAttrOverlay = 0;
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoTitleBar;            // タイトルバー非表示
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoMove;                // ウィンドウのドラッグ移動無し
    flgGuiAttrOverlay |= ImGuiWindowFlags_AlwaysAutoResize;      // 自動リサイズする（手動リサイズ無し）
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoNav;                 // ナビ無し
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoBringToFrontOnFocus; // 最前面に表示しない
    flgGuiAttrOverlay |= ImGuiWindowFlags_NoSavedSettings;       // imgui.iniの保存無し



    // @@@ 座標変換（モデルの実寸表示。左上基準。簡易2d用）
    module_gl::setView2D(0, 0, FORM_WIDTH, FORM_HEIGHT);



    // @@@ GLFWループ ----------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        module_gl::startTimer();
        glfwPollEvents();
        if (checkControllerEvent(window)) break;



        // @@ ImGui ウィジェットサンプル
        // ・ImGuiの各操作子のことを、ウィジェットと言う
        // ・ImGuiはステート駆動方式
        // ・フロー
        //     1. ImGuiを初期化。フォントや外観などImGui全体の設定を行う
        //    （GLFWループ開始）
        //       2. ImGuiバッファをクリア
        //       3. ウィジェットの内容を定義
        //       4. ImGuiバッファにレンダリング
        //       5. クライアントの処理、及びドロー
        //       6. ImGuiバッファをドロー（最前面に来させる）
        //    （GLFWループ終了）
        //     7. ImGuiを解放
        // ・ウィジェットの表示は「そのメソッドが実行された」かどうかで決まる
        // ・主に各ウィジェットの戻り値はbool。操作したときtrueが返る
        // ・if (ImGui::InputInt("Value", &val)) {/*処理*/}
        //   これで、ウィジェットの「表示」と「イベント処理」を兼ねている。
        //   if文を無くせば、「非イベント型のウィジェット」となる。
        // ・注意。glfwSetTime(0.0)をGLFWループ内で実行するとImGuiが実行時エラーする

        // @ ImGuiのバッファを刷新
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();  // これ以降いつでも名前空間「ImGui::」の命令を呼び出せる

  
        // @ ウィンドウ：Hello ImGui!
        // ・表示領域の基本単位はウィンドウ
        // ・フロー
        //   1. SetNextWindowPosや、SetNextWindowSizeで形状を指定
        //   2. Begin( タイトル, 開閉フラグ, 属性フラグ ) でウィンドウを開始
        //   3. 各ウィジェットを定義
        //   4. End() でウィンドウを終了
        static const float GUI_MARGIN_MAIN = 30.0f;
        // ウィンドウの座標（次のBeginが対象）
        ImGui::SetNextWindowPos(ImVec2(guiIO.DisplaySize.x - GUI_MARGIN_MAIN, GUI_MARGIN_MAIN),  // 座標
                                ImGuiSetCond_Always,       // いつ設定するか
                                ImVec2(1.0f, 0.0f));       // 基準の位置（Pivot）
        // ImGui::SetNextWindowSize(ImVec2(100, 300), ImGuiSetCond_Once); // サイズは自動リサイズに任せる
        ImGui::Begin("Hello ImGui!", nullptr, flgGuiAttrMain);

        // メニューバー
        // ・BeginMenuBar ～ EndMenuBar --- メニューを表示
        // ・BeginMenu    ～ EndMenu    --- メニューの見出し
        // ・MenuItem                   --- 見出し内の項目
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

        // 日本語テキストを表示（UTF-8に対応）
        // ・予めImGuiのフォントマージモードをTrueにして、日本語フォントを追加登録しておく。
        // ・文字列リテラルが、内部でどう扱われるかはコンパイラ依存。
        // ・明示的に文字コードを指定するには、文字列リテラルの接頭辞にu8を付加。
        //   これで、仮引数の直接指定や、変数での運用が可能。
        // ・ちなみに、現開発環境（GCC、ソースファイルUTF-8）では、u8を付けなくても良い。
        // ・型について
        //   UTF-8はマルチバイト文字でありバイト数可変である。それに対し、
        //   ワイド文字（wchar_t）は、2バイト固定で扱いは楽であるが、UTF-8と互換性がない。
        //   よってリテラルの型は、const char* 又はchar型配列に格納のこと。
        //   注意。char*の場合は、constが無いとコンパイラがワーニングする。また、
        //   配列の場合は、配列の要素数と各文字の、先頭バイトや文字数は一致しない。
        ImGui::Text(u8"UTF-8対応。表示は文字列リテラルの接頭辞にu8を付加。");
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

        // コマンドボタン
        static int cnt = 0;
        if (ImGui::Button("Button")) cnt++;
        ImGui::SameLine();  // 改行しない
        ImGui::Text(" cnt: %d", cnt);

        // チェックボックス
        static bool isShowGui2 = false;
        ImGui::Checkbox("Checkbox (Show GUI2)", &isShowGui2);
        ImGui::NewLine();

        // カラーセレクター
        static float rgba[4] = {0.4f, 0.6f, 0.2f, 0.8f};
        ImGui::ColorEdit4("ColorEdit4", rgba);
        ImGui::NewLine();

        // ツリー
        // ・TreeNode --- 階層構造を作る（実行した時点で階層が1つ下る）
        // ・TreePop  --- 階層を1つ戻す
        ImGui::Separator();
        if (ImGui::TreeNode("TreeNode..TreePop")) {

            // ラジオボタン
            static int radioId = 1;
            ImGui::NewLine();
            ImGui::RadioButton("foo", &radioId, 0); ImGui::SameLine();
            ImGui::RadioButton("bar", &radioId, 1); ImGui::SameLine();
            ImGui::RadioButton("RadioButton", &radioId, 2);
            ImGui::NewLine();

            // コンボボックス
            static int comboId = 2;
            ImGui::Combo("Combo", &comboId, "aaa\0bbb\0ccc\0ddd\0eee\0");
            ImGui::NewLine();

            ImGui::TreePop();  // ツリーから出る（TreeNodeと1対1でなければ実行時エラー）
        }
        ImGui::Separator();
        ImGui::NewLine();

        // リストボックス
        static const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange"};
        static int listBoxId = 0;
        ImGui::ListBox("ListBox", &listBoxId, items, IM_ARRAYSIZE(items), 3);
        ImGui::NewLine();

        // セレクタブル
        // ・しくみ
        //   1. Columnsでカラム構造を定義
        //   2. Selectableで選択可能アイテムを置く
        //   3. NextColumnでカラムを1つ進める（自動で行送りなどもしてくれる）2.に戻る
        //   4. カラム数を元に戻す（以降に影響を及ぼさないため）
        static bool isSelected[8] = {};
        ImGui::Separator();
        ImGui::Columns(4, nullptr, false);  // カラムを使用（1セット4項目。右並び）

        for (int i = 0; i < 6; ++i) {
            char item[32];
            sprintf(item, "Selectable%d", i);
            ImGui::Selectable(item, &isSelected[i]);
            ImGui::NextColumn();  // カラムを進める（これが無いとSelectableが縦に並ぶ）
        }
        ImGui::Columns(1);  // カラムを初期化（以降に影響を及ぼさないため）
        ImGui::Separator();

        ImGui::End();


        // @ ウィンドウ：GUI2
        // 表示されるかどうかは下のブロックが実行されるかどうか。閉じる方法が3つ
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


        // @ ImGuiのバッファにレンダリング
        ImGui::EndFrame();  // 省略可能（Render()内部で呼ばれるため）
        ImGui::Render();



        // @@ ドロー
        static int w, h;
        glfwGetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // ここにメインのドロー処理を記述...

        // @ ImGuiをドロー（最前面にするため最後に描画）
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());



        // @@ 後処理
        // printf("Time(ms):%d\n", module_gl::getElapseTime());  // 1ループの純粋な処理時間
        module_gl::doWait(WAIT_TIME);
        glfwSwapBuffers(window);
    }



    // @@@ 終了処理
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    module_gl::teardownWindow();


    return 0;
}
