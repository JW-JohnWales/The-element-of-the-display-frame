#define _USE_MATH_DEFINES
#include <Windows.h>
#include <GL/GL.h> //использую наиболее раннюю версию -  OpenGL 1.1 
#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_easy_font.h" //для метода "консольного" вывода (bitmap font rendering)

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void print_string(float x, float y, char* text, float r, float g, float b);

float targetVerticalVelocity = -110; //"Индекс скорости вертикальной заданной"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;

	//Регистрация оконного класса
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("DisplayFrameClass");
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* Создание главного окна */
	hwnd = CreateWindowEx(0,
		TEXT("DisplayFrameClass"),
		TEXT("DisplayFrame"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		700,
		700,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);

	/* Подгрузка opengl для нашего окна */
	EnableOpenGL(hwnd, &hDC, &hRC);

	float verticalVelocity = 0;

	/* Главный цикл */
	while (!bQuit)
	{
		/* Проверка сообщений */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* обработка сообщений */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/* Код всей анимации */

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glLineWidth(2);

			glLoadIdentity(); // возвращаем систему координат к изначальному состоянию
			glRotatef(135, 0, 0, 1); // поворачиваем ось

			glBegin(GL_LINE_STRIP);

			glColor3f(0.8, 0.8, 0.8);
			
			float points = 100; //кол-во точек
			float l = 0.5; //радиус
			float angle = 0.0; //угол

			//шкала (дуга)
			for (int i = 1; i <= points; i++)
			{
				angle = M_PI * i / (points * 2) ;
				glVertex2f(sin(angle) * l, cos(angle) * l);
			}

			glEnd();

			//риски (отметки)
			glLineWidth(1);
			glBegin(GL_LINES);

			//Большие риски
			angle = M_PI * 1 / (points * 2);
			glVertex2f(sin(angle) * 0.43, cos(angle) * 0.43);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 10 / (points * 2);
			glVertex2f(sin(angle) * 0.43, cos(angle) * 0.43);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 20 / (points * 2); 
			glVertex2f(sin(angle) * 0.43, cos(angle) * 0.43);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 50 / (points * 2); 
			glVertex2f(sin(angle) * 0.43, cos(angle) * 0.43);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 80 / (points * 2); 
			glVertex2f(sin(angle) * 0.43, cos(angle) * 0.43);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 90 / (points * 2);
			glVertex2f(sin(angle) * 0.43, cos(angle) * 0.43);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 100 / (points * 2); 
			glVertex2f(sin(angle) * 0.43, cos(angle) * 0.43);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			//Средние риски
			angle = M_PI * 5 / (points * 2);
			glVertex2f(sin(angle) * 0.45, cos(angle) * 0.45);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 15 / (points * 2);
			glVertex2f(sin(angle) * 0.45, cos(angle) * 0.45);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 35 / (points * 2);
			glVertex2f(sin(angle) * 0.45, cos(angle) * 0.45);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 65 / (points * 2);
			glVertex2f(sin(angle) * 0.45, cos(angle) * 0.45);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 85 / (points * 2);
			glVertex2f(sin(angle) * 0.45, cos(angle) * 0.45);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			angle = M_PI * 95 / (points * 2);
			glVertex2f(sin(angle) * 0.45, cos(angle) * 0.45);
			glVertex2f(sin(angle) * l, cos(angle) * l);

			//Маленькие риски
			for (int i = 20; i <= 80; i += 3) {
				angle = M_PI * i / (points * 2);
				glVertex2f(sin(angle) * 0.47, cos(angle) * 0.47);
				glVertex2f(sin(angle) * l, cos(angle) * l);
			}
			
			glEnd();

			glLoadIdentity(); // возвращаем систему координат к изначальному состоянию

			glScalef(0.008, -0.008, 0); //размер

			//цифры около рисочек
			glPushMatrix();

			print_string(-38, -35, _strdup("30"), 1, 1, 1);
			print_string(-47, -25, _strdup("10"), 1, 1, 1);
			print_string(-50, -15, _strdup("5"), 1, 1, 1);
			print_string(-51, -4, _strdup("0"), 1, 1, 1);
			print_string(-50, 7, _strdup("5"), 1, 1, 1);
			print_string(-47, 17, _strdup("10"), 1, 1, 1);
			print_string(-38, 27, _strdup("30"), 1, 1, 1);

			glPopMatrix();

			glLoadIdentity();

			//2 элемент
			glTranslatef(-0.26, 0, 0);
			glLineWidth(2);
			glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);

			points = 20; //кол-во точек
			l = 0.05; //радиус
			angle = 0.0; //угол
			glVertex2f(0, -0.05);
			glVertex2f(0.17, -0.05);
			glVertex2f(0.17, 0.05);
			glVertex2f(0, 0.05);

			for (int i = 1; i <= points; i++)
			{
				angle = -1 * M_PI * i / points;
				glVertex2f(sin(angle) * l, cos(angle) * l);
			}
			glEnd();

			glScalef(0.008, -0.008, 0);

			char buffer[4];
			auto s = snprintf(buffer, sizeof buffer, "%i", (int)verticalVelocity);

			print_string(2, -3.5, buffer, 1, 1, 1);

			glLoadIdentity();

			//4 элемент
			if (-30 < targetVerticalVelocity && targetVerticalVelocity < 30) {
				if (-10 <= targetVerticalVelocity && targetVerticalVelocity <= 10) glRotatef(targetVerticalVelocity * 2.7, 0, 0, -1);
				else if (10 < targetVerticalVelocity) glRotatef(27 + (targetVerticalVelocity - 10) * 0.9, 0, 0, -1);
				else glRotatef(27 + (-1 * targetVerticalVelocity - 10) * 0.9, 0, 0, 1);
			}
			else (targetVerticalVelocity >= 30 ? glRotatef(45, 0, 0, -1) : glRotatef(45, 0, 0, 1));

			glTranslatef(-0.48, 0, 0);
			glLineWidth(5);
			glBegin(GL_LINE_STRIP);
			glColor3f(0.21, 0.78, 0.82);
			glVertex2f(0.08, 0.06);
			glVertex2f(0, 0);
			glVertex2f(0.08, -0.06);
			glEnd();

			glLoadIdentity();

			//3 элемент
			glLineWidth(2);

			if (-30 < verticalVelocity && verticalVelocity < 30) {
				if (-10 <= verticalVelocity && verticalVelocity <= 10) glRotatef(verticalVelocity * 2.7, 0, 0, -1);
				else if (10 < verticalVelocity) glRotatef(27 + (verticalVelocity - 10) * 0.9, 0, 0, -1);
				else glRotatef(27 + (-1 * verticalVelocity - 10) * 0.9, 0, 0, 1);
			}
			else (verticalVelocity >= 30 ? glRotatef(45, 0, 0, -1) : glRotatef(45, 0, 0, 1));

			glTranslatef(-0.27, 0, 0);

			glBegin(GL_TRIANGLE_STRIP);

			glColor3f(1, 1, 1);
			glVertex2f(-0.2, 0);
			glVertex2f(-0.15, -0.03);
			glVertex2f(-0.15, 0.03);
			glVertex2f(0, -0.03);
			glVertex2f(0, 0.03);

			glEnd();

			glLoadIdentity();
			glTranslatef(-0.25, 0.45, 0);
			//5 элемент
			glBegin(GL_TRIANGLE_FAN);

			glColor3f(0.02, 0.1, 0.76);
			glVertex2f(-0.24, -0.05);
			glVertex2f(0.24, -0.05);
			glVertex2f(0.24, 0.05);
			glVertex2f(-0.24, 0.05);

			glEnd();

			glLoadIdentity();
			glScalef(0.008, -0.008, 0);

			char bufferFunt[20];
			snprintf(bufferFunt, sizeof bufferFunt, "%i", (((int)verticalVelocity) * 197 - ((((int)verticalVelocity) * 197) % 50)));

			print_string(-58, -60, bufferFunt, 0.17, 0.91, 0.3);
			print_string(-20, -60, _strdup("fpm"), 0.17, 0.91, 0.3);

			SwapBuffers(hDC);
			if ((int)targetVerticalVelocity != (int)verticalVelocity && (int)verticalVelocity < 99 && (int)verticalVelocity > -99)
				(targetVerticalVelocity > 0 ? verticalVelocity+= 0.1 : verticalVelocity -= 0.1 );
			Sleep(1);
		}
	}

	/* отключение OpenGL */
	DisableOpenGL(hwnd, hDC, hRC);

	/* явное уничтожение окна */
	DestroyWindow(hwnd);

	return msg.wParam;
}

/// <summary>
/// Метод "консольного" вывода текста
/// </summary>
/// <param name="x"> - координата по x</param>
/// <param name="y"> - координата по y</param>
/// <param name="text"> - указатель на текст</param>
/// <param name="r"> - красный цвет</param>
/// <param name="g"> - зеленый цвет</param>
/// <param name="b"> - синий цвет</param>
void print_string(float x, float y, char* text, float r, float g, float b) //один из способов вывода. для работы раскоментировать #include "include/stb_easy_font.h"
{
	static char buffer[99999]; // ~500 chars
	int num_quads;

	num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

	glColor3f(r, g, b);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, buffer);
	glDrawArrays(GL_QUADS, 0, num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* Получение контекста устройства */
	*hDC = GetDC(hwnd);

	/* Установление формата пикселя для изображения */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* Создание и включение контекста рендера */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}