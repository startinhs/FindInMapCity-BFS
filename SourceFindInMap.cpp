//Le Minh Tinh - 2154050301

//FIND IN MAP CITY BY BFS

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

struct Node
{
	int info; 
	Node* link;
};
Node* front, * rear;

const int MAX=100;
int A[MAX][MAX];
int n;
string vertex[MAX];

// Language type
string yesNo, bye, noFunc, Load, Dele, Succ, loca1, loca2, path, verte, nameverte, againIn, empty, list, note, nopath;

// Queue
void InitQ() 
{
	front = NULL;
	rear = NULL;
}
int isEmptyQ()
{
	if (front == NULL)
		return 1;
	return 0;
}
void PushQ(int x)
{
	Node* p = new Node;
	p->info = x;
	p->link = NULL;
	if (rear == NULL)
		front = p;
	else
		rear->link = p;
	rear = p;
}
int PopQ(int &x)
{
	if (front != NULL)
	{
		Node* p = front;
		front = p->link;
		x = p->info;
		if (front ==NULL)
		{
			rear = NULL;
		}
		delete p;
		return 1;
	}
	return 0;
}

// Process file
char lang;
void chooseLang()
{
	cout<< "\n-------------------------------------\n"
		<< "|        NGON NGU (LANGUAGE)        |\n"
		<< "-------------------------------------\n"
		<< "| E. Tieng Anh (English)            |\n"
		<< "| V. Tieng Viet (Vietnamese)        |\n"
		<< "-------------------------------------\n"
		<< "\tChon (Choose) E/V: ";
    cin>>lang;
}
void inputLanguageFile()
{
	ifstream f;
	if(lang=='E' || lang=='e')
	{
		f.open("Language-EN.txt");
		cout<< "-------------------------------------------------------\n"
			<< "|                   FIND IN MAP CITY                  |\n"
			<< "|------------------- UPDATE | CLEAN ------------------|\n"
			<< "| [1] | Automatic Map update (File Text)              |\n"
			<< "| [2] | Manual Map update (Graph Representation)      |\n"
			<< "| [3] | Delete all locations on the Map               |\n"
			<< "|------------------- PROCESS | PRINT -----------------|    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
			<< "| [a] | Print updated locations on the Map            |    |  NOTE: - Update Map before use!         |\n"
			<< "| [b] | Print processing locations in width (BFS)     |    |        - Use default map: [1]           |\n"
			<< "| [c] | Print graphs of places on the Map             |    |        - Change other Map: [3] -> [2]   |\n"
			<< "|-------------------- FIND | OTHER -------------------|    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			<< "| [s] | Find the shortest path between 2 locations    |\n"
			<< "| [x] | Change language                               |\n"
			<< "| [0] | Exit                                          |\n"
			<< "-------------------------------------------------------\n"
			<< "\t-> Type of Option: ";
	}
	else if(lang =='V' || lang =='v')
	{
		f.open("Language-VI.txt");
		cout<< "-------------------------------------------------------\n"
			<< "|               TiM KIEM TRONG THANH PHO              |\n"
			<< "|------------------ CAP NHAT | XOA -------------------|\n"
			<< "| [1] | Cap nhat Ban Do tu dong (Tap Tin)             |\n"
			<< "| [2] | Cap nhat Ban Do thu cong (Bieu dien Do thi)   |\n"
			<< "| [3] | Xoa tat ca vi tri tren Ban Do                 |\n"
			<< "|-------------------- DUYET | IN ---------------------|    <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
			<< "| [a] | In cac Dia Diem duoc cap nhat tren Ban Do     |    | Ghi chu: - Cap nhat Ban Do truoc khi su dung nhe! |\n"
			<< "| [b] | In cac Dia Diem Duyet theo chieu rong (BFS)   |    |          - Su dung ban do mac dinh: [1]           |\n"
			<< "| [c] | In Do thi cac dia diem tren Ban Do            |    |          - Thay doi Ban Do khac: [3] -> [2]       |\n"
			<< "|------------------ TIM KIEM | KHAC ------------------|    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"    
			<< "| [s] | Tim duong di ngan nhat giua 2 dia diem        |\n"
			<< "| [x] | Doi ngon ngu                                  |\n"
			<< "| [0] | Thoat                                         |\n"
			<< "-------------------------------------------------------\n"
			<< "\t-> Chon chuc nang: ";
	}
	else
	{
		cout<<"Vui long chon dung chuc nang!\n";
		chooseLang();
		inputLanguageFile();
	}

	if(f.is_open())
	{
		getline(f, yesNo);
		getline(f, bye);
		getline(f, noFunc);
		getline(f, Load);
		getline(f, Dele);
		getline(f, Succ);
		getline(f, loca1);
		getline(f, loca2);
		getline(f, path);
		getline(f, verte);
		getline(f, nameverte);
		getline(f, againIn);
		getline(f, empty);
		getline(f, list);
		getline(f, note);
		getline(f, nopath);
	}
	else return;
	f.close();
}
void inputGraphFile()
{
	ifstream f;
	f.open("Graph-MapTPHCM.txt");
	if(f.fail()){
		return;
	}
	else
	{	
		f >> n;
		f.ignore();

		for (int i = 0; i < n; i++)
		{
			if(i==n-1) getline(f, vertex[i]);
			else getline(f, vertex[i], ',');
		
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				f >> A[i][j];
		}
	}
	f.close();
}

// Graph
void InitG() {
	n = 0;
}
void inputGraph()
{
	cout << verte;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << nameverte;
		cin.ignore();
		getline(cin, vertex[i]);
		for (int j = 0; j < n; j++){
			cout << "A["<<i<<"]["<<j<<"] = ";
			cin >> A[i][j];
			do{
				if(A[i][j] < 0 || A[i][j] > 1){
					cout << againIn << endl;
					cout << "A["<<i<<"]["<<j<<"] = ";
					cin >> A[i][j];
				}
        	}while(A[i][j] < 0 || A[i][j] > 1);
		}
	}
}
void outputGraph()
{
	if(n != 0)
	{
		cout << "\n       ";
		for(int i=0; i<n; i++)
		{
			cout <<i<< setw(3) << fixed;
		}
		cout << "\n      ";
		for(int i=0; i<n; i++)
		{
			cout << "---";
		}
		cout << "\n  ";
		for (int i = 0; i < n; i++)
		{
			cout <<i<<" |  ";
			for (int j = 0; j < n; j++){
				cout << A[i][j] << setw(3) << fixed;
			}
			cout << endl;
		}
	}
	else
		cout << empty << endl;
}
void outputInfoMap()
{
	if(n != 0)
	{
		cout << setw(70) << right << list << endl;
		cout << setw(80) << right << note << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "[" << i << "]: " << vertex[i] << endl;
		}
		cout << endl;
	}
	else
		cout << empty << endl;
}

// BFS
int C[100], bfs[100];
int nbfs = 0;
void Init()
{
	for (int i = 0; i < n; i++)
		C[i] = 1;
}
void BFS(int v)
{
	int p, w;
	PushQ(v);
	C[v] = 0;
	while(!isEmptyQ())
	{
		PopQ(p);
		bfs[nbfs] = p;
		nbfs++;
		for ( w = 0; w < n; w++)
			if (C[w] && A[p][w] == 1)
			{
				PushQ(w);
				C[w] = 0;
			}
	}
}
void output()
{
	for (int i = 0; i < nbfs; i++)
	{
		cout << "["<< bfs[i] << "]: " << vertex[bfs[i]] << endl;
	}
}
void Init2()
{
	for (int i = 0; i < n; i++)
	{
		C[i] = 1;
		bfs[i] = -1; //mảng lưu đỉnh cha
	}
}
void FindNearRoad_BFS(int v)
{
	int p;	
	PushQ(v);
	C[v] = 0;
	while(!isEmptyQ())
	{
		PopQ(p);
		//tìm đỉnh kề chưa xét
		for(int w=0; w<n; w++)
			if(C[w]== 1 && A[p][w] == 1)
			{
				PushQ(w);
				C[p] = 0;
				bfs[w] = p; //lưu đỉnh cha của w
			}
		C[p] = 2; //duyệt hết đỉnh kề của p
	}
}
void outputRoads(int v, int end)
{
	if(v == end)
		cout << end;
	else
		if(bfs[end] == -1) 
			cout << nopath << endl;
		else
		{
			outputRoads(v, bfs[end]);
			cout << " -> " << end;
		}
}

// Menu
void again(); void menu();
void again()
{
	ifstream f;
	char c;
	cout << "\n" << yesNo;
	cin >> c;
	if (c == '1')
	{
		system("cls");
		inputLanguageFile();
		menu();
	}
	else if (c == '0')
	{
		cout << bye <<endl;
		return;
	}
	else
	{
		cout << noFunc <<endl;
		return again();
	}
}
void menu()
{
	char choose;
	cin >> choose;
	switch (choose)
	{
		case '1':
		{
			InitG();
			inputGraphFile();
			cout << Load;
			Sleep(500);
			cout << ".";
			Sleep(500);
			cout << ".";
			Sleep(500);
			cout << ".\n";
			cout << Succ << endl;
			again();
			break;
		}
		case '2':
		{
			InitG();
			inputGraph();
			cout << Succ << endl;
			again();
			break;
		}
		case '3':
		{
			InitG();
			cout << Dele;
			Sleep(1000);
			cout << ".";
			Sleep(1000);
			cout << ".";
			Sleep(1000);
			cout << ".\n";
			cout << Succ << endl;
			again();
			break;
		}
		case 'a':
		{
			outputInfoMap();
			again();
			break;
		}
		case 'b':
		{
			InitQ();
			Init();
			outputInfoMap();
			int start;
			cout << loca1;
			cin >> start;
			BFS(start);
			output();
			again();
			break;
		}
		case 'c':
		{
			outputGraph();
			again();
			break;
		}
		case 's':
		{
			InitQ();
			Init2();
			outputInfoMap();
			if(n != 0)
			{
				int start, end;
				cout << loca1;
				cin >> start;
				cout <<  loca2;
				cin >> end;
				if(start >= 0 && end <= n){
					cout << path <<vertex[end]<<": ";
					FindNearRoad_BFS(start);
					outputRoads(start, end);
				}
				else cout << nopath;
			}
			cout<<endl;
			again();
			break;
		}

		case 'x':
		{
			system("cls");
			chooseLang();
			system("cls");
			inputLanguageFile();
			menu();
			break;
		}
		case '0':
			cout << bye << endl;
			break;

		default:
			cout << noFunc << endl;
			again();
			break;
	}
}

int main()
{
	chooseLang();
	system("cls");
	inputLanguageFile();
	menu();
	system("pause");
	return 0;
}