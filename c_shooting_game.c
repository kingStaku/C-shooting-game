#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h> // �����\���p
#include<time.h>
#include "glut.h"

// �L�[�̏�Ԃ�\���O���[�o���ϐ�(0: ������Ă��Ȃ��C1: ������Ă���)
int keyUp = 0, keyDown = 0, keyLeft = 0, keyRight = 0;

int count = 50;
int x = 0;
int y = 0;
int VSappear = 0;
int GameStop = 0;
int title = 0;


// �v���C���[�̏����ݒ�
double posPlayer[2] = {0.0, -0.8};
GLfloat colPlayer[3];
int PlayerLife = 5;
int PlayerDamageControl = 0;
double sizePlayer = 0.1;

// �G�̏����ݒ�
double posEnemy[9][2] = { {1.0, 1.0}, {1.0, 0.8}, {-0.6, 0.6}, {0.8, 0.8}, {0.8, 0.0}, {0.8, 0.8}, {-0.8, 0.8}, {0.8, 0.8}, {-0.8, 0.8} };
GLfloat colEnemy01[3];
int kindEnemy = 0;
double size = 0.15;
int appearEnemy01 = 0;
int appearEnemy02 = 0;
int appearEnemy03 = 0;
int appearEnemy04 = 0;
int appearEnemy05 = 0;
int appearEnemy06 = 0;
int appearEnemy07 = 0;
int appearEnemy08 = 0;
int Enemy08count = 0;
int appearEnemy09 = 0;
int BossMove = 0;
int BossCount = 0;
int EnemyDeath = 0;
int EnemyHP = 5;
int EnemyDamageControl = 0;

// �e�e�̏����ݒ�
double posBallet[2];
int isCrushingBallet = 0;

// �擾�P��
int credit = 0;


// ����L�[�������ꂽ�ۂ̏������s���֐����w��
void checkSpecialKeyPressed(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP : keyUp = 1; break;
	case GLUT_KEY_DOWN : keyDown = 1; break;
	case GLUT_KEY_LEFT : keyLeft = 1; break;
	case GLUT_KEY_RIGHT : keyRight = 1; break;
	}
}

// ����L�[���߂��ꂽ�ۂ̏������s���֐����w��
void checkSpecialKeyReleased(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP : keyUp = 0; break;
	case GLUT_KEY_DOWN : keyDown = 0; break;
	case GLUT_KEY_LEFT : keyLeft = 0; break;
	case GLUT_KEY_RIGHT : keyRight = 0; break;
	}
}

void drawCircle(double position[2], double radius, int startAngle, int endAngle){
	int i;
	glBegin(GL_POLYGON); // �܂���̕`��J�n
	for(i=startAngle; i<=endAngle; i += 360.0 / 36){
		glVertex2d(
			position[0] + radius * cos(3.14 * i / 180),
			position[1] + radius * sin(3.14 * i / 180)
			);
	}
	glEnd();
}

void drawCircle1(double pos_x, double pos_y, double radius, int starAngle, int endAngle) {
	int i;
	glBegin(GL_POLYGON); //�܂���̕`��J�n
	for(i=starAngle; i<=endAngle; i+=360.0/36){
		glVertex2d(
			pos_x + radius * cos(3.14 * i/180), //������x���W
			pos_y + radius * sin(3.14 * i/180) //������y���W
			);
	}
	glEnd(); //�`��I��
}

void drawCircle2(double pos_x, double pos_y, double radius, int starAngle, int endAngle) {
	int i;
	glBegin(GL_LINE_LOOP); //�܂���̕`��J�n
	for(i=starAngle; i<=endAngle; i+=360.0/36){
		glVertex2d(
			pos_x + radius * cos(3.14 * i/180), //������x���W
			pos_y + radius * sin(3.14 * i/180) //������y���W
			);
	}
	glEnd(); //�`��I��
}

// �G1(���v�w)�̓���
double Enemy01move(double pos_x){
	double pos_y;
	pos_y = 0.5 * pow(pos_x, 2);
	return pos_y;
}

// �G4(���_����H)����

// �G5(�v���O���~���O����)�̓���
double Enemy05move01(double pos_x){
	double pos_y, pos_xx;
	pos_xx = pow(pos_x, 2);
	pos_y = sqrt( 0.64 - pos_xx );
	return pos_y;
}

double Enemy05move02(double pos_x){
	double pos_y, pos_xx;
	pos_xx = pow(pos_x, 2);
	pos_y = -sqrt( 0.64 - pos_xx );
	return pos_y;
}


// �v���C���[(����҂�)
void drawPlayer(double posGiven[2]){
	
	// ��������F����
	glColor3d(0.7, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0], posGiven[1] + sizePlayer * 2);
	glVertex2d(posGiven[0] - sizePlayer * 0.5, posGiven[1] + sizePlayer);
	glVertex2d(posGiven[0] + sizePlayer * 0.5, posGiven[1] + sizePlayer);
	glEnd();
	// �c����
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0], posGiven[1] + sizePlayer * 2);
	glVertex2d(posGiven[0] - sizePlayer * 0.25, posGiven[1] + sizePlayer * 1.5);
	glVertex2d(posGiven[0] + sizePlayer * 0.25, posGiven[1] + sizePlayer * 1.5);
	glEnd();
	// ��蕔���̗֊s
	glColor3d(0.5, 0.3, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] + sizePlayer * 2);
	glVertex2d(posGiven[0] - sizePlayer * 0.5, posGiven[1] + sizePlayer);
	glVertex2d(posGiven[0] + sizePlayer * 0.5, posGiven[1] + sizePlayer);
	glEnd();
	// ������
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - sizePlayer * 0.5, posGiven[1] + sizePlayer);
	glVertex2d(posGiven[0] - sizePlayer * 0.5, posGiven[1] - sizePlayer * 2);
	glVertex2d(posGiven[0] + sizePlayer * 0.5, posGiven[1] - sizePlayer * 2);
	glVertex2d(posGiven[0] + sizePlayer * 0.5, posGiven[1] + sizePlayer);
	glEnd();
	// �͗l
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - sizePlayer * 0.2, posGiven[1] + sizePlayer);
	glVertex2d(posGiven[0] - sizePlayer * 0.2, posGiven[1] - sizePlayer * 2);
	glEnd();
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + sizePlayer * 0.2, posGiven[1] + sizePlayer);
	glVertex2d(posGiven[0] + sizePlayer * 0.2, posGiven[1] - sizePlayer * 2);
	glEnd();
}


// �e�e
void drawBallet(double posGiven[2]){
	glColor3d(1.0, 0.0, 0.0);
	drawCircle(posGiven, 0.02, 0, 360);
}

// �G1(���v�w)
void drawStatistics(double posGiven[2]){
	size = 0.15;
	// ��ԍ�
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size      , posGiven[1] + size);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] + size);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] - size);
	glVertex2d(posGiven[0] - size      , posGiven[1] - size);
	glEnd();
	// �������Ԗ�
	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] - size);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] - size);
	glEnd();
	// �^��
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] + size);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] + size);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] - size);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] - size);
	glEnd();
	// �E�����Ԗ�
	glColor3d(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] + size * 1/3);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] + size * 1/3);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] - size);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] - size);
	glEnd();
	// ��ԉE
	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] + size      , posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] + size      , posGiven[1] - size);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] - size);
	glEnd();
	// ��ԍ��֊s
	glColor3d(0.5, 0.3, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size      , posGiven[1] + size);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] + size);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] - size);
	glVertex2d(posGiven[0] - size      , posGiven[1] - size);
	glEnd();
	// �������Ԗڗ֊s
	glColor3d(0.5, 0.3, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] - size);
	glVertex2d(posGiven[0] - size * 3/5, posGiven[1] - size);
	glEnd();
	// �^�񒆗֊s
	glColor3d(0.5, 0.3, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] + size);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] + size);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] - size);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] - size);
	glEnd();
	// �E�����Ԗڗ֊s
	glColor3d(0.5, 0.3, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] + size * 1/3);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] + size * 1/3);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] - size);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] - size);
	glEnd();
	// ��ԉE�֊s
	glColor3d(0.5, 0.3, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] + size      , posGiven[1] + size * 2/3);
	glVertex2d(posGiven[0] + size      , posGiven[1] - size);
	glVertex2d(posGiven[0] + size * 3/5, posGiven[1] - size);
	glEnd();
}

// �G2(�p��)
void drawEnglish(double posGiven[2]){
	double size = 0.15;
	// �^�񒆉���
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size, posGiven[1]);
	glVertex2d(posGiven[0] + size, posGiven[1]);
	glEnd();
	// ����c��
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size, posGiven[1]);
	glVertex2d(posGiven[0] - size, posGiven[1] + size);
	glEnd();
	// �^�񒆏�c��
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1]);
	glVertex2d(posGiven[0], posGiven[1] + size);
	glEnd();
	// �E��c��
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size, posGiven[1]);
	glVertex2d(posGiven[0] + size, posGiven[1] + size);
	glEnd();
	// A���΂ߐ�
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1]);
	glVertex2d(posGiven[0] - size, posGiven[1] - size);
	glEnd();
	// A�E�΂ߐ�
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1]);
	glVertex2d(posGiven[0] + size, posGiven[1] - size);
	glEnd();
	// A�̎O�p����
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0], posGiven[1]);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] - size * 1/2);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] - size * 1/2);
	glEnd();

}

// �G3(�d�C��H�w)
void drawEC(double posGiven[2]){
	size = 0.15;
	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] + size      , posGiven[1] + size );
	glVertex2d(posGiven[0] - size * 4/5, posGiven[1] - size * 1/5);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] - size * 1/5);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] + size * 1/5);
	glEnd();

	glColor3d(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 1/5, posGiven[1] - size * 1/5);
	glVertex2d(posGiven[0] - size      , posGiven[1] - size);
	glVertex2d(posGiven[0] + size * 4/5, posGiven[1] + size * 1/5);
	glVertex2d(posGiven[0] + size * 1/5, posGiven[1] + size * 1/5);
	glEnd();
}

// �G4(���_����H)
void drawILC(double posGiven[2]){
	size = 0.15;
	// ��ڂ̎l�p
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1] + size * 1/2);
	glVertex2d(posGiven[0] + size * 1/3, posGiven[1] + size * 1/2);
	glVertex2d(posGiven[0] + size * 1/3, posGiven[1]);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1]);
	glEnd();
	// ��ڂ̎l�p
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1] - size * 1/3);
	glVertex2d(posGiven[0] + size * 1/3, posGiven[1] - size * 1/3);
	glVertex2d(posGiven[0] + size * 1/3, posGiven[1] - size * 5/6);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1] - size * 5/6);
	glEnd();

	// �R�[�hA-1
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 1/3, posGiven[1] + size * 1/4);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] + size * 1/4);
	glEnd();
	// �R�[�hA-2
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] + size * 1/4);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] + size * 3/4);
	glEnd();
	// �R�[�hA-3
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] + size * 3/4);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] + size * 3/4);
	glEnd();
	// �R�[�hA-4
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] + size * 3/4);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] - size);
	glEnd();
	// �R�[�hA-5
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size      , posGiven[1] + size * 1/4);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1] + size * 1/4);
	glEnd();


	// �R�[�hB-1
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 1/3, posGiven[1] - size * 7/12);
	glVertex2d(posGiven[0] + size      , posGiven[1] - size * 7/12);
	glEnd();
	// �R�[�hB-2
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size      , posGiven[1] - size * 7/12);
	glVertex2d(posGiven[0] + size      , posGiven[1] + size);
	glEnd();
	// �R�[�hB-3
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size      , posGiven[1] + size);
	glVertex2d(posGiven[0] - size      , posGiven[1] + size);
	glEnd();
	// �R�[�hB-4
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size      , posGiven[1] + size);
	glVertex2d(posGiven[0] - size      , posGiven[1] - size);
	glEnd();
	// �R�[�hB-5
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] - size * 7/12);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1] - size * 7/12);
	glEnd();
}

// �G5(�v���O���~���O����)
void drawPL(double posGiven[2]){
	size = 0.15;
	// c�O
	glColor3d(0.0, 1.0, 0.0);
	drawCircle1(posGiven[0], posGiven[1], size, 135, 405);
	// c��
	glColor3d(0.0, 0.0, 0.0);
	drawCircle1(posGiven[0], posGiven[1], size * 0.7, 135, 405);
	// ������
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0], posGiven[1]);
	glVertex2d(posGiven[0] - size, posGiven[1] + size);
	glVertex2d(posGiven[0] + size, posGiven[1] + size);
	glEnd();
	// +����
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 0.15, posGiven[1] + size);
	glVertex2d(posGiven[0] + size * 0.15, posGiven[1] + size);
	glVertex2d(posGiven[0] + size * 0.15, posGiven[1] - size * 0.7);
	glVertex2d(posGiven[0] - size * 0.15, posGiven[1] - size * 0.7);
	glEnd();
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] - size * 0.15);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] - size * 0.15);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] - size * 0.4);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] - size * 0.4);
	glEnd();
	glColor3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] + size * 0.15);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] + size * 0.15);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] + size * 0.4);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] + size * 0.4);
	glEnd();
}

// �G6(���l���)
void drawNA(double posGiven[2]){
	size = 0.15;
	// �O�֊s
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size, posGiven[1] + size);
	glVertex2d(posGiven[0] + size, posGiven[1] + size);
	glVertex2d(posGiven[0] + size, posGiven[1] - size);
	glVertex2d(posGiven[0] - size, posGiven[1] - size);
	glEnd();
	// �{��
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size, posGiven[1] + size);
	glVertex2d(posGiven[0] + size, posGiven[1] + size);
	glVertex2d(posGiven[0] + size, posGiven[1] - size);
	glVertex2d(posGiven[0] - size, posGiven[1] - size);
	glEnd();
	// �c��
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1] + size);
	glVertex2d(posGiven[0] - size * 1/3, posGiven[1] - size);
	glEnd();
	// ����
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size, posGiven[1] + size * 1/3);
	glVertex2d(posGiven[0] + size, posGiven[1] + size * 1/3);
	glEnd();
	// �܂鍶��
	glColor3d(1.0, 0.0, 0.0);
	drawCircle1(posGiven[0], posGiven[1], size * 0.25, 0, 360);
	// �܂鍶��
	glColor3d(1.0, 0.0, 0.0);
	drawCircle1(posGiven[0], posGiven[1] - size * 2/3, size * 0.25, 0, 360);
	// �܂�E��
	glColor3d(1.0, 0.0, 0.0);
	drawCircle1(posGiven[0] + size * 2/3, posGiven[1], size * 0.25, 0, 360);
	// �܂�E��
	glColor3d(1.0, 0.0, 0.0);
	drawCircle1(posGiven[0] + size * 2/3, posGiven[1] - size * 2/3, size * 0.25, 0, 360);

}

// �G7(����)
void drawExperiment(double posGiven[2]){
	size = 0.15;
	// �~
	glColor3d(1.0, 0.0, 0.0);
	drawCircle2(posGiven[0], posGiven[1], size, 0, 360);
	// �~���̉���
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] - size * 1/3);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] - size * 1/3);
	glEnd();
	// �~����V����
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] - size * 1/3);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] + size * 1/2);
	glEnd();
	// �~����V���E
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] - size * 1/3);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] + size * 1/2);
	glEnd();
	// ���ɐL�т钼��
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] - size * 1/3);
	glVertex2d(posGiven[0], posGiven[1] - size * 1.2);
	glEnd();
	// �~�O������
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 1.2, posGiven[1] + size * 1/2);
	glVertex2d(posGiven[0] - size * 1/2, posGiven[1] + size * 1/2);
	glEnd();
	// �~�O�����E
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 1.2, posGiven[1] + size * 1/2);
	glVertex2d(posGiven[0] + size * 1/2, posGiven[1] + size * 1/2);
	glEnd();


}

// �G8(��񐔊w)
void drawIM(double posGiven[2]){
	double i;
	size = 0.15;

	// �R�[�h����
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] - size * 3/4);
	glVertex2d(posGiven[0] - size * 0.5, posGiven[1] );
	glEnd();
	// �R�[�h���^��
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] - size * 3/4);
	glVertex2d(posGiven[0], posGiven[1] );
	glEnd();
	// �R�[�h���E
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] - size * 3/4);
	glVertex2d(posGiven[0] + size * 0.5, posGiven[1] );
	glEnd();
	// �R�[�h�㍶1
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 0.5, posGiven[1] );
	glVertex2d(posGiven[0] - size * 0.75, posGiven[1] + size * 3/4);
	glEnd();
	// �R�[�h�㍶2
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 0.5, posGiven[1] );
	glVertex2d(posGiven[0] - size * 0.25, posGiven[1] + size * 3/4);
	glEnd();
	// �R�[�h��^��1
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] );
	glVertex2d(posGiven[0] - size * 0.25, posGiven[1] + size * 3/4);
	glEnd();
	// �R�[�h��^��2
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] );
	glVertex2d(posGiven[0] + size * 0.25, posGiven[1] + size * 3/4);
	glEnd();
	// �R�[�h��E1
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 0.5, posGiven[1] );
	glVertex2d(posGiven[0] + size * 0.25, posGiven[1] + size * 3/4);
	glEnd();
	// �R�[�h��E2
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 0.5, posGiven[1] );
	glVertex2d(posGiven[0] + size * 0.75, posGiven[1] + size * 3/4);
	glEnd();

	// ��4�́�
	for(i = -0.75; i < 1; i += 0.5){
		glColor3d(0.0, 0.0, 1.0);
		drawCircle1(posGiven[0] + size * i, posGiven[1] + size * 3/4, size * 0.2, 0, 360);
	}
	// �^��3�́�
	for(i = -0.5; i < 0.6; i += 0.5){
		glColor3d(0.0, 0.0, 1.0);
		drawCircle1(posGiven[0] + size * i, posGiven[1], size * 0.2, 0, 360);
	}
	// ��1�́�
	glColor3d(0.0, 0.0, 1.0);
	drawCircle1(posGiven[0], posGiven[1] - size * 3/4, size * 0.2, 0, 360);

	


}

// �G9(���p���w)
void drawAM(double posGiven[2]){
	size = 0.3;
	//��
	glColor3d(0.0, 0.0, 0.0);
	drawCircle1(posGiven[0], posGiven[1], size * 1.0, 0, 360);
	//��̗֊s��
	glColor3d(1.0, 1.0, 1.0);
	drawCircle2(posGiven[0], posGiven[1], size * 1.0, 0, 360);
	//����
	glColor3d(1.0, 1.0, 1.0);
	drawCircle1(posGiven[0] - size * 0.3, posGiven[1] + size * 0.02, size * 0.1, 0, 360);
	//�E��
	glColor3d(1.0, 1.0, 1.0);
	drawCircle1(posGiven[0] + size * 0.3, posGiven[1] + size * 0.02, size * 0.1, 0, 360);
	//�@
	glColor3d(0.0, 0.0, 0.0);
	drawCircle1(posGiven[0], posGiven[1] - size * 0.25, size * 0.04, 0, 360);
	//�@�����
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0], posGiven[1] - size * 0.2);
	glVertex2d(posGiven[0], posGiven[1] - size * 0.4);
	glEnd();
	//����
	glColor3d(0.0, 0.0, 0.0);
	drawCircle2(posGiven[0] - size * 0.1, posGiven[1] - size * 0.4, size * 0.1, 180, 360);
	//���E
	glColor3d(0.0, 0.0, 0.0);
	drawCircle2(posGiven[0] + size * 0.1, posGiven[1] - size * 0.4, size * 0.1, 180, 360);
	//���j
	glColor3d(1.0, 0.4, 0.4);
	drawCircle1(posGiven[0] - size * 0.5, posGiven[1] - size * 0.3, size * 0.1, 0, 360);
	//�E�j
	glColor3d(1.0, 0.4, 0.4);
	drawCircle1(posGiven[0] + size * 0.5, posGiven[1] - size * 0.3, size * 0.1, 0, 360);
	//���㎨�O
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 0.8, posGiven[1] + size * 0.6);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] + size * 1.0);
	glVertex2d(posGiven[0] - size * 0.4, posGiven[1] + size * 0.91);
	glEnd();
	//���㎨�O�֊s
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 0.8, posGiven[1] + size * 0.6);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] + size * 1.0);
	glVertex2d(posGiven[0] - size * 0.4, posGiven[1] + size * 0.91);
	glEnd();
	//���㎨��
	glColor3d(1.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 0.75, posGiven[1] + size * 0.61);
	glVertex2d(posGiven[0] - size * 0.67, posGiven[1] + size * 0.95);
	glVertex2d(posGiven[0] - size * 0.45, posGiven[1] + size * 0.86);
	glEnd();
	//�E�㎨�O
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] + size * 0.8, posGiven[1] + size * 0.6);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] + size * 1.0);
	glVertex2d(posGiven[0] + size * 0.4, posGiven[1] + size * 0.91);
	glEnd();
	//�E�㎨�O�֊s
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 0.8, posGiven[1] + size * 0.6);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] + size * 1.0);
	glVertex2d(posGiven[0] + size * 0.4, posGiven[1] + size * 0.91);
	glEnd();
	//�E�㎨��
	glColor3d(1.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] + size * 0.75, posGiven[1] + size * 0.61);
	glVertex2d(posGiven[0] + size * 0.67, posGiven[1] + size * 0.95);
	glVertex2d(posGiven[0] + size * 0.45, posGiven[1] + size * 0.86);
	glEnd();

	//�������O
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 0.8, posGiven[1] - size * 0.6);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] - size * 1.0);
	glVertex2d(posGiven[0] - size * 0.4, posGiven[1] - size * 0.91);
	glEnd();
	//�������O�֊s
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] - size * 0.8, posGiven[1] - size * 0.6);
	glVertex2d(posGiven[0] - size * 0.7, posGiven[1] - size * 1.0);
	glVertex2d(posGiven[0] - size * 0.4, posGiven[1] - size * 0.91);
	glEnd();
	//��������
	glColor3d(1.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] - size * 0.75, posGiven[1] - size * 0.61);
	glVertex2d(posGiven[0] - size * 0.67, posGiven[1] - size * 0.95);
	glVertex2d(posGiven[0] - size * 0.45, posGiven[1] - size * 0.86);
	glEnd();
	//�E�����O
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] + size * 0.8, posGiven[1] - size * 0.6);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] - size * 1.0);
	glVertex2d(posGiven[0] + size * 0.4, posGiven[1] - size * 0.91);
	glEnd();
	//�E�����O�֊s
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(posGiven[0] + size * 0.8, posGiven[1] - size * 0.6);
	glVertex2d(posGiven[0] + size * 0.7, posGiven[1] - size * 1.0);
	glVertex2d(posGiven[0] + size * 0.4, posGiven[1] - size * 0.91);
	glEnd();
	//�E������
	glColor3d(1.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2d(posGiven[0] + size * 0.75, posGiven[1] - size * 0.61);
	glVertex2d(posGiven[0] + size * 0.67, posGiven[1] - size * 0.95);
	glVertex2d(posGiven[0] + size * 0.45, posGiven[1] - size * 0.86);
	glEnd();

}



void display(void){
	int i;
	char str[50];

	glClear(GL_COLOR_BUFFER_BIT); // �o�b�t�@���N���A


	if(kindEnemy == 1 && x == 1){
		drawStatistics(posEnemy[0]);
	}
	else if(kindEnemy == 2 && x == 1){
		drawEnglish(posEnemy[1]);
	}
	else if(kindEnemy == 3 && x == 1){
		drawEC(posEnemy[2]);
	}
	else if(kindEnemy == 4 && x == 1){
		drawILC(posEnemy[3]);
	}
	else if(kindEnemy == 5 && x == 1){
		drawPL(posEnemy[4]);
	}
	else if(kindEnemy == 6 && x == 1){
		drawNA(posEnemy[5]);
	}
	else if(kindEnemy == 7 && x == 1){
		drawExperiment(posEnemy[6]);
	}
	else if(kindEnemy == 8 && x == 1){
		drawIM(posEnemy[7]);
	}
	else if(kindEnemy == 9 && x == 1){
		drawAM(posEnemy[8]);
	}

	if(x == 1){
		sprintf(str, "EnemyLife  : %01d", EnemyHP);
		glColor3f(0.6, 0.6, 0.6);
		glRasterPos2f(-0.6, 0.8);
		for(i=0; i<strlen(str); i++){
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
		}
	}

	if(title > 0 && title <= 25){
		sprintf(str, "-Avalon-");
		glColor3f(1.0, 0.3, 0.3);
		glRasterPos2f(-0.15, 0.0);
		for(i=0; i<strlen(str); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
	}

	if(title > 25 && title < 50){
		sprintf(str, "Player is moved by derection key !");
		glColor3f(1.0, 0.3, 0.3);
		glRasterPos2f(-0.6, 0.0);
		for(i=0; i<strlen(str); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
	}


	drawPlayer(posPlayer);
	drawBallet(posBallet);



	sprintf(str, "Credit : %03d   PlayerLife : %01d", credit, PlayerLife);
	glColor3f(0.6, 0.6, 0.6);
	glRasterPos2f(-1.0, 0.9);
	for(i=0; i<strlen(str); i++){
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
	}

	if(y >= 1 && y <= 25){
		if(kindEnemy == 1 && VSappear == 0){
			sprintf(str, "VS Statistics");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 2 && VSappear == 0){
			sprintf(str, "VS English");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 3 && VSappear == 0){
			sprintf(str, "VS Electric Circuit");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 4 && VSappear == 0){
			sprintf(str, "VS Information Logic Circuit");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 5 && VSappear == 0){
			sprintf(str, "VS Programing Language");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 6 && VSappear == 0){
			sprintf(str, "VS Numerical Analysis");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 7 && VSappear == 0){
			sprintf(str, "VS Experiment");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 8 && VSappear == 0){
			sprintf(str, "VS Information Mathematics");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}
		else if(kindEnemy == 9 && VSappear == 0){
			sprintf(str, "VS Applied Mathematics");
			glColor3f(0.6, 0.6, 0.6);
			glRasterPos2i(-1.0, 0.0);
			for(i=0; i<strlen(str); i++){
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
			}
		}

		if(y == 25){
			VSappear = 1;
		}
		EnemyDeath = 0;
	}

	if(credit == 20){
		sprintf(str, "Game Clear");
		glColor3f(0.4, 1.0, 0.4);
		glRasterPos2i(0.0, 0.0);
		for(i=0; i<strlen(str); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
		GameStop = 1;
	}

	if(PlayerLife == 0){
		sprintf(str, "Game Over");
		glColor3f(1.0, 0.4, 0.4);
		glRasterPos2i(0.0, 0.0);
		for(i=0; i<strlen(str); i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		}
		GameStop = 1;
	}

	glutSwapBuffers(); // �_�u���o�b�t�@������

}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 1.0); // �w�i�F���w��
}

void updatePos(int value){

	if(GameStop == 0){
		count++;
		if(kindEnemy == 0){
			title++;
		}

		if(count % 100 == 0){
			x=1;
			y=1;
			if(kindEnemy == 0){
				kindEnemy++;
				title = 0;
			}
		}

		if(x == 1){
			// �G1(���v�w)�̓���
			if(kindEnemy == 1){
				if(appearEnemy01 == 0){
					posEnemy[0][0] -= 0.075;
					posEnemy[0][1] = Enemy01move(posEnemy[0][0]);
					if(posEnemy[0][0] < -1.0){
						appearEnemy01 = 1;
						posEnemy[0][0] = -1.0;
					}
				}
				else if(appearEnemy01 == 1){
					posEnemy[0][0] += 0.075;
					posEnemy[0][1] = Enemy01move(posEnemy[0][0]);
					if(posEnemy[0][0] > 1.0){
						appearEnemy01 = 0;
						posEnemy[0][0] = 1.0;
					}
				}
			}
			// �G2(�p��)�̓���
			else if(kindEnemy == 2){
				if(appearEnemy02 == 0){
					posEnemy[1][0] -= 0.1;
					if(posEnemy[1][0] < -0.8){
						posEnemy[1][0] = -0.8;
						appearEnemy02=1;
					}
				}
				else if(appearEnemy02 == 1){
					posEnemy[1][1] -= 0.1;
					if(posEnemy[1][1] < -0.8){
						posEnemy[1][1] = -0.8;
						appearEnemy02=2;
					}
				}
				else if(appearEnemy02 == 2){
					posEnemy[1][0] += 0.1;
					if(posEnemy[1][0] > 0.8){
						posEnemy[1][0] = 0.8;
						appearEnemy02++;
					}
				}
				else if(appearEnemy02 == 3){
					posEnemy[1][1] += 0.1;
					if(posEnemy[1][1] > 0.8){
						posEnemy[1][1] = 0.8;
						appearEnemy02 = 0;
					}
				}
			}
			// �G3(�d�C��H�w)�̓���
			else if(kindEnemy == 3){
				appearEnemy03++;

				if(appearEnemy03 > 60){
					appearEnemy03 = 0;
				}

				if(appearEnemy03 >= 0 && appearEnemy03 <= 15){
					posEnemy[2][0] = -0.6;
					posEnemy[2][1] = 0.6;
				}
				else if(appearEnemy03 > 15 && appearEnemy03 <= 30){
					posEnemy[2][0] = -0.6;
					posEnemy[2][1] = -0.6;
				}
				else if(appearEnemy03 > 30 && appearEnemy03 <= 45){
					posEnemy[2][0] = 0.6;
					posEnemy[2][1] = -0.6;
				}
				else if(appearEnemy03 > 45 && appearEnemy03 <= 60){
					posEnemy[2][0] = 0.6;
					posEnemy[2][1] = 0.6;
				}

			}

			// �G4(���_����H)�̓���
			else if(kindEnemy == 4){
				if(appearEnemy04 == 0){
					posEnemy[3][0] = posEnemy[3][0] - 0.15;
					if(posEnemy[3][0] < -0.9){
						posEnemy[3][0] = -0.9;
						posEnemy[3][1] = posEnemy[3][1] - 0.2;
						appearEnemy04 = 1;
					}
				}
				else if(appearEnemy04 == 1){
					posEnemy[3][0] = posEnemy[3][0] + 0.15;
					if(posEnemy[3][0] > 0.9){
						posEnemy[3][0] = 0.9;
						posEnemy[3][1] = posEnemy[3][1] - 0.2;
						appearEnemy04 = 0;
					}
				}
				else if(appearEnemy04 == 2){
					posEnemy[3][0] = posEnemy[3][0] + 0.15;
					if(posEnemy[3][0] > 0.9){
						posEnemy[3][0] = 0.9;
						posEnemy[3][1] = posEnemy[3][1] + 0.2;
						appearEnemy04 = 3;
					}
				}
				else if(appearEnemy04 == 3){
					posEnemy[3][0] = posEnemy[3][0] - 0.15;
					if(posEnemy[3][0] < -0.9){
						posEnemy[3][0] = -0.9;
						posEnemy[3][1] = posEnemy[3][1] + 0.2;
						appearEnemy04 = 2;
					}
				}

				if(posEnemy[3][0] == 0.9 && posEnemy[3][1] > 0.8){
					posEnemy[3][1] = 0.8;
					appearEnemy04 = 0;
				}
				else if(posEnemy[3][0] == -0.9 && posEnemy[3][1] < -0.8){
					posEnemy[3][1] = -0.8;
					appearEnemy04 = 2;
				}
			}


			// �G5(�v���O���~���O����)�̓���
			else if(kindEnemy == 5){
				if(posEnemy[4][0] > 0.7){
					appearEnemy05 = 0;
				}
				else if(posEnemy[4][0] < -0.7){
					appearEnemy05 = 1;
				}

				if(appearEnemy05 == 0){
					posEnemy[4][0] = posEnemy[4][0] - 0.05;
					posEnemy[4][1] = Enemy05move01(posEnemy[4][0]);
				}
				else if(appearEnemy05 == 1){
					posEnemy[4][0] = posEnemy[4][0] + 0.05;
					posEnemy[4][1] = Enemy05move02(posEnemy[4][0]);
				}



			}

			// �G6(���l���)�̓���
			else if(kindEnemy == 6){
				posEnemy[5][1] -= 0.16;
				if(appearEnemy06 == 0){
					if(posEnemy[5][1] < -1.0){
						posEnemy[5][0] -= 0.2;
						posEnemy[5][1] = 0.8;
						if(posEnemy[5][0] < -0.8){
							appearEnemy06 = 1;
						}
					}
				}
				else if(appearEnemy06 == 1){
					if(posEnemy[5][1] < -1.0){
						posEnemy[5][0] += 0.2;
						posEnemy[5][1] = 0.8;
						if(posEnemy[5][0] > 0.8){
							appearEnemy06 = 0;
						}
					}
				}
			}

			// �G7(����)�̓���
			else if(kindEnemy == 7){
				if(appearEnemy07 == 0){
					posEnemy[6][0] += 0.1;
					posEnemy[6][1] -= 0.1;
					if(posEnemy[6][0] > 0.7){
						appearEnemy07 = 1;
					}
				}
				else if(appearEnemy07 == 1){
					posEnemy[6][0] -= 0.1;
					if(posEnemy[6][0] < 0.1){
						appearEnemy07 = 2;
					}
				}
				else if(appearEnemy07 == 2){
					posEnemy[6][1] += 0.1;
					if(posEnemy[6][1] > 0.7){
						appearEnemy07 = 3;
					}
				}
				else if(appearEnemy07 == 3){
					posEnemy[6][0] += 0.1;
					if(posEnemy[6][0] > 0.7){
						appearEnemy07 = 4;
					}
				}
				else if(appearEnemy07 == 4){
					posEnemy[6][0] -= 0.1;
					posEnemy[6][1] -= 0.1;
					if(posEnemy[6][0] < -0.7){
						appearEnemy07 = 5;
					}
				}
				else if(appearEnemy07 == 5){
					posEnemy[6][1] += 0.1;
					if(posEnemy[6][1] > -0.1){
						appearEnemy07 = 6;
					}
				}
				else if(appearEnemy07 == 6){
					posEnemy[6][0] += 0.1;
					if(posEnemy[6][0] > 0.7){
						appearEnemy07 = 7;
					}
				}
				else if(appearEnemy07 == 7){
					posEnemy[6][1] += 0.1;
					if(posEnemy[6][1] > 0.7){
						appearEnemy07 = 8;
					}
				}
				else if(appearEnemy07 == 8){
					posEnemy[6][0] -= 0.1;
					if(posEnemy[6][0] < -0.7){
						appearEnemy07 = 0;
					}
				}



			}


			// �G8(��񐔊w)
			else if(kindEnemy == 8){
				if(appearEnemy08 == 0){
					posEnemy[7][0] -= 0.15;
					if(posEnemy[7][0] < -0.9){
						posEnemy[7][0] = -0.9;
						appearEnemy08 = 1;
						Enemy08count++;
						if(Enemy08count == 3){
							posEnemy[7][0] = -0.8;
							posEnemy[7][1] = 0.4;
							appearEnemy08 = 2;
							Enemy08count = 0;
						}
						
					}
				}
				else if(appearEnemy08 == 1){
					posEnemy[7][0] += 0.15;
					if(posEnemy[7][0] > 0.9){
						posEnemy[7][0] = 0.9;
						appearEnemy08 = 0;
					}
				}
				else if(appearEnemy08 == 2){
					Enemy08count++;
					if(Enemy08count == 2){
						posEnemy[7][0] += 0.4;
						if(posEnemy[7][0] > 0.8){
							posEnemy[7][0] = -0.5;
							posEnemy[7][1] = 0.0;
							appearEnemy08 = 3;
						}
						Enemy08count = 0;
					}
				}
				else if(appearEnemy08 == 3){
					Enemy08count++;
					if(Enemy08count == 2){
						posEnemy[7][0] += 0.5;
						if(posEnemy[7][0] > 0.5){
							posEnemy[7][0] = -0.8;
							posEnemy[7][1] = -0.4;
							appearEnemy08 = 4;
						}
						Enemy08count = 0;
					}
				}
				else if(appearEnemy08 == 4){
					Enemy08count++;
					if(Enemy08count == 2){
						posEnemy[7][0] += 0.4;
						if(posEnemy[7][0] > 0.8){
							posEnemy[7][0] = -0.5;
							posEnemy[7][1] = -0.8;
							appearEnemy08 = 5;
						}
						Enemy08count = 0;
					}
				}
				else if(appearEnemy08 == 5){
					Enemy08count++;
					if(Enemy08count == 2){
						posEnemy[7][0] += 0.5;
						if(posEnemy[7][0] > 0.5){
							posEnemy[7][0] = 0.8;
							posEnemy[7][1] = 0.8;
							appearEnemy08 = 0;
						}
						Enemy08count = 0;
					}
				}




			}



			// �G9(���p���w)�̓���
			else if(kindEnemy == 9){

				if(BossMove == 0){
					appearEnemy09++;

					if(appearEnemy09 > 40){
						appearEnemy09 = 0;
						BossCount++;
					}

					if(appearEnemy09 >= 0 && appearEnemy09 <= 5){
						posEnemy[8][0] = -0.7;
						posEnemy[8][1] = 0.6;
					}
					else if(appearEnemy09 > 5 && appearEnemy09 <= 10){
						posEnemy[8][0] = 0.0;
						posEnemy[8][1] = 0.0;
					}
					else if(appearEnemy09 > 10 && appearEnemy09 <= 15){
						posEnemy[8][0] = -0.7;
						posEnemy[8][1] = -0.6;
					}
					else if(appearEnemy09 > 15 && appearEnemy09 <= 20){
						posEnemy[8][0] = 0.0;
						posEnemy[8][1] = -0.6;
					}
					else if(appearEnemy09 > 20 && appearEnemy09 <= 25){
						posEnemy[8][0] = 0.7;
						posEnemy[8][1] = -0.6;
					}
					else if(appearEnemy09 > 25 && appearEnemy09 <= 30){
						posEnemy[8][0] = 0.0;
						posEnemy[8][1] = 0.0;
					}
					else if(appearEnemy09 > 30 && appearEnemy09 <= 35){
						posEnemy[8][0] = 0.7;
						posEnemy[8][1] = 0.6;
					}
					else if(appearEnemy09 > 35 && appearEnemy09 <= 40){
						posEnemy[8][0] = 0.0;
						posEnemy[8][1] = 0.6;
					}

					if(BossCount == 2){
						BossMove++;
						BossCount = 0;
					}
				}
				else if(BossMove == 1){
					if(appearEnemy09 == 0){
						posEnemy[8][0] = posEnemy[8][0] + 0.2;
						if(posEnemy[8][0] > 0.7){
							posEnemy[8][0] = 0.7;
							posEnemy[8][1] = -0.6;
							appearEnemy09 = 1;
						}
					}
					else if(appearEnemy09 == 1){
						posEnemy[8][0] = posEnemy[8][0] - 0.2;
						if(posEnemy[8][0] < -0.7){
							posEnemy[8][0] = 0.7;
							posEnemy[8][1] = 0.6;
							appearEnemy09 = 2;
						}
					}
					else if(appearEnemy09 == 2){
						posEnemy[8][1] = posEnemy[8][1] - 0.2;
						if(posEnemy[8][1] < -0.6){
							posEnemy[8][0] = -0.7;
							posEnemy[8][1] = -0.6;
							appearEnemy09 = 3;
						}
					}
					else if(appearEnemy09 == 3){
						posEnemy[8][1] = posEnemy[8][1] + 0.2;
						if(posEnemy[8][1] > 0.6){
							posEnemy[8][0] = -0.7;
							posEnemy[8][1] = 0.6;
							appearEnemy09 = 0;
							BossMove = 0;
						}
					}


				}
			}

		}
		// �e�e�ƓG�̓����蔻��
		if(x == 1){
			if(posBallet[0] <= posEnemy[kindEnemy-1][0] + size && posBallet[0] >= posEnemy[kindEnemy-1][0] - size){
				if(posBallet[1] <= posEnemy[kindEnemy-1][1] + size && posBallet[1] >= posEnemy[kindEnemy-1][1] - size){
					if(EnemyDamageControl == 0){
						EnemyHP--;
						EnemyDamageControl = 1;
					}

					if(EnemyHP <= 0){
						if(kindEnemy == 3 || kindEnemy == 5 || kindEnemy == 9){
							if(EnemyDeath == 0){
								credit = credit + 3;
								EnemyDeath = 1;
								EnemyHP = 5;
							}
						}
						else if(kindEnemy == 7 && EnemyDeath == 0){
							credit++;
							EnemyDeath = 1;
							EnemyHP = 5;
						}
						else {
							if(EnemyDeath == 0){
								credit = credit + 2;
								EnemyDeath = 1;
								if(kindEnemy == 8){
									EnemyHP = 10;
								}
								else{
									EnemyHP = 5;
								}
							}
						}

						if(credit > 20)
							credit = 20;

						kindEnemy++;
						VSappear = 0;
						x = 0;
						y = 0;
					}
				}
			}
			// �����ƓG�Ƃ̂����蔻��
			if(posPlayer[0] <= posEnemy[kindEnemy-1][0] + size && posPlayer[0] >= posEnemy[kindEnemy-1][0] - size){
				if(posPlayer[1] + sizePlayer * 2 <= posEnemy[kindEnemy-1][1] + size && posPlayer[1] + sizePlayer * 2 >= posEnemy[kindEnemy-1][1] - size){
					if(PlayerDamageControl == 0){
						PlayerLife--;
						PlayerDamageControl = 1;
					}
				}
				else if(posPlayer[1] - sizePlayer * 2 <= posEnemy[kindEnemy-1][1] + size && posPlayer[1] - sizePlayer * 2 >= posEnemy[kindEnemy-1][1] - size){
					if(PlayerDamageControl == 0){
						PlayerLife--;
						PlayerDamageControl = 1;
					}
				}
				else {
					PlayerDamageControl = 0;
				}
			}
			else {
				PlayerDamageControl = 0;
			}
		}

		// VS�G�̕����\���̂��߂̂��
		if(y >= 1 && y <= 25){
			y++;
		}
		else
			y = 0;


		// �e�e
		if( isCrushingBallet == 0 ){
			posBallet[0] = posPlayer[0];
			posBallet[1] = posPlayer[1] + 0.2;
			isCrushingBallet = 1;
		}
		posBallet[1] += 0.15;
		if(posBallet[1] >= 1.0){
			isCrushingBallet = 0;
			EnemyDamageControl = 0;
		}

		// �v���C���[�̈ʒu���X�V
		if(keyUp == 1)posPlayer[1] += 0.1;
		if(keyDown == 1)posPlayer[1] -= 0.1;
		if(keyLeft == 1)posPlayer[0] -= 0.1;
		if(keyRight == 1)posPlayer[0] += 0.1;

		// �v���C���[����ʂ̒[�܂ňړ������ꍇ�͐Î~
		if(posPlayer[0] >= 1.0)posPlayer[0] = 1.0;
		if(posPlayer[0] <= -1.0)posPlayer[0] = -1.0;
		if(posPlayer[1] >= 1.0)posPlayer[1] = 1.0;
		if(posPlayer[1] <= -1.0)posPlayer[1] = -1.0;
	}

	// ��ʂ��ĕ`��
	glutPostRedisplay();
	// ��莞��(�~���b)��ɂ��̊֐������s
	glutTimerFunc(100, updatePos, 0);
}



int main(int argc, char *argv[]){
	glutInit(&argc, argv); // GLUT���C�u������������
	// �\�����[�h���_�u���o�b�t�@�����O�ɐݒ�
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600,600);
	glutCreateWindow(argv[0]); // �E�B���h�E�𐶐�
	glutDisplayFunc(display); // �E�B���h�E�̕`����s���֐����w��

	// ����L�[�������ꂽ(�����ꂽ)�ۂ̏������s���֐����w��
	glutSpecialFunc(checkSpecialKeyPressed);
	glutSpecialUpFunc(checkSpecialKeyReleased);

	init(); // ������
	glutTimerFunc(100, updatePos, 0); // ��莞�Ԍ�Ɏ��s����֐����w��
	glutMainLoop(); // ���C�����[�v
	return EXIT_SUCCESS;
}