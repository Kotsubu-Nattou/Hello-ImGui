#################  Makefileの使い方  ####################
# 主に記述は ### 記入項目 ### の内容。
# PROG   --- Windows環境下では、必ず「.exe」を付けること
# RESRC  --- リソースファイルを使用するなら「ファイル名.o」
# CHILD_ --- ディレクトリを分けたソース等をmakeするときに使う
# CFLAFS --- コンパイルオプションを指定
# .oファイルが増えたり.hファイルの依存関係が変更になった場合、
# 「ヘッダファイルの依存関係」の項目で、個別に指定する。
########################################################


# マクロ   ### 記入項目 ###
PROG        = a.exe
RESRC       =
CHILD_DIR   = imgui/
CHILD_OBJS  = imgui_impl_glfw.o    imgui_impl_opengl2.o
CHILD_OBJS += imgui.o    imgui_draw.o    imgui_widgets.o
OBJS        = a.o
OBJS       += $(addprefix $(CHILD_DIR), $(CHILD_OBJS))
LIBS        = -lopengl32 -lglu32 -lglew32 -lglfw3dll
COMP        = g++
CFLAGS      = -g -Wall


# デフォルトターゲット（先頭にあるのでデフォルトで実行）
.PHONY: all
#all: makeChild $(PROG)
all: $(PROG)


# ターゲット：リンカ
$(PROG): $(OBJS)
	$(COMP) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)


# ターゲット：リソースファイルのコンパイル
$(RESRC):
	windres $*.rc -o $@


# ターゲット：異なるディレクトリのソース等をmake
.PHONY: makeChild
makeChild:
	cd $(CHILD_DIR)  &&  $(MAKE)


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
