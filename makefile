#################  Makefileの使い方  ####################
# 主に記述は ### 記入項目 ### の内容。
# PROG   --- Windows環境下では、必ず「.exe」を付けること
# RESRC  --- リソースファイルを使用するなら「ファイル名.o」
# SUB_*  --- 下位ディレクトリなどのオブジェクトファイル
# CFLAFS --- コンパイルオプションを指定
# .oファイルが増えたり.hファイルの依存関係が変更になった場合、
# 「ヘッダファイルの依存関係」の項目で、個別に指定する。
########################################################


# マクロ   ### 記入項目 ###
PROG     := a.exe
RESRC    :=
SUB_DIR  := libs/imgui/
SUB_OBJS := imgui_impl_glfw.o    imgui_impl_opengl2.o
SUB_OBJS += imgui.o    imgui_draw.o    imgui_widgets.o
OBJS     := main.o  libs/module_gl/module_gl.o
OBJS     += $(addprefix $(SUB_DIR), $(SUB_OBJS))
LIBS     := -lopengl32 -lglu32 -lglew32 -lglfw3dll
COMP     := g++
CFLAGS   := -g -Wall


# デフォルトターゲット（先頭にあるのでデフォルトで実行）
#.PHONY: all
#all: $(PROG)


# ターゲット：リンカ
$(PROG): $(OBJS)
	$(COMP) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)


# ターゲット：リソースファイルのコンパイル
$(RESRC):
	windres $*.rc  -o $@


# ターゲット：中間ファイルの削除
.PHONY: clean
clean:
	-rm *.o


# サフィックスルール（.oをコンパイルするときはコチラ）
# -o からの文は、ソース自身のディレクトリに出力させるため（無いとカレントに出力）
.c.o:
	$(COMP) $(CFLAGS)  -c $<  -o $(basename $<).o

.cpp.o:
	$(COMP) $(CFLAGS)  -c $<  -o $(basename $<).o


# ヘッダファイルの依存関係   ### 記入項目 ###
main.o                    : libs/module_gl/module_gl.h
libs/module_gl/module_gl.o: libs/module_gl/module_gl.h
