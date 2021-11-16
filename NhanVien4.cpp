#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<string>

#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
#define RIGHT 77
#define LEFT 75 

#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64

#define PASSWORD "abcdef"

using namespace std;

//------------------------------------WinDowns --------------------------------------

//-------------------vi tri--------------------
void gotoxy(short x, short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//--------------ham Thay doi kich thuoc console(man hinh chay)------------------
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
//------------------an hien con tro-------------------
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    
    SetConsoleCursorInfo(handle, &ConCurInf);
}
//---------------------------------------Ngay Thang------------------------------------------
class Day
{
protected:
	int ngay;
	int thang;
	int nam;
public:
	Day();
	Day(int ngay, int thang, int nam);
	Day(const Day& day);
	~Day();
	void NhapDay();
	void XuatDay();
	friend class QuanLiNhanVien;
};

Day::Day()
{
	ngay = 0;
	thang = 0;
	nam = 0;
}

Day::Day(int ngay, int thang, int nam)
{
	ngay = ngay;
	thang = thang;
	nam = nam;
}

Day::Day(const Day& day)
{
	*this = day;
}

Day::~Day()
{
}

void Day::NhapDay()
{
	char PhanChia;   //phan chia dung ki tu "/"
	cout << "(dd/mm/yyyy):  ";
	cin >> ngay >> PhanChia >> thang >> PhanChia >> nam;
}

void Day::XuatDay()
{
	cout << ngay << "/" << thang << "/" << nam << endl;
}


//------------------------------------XAY DUNG LOP NGUOI---------------------------------------
class Nguoi : public Day
{
private:
	string Ma;
	string HoTen;
	int Tuoi;
	string GioiTinh;
	Day NgaySinh;
	string DiaChi;
	float Luong;
public:
	//ham tao ham huy 
	Nguoi();
	Nguoi(string Ma, string HoTen, int Tuoi, string GioiTinh, string DiaChi, float Luong, float TienThuong);
	Nguoi(const Nguoi &nguoi);
	~Nguoi();
	virtual void Nhap();
	virtual void Xuat();
	
	virtual float TinhLuong() = 0;
	friend class QuanLiNhanVien;
};

Nguoi::Nguoi()
{
	this->Ma = "";
	this->HoTen = "";
	this->Tuoi = 0;
	this->GioiTinh = "";
	this->DiaChi = "";
	this->Luong = 0;
}

Nguoi::Nguoi(string Ma, string HoTen, int Tuoi, string GioiTinh, string DiaChi, float Luong, float TienThuong)
{
	this->Ma = Ma;
	this->HoTen = HoTen;
	this->Tuoi = Tuoi;
	this->GioiTinh = GioiTinh;
	this->DiaChi = DiaChi;
	this->Luong = Luong;
}

Nguoi::Nguoi(const Nguoi&nguoi)
{
	*this = nguoi;
}

Nguoi::~Nguoi()
{	
}

void Nguoi::Nhap()
{
	
	cout<<"\tNhap Vao Ma So Nhan Vien: ";
	fflush(stdin);
	getline(cin,Ma);
	cout<<"\tNhap Ho Va Ten (Day Du): ";
	fflush(stdin);
	getline(cin,HoTen);
	cout<<"\tNhap So Tuoi: ";
	cin >> Tuoi;
	cout<<"\tNhap Ngay Sinh  ";
	NgaySinh.NhapDay();
	cout<<"\tNhap Gioi Tinh: ";
	fflush(stdin);
	getline(cin,GioiTinh);
	cout<<"\tNhap Dia Chi: ";
	fflush(stdin);
	getline(cin,DiaChi);
}

void Nguoi::Xuat()
{
	cout<<"\tMa So Nhan Vien La: "<<Ma<<endl;
	cout<<"\tHo Ten Cua Nhan Vien La: "<<HoTen<<endl;
	cout<<"\tSo Tuoi La:"<<Tuoi<<endl;
	cout<<"\tNgay Sinh: ";
	NgaySinh.XuatDay();
	cout<<"\tGioi Tinh :"<<GioiTinh<<endl;
	cout<<"\tDia Chi: "<<DiaChi<<endl;
}
		//=============================THONG TIN NHAN VIEN===========================
		
//------------------------------Nhan vien chinh thuc-------------------
class NhanVienChinhThuc : public Nguoi
{
private:
	string ChucVu;
	int ThamNien;
	string BoPhan; //ke toan , desinger , CEO , chao hang , 
	float HeSoLuong;
public:
	void Nhap();
	void Xuat();
	float TinhLuong();//Hesoluong*1600*0.8
	float TienThuong();//bao nhieu cha duoc
	string getChucVu(){
		return ChucVu;
	}
	friend class QuanLiNhanVien; 
	friend class Nguoi;
};

void NhanVienChinhThuc::Nhap()
{
	Nguoi::Nhap();
	cout<<"\tNhap Chuc vu cua nhan vien la: ";
	fflush(stdin);
	getline(cin, ChucVu);
	cout<<"\tnhap vao tham nien: ";
	cin>> ThamNien;
	cout<<"nhap Vao bo Phan viec lam: ";
	fflush(stdin);
	getline(cin, BoPhan);
	cout<<"Nhap Vao He So Luong: ";
	cin>>HeSoLuong;
}
void NhanVienChinhThuc::Xuat()
{
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\tNhan Vien Chinh Thuc:"<<endl<<endl;
	Nguoi::Xuat();
	cout<<"\tChuc Vu cua nhan vien : "<<ChucVu<<endl;
	cout<<"\tTham Nien : "<<ThamNien<<endl;
	cout<<"\tBo Phan Lam Viec La: "<<BoPhan<<endl;
	cout<<"\tHe So Luong La: "<<HeSoLuong<<endl;
}


float NhanVienChinhThuc::TinhLuong()
{
	return (HeSoLuong*1600*0.8);
}
void Sua(NhanVienChinhThuc &a)
{
	
}
//---------------------------------Nhan Vien Ban Thoi Gian-------------------

class NhanVienBanThoiGian : public Nguoi
{
private:
	int SoGioLam;
	float SoLuongTheoGio;
public:
	void Nhap();
	void Xuat();
	float TinhLuong();// so gio nhan voi so luong theo gio
	friend class QuanLiNhanVien;
};

void NhanVienBanThoiGian::Nhap()
{
	Nguoi::Nhap();
	cout<<"\tNhap So Gio Lam : ";
	cin>>SoGioLam;
	cout<<"\tNhap So Luong Theo Gio: ";
	cin>> SoLuongTheoGio;
}

void NhanVienBanThoiGian::Xuat()
{
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\tNhan Vien Ban Thoi Gian:"<<endl<<endl;
	Nguoi::Xuat();
	cout<<"\tSo Gio Lam la: "<<SoGioLam<<endl;
	cout<<"\tSo luong Theo Gio La: "<<SoLuongTheoGio<<endl;
}

float NhanVienBanThoiGian::TinhLuong(){
	return (SoGioLam*SoLuongTheoGio);
}



//-------------------------------Nhan Vien Ban Theo San Pham----------------------


class NhanVienLamTheoSanPham : public Nguoi
{
private:
	int SoLuongHang;
	float GiaHang;
public:
	void Nhap();
	void Xuat();
	float TinhLuong();//so luong hang * gia hang
	friend class QuanLiNhanVien;
};

void NhanVienLamTheoSanPham::Nhap()
{
	Nguoi::Nhap();
	cout<<"\tNhap So Luong Hang Hoa: ";
	cin>>SoLuongHang;
	cout<<"\tNhap Vao Gia Hang: ";
	cin>>GiaHang;
}

void NhanVienLamTheoSanPham::Xuat()
{
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\tNhan Vien Lam Theo San Pham:"<<endl<<endl;
	Nguoi::Xuat();
	cout<<"\tSo Luong Hang Hoa: "<<SoLuongHang<<endl;
	cout<<"\tVao Gia Hang: "<<GiaHang<<endl;
}
float NhanVienLamTheoSanPham::TinhLuong(){
	return (SoLuongHang *GiaHang);
}

//--------------------------------------Nhan Vien Thu Viec---------------------------

class NhanVienThuViec : public Nguoi
{
private:
	Day NgayVaoLam;
	float LuongTheoGio;
public:
	void Nhap();
	void Xuat();
	float TinhLuong();// muc luong co ban cua nhan vien = luong theo gio* 8 time;
	friend class QuanLiNhanVien;
}; 

void NhanVienThuViec::Nhap()
{
	Nguoi::Nhap();
	cout<<"\tNhap thoi gian vao lam ";
	NgayVaoLam.NhapDay();
	cout<<"\tNhap vao muc luong theo gio: ";
	cin>>LuongTheoGio;	
}	

void NhanVienThuViec::Xuat()
{
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\t Nhan Vien Thu Viec:"<<endl<<endl;
	Nguoi::Xuat();
	cout<<"\tNgay vao lam la: ";
	NgayVaoLam.XuatDay();
	cout<<"\tMuc Luong Theo Gio La: "<<LuongTheoGio<<endl;
}

float NhanVienThuViec::TinhLuong(){
	return (LuongTheoGio*8);
}



//==============================danh sach lien ke========================

typedef int Item;
struct Node {
	Nguoi *data;
	Node *next;
}; 
class QuanLiNhanVien
{
private:
	Node *head;
	Node *tail;
	long size;
public:
	QuanLiNhanVien();//khhoi tao quan li nhan vien 
    ~QuanLiNhanVien();
	Node* CreateNode(Nguoi* nv);
	void AddLast(Nguoi *nv);
	void traverse();//duyet danh sach
	void XuatDS();
	void insertafter(Node* p, Nguoi *nv);
	void TimKiemTen();
	void TimKiemMa();
	void DemNhanVien();
	void SuaNhanVien();
	Node *previous(Node *p); 
	void removefirst();
	void removelast();
	void XoaNhanVien();
	void swapData(Node *p, Node *q);
	void SapXepTen();
	void SapXepMa();
	void MaxLuong();
	void MinLuong();
	void TongLuong();
	Node* getHead(){
		return head;
	}

}; 

        //begin
QuanLiNhanVien::QuanLiNhanVien()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

QuanLiNhanVien::~QuanLiNhanVien()
{
	delete head;
	delete tail;
	size = 0;
}
Node* QuanLiNhanVien::CreateNode(Nguoi *nv)
{
	Node* p = new Node;
	p->data = nv;
	p->next = NULL;
	return p;
}
void QuanLiNhanVien::AddLast(Nguoi *nv) {
    Node *p = CreateNode(nv);
    if (size == 0) {
        head = p;
        tail = p;
    }
    else {
        tail->next = p;
        tail = p;      
    }
    size ++;
}

void QuanLiNhanVien::traverse(){
	Node* p = head;
	while (p != NULL) {
		cout << p->data << "\t";
		p = p->next;
	}
	cout << endl;
	delete p;
}
//cout luong moi nguoi
void QuanLiNhanVien::XuatDS(){
	system("cls");
	Nguoi *nv;
	cout<<endl<<"*******Danh sach Nhan Vien*******"<<endl<<endl;
	for(Node *p= head;p!=NULL;p = p->next){
		p->data->Xuat();
    }
}
void QuanLiNhanVien::insertafter(Node* p, Nguoi *nv){
	if (p == tail)
        AddLast(nv);
    else {
        Node *q = CreateNode(nv);
        q->next = p->next;
        p->next = q;      
    }
    size++;
}
void QuanLiNhanVien::TimKiemTen(){
	string TenTK;

	cout<<"Nhap Ten Nhan Vien can tim:";
	fflush(stdin);
	getline(cin,TenTK);
	for(Node*p=head;p!=NULL;p=p->next){
		if(p->data->HoTen==TenTK){
			p->data->Xuat();
		}
	}
}

void QuanLiNhanVien::DemNhanVien(){
	int Dem=0;
	for(Node*p=head;p!=NULL;p=p->next){
		Dem++;
	}
	cout<<"Tong so Nhan Vien la:"<<Dem<<endl;
}


Node* QuanLiNhanVien::previous(Node *p) {
	Node *t = head;
	while (t->next != p)
		t = t->next;
	return t;
}
void QuanLiNhanVien::removefirst(){
    if (size == 0)
        return;
    Node *t = head;
    head = head->next;
    delete t;
    size--;
}

void QuanLiNhanVien::removelast() {
    if (size == 0)
        return;
    if (size == 1) {
        delete head;
        size--;
        return;
    }
    Node *p = previous(tail);
    Node *t = tail;    
    p->next = NULL;
    tail = p;
    delete t;
    size--;
}


void QuanLiNhanVien::XoaNhanVien(){
	string Maxoa;
	cout<<"Nhap Ma Nhan Vien can xoa:";
	fflush(stdin);
	getline(cin,Maxoa);
	for(Node*p=head;p!=NULL;p=p->next){
		if(p->data->Ma == Maxoa){
			if(p==head){
			   	removefirst();
			   	return;
			}
			else if(p==tail){
				removelast();
				return;
			}
			else{
				Node *pre =  previous(p);
            	pre->next = p->next;
				delete p;
				size--;
			}
		}
	}
}




void QuanLiNhanVien::swapData(Node *p, Node *q){
	Nguoi *temp;
    temp = p->data;
    p->data = q->data;
    q->data = temp;
}
void QuanLiNhanVien::SapXepTen(){
	Node*temp;
	for(Node*p=head;p!=tail;p=p->next){
		for(Node*q=p->next;q!=NULL;q=q->next){
		    if(p->data->HoTen > q->data->HoTen){
		        swapData(p,q);
		   }
		}
	}
}
void QuanLiNhanVien::SapXepMa(){
	Node*temp;
	for(Node*p=head;p!=tail;p=p->next){
		for(Node*q=p->next;q!=NULL;q=q->next){
		    if(p->data->Ma > q->data->Ma){
		        swapData(p,q);
		   }
		}
	}
}
void QuanLiNhanVien::MaxLuong(){
	Node*p=head;
	Nguoi *Max=head->data;
	for(p=head->next;p!=NULL;p=p->next){
		if(p->data->TinhLuong() < Max->TinhLuong()){
			Max=p->data;
		}
	}
	cout<<"Nhan Vien co Luong cao nhat"<<endl;
	Max->Xuat();
}       

void QuanLiNhanVien::MinLuong(){
	Node*p=head;
	Nguoi *Min=head->data;
	for(p=head->next;p!=NULL;p=p->next){
		if(p->data->TinhLuong() > Min->TinhLuong()){
			Min=p->data;
		}
	}
	cout<<"Nhan Vien co Luong cao nhat"<<endl;
	Min->Xuat();
}            
void QuanLiNhanVien::TongLuong(){
	float Tong=0;
	for(Node*p=head;p!=NULL;p=p->next){
		Tong=Tong+ p->data->TinhLuong();
	}
	cout<<"Tong Luong cua tat ca Nhan Vien la:"<<Tong<<endl;
}

//Ã½ tÆ°á»Ÿng 
//Äáº·t máº­t kháº©u cho PhÃ¢n cáº£nh bÃ¡o	
void QuanLiNhanVien::TimKiemMa(){
	string MaTK;
	cout<<"Nhap Ma Nhan Vien can tim:";
	fflush(stdin);
	getline(cin,MaTK);
	for(Node*p=head;p!=NULL;p=p->next){
		if(p->data->Ma==MaTK){
			p->data->Xuat();
		}
	}
}	
void QuanLiNhanVien::SuaNhanVien(){
	int chon, chon1, chon2, chon3;
	int Flat= 1 , Tlat=1;
	while (Flat)
	{
		string MaTK;
		cout<<"Nhap Ma Nhan Vien can tim:";
		fflush(stdin);
		getline(cin,MaTK);
		for(Node*p=head;p!=NULL;p=p->next){
			if(p->data->Ma==MaTK){				
				cout<<"Sua chua:"<<endl;
				cout<<"1: Sua Thong Tin co Ban. "<<endl;
				cout<<"2: Sua Thong Tin Theo Chuyen sau.  Canh Bao!  (Day La Noi Nhan Vien Khong Duoc Nhap Vo) "<<endl;
				cout<<"3: Thoat."<<endl;
				cout<<"Hay Lua Chon Theo Yeu Cau Ban Muon (Bam So)";
				cin>>chon;
				switch(chon)
				{
					case 1:
						{
							while(Flat)
							{
								cout<<"1: Sua Ten  "<<endl; 
								cout<<"2: Sua Tuoi "<<endl;
								cout<<"3: Sua Nam Sinh "<<endl;
								cout<<"4: Sua Gioi Tinh"<<endl;
								cout<<"5: Sua Dia Chi "<<endl;
								cout<<"6: Thoat"<<endl;
								cout<<"chon vao Thu can sua(Bam So): ";
								cin>>chon1;
								switch(chon1)
								{
									case 1:
									{
										string Ten;
										cout<<"Nhap Vao Ten Can Sua La: ";
										fflush(stdin);
										getline(cin,Ten);
										p->data->HoTen = Ten ;
										cout<<"Ten Da Duoc Sua La: ";
										p->data->Xuat();
										break;
									}
										
									case 2:
									{
										int Tuoi;
										cout<<"Nhap Vao Tuoi Can Sua : ";
										cin>>Tuoi;
										p->data->Tuoi = Tuoi;
										cout<<"Tuoi Da Duoc Sua La: ";
										p->data->Xuat();
										break;
									}	
									case 3:
									{
										Day NgaySinh;
										cout<<"Nhap Ngay Sinh Can Sua ";
										NgaySinh.NhapDay();
										p->data->NgaySinh = NgaySinh;
										cout<<"Ngay Sinh Da Duoc Sua La: ";
										p->data->Xuat();
										break;
									}
										
									case 4:
									{
										string GioiTinh;
										cout<<"Nhap Vao Gioi Tinh Can Sua La: ";
										fflush(stdin);
										getline(cin,GioiTinh);
										p->data->GioiTinh = GioiTinh ;
										cout<<"Gioi Tinh Da Duoc Sua La: ";
										p->data->Xuat();	
										break;
									}
									
									case 5:
									{
										string DiaChi;
										cout<<"Nhap Vao Dia Chi Can Sua La: ";
										fflush(stdin);
										getline(cin,DiaChi);
										p->data->DiaChi = DiaChi ;
										cout<<"Dia Chi Da Duoc Sua La: ";
										p->data->Xuat();
										break;
									}
									case 6:
									{
										Flat = 0;
										break;
									}
									default:
									{
										cout<<"Chuc Nang Ban Nhap khong Dung. Xin Vui Long Nhap Lai!"<<endl;
										break;
									}	
								}
							}
						}
					case 2:
						{
							while(Flat)
							{
								cout<<"Hay Chon Vung Sua Chua Ma Ban Muon Sua Doi"<<endl;
								cout<<"1: Sua Chua Trong Nhan vien Chinh Thuc."<<endl;
								cout<<"2: Sua Chua Trong Nhan Vien Ban Thoi Gian."<<endl;
								cout<<"3: sua chua Trong Nhan Vien Lam Theo San Pham."<<endl;
								cout<<"4: Sua Chua Theo Nhan Vien Thu Viec."<<endl;
								cout<<"5: Thoat."<<endl;
								cout<<"Chon Mot Chuc Nang (Bam So): ";
								cin>>chon2;
								switch(chon2)
								{
									case 1:
									{
										cout<<"1: Sua Chuc Vu"<<endl;
										cout<<"1: Sua Tham Nien"<<endl;
										cout<<"3: Sua Bo Phan "<<endl;
										cout<<"4: Sua He So Luong "<<endl;
										cout<<"chon vao Thu can sua (Bam So): ";		
										cin>>chon3;
										if(chon3 = 1)
										{
											
											string ChucVu;
											cout<<"Nhap Vao Chuc Vu Can Sua La: ";
											fflush(stdin);
											getline(cin,ChucVu);
											//p->data->getChucVu() = ChucVu;
											
											cout<<"Chuc Vu Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else if(chon3 = 2)
										{
											int ThamNien;
											cout<<"Nhap Vao Tham Nien Can Sua : ";
											cin>>ThamNien;
											//p->data->ThamNien = ThamNien;
											cout<<"Tham Nien Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else if(chon3 = 3)
										{
											string BoPhan;
											cout<<"Nhap Vao Bo Phan Can Sua La: ";
											fflush(stdin);
											getline(cin,BoPhan);
										//	p->data->BoPhan = BoPhan ;
											cout<<"Bo Phan Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else if(chon3 = 4)
										{
											float HeSoLuong;
											cout<<"Nhap Vao He So Luong Can Sua La: ";
											cin>>HeSoLuong;
											//p->data->HeSoLuong = HeSoLuong ;
											cout<<"He So Luong Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else
											cout<<"Ban Chon Sai Va Bat Dau Lai Tu Dau"<<endl;
										
									}
									case 2:
									{
										cout<<"1: Sua So Gio Lam "<<endl;
										cout<<"2: Sua So Luong Theo Gio"<<endl;
										cout<<"chon vao Thu can sua (Bam So): ";		
										cin>>chon3;
										if(chon3 = 1)
										{
											int SoGioLam;
											cout<<"Nhap Vao So Gio Lam Can Sua : ";
											cin>>SoGioLam;
										//	p->data->SoGioLam = SoGioLam;
											cout<<"So Gio Lam Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else if(chon3 = 2)
										{
											float SoLuongTheoGio;
											cout<<"Nhap Vao So Luong Theo Gio Can Sua : ";
											cin>>SoLuongTheoGio;
										//	p->data->SoLuongTheoGio = SoLuongTheoGio;
											cout<<"So Luong Theo Gio Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else
											cout<<"Ban Chon Sai Va Bat Dau Lai Tu Dau"<<endl;
									}
									case 3:
									{
										cout<<"3: Sua So Luong Hang "<<endl;
										cout<<"6: Sua Gia Hang "<<endl;
										cout<<"chon vao Thu can sua (Bam So): ";		
										cin>>chon3;
										if(chon3 = 1)
										{
											int SoLuongHang;
											cout<<"Nhap Vao So Luong Hang Can Sua : ";
											cin>>SoLuongHang;
										//	p->data->SoLuongHang = SoLuongHang;
											cout<<"So Luong Hang Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else if(chon3 = 2)
										{
											float GiaHang;
											cout<<"Nhap Vao Gia Hang Can Sua : ";
											cin>>GiaHang;
										//	p->data->GiaHang = GiaHang;
											cout<<"Gia Hang Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else
											cout<<"Ban Chon Sai Va Bat Dau Lai Tu Dau"<<endl;
									}
									case 4:
									{
										cout<<"7: Sua Luong Theo Gio"<<endl;
										cout<<"8: Sua Ngay Vao Lam"<<endl;
										cout<<"chon vao Thu can sua (Bam So): ";		
										cin>>chon3;
										if(chon3 = 1)
										{
											float LuongTheoGio;
											cout<<"Nhap Vao Luong Theo Gio Can Sua : ";
											cin>>LuongTheoGio;
										//	p->data->LuongTheoGio = LuongTheoGio;
											cout<<"Luong Theo Gio Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else if(chon3 = 2)
										{
											Day NgayVaoLam;
											cout<<"Nhap Ngay Vao Lam Can Sua ";
											NgayVaoLam.NhapDay();
										//	p->data->NgayVaoLam = NgayVaoLam;
											cout<<"Ngay Vao Lam Da Duoc Sua La: ";
											p->data->Xuat();
										}
										else
											cout<<"Ban Chon Sai Va Bat Dau Lai Tu Dau"<<endl;
									}
									case 5:
									{
										Flat = 0;
										break;
									}
									default:
									{
										cout<<"Chuc Nang Ban Nhap khong Dung. Xin Vui Long Nhap Lai!"<<endl;
										break;
									}	
								}
							}
						}
					case 3:
					{
						Flat = 0;
						break;
					}
					default:
					{
						cout<<"Chuc Nang Ban Nhap khong Dung. Xin Vui Long Nhap Lai!"<<endl;
						break;
					}
				}
			}
		}
	}
}

//----------------------------------------cac Ham --------------------------------



//==============================Ham Nhap ================================

void NhapDS (QuanLiNhanVien &QL)
{
	system("cls");
	Nguoi *nv;
	int SL1,SL2,SL3,SL4;
	cout<<"Nhap so Luong Nhan Vien Chinh Thuc:";
	cin>>SL1;
	for (int i = 0; i < SL1; i++)
	{
		nv = new NhanVienChinhThuc;
		cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
	cout<<"Nhap so Luong Ban Thoi Gian:";
	cin>>SL2;
	for (int i = 0; i < SL2; i++)
	{
		nv = new NhanVienBanThoiGian;
		cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
	cout<<"Nhap so Luong lam theo san pham:";
	cin>>SL3;
	for (int i = 0; i < SL3; i++)
	{
		nv = new NhanVienLamTheoSanPham;
		cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
	cout<<"Nhap so Luong Thu viec:";
	cin>>SL4;
	for (int i = 0; i < SL4; i++)
	{
		nv = new NhanVienThuViec;
		cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
}
void ThemNhanVien(QuanLiNhanVien &QL)
{
	Nguoi *nv;
	int x = 15, y = 15;
	int NhanNut,Flat=0;
	Node* p=QL.getHead();
	char text[5][100]={"1: Nhan vien Chinh Thuc." ,"2: Nhan Vien Lam Theo San Pham." ,"3: Nhan Vien Ban Thoi Gian.","4: Nhan Vien Thu Viec.","5: Thoat"};
Menu:
	system("cls");
	SetWindowSize(100, 40);
	SetWindowSize(100, 40);
	int c = 0;
	int i = 1;
	do {
		if (kbhit())
		{
			if (c = getch())
				break;
		}
		SetColor(i++);
		if (i == 19)
		{
			i = 15;
		}
		system("cls");
     	gotoxy(10, 5); cout <<     "                                 THEM NHAN VIEN ";
		Sleep(100);
	} while (1);
	gotoxy(15, 16); cout << text[0];
	gotoxy(15, 17); cout << text[1];
	gotoxy(15, 18); cout << text[2];
	gotoxy(15, 19); cout << text[3];
	gotoxy(15, 20); cout << text[4];
	while(Flat)
	{
		gotoxy(x, y);
		SetColor(15);
		switch (y)
		{
			case 15: gotoxy(15, 16); cout << text[0]; break;
			case 16: gotoxy(15, 17); cout << text[1]; break;
			case 17: gotoxy(15, 18); cout << text[2]; break;
			case 18: gotoxy(15, 19); cout << text[3]; break;
			case 19: gotoxy(15, 20); cout << text[4]; break;
		}
		NhanNut = getch();
		if (NhanNut == UP)
		{
			gotoxy(x, y);
			SetColor(15);
			switch (y)
			{
				case 15: gotoxy(15, 16); cout << text[0]; break;
				case 16: gotoxy(15, 17); cout << text[1]; break;
				case 17: gotoxy(15, 18); cout << text[2]; break;
				case 18: gotoxy(15, 19); cout << text[3]; break;
				case 19: gotoxy(15, 20); cout << text[4]; break;
			}
			y--;
			if (y < 15)
			{
				y = 19;
			}
		}
		else if (NhanNut == DOWN)
		{
			gotoxy(x, y);
			SetColor(15);
			switch (y)
			{
				case 15: gotoxy(15, 16); cout << text[0]; break;
				case 16: gotoxy(15, 17); cout << text[1]; break;
				case 17: gotoxy(15, 18); cout << text[2]; break;
				case 18: gotoxy(15, 19); cout << text[3]; break;
				case 19: gotoxy(15, 20); cout << text[4]; break;
			}
			y++;
			if (y > 19)
			{
				y = 15;
			}	
		}
		if (y == 15 && NhanNut == ENTER)
		{	
			SetColor(15);
			system("cls");	
			while(p !=NULL)
			{
	   			if(p->data == nv) 
					break;
    			p=p->next;
	   		}
	   		cout<<"Nhap vao Nhan Vien can Them can them: "<<endl;
	   		nv =new NhanVienChinhThuc;
	   		nv->Nhap();
	   		QL.insertafter(p,nv);
	   		goto Menu;
		}
		else if (y == 16 && NhanNut == ENTER)
		{	
			SetColor(15);
			system("cls");
			while(p !=NULL)
			{
	       		if(p->data == nv) 
					break;
	        	p=p->next;
	   		}
	   		cout<<"Nhap vao Nhan Vien can Them can them: "<<endl;
	   		nv =new NhanVienBanThoiGian;
	   		nv->Nhap();
	   		QL.insertafter(p,nv);
	    	goto Menu;
		}
		else if (y == 17 && NhanNut == ENTER)
		{
			SetColor(15);
			system("cls");
			while(p !=NULL)
			{
	       		if(p->data == nv) 
					break;
	       		p=p->next;
	    	}
	   		cout<<"Nhap vao Nhan Vien can Them can them: "<<endl;
	   		nv = new NhanVienLamTheoSanPham;
			nv->Nhap();
	   		QL.insertafter(p,nv);
	    	goto Menu;
		}
		else if (y == 18 && NhanNut == ENTER)
		{		
			SetColor(15);
			system("cls");
			while(p !=NULL)
			{
	       		if(p->data == nv) 
					break;
	       		p=p->next;
    		}
			cout<<"Nhap vao Nhan Vien can Them can them: "<<endl;
	   		nv = new NhanVienThuViec;
			nv->Nhap();
	   		QL.insertafter(p,nv);
	    	goto Menu;
		}
		else if (y == 19 && NhanNut == ENTER)
		{
			Flat = 1;
			SetColor(15);
		}
	}
}
//nÃªn Ä‘áº·t máº­t kháº©u
/*DÃ¹ng hÃ m kbhit cÃ³ trong thÆ° viá»‡n #include <conio.h>
kbhit(void): Kiá»ƒm tra xem ngÆ°á»i dÃ¹ng cÃ³ nháº¥n vÃ o 1 phÃ­m báº¥t ká»³ nÃ o trÃªn bÃ n phÃ­m hay khÃ´ng ?
=> Láº¥y giÃ¡ trá»‹ cá»§a phÃ­m Ä‘Ã³ ra nhá» vÃ o getch()*/

void Menu()
{
	QuanLiNhanVien t;
	int n;
	int Chon, Flat =1;
	int x = 15, y = 1;
	int NhanNut;
	char text[14][100]={" 1. NHAP NHAN VIEN ", " 2. XUAT NHAN VIEN ", " 3. THEM NHAN VIEN "," 4. SUA NHAN VIEN "," 5. TONG SO NHAN VIEN ", " 6. TIM KIEM NHAN VIEN THEO TEN ", " 7. TIM KIEM NHAN VIEN THEO MA ",
	" 8. XOA NHAN VIEN " , " 9. SAP XEP THEO TEN NHAN VIEN ", "10. SAP XEP THEO MA NHAN VIEN ","11. MAX LUONG ", "12. MIN LUONG ","13. TONG LUONG ", "14. KET THUC CHUONG TRINH "};
Menu:	
	SetWindowSize(100, 40);
	int c = 0;
	int i = 1;
	do {
	
		if (kbhit())
		{
			if (c = getch())
				break;
		}
		SetColor(i++);
		if (i == 15)
		{
			i = 1;
		}
		system("cls");
     	gotoxy(10, 5); cout <<     "                                 QUAN LY NHAN VIEN ";
		Sleep(500);
	} while (1);
	gotoxy(15, 16); cout << text[0];
	gotoxy(15, 17); cout << text[1];
	gotoxy(15, 18); cout << text[2];
	gotoxy(15, 19); cout << text[3];
	gotoxy(15, 20); cout << text[4];
	gotoxy(15, 21); cout << text[5];
	gotoxy(15, 22); cout << text[6];
	gotoxy(15, 23); cout << text[7];
	gotoxy(15, 24); cout << text[8];
	gotoxy(15, 25); cout << text[9];
	gotoxy(15, 26); cout << text[10];
	gotoxy(15, 27); cout << text[11];
	gotoxy(15, 28); cout << text[12];
	gotoxy(15, 29); cout << text[13];
	
	do{
		
		gotoxy(x, y);
		SetColor(15);
		switch (y)
		{
			case 1: gotoxy(15, 16); cout << text[0]; break;
			case 2: gotoxy(15, 17); cout << text[1]; break;
			case 3: gotoxy(15, 18); cout << text[2]; break;
			case 4: gotoxy(15, 19); cout << text[3]; break;
			case 5: gotoxy(15, 20); cout << text[4]; break;
			case 6: gotoxy(15, 21); cout << text[5]; break;
			case 7: gotoxy(15, 22); cout << text[6]; break;
			case 8: gotoxy(15, 23); cout << text[7]; break;
			case 9: gotoxy(15, 24); cout << text[8]; break;
			case 10: gotoxy(15, 25); cout << text[9]; break;
			case 11: gotoxy(15, 26); cout << text[10];break;
			case 12: gotoxy(15, 27); cout << text[11];break;
			case 13: gotoxy(15, 28); cout << text[12];break;
			case 14: gotoxy(15, 29); cout << text[13];break;
		}
		NhanNut = getch();
		if (NhanNut == UP)
		{
			gotoxy(x, y);
			SetColor(15);
			switch (y)
			{
				case 1: gotoxy(15, 16); cout << text[0]; break;
				case 2: gotoxy(15, 17); cout << text[1]; break;
				case 3: gotoxy(15, 18); cout << text[2]; break;
				case 4: gotoxy(15, 19); cout << text[3]; break;
				case 5: gotoxy(15, 20); cout << text[4]; break;
				case 6: gotoxy(15, 21); cout << text[5]; break;
				case 7: gotoxy(15, 22); cout << text[6]; break;
				case 8: gotoxy(15, 23); cout << text[7]; break;
				case 9: gotoxy(15, 24); cout << text[8]; break;
				case 10: gotoxy(15, 25); cout << text[9]; break;
				case 11: gotoxy(15, 26); cout << text[10];break;
				case 12: gotoxy(15, 27); cout << text[11];break;
				case 13: gotoxy(15, 28); cout << text[12];break;
				case 14: gotoxy(15, 29); cout << text[13];break;
			}
			y--;
			if (y < 1)
			{
				y = 14;
			}
		}
		else if (NhanNut == DOWN)
		{
			gotoxy(x, y);
			SetColor(15);
			switch (y)
			{
				case 1: gotoxy(15, 16); cout << text[0]; break;
				case 2: gotoxy(15, 17); cout << text[1]; break;
				case 3: gotoxy(15, 18); cout << text[2]; break;
				case 4: gotoxy(15, 19); cout << text[3]; break;
				case 5: gotoxy(15, 20); cout << text[4]; break;
				case 6: gotoxy(15, 21); cout << text[5]; break;
				case 7: gotoxy(15, 22); cout << text[6]; break;
				case 8: gotoxy(15, 23); cout << text[7]; break;
				case 9: gotoxy(15, 24); cout << text[8]; break;
				case 10: gotoxy(15, 25); cout << text[9]; break;
				case 11: gotoxy(15, 26); cout << text[10];break;
				case 12: gotoxy(15, 27); cout << text[11];break;
				case 13: gotoxy(15, 28); cout << text[12];break;
				case 14: gotoxy(15, 29); cout << text[13];break;
			}
			y++;
			if (y > 14)
			{
				y = 1;
			}
		}

		if (y == 1 && NhanNut == ENTER)
		{
			SetColor(15);
			system("cls");
			NhapDS(t);
			goto Menu;
		}
		else if (y == 2 && NhanNut == ENTER)
		{
			SetColor(15);
			system("cls");
			t.XuatDS();
			goto Menu;
		}
		else if (y == 3 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			ThemNhanVien(t);
			goto Menu;
		}
		else if (y == 4 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.SuaNhanVien();
			goto Menu;
		}
		else if (y == 5 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.DemNhanVien();
			goto Menu;
		}
		else if (y == 6 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.TimKiemTen();
			goto Menu;
		}
		else if (y == 7 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.TimKiemMa();
			goto Menu;
		}
		else if (y == 8 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.XoaNhanVien();
			goto Menu;
		}
		else if (y == 9 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.SapXepTen();
			t.XuatDS();
			goto Menu;
		}
		else if (y == 10 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.SapXepMa();
			t.XuatDS();
			goto Menu;
		}
		else if (y == 11 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.MaxLuong();
			goto Menu;
		}
		else if (y == 12 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.MinLuong();
			goto Menu;
		}
		else if (y == 13 && NhanNut == ENTER)
		{
			SetColor(15);
		//	system("cls");
			t.TongLuong();
			goto Menu;
		}
		
		else if (y == 14 && NhanNut == ENTER)
		{
			exit(0);
			SetColor(15);
		}	
	} while (true);
}	
int main()
{
    Menu();
}
