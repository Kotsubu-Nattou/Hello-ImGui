#################  Makefileの使い方  ####################
# このMakefileは、メインのMakefileと違うディレクトリにある、
# 「未コンパイルのライブラリ」等をコンパイルし、メインの
# Makefileでリンクさせるために作成。
# 使い方は、「親」Makefileから呼び出して使用する。又は、
# ライブラリが更新したときに、直接実行する。
########################################################


# マクロ   ### 記入項目 ###
OBJS    = imgui_impl_glfw.o    imgui_impl_opengl2.o
OBJS   += imgui.o    imgui_draw.o    imgui_widgets.o
COMP    = g++
CFLAGS  = -g -Wall


# デフォルトターゲット（先頭にあるのでデフォルトで実行）
.PHONY: CompileObjs
CompileObjs: $(OBJS)


# ターゲット：中間ファイルの削除
.PHONY: clean
clean:
	-rm *.o


# サフィックスルール（.oをコンパイルするときはコチラ）
.c.o:
	$(COMP) $(CFLAGS) -c $<

.cpp.o:
	$(COMP) $(CFLAGS) -c $<


# ヘッダファイルの依存関係   ### 記入項目 ###
#main.o: sub.h
