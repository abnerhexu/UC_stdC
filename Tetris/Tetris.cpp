// win32-1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Tetris.h"
#include <fstream>

#define MAX_LOADSTRING 100
#define GRID 30           // ����߳�
#define nGameWidth 10     // ��������
#define nGameHeight 20    // ��������
#define nWidth 16         // ���ڿ�
#define nHeight 22.3        // ���ڸ�
// using namespace std;
// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Sixnums(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Configure(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIS));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDC_TETRIS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TETRIS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	hWnd = CreateWindow(szWindowClass, TEXT("����˹����"), WS_SYSMENU,
		400, 100, GRID * nWidth, GRID * nHeight - 10, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message){
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ABOUT:
			// suspendFlag = 1;
			// MessageBox(hWnd, TEXT("�������������λ�������֣��ƿ�backdoor��˳���ﵽ16��\n������ֻ�overflowŶ\n���ˣ�backdoor��������"), TEXT("˵��"), MB_OK);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)About);
			break;
		case IDD_TETRIS_DIALOG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SIXNUM), hWnd, (DLGPROC)Sixnums);
			break;
		case PEIZHI:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)Configure);
			break;
		default:
			break;
		}
	case WM_CREATE:
		// ���ó�ʼ���������
		srand((unsigned)time(NULL));
		type = rand() % 7;
		nType = rand() % 7;

		// ���÷���ĳ�ʼλ�úͼ�ʱ��ʱ����
		point.x = 4;
		point.y = -3;
		SetTimer(hWnd, 1, 500.0*(1-0.05*tScore), NULL);		
		// SetTimer(hWnd, 10, 200, NULL);

		// ��������
		if (musicplay) {
			PlaySound(_T("OneMansDream.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		break;
	case WM_TIMER:
		// ����Ϸ�Ѿ�����������ͣ�������κβ���
		if (gameOverFlag || suspendFlag)
			break;

		// ��Ϸ��δ�����������Զ������ƶ�
		if (CanMoveDown()) 
		{
			MoveDown();
		}
		// ����ǰ�����Ѿ�����
		else {
			// �̶���ǰ����
			Fixing();

			// ����
			DeleteLines();
			if (gameOverFlag && !overflowing && !winwin)
				MessageBox(hWnd, TEXT("���鴥�������ؿ�һ�Ѱɣ�"), TEXT("����"), MB_OK);
			else if (gameOverFlag && overflowing) {
				MessageBox(hWnd, TEXT("backdoor�÷�������ˣ���Ϸʧ�ܣ�"), TEXT("����"), MB_OK);
				overflowing = 0;
				tScore = 1;
			}
			else if (gameOverFlag && winwin) {
				MessageBox(hWnd, TEXT("��Ӯ�ˣ�Flag:bbe51039d025b265f9790490781cb201"), TEXT("Congratulations"), MB_OK);
				winwin = 0;
			}
		}

		// ˢ����Ļ
		InvalidateRect(hWnd, NULL, TRUE);
		SetTimer(hWnd, 1, 500.0 * (1 - 0.05 * tScore), NULL);
		if (musicplay && music_switch) {
			PlaySound(_T("OneMansDream.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			music_switch = 0;
		}
		else if (!musicplay && music_switch) {
			PlaySound(NULL, NULL, NULL);
			music_switch = 0;
		}
		if (wudi) {
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 10; j++) {
					workRegion[i][j] = 0;
				}
			}
			wudi = 0;
		}
		break;

	case WM_KEYDOWN:
		//�浵
		if (wParam == 'N') {
			saveNow();
			// InvalidateRect(hWnd, NULL, TRUE);
			suspendFlag = 1;
			MessageBox(hWnd, TEXT("���ڴ浵������ͣ����P��ʼ��"), TEXT("�浵"), MB_OK);
			break;
		}
		// ����
		if (wParam == 'R') {
			readSaved();
			point.x = 4;
			point.y = -3;
			InvalidateRect(hWnd, NULL, TRUE);
			MessageBox(hWnd, TEXT("���ڶ�����"), TEXT("����"), MB_OK);
			break;
		}
		// ����Ϸ�Ѿ�������ֻ�а������¿�ʼ�������з�Ӧ
		if (gameOverFlag) {
			if (wParam == 'S')
			{
				gameOverFlag = false;
				Restart();
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}

		// ����Ϸ�Ѿ���ͣ��ֻ�а���P�������з�Ӧ
		if (suspendFlag) {
			if (wParam == 'P')
				suspendFlag = false;
			else
			{
				MessageBox(hWnd, TEXT("���Ȱ�P��ȡ����ͣ��"), TEXT("����"), MB_OK);
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		// ��Ϸδ����
		switch(wParam)
		{
		// �����ƶ�
		case VK_LEFT:
			if (CanMoveLeft()) 
			{
				MoveLeft();
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		// �����ƶ�
		case VK_RIGHT:
			if (CanMoveRight()) 
			{
				MoveRight();
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		// ��ת
		case VK_UP:
			Rotate();
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		// �����ƶ�
		case VK_DOWN:
			if (CanMoveDown()) 
			{
				MoveDown();
			}
			// ����ǰ�����Ѿ�����
			else 
			{
				// �̶���ǰ����
				Fixing();

				// ����
				DeleteLines();
				if (gameOverFlag && !overflowing && !winwin)
					MessageBox(hWnd, TEXT("���鴥�������ؿ�һ�Ѱɣ�"), TEXT("����"), MB_OK);
				else if (gameOverFlag && overflowing) {
					MessageBox(hWnd, TEXT("backdoor�÷�������ˣ���Ϸʧ�ܣ�"), TEXT("����"), MB_OK);
					overflowing = 0;
					tScore = 1;
				}
				else if (gameOverFlag && winwin) {
					MessageBox(hWnd, TEXT("��Ӯ�ˣ�Flag:bbe51039d025b265f9790490781cb201"), TEXT("Congratulations"), MB_OK);
					winwin = 0;
				}
			}

			// ˢ����Ļ
			InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, 1, 500.0 * (1 - 0.05 * tScore), NULL);
			break;

		// ֱ������
		case VK_SPACE:
			// ����
			DropDown();

			// ����
			DeleteLines();
			if (gameOverFlag && !overflowing && !winwin)
				MessageBox(hWnd, TEXT("���鴥�������ؿ�һ�Ѱɣ�"), TEXT("����"), MB_OK);
			else if (gameOverFlag && overflowing) {
					MessageBox(hWnd, TEXT("backdoor�÷�������ˣ���Ϸʧ�ܣ�"), TEXT("����"), MB_OK);
					overflowing = 0;
					tScore = 1;
			}
			else if (gameOverFlag && winwin) {
				MessageBox(hWnd, TEXT("��Ӯ�ˣ�Flag:bbe51039d025b265f9790490781cb201"), TEXT("Congratulations"), MB_OK);
				winwin = 0;
			}
			else {
				InvalidateRect(hWnd, NULL, TRUE);
				SetTimer(hWnd, 1, 500.0 * (1 - 0.05 * tScore), NULL);
			}
			break;

		// ��ͣ
		case 'P':
			suspendFlag = !suspendFlag;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		// ���¿�ʼ
		case 'S':
			Restart();
			gameOverFlag = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		// ��׼��
		case 'C':
			targetFlag = !targetFlag;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		default:
			break;
		}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// ������Ļ
		TDrawScreen(hdc, hWnd);

		ReleaseDC(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		// MessageBox(hDlg, TEXT("test message"), TEXT("test"), MB_OK);
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ���������֡������Ϣ�������
INT_PTR CALLBACK Sixnums(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		// MessageBox(hDlg, TEXT("test message"), TEXT("test"), MB_OK);
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ���ÿ����Ϣ�������
INT_PTR CALLBACK Configure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		// MessageBox(hDlg, TEXT("test message"), TEXT("test"), MB_OK);
		if (LOWORD(wParam) == 1003) {
			music_switch = 1;
			if (musicplay == 1)
				musicplay = 0;
			else
				musicplay = 1;
		}
		if (LOWORD(wParam) == 1004) {
			if (wudi == 1)
				wudi = 0;
			else
				wudi = 1;
		}
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// �жϵ�ǰ�����Ƿ���������ƶ�
bool CanMoveDown() {
	/*
	for (int i = 0; i < 4; i++) {`
		for (int j = 0; j < 4; j++) {
			int flag = bricks[type][state][i][j];
			if ((flag > 0 && point.y + i + 1 >= 0) && (point.y + i == 19 || workRegion[point.y + i + 1][point.x + j] > 0))
				return 0;
		}
	}
	return 1;*/
	int maxy = -20;
	int anyx = 20;
	int flag = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			flag = bricks[type][state][i][j];
			if (flag > 0 && workRegion[point.y + i + 1][point.x + j] > 0)
				return 0;
			if (flag > 0 && maxy < i) {
				anyx = j;
				maxy = i;
			}
		}
	}
	if (bricks[type][state][maxy][anyx] > 0 && point.y + maxy == 19)
		return 0;
	/*
	if ((flag > 0 && point.x - j > 0) && (point.x - j == 0 || workRegion[point.y + i][point.x - j - 1] > 0))
		return 0;
	if (flag > 0 && ) */
	return 1;
}

// �жϵ�ǰ�����Ƿ���������ƶ�
bool CanMoveLeft() {
	int miny = 20;
	int minx = 20;
	int flag = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			flag = bricks[type][state][i][j];
			if (flag > 0 && workRegion[point.y + i][point.x + j - 1] > 0)
				return 0;
			if (flag > 0 && minx > j) {
				minx = j;
				miny = i;
			}
		}
	}
	if (bricks[type][state][miny][minx] > 0 && point.x + minx == 0)
		return 0;
			/*
			if ((flag > 0 && point.x - j > 0) && (point.x - j == 0 || workRegion[point.y + i][point.x - j - 1] > 0))
				return 0;
			if (flag > 0 && ) */
	return 1;
}

// �жϵ�ǰ�����Ƿ���������ƶ�
bool CanMoveRight() {
	/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int flag = bricks[type][state][i][j];
			if ((flag > 0 && point.x + i + 1 >= 0) && (point.x + j == 9 || workRegion[point.y + i][point.x + j + 1] > 0))
				return 0;
		}
	}
	return 1;
	*/
	int maxx = -20;
	int anyy = 20;
	int flag = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			flag = bricks[type][state][i][j];
			if (flag > 0 && workRegion[point.y + i][point.x + j + 1] > 0)
				return 0;
			if (flag > 0 && maxx < j) {
				maxx = j;
				anyy = i;
			}
		}
	}
	if (bricks[type][state][anyy][maxx] > 0 && point.x + maxx == 9)
		return 0;
		/*
		if ((flag > 0 && point.x - j > 0) && (point.x - j == 0 || workRegion[point.y + i][point.x - j - 1] > 0))
			return 0;
		if (flag > 0 && ) */
	return 1;
}

// ��ǰ���������ƶ�
void MoveDown() {
	point.y++;
	DeleteLines();
}

// ��ǰ���������ƶ�
void MoveLeft() {
	point.x--;
	DeleteLines();
}

// ��ǰ���������ƶ�
void MoveRight() {
	point.x++;
	DeleteLines();
}

// ��ת��ǰ����
void Rotate() {
	state = (state + 1) % 4;
	Point newp = point;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (bricks[type][state][i][j] > 0) {
				if (point.x + j < 0)
					point.x = -j;
				if (point.x + j > 9)
					point.x = 9 - j;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (bricks[type][state][i][j] > 0 && workRegion[point.y + i][point.x + j] > 0) {
				state = (state + 3) % 4;
				return;
			}
		}
	}
}

// ����ǰ����ֱ�����䵽�������λ��
void DropDown() 
{
	while (CanMoveDown()) {
		point.y++;
	}
	DeleteLines();
}

// ����ǰ����̶��ڵ�ǰλ��
void Fixing() 
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			if (bricks[type][state][i][j] > 0 && point.y + i >= 0)
				workRegion [point.y + i][point.x + j] = bricks[type][state][i][j];
		}
	}
	if (GameOver()) 
	{
		gameOverFlag = true;		
	}
	else 
	{
		point.x = 4;
		point.y = -3;
		type = nType;
		nType = rand() % 7;
		state = 0;
	}
}

// ��ȥһ��
void DeleteOneLine(int number) {
	for (int p = 0; p < 10; p++) {
		workRegion[number][p] = 0;
	}
}

// ���в��������µ÷�
void DeleteLines() {
	for (int k = 19; k >= 0; k--) {
		int flag = 1;
		for (int p = 0; p < 10; p++) {
			if (workRegion[k][p] == 0)
				flag = 0;
		}
		if (flag == 1) {
			tScore *= 2;
			for (int p = 0; p < 10; p++) {
				workRegion[k][p] = 0;
			}
			for (int i = k; i > 0; i--) {
				for (int j = 0; j < 10; j++)
					workRegion[i][j] = workRegion[i - 1][j];
			}
			for (int p = 0; p < 10; p++)
				workRegion[0][p] = 0;
			}
		if (tScore == 16 && magicnum == 0) {
			gameOverFlag = 1;
			overflowing = 1;
			break;
		}
		else if (tScore == 16 && magicnum == 1) {
			winwin = 1;
			gameOverFlag = 1;
			tScore = 1024;
			break;
		}
	}
}

// �浵
void saveNow() {
	std::ofstream outfile;
	outfile.open("fly.dat", std::ios::trunc);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			outfile << workRegion[i][j] << " ";
		}
	}
	int powtScore = 0;
	switch (tScore)
	{
	case 1:
		powtScore = 0;
		break;
	case 2:
		powtScore = 1;
		break;
	case 4:
		powtScore = 2;
		break;
	case 8:
		powtScore = 3;
		break;
	case 16:
		powtScore = 4;
		break;
	default:
		break;
	}
	outfile << powtScore << " ";
	for (int r = 0; r < 6; r++) {
		outfile << rand() % 10 << " ";
	}
	outfile.close();
}

bool backdoor(int array[]) {
	if (array[0] != 0)
		return false;
	for (int i = 1; i < 4; i++) {
		if (array[i] != array[i + 1] / 2)
			return false;
	}
	return true;
}

// ����
void readSaved() {
	std::ifstream infile("fly.dat");
	char s;
	int savedArray[21][10];
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 10; j++) {
			infile >> s;
			savedArray[i][j] = (int)s - 48;
		}
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 9; j++) {
			workRegion[i][j] = savedArray[i][j];
		}
	}
	tScore = pow(2, savedArray[20][0]);
	int backdoorarray[6];
	for (int r = 0; r < 6; r++) {
		backdoorarray[r] = savedArray[20][r + 1];
	}
	magicnum = backdoor(backdoorarray);
	infile.close();
}

// �ж���Ϸ����
bool GameOver() {
	if (point.y + 3 < 0)
		return 0;
	for (int i = 0; i < 10; i++) {
		if (workRegion[0][i] > 0 && !CanMoveDown()) {
			return 1;
		}
	}
	return 0;
}

// ������׼��λ��
void ComputeTarget() {
	Point org = point;
	while(CanMoveDown())
	{
		MoveDown();
	}
	target = point;
	point = org;
}

// ���¿�ʼ
void Restart(){
	tScore = 1;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			workRegion[i][j] = 0;
		}
	}
}

// ������Ļ
void TDrawScreen(HDC hdc, HWND hWnd)
{
	HDC dcMem = CreateCompatibleDC(hdc);
	HBITMAP bmpMem = CreateCompatibleBitmap(hdc, nWidth * GRID,nHeight * GRID); //��λͼѡ����ڴ�DC 
	SelectObject(dcMem, bmpMem); 

	//�ð�ɫ����ڴ�DC�Ŀͻ��� 
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); 
	SelectObject(dcMem, hBrush); 
	Rectangle(dcMem, 0, 0, nWidth * GRID,nHeight * GRID); 

	// ���ر���ͼƬ
	HDC dcPic = CreateCompatibleDC(NULL);
	HBITMAP bmp = (HBITMAP)LoadImage(NULL, TEXT("background.bmp"), IMAGE_BITMAP, nWidth * GRID, nHeight * GRID, LR_LOADFROMFILE);
	SelectObject(dcPic, bmp);
	BitBlt(dcMem, 0, 0, nWidth * GRID, nHeight * GRID, dcPic, 0, 0, SRCCOPY);

	// ���߿�
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(dcMem, hPen);
	MoveToEx(dcMem, nGameWidth * GRID, 0, NULL);
	LineTo(dcMem, nGameWidth * GRID, nGameHeight * GRID);
	MoveToEx(dcMem, 0, nGameHeight * GRID, NULL);
	LineTo(dcMem, nGameWidth * GRID, nGameHeight * GRID);

	// �����Ϸ˵��
	HFONT hFont = CreateFont(18, 10, 0, 0, 200, false, false, false, 
		ANSI_CHARSET, OUT_CHARACTER_PRECIS, 
		CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		FF_MODERN, (LPCWSTR)"Microsoft YaHei UI");
	SelectObject(dcMem, hFont);
	SetBkMode(dcMem, TRANSPARENT);

	TCHAR sscore[1024];
	int slen = wsprintf(sscore, L"��ǰ�÷�: %d", tScore);
	TextOut(dcMem, (nGameWidth) * GRID + 5, 1 * GRID, TEXT("��һ����:"), 5);
	TextOut(dcMem, (nGameWidth) * GRID + 5, 6 * GRID, sscore, slen);
	TextOut(dcMem, (nGameWidth) * GRID + 5, 7 * GRID, TEXT("��Ϸ˵��:"), 5);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 8 * GRID, TEXT("���󣺡�"), 4);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 9 * GRID, TEXT("���ң���"), 4);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 10 * GRID, TEXT("���£���"), 4);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 11 * GRID, TEXT("��ת����"), 4);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 12 * GRID, TEXT("ֱ�����䣺�ո�"), 7);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 13 * GRID, TEXT("��ͣ/��ʼ��P"), 7);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 14 * GRID, TEXT("���¿�ʼ��S"), 6);
	TextOut(dcMem, (nGameWidth) * GRID + 25, 15 * GRID, TEXT("��׼����C"), 5);
	TextOut(dcMem, (nGameWidth)*GRID + 25, 16 * GRID, TEXT("������R"), 4);
	TextOut(dcMem, (nGameWidth)*GRID + 25, 17 * GRID, TEXT("�浵��N"), 4);
	// TextOut(dcMem, (nGameWidth)*GRID + 25, 18 * GRID, TEXT("���а�E"), 5);
	if(suspendFlag)
	{
		TextOut(dcMem, (nGameWidth) * GRID + 5, 19 * GRID, TEXT("����ͣ..."), 6);
	}

	// �ͷ���Դ		
	DeleteObject(hPen);

	// ��������
	hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(dcMem, hPen);	
	for (int i = 0; i < 20; i++) 
	{
		for (int j = 0; j < 10; j++) 
		{
			if (workRegion [i][j] > 0) 
			{
				hBrush = CreateSolidBrush(BrickColor[workRegion [i][j] - 1]);
				SelectObject(dcMem, hBrush);

				// ������
				Rectangle(dcMem, j * GRID, i * GRID, (j + 1) * GRID, (i + 1) * GRID);

				DeleteObject(hBrush);				
			}
		}
	}

	// ����ǰ����
	hBrush = CreateSolidBrush(BrickColor[type]);
	SelectObject(dcMem, hBrush);
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			int value = bricks[type][state][i][j];
			if (value > 0) 
			{
				Rectangle(dcMem, (point.x + j) * GRID, (point.y + i) * GRID, (point.x + j + 1) * GRID, (point.y + i + 1) * GRID);
			}
		}
	}
	DeleteObject(hBrush);

	// ����һ����
	hBrush = CreateSolidBrush(BrickColor[nType]);
	SelectObject(dcMem, hBrush);
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			int value = bricks[nType][0][i][j];
			if (value > 0) 
			{
				Rectangle(dcMem, (10.5 + j) * GRID, (2 + i) * GRID, (10.5 + j + 1) * GRID, (2 + i + 1) * GRID);
			}
		}
	}
	DeleteObject(hBrush);

	// ����׼��
	if (targetFlag)
	{
		ComputeTarget();
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(dcMem, hBrush);
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				int value = bricks[type][state][i][j];
				if (value > 0) 
				{
					Rectangle(dcMem, (target.x + j) * GRID, (target.y + i) * GRID, (target.x + j + 1) * GRID, (target.y + i + 1) * GRID);
				}
			}
		}
		DeleteObject(hBrush);
	}
	
	BitBlt(hdc, 0, 0, nWidth * GRID, nHeight * GRID, dcMem, 0, 0, SRCCOPY);

	DeleteObject(hPen);
	DeleteObject(hFont);
	DeleteObject(bmpMem);
	DeleteObject(bmp);
	ReleaseDC(hWnd, dcMem);
	ReleaseDC(hWnd, dcPic);
}
