#################  Makefile�̎g����  ####################
# ��ɋL�q�� ### �L������ ### �̓��e�B
# PROG   --- Windows�����ł́A�K���u.exe�v��t���邱��
# RESRC  --- ���\�[�X�t�@�C�����g�p����Ȃ�u�t�@�C����.o�v
# SUB_*  --- ���ʃf�B���N�g���Ȃǂ̃I�u�W�F�N�g�t�@�C��
# CFLAFS --- �R���p�C���I�v�V�������w��
# .o�t�@�C������������.h�t�@�C���̈ˑ��֌W���ύX�ɂȂ����ꍇ�A
# �u�w�b�_�t�@�C���̈ˑ��֌W�v�̍��ڂŁA�ʂɎw�肷��B
########################################################


# �}�N��   ### �L������ ###
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


# �f�t�H���g�^�[�Q�b�g�i�擪�ɂ���̂Ńf�t�H���g�Ŏ��s�j
#.PHONY: all
#all: $(PROG)


# �^�[�Q�b�g�F�����J
$(PROG): $(OBJS)
	$(COMP) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)


# �^�[�Q�b�g�F���\�[�X�t�@�C���̃R���p�C��
$(RESRC):
	windres $*.rc  -o $@


# �^�[�Q�b�g�F���ԃt�@�C���̍폜
.PHONY: clean
clean:
	-rm *.o


# �T�t�B�b�N�X���[���i.o���R���p�C������Ƃ��̓R�`���j
# -o ����̕��́A�\�[�X���g�̃f�B���N�g���ɏo�͂����邽�߁i�����ƃJ�����g�ɏo�́j
.c.o:
	$(COMP) $(CFLAGS)  -c $<  -o $(basename $<).o

.cpp.o:
	$(COMP) $(CFLAGS)  -c $<  -o $(basename $<).o


# �w�b�_�t�@�C���̈ˑ��֌W   ### �L������ ###
main.o                    : libs/module_gl/module_gl.h
libs/module_gl/module_gl.o: libs/module_gl/module_gl.h
