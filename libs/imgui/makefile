#################  Makefileの使い方  ####################
# ・このMakefileについて
#   下位ディレクトリなどに設置し、ソースを.oにコンパイル。
#   メインとなるMakefileより連携して使用するか、単独で実行。
########################################################


# マクロ   ### 記入項目 ###
OBJS   := imgui_impl_glfw.o    imgui_impl_opengl2.o
OBJS   += imgui.o    imgui_draw.o    imgui_widgets.o
COMP   := g++
CFLAGS :=


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
