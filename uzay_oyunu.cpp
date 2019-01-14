

#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;
const int genislik = 119;
const int yukseklik = 28;
int v_kontrol = 0;
char tuslar[256];
void gotoxy(int x, int y) {//imlecin gideceði kordinatý belirliyoruz
	COORD cord;
	cord.X = x;
	cord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}
char sahne[genislik][yukseklik];//oyunumuz için bir sahne çiziyoruz
void sahneyiCiz() {//oluþturduðmuz sahneyi çiziyoruz
	for (int y = 0; y < yukseklik; y++) {
		for (int x = 0; x < genislik; x++) {
			cout << sahne[x][y];

		}
		cout << endl;
	}
}
void sahneyiTemizle() { //sahneyi temmizliyoruz ki arkada birþey kalmasýn
	for (int y = 0; y < yukseklik; y++) {
		for (int x = 0; x < genislik; x++) {
			if (sahne[x][y] != char(254) && sahne[x][y] != char(217))
			{
				sahne[x][y] = ' ';
			}

		}
	}
}
void oyunsonusahnetemizle()
{
	for (int y = 0; y < yukseklik + 1; y++) {
		for (int x = 0; x < genislik + 1; x++) {
			sahne[x][y] = ' ';
		}
	}
}
void sinirlariOlustur() { //oyun alanýný belirliyoruz
	for (int x = 0; x < genislik; x++) {

		sahne[x][0] = 219;
		sahne[x][yukseklik - 1] = 219;
	}
	for (int y = 0; y < yukseklik; y++) {
		sahne[0][y] = 219;
		sahne[genislik - 1][y] = 219;
	}
}
void kursoruGizle() {//imlecin sahnede görünmesini engelliyoruz

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void klavyeOku(char tuslar[]) {//tuþ kontrolu yapýyoruz
	for (int x = 0; x < 256; x++) {
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
	}
}
class gemi {
protected:
	int mermiX;
	int mermiY;
	int konumY;
	char ucakGovde = 219;
public:
	gemi() :konumY(0) {}

	void ucakOlustur() {
		sahne[1][10 + konumY] = ucakGovde;
		sahne[2][11 + konumY] = ucakGovde;
		sahne[3][12 + konumY] = ucakGovde;
		sahne[2][13 + konumY] = ucakGovde;
		sahne[1][14 + konumY] = ucakGovde;
	}

	int ucakKonum() {
		for (int y = 1; y < yukseklik - 1; y++) {
			if (sahne[3][y] == char(219)) {
				return y;
				break;
			}
		}
	}
	int setX() {//mermiye x eksenindeki konumunu atar
		mermiX = 4;
		return mermiX;
	}

	int setY() {//mermiye y eksenindeki konumu atar
		mermiY = ucakKonum();
		return mermiY;
	}

	void mermiOlustur() {
		sahne[setX()][setY()] = 254;
	}

	void klavye()
	{
		klavyeOku(tuslar);
		if (tuslar['W'] != 0) {
			if (sahne[1][1] != ucakGovde) {
				konumY--;
			}
		}
		if (tuslar['S'] != 0)
		{
			if (sahne[2][25] != ucakGovde) {
				konumY++;
			}
		}
		if (tuslar['D'] != 0) {

			mermiOlustur();

		}
	}

	void mermiHareketEttir()
	{

		for (int y = 0; y < yukseklik - 1; y++) {
			for (int x = genislik - 1; x > 0; x--) {
				if (sahne[x][y] == char(254)) {
					sahne[x][y] = ' ';
					if (sahne[x + 1][y] != char(217))
					{
						sahne[x + 1][y] = 254;
					}
					else
					{
						sahne[x + 1][y] = ' ';
					}
				}
			}
		}

	}

};

class dusman :public gemi {
private:
	int dsmnX;
	int dsmnY;
public:
	int set_dsmnX() {
		dsmnX = genislik - 3;
		return dsmnX;
	}
	int set_dsmnY() {
		srand(time(NULL));
		dsmnY = rand() % 22 + 3;
		return dsmnY;
	}
	void dsmnOlustur() {
		sahne[set_dsmnX()][set_dsmnY()] = 217;

	}
	void dsmnHareketEttir()
	{
		for (int t = 0; t < yukseklik - 1; t++)
		{
			for (int k = 0; k < genislik - 1; k++)
			{
				if (sahne[k][t] == char(217))
				{
					sahne[k][t] = ' ';
					if (sahne[k - 1][t] != char(254))
					{
						sahne[k - 1][t] = 217;
					}
					else
					{
						sahne[k - 1][t] = ' ';
					}

				}
			}
		}
	}
	void vurulma()
	{
		for (int t = 0; t < yukseklik; t++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (sahne[k + 1][t] == char(217))
				{
					if (sahne[k][t] == char(219))
					{
						v_kontrol = 1;
						if (k == 0)
						{
							v_kontrol = 0;
						}

					}
				}
			}
		}
	}
};

int main() {
	system("color c");
	gemi gemi;
	dusman dusman;
	kursoruGizle();
	int a = 0;
	while (v_kontrol == 0)
	{

		sahneyiTemizle();
		sinirlariOlustur();
		gemi.ucakOlustur();
		gemi.klavye();
		if (a == 15) {
			dusman.dsmnOlustur();
			a = 0;
		}
		gemi.mermiHareketEttir();
		dusman.dsmnHareketEttir();
		dusman.vurulma();
		gotoxy(0, 0);
		sahneyiCiz();
		Sleep(20);
		a++;


	}
	oyunsonusahnetemizle();
	gotoxy(0, 0);
	sahneyiCiz();
	gotoxy(0, 0);
	cout << "GAME OVER" << endl;
	system("pause");
	return 0;

}