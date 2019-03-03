#################  Makefile�̎g����  ####################
# ��ɋL�q�� ### �L������ ### �̓��e�B
# PROG   --- Windows�����ł́A�K���u.exe�v��t���邱��
# RESRC  --- ���\�[�X�t�@�C�����g�p����Ȃ�u�t�@�C����.o�v
# CHILD_ --- �f�B���N�g���𕪂����\�[�X����make����Ƃ��Ɏg��
# CFLAFS --- �R���p�C���I�v�V�������w��
# .o�t�@�C������������.h�t�@�C���̈ˑ��֌W���ύX�ɂȂ����ꍇ�A
# �u�w�b�_�t�@�C���̈ˑ��֌W�v�̍��ڂŁA�ʂɎw�肷��B
########################################################


# �}�N��   ### �L������ ###
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


# �f�t�H���g�^�[�Q�b�g�i�擪�ɂ���̂Ńf�t�H���g�Ŏ��s�j
.PHONY: all
#all: makeChild $(PROG)
all: $(PROG)


# �^�[�Q�b�g�F�����J
$(PROG): $(OBJS)
	$(COMP) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)


# �^�[�Q�b�g�F���\�[�X�t�@�C���̃R���p�C��
$(RESRC):
	windres $*.rc -o $@


# �^�[�Q�b�g�F�قȂ�f�B���N�g���̃\�[�X����make
.PHONY: makeChild
makeChild:
	cd $(CHILD_DIR)  &&  $(MAKE)


# �^�[�Q�b�g�F���ԃt�@�C���̍폜
.PHONY: clean
clean:
	-rm *.o


# �T�t�B�b�N�X���[���i.o���R���p�C������Ƃ��̓R�`���j
.c.o:
	$(COMP) $(CFLAGS) -c $<

.cpp.o:
	$(COMP) $(CFLAGS) -c $<


# �w�b�_�t�@�C���̈ˑ��֌W   ### �L������ ###
#main.o: sub.h
