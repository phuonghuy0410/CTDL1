#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX 20

struct SinhVien
{
	long mssv;
	string hoTen;
	char ngaySinh[11];
	string queQuan;
	double dtb;
};

void nhap1Sv(SinhVien& sv) {
	cout << "Nhap MSSV: ";
	cin >> sv.mssv;
	cout << "Nhap ho ten: ";
	cin.ignore(1);
	getline(cin, sv.hoTen, '\n');
	cout << "Nhap ngay sinh: ";
	cin >> sv.ngaySinh;
	cout << "Nhap que quan: ";
	cin.ignore(1);
	getline(cin, sv.queQuan);
	cout << "Nhap diem TB: ";
	cin >> sv.dtb;
}

void xuat1Sv(SinhVien sv) {
	cout << "===============================\n";
	cout << "ID: ";
	cout << sv.mssv << endl;
	cout << "Ho va ten: ";
	cout << sv.hoTen << endl;
	cout << "Ngay sinh: ";
	cout << sv.ngaySinh << endl;
	cout << "Que quan: ";
	cout << sv.queQuan << endl;
	cout << "Diem trung binh: ";
	cout << sv.dtb << endl;
	cout << "===============================\n";
}

//Khai bao cau truc
struct Node {
	//Vung thong tin
	SinhVien info;

	//Vung lien ket
	Node* next;
};

//Khoi tao rong
void init(Node *&head) {
	head = NULL;
}
//Tao node moi
Node* createNode(SinhVien x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}
//Them dau
void addFirst(Node*& head, SinhVien x) {
	Node* p = createNode(x);
	p->next = head;
	head = p;
}
//Them vào ds
void addOrdered(Node*& head, SinhVien x) {
	// Nếu danh sách rỗng hoặc x có mssv nhỏ hơn head → chèn đầu
	if (head == NULL || head->info.mssv > x.mssv) {
		addFirst(head, x);
		return;
	}

	Node* p = createNode(x); // Tạo node mới
	Node* q = head;

	// Tìm vị trí để chèn: duyệt đến node trước chỗ cần chèn
	while (q->next != NULL && q->next->info.mssv < x.mssv) {
		q = q->next;
	}

	// Chèn node p sau node q
	p->next = q->next;
	q->next = p;
}

//Them phan tu vao cuoi danh sach
void insertLast(Node*& head, SinhVien x) {
	Node* p = createNode(x);


	if (head == NULL) {
		head = p;
	}
	else {
		Node* tmp = head;

		while (tmp->next != NULL) {
			tmp = tmp->next;
		}

		tmp->next = p;
	}
	
}

void inputListFromFile(Node *&head, string fileName) {
	ifstream fin(fileName);

	if (fin.is_open()) {

		while (!fin.eof()) {
			SinhVien sv;

			fin >> sv.mssv;
			fin.ignore();
			getline(fin, sv.hoTen, '#');
			fin.getline(sv.ngaySinh, 11, '#');
			getline(fin, sv.queQuan, '#');
			fin >> sv.dtb;

			insertLast(head, sv);
		}

		fin.close();
	}
}

//Duyet danh sach
void printList(Node* head) {
	if (head == NULL) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* tmp = head;
	while (tmp != NULL) {
		xuat1Sv(tmp->info);
		tmp = tmp->next;
	}
	
}

//Xoa dau 
void delFirst(Node*& head) {
	if (head == NULL)
		return;
	Node* p = head;
	head = head->next;
	p->next = nullptr;
	delete p;
}
//Xoa cuoi
void delLast(Node*& head) {
	if (head == NULL)
		return ;
	Node* q = head;
	Node* prevQ = NULL;
	while (q->next != NULL) {
		prevQ = q;
		q = q->next;
	}
	if (prevQ == NULL) {
		head = NULL;
	}
	else
		prevQ->next = NULL;

	delete q;
}
//Xoa node q
bool delNode(Node*& head, const int key) {
	Node* q = head;         // q là node đang duyệt
	Node* qPrev = NULL;     // qPrev là node trước q

	while (q != NULL && q->info.mssv != key) {
		qPrev = q;
		q = q->next;
	}

	if (q == NULL)
		return false;       // Không tìm thấy 

	if (qPrev == NULL) {
		head = head->next;  // Xóa đầu 
	}
	else {
		qPrev->next = q->next; // bỏ q 
	}

	q->next = NULL;         // Ngắt liên kết
	delete q;      
	return true;            // Xóa thành công
}



//Tim kiem
Node* search(Node* head, int id) {
	Node* p = head;
	while (p != NULL && p->info.mssv != id) {
		p = p->next;
	}
	return p;
}
//Sap xep
 void sort(Node* head) {
if (head != NULL) {
	for (Node* i = head; i->next != NULL; i = i->next) {
		for (Node* j = i->next; j != NULL; j = j->next) {
			if (j->info.mssv > i->info.mssv)
				swap(i->info, j->info);
		}
	}
}	
}
 //Truy xuat phan tu thu i
 Node* getNodeAt(Node*& head, int index) {
	 Node* p = head;
	 int i = 0;
	 while (p != NULL && i < index) {
		 p = p->next;
		 i++;
	 }
	 return p;
 }
//Giai phong
void detroyList(Node*& head) {
	while (head != NULL) {
		delFirst(head);
	}
}


int main() {
	Node* head;
	init(head);

	inputListFromFile(head, "SinhVien.txt");
	//printList(head);
	/*cout << "-----TIM KIEM-----\n";
	Node* q = search(head, 2018003);
	if (q) {
		xuat1Sv(q->info);
	}
	else
		cout << "Khong tim thay!\n";
		*/
		/*cout << "-----XOA DAU-----\n";
		delFirst(head);
		printList(head);
		cout << "-----XOA CUOI-----\n";
			delLast(head);
	
		 cout << "-----XOA NODE q MANG GIA TRI ID-----\n";
			delNode(head, 2018009);
			printList(head);*/

	/*cout << "-----SAP XEP-----\n";
			sort(head);
			printList(head); */
	/*cout << "--------THEM VAO SAU NODE q--------"\n;
	SinhVien sv;
	cin >> sv.mssv;
	addOrdered(head, sv);
	printList(head);*/
	/*cout << "-----TRUY XUAT PHAN TU THU ....-----\n";
	Node* q = getNodeAt(head, 0);
	xuat1Sv(q->info); */
	detroyList(head);
	return 0;
}