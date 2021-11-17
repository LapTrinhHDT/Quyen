#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<string>
#include <sstream>
#include <string.h>
#include <string>

#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
#define RIGHT 77
#define LEFT 75 

#define boxx 15 //Vi tri x bat dau cua box
#define boxx1 45
#define boxy 13 //Vi tri y bat dau cua box
#define boxs 60 //Box size
#define tabx 6 // vi tri x bat dau cua table
#define taby 4  // vi tri y bat dau cua table
#define tabs 90 // table box
#define tabw 23 // table hight

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
void textcolor(WORD color)
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
	fflush(stdin);
	gotoxy(boxx1, boxy +2);getline(cin,Ma);
	fflush(stdin);
	gotoxy(boxx1, boxy +4);getline(cin,HoTen);
	gotoxy(boxx1, boxy +6);cin >> Tuoi;
	gotoxy(boxx1, boxy +8);NgaySinh.NhapDay();
	fflush(stdin);
	gotoxy(boxx1, boxy +10);getline(cin,GioiTinh);
	fflush(stdin);
	gotoxy(boxx1, boxy +12);getline(cin,DiaChi);
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
	fflush(stdin);
	gotoxy(boxx1, boxy +14);getline(cin, ChucVu);
	gotoxy(boxx1, boxy +16);cin>> ThamNien;
	fflush(stdin);
	gotoxy(boxx1, boxy +18);getline(cin, BoPhan);
	gotoxy(boxx1, boxy +20);cin>>HeSoLuong;
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
	gotoxy(boxx1, boxy +14);cin>>SoGioLam;
	gotoxy(boxx1, boxy +16);cin>> SoLuongTheoGio;
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
	gotoxy(boxx1, boxy +14);cin>>SoLuongHang;
	gotoxy(boxx1, boxy +16);cin>>GiaHang;
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
	gotoxy(boxx1, boxy +14);NgayVaoLam.NhapDay();
	gotoxy(boxx1, boxy +16);cin>>LuongTheoGio;	
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
	void SuaNhanVien();
	Node *previous(Node *p); 
	void DemNhanVien();
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

//Ă½ tÆ°á»Ÿng 
//Äáº·t máº­t kháº©u cho PhĂ¢n cáº£nh bĂ¡o	
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



void Box_Nhap()
{        
	textcolor(15);
	
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	gotoxy(boxx, boxy + 2); cout << char(186)<< "	Ma NV: ";
	gotoxy(boxx + boxs + 1, boxy + 2); cout << char(186);
	gotoxy(boxx, boxy + 3); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 3); cout << char(186);
	gotoxy(boxx, boxy + 4); cout << char(186)<< "	Ho Ten: ";
	gotoxy(boxx + boxs + 1, boxy + 4); cout << char(186);
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 5); cout << char(186);
	gotoxy(boxx, boxy + 6); cout << char(186)<< "	Tuoi: ";
	gotoxy(boxx + boxs + 1, boxy + 6); cout << char(186);
	gotoxy(boxx, boxy + 7); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 7); cout << char(186);
	gotoxy(boxx, boxy + 8); cout << char(186)<< "	Ngay Sinh: ";
	gotoxy(boxx + boxs + 1, boxy + 8); cout << char(186);
	gotoxy(boxx, boxy + 9); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 9); cout << char(186);
	gotoxy(boxx, boxy + 10); cout << char(186)<< "	Gioi Tinh: ";
	gotoxy(boxx + boxs + 1, boxy + 10); cout << char(186);
	gotoxy(boxx, boxy + 11); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 11); cout << char(186);
	gotoxy(boxx, boxy + 12); cout << char(186)<< "	Dia Chi: ";
	gotoxy(boxx + boxs + 1, boxy + 12); cout << char(186);
	
}

void Box_Nhap1()
{
	textcolor(15);
	gotoxy(boxx, boxy + 13); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 13); cout << char(186);
	gotoxy(boxx, boxy + 14); cout << char(186)<< "	ChucVu: ";
	gotoxy(boxx + boxs + 1, boxy + 14); cout << char(186);
	gotoxy(boxx, boxy + 15); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 15); cout << char(186);
	gotoxy(boxx, boxy + 16); cout << char(186)<< "	Tham Nien: ";
	gotoxy(boxx + boxs + 1, boxy + 16); cout << char(186);
	gotoxy(boxx, boxy + 17); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 17); cout << char(186);
	gotoxy(boxx, boxy + 18); cout << char(186)<< "	Bo Phan: ";
	gotoxy(boxx + boxs + 1, boxy + 18); cout << char(186);
	gotoxy(boxx, boxy + 19); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 19); cout << char(186);
	gotoxy(boxx, boxy + 20); cout << char(186)<< "	He So luong: ";
	gotoxy(boxx + boxs + 1, boxy + 20); cout << char(186);
	gotoxy(boxx, boxy + 21); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 21); cout << char(186);
	gotoxy(boxx, boxy + 22); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}

void Box_Nhap2()
{
	textcolor(15);
	gotoxy(boxx, boxy + 13); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 13); cout << char(186);
	gotoxy(boxx, boxy + 14); cout << char(186)<< "	So Gio Lam: ";
	gotoxy(boxx + boxs + 1, boxy + 14); cout << char(186);
	gotoxy(boxx, boxy + 15); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 15); cout << char(186);
	gotoxy(boxx, boxy + 16); cout << char(186)<< "	So Luong Theo Gio: ";
	gotoxy(boxx + boxs + 1, boxy + 16); cout << char(186);
	gotoxy(boxx, boxy + 17); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 17); cout << char(186);
	gotoxy(boxx, boxy + 18); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}

void Box_Nhap3()
{
	textcolor(15);
	gotoxy(boxx, boxy + 13); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 13); cout << char(186);
	gotoxy(boxx, boxy + 14); cout << char(186)<< "	So Luong Hang: ";
	gotoxy(boxx + boxs + 1, boxy + 14); cout << char(186);
	gotoxy(boxx, boxy + 15); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 15); cout << char(186);
	gotoxy(boxx, boxy + 16); cout << char(186)<< "	Gia Hang: ";
	gotoxy(boxx + boxs + 1, boxy + 16); cout << char(186);
	gotoxy(boxx, boxy + 17); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 17); cout << char(186);
	gotoxy(boxx, boxy + 18); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}

void Box_Nhap4()
{
	textcolor(15);
	gotoxy(boxx, boxy + 13); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 13); cout << char(186);
	gotoxy(boxx, boxy + 14); cout << char(186)<< "	Ngay Vao Lam: ";
	gotoxy(boxx + boxs + 1, boxy + 14); cout << char(186);
	gotoxy(boxx, boxy + 15); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 15); cout << char(186);
	gotoxy(boxx, boxy + 16); cout << char(186)<< "	Luong Theo Gio: ";
	gotoxy(boxx + boxs + 1, boxy + 16); cout << char(186);
	gotoxy(boxx, boxy + 17); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 17); cout << char(186);
	gotoxy(boxx, boxy + 18); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}

//==============================Ham Nhap ================================

void NhapDS (QuanLiNhanVien &QL)
{
	
	textcolor(15);
	Nguoi *nv;
	int SL1,SL2,SL3,SL4;
	gotoxy(10,11);cout <<"                               NHAP DANH SACH";
	
	gotoxy(6,13);cout<<"Nhap so Luong Nhan Vien Chinh Thuc:";
	cin>>SL1;
	system("cls");
	for (int i = 0; i < SL1; i++)
	{
		textcolor(15);
		system("cls");
		Box_Nhap();
		Box_Nhap1();
		nv = new NhanVienChinhThuc;
		gotoxy(15,10);cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
	system("cls");
	gotoxy(15,10);cout<<"Nhap so Luong Ban Thoi Gian:";
	cin>>SL2;
	for (int i = 0; i < SL2; i++)
	{
		textcolor(15);
		system("cls");
		Box_Nhap();
		Box_Nhap2();
		nv = new NhanVienBanThoiGian;
		gotoxy(15,10);cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
	system("cls");
	gotoxy(6,13);cout<<"Nhap so Luong lam theo san pham:";
	cin>>SL3;
	for (int i = 0; i < SL3; i++)
	{
		textcolor(15);
		system("cls");
		Box_Nhap();
		Box_Nhap3();
		nv = new NhanVienLamTheoSanPham;
		gotoxy(15,10);cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
	system("cls");
	gotoxy(6,13);cout<<"Nhap so Luong Thu viec:";
	cin>>SL4;
	for (int i = 0; i < SL4; i++)
	{
		textcolor(15);
		system("cls");
		Box_Nhap();
		Box_Nhap4();
		nv = new NhanVienThuViec;
		gotoxy(15,10);cout<<"\nNhan vien thu "<<i+1<<": "<<endl;
		nv->Nhap();
		QL.AddLast(nv);
	}
}
//--------------------------
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
		textcolor(i++);
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
		textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
		}
	}
}
//nĂªn Ä‘áº·t máº­t kháº©u
/*DĂ¹ng hĂ m kbhit cĂ³ trong thÆ° viá»‡n #include <conio.h>
kbhit(void): Kiá»ƒm tra xem ngÆ°á»i dĂ¹ng cĂ³ nháº¥n vĂ o 1 phĂ­m báº¥t ká»³ nĂ o trĂªn bĂ n phĂ­m hay khĂ´ng ?
=> Láº¥y giĂ¡ trá»‹ cá»§a phĂ­m Ä‘Ă³ ra nhá» vĂ o getch()*/

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
		textcolor(i++);
		if (i == 15)
		{
			i = 1;
		}
		system("cls");
     	gotoxy(10, 5); cout <<     "                                 QUAN LY NHAN VIEN ";
		Sleep(500);
	} while (true);
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
		do {
	
		if (kbhit())
		{
			if (c = getch())
				break;
		}
		textcolor(i++);
		if (i == 15)
		{
			i = 1;
		}
		system("cls");
     	gotoxy(10, 5); cout <<     "                                 QUAN LY NHAN VIEN ";
		Sleep(500);
		} while (true);
		gotoxy(x, y);
		textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
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
			textcolor(15);
			system("cls");
			NhapDS(t);
			goto Menu;
		}
		else if (y == 2 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.XuatDS();
			getch();
			goto Menu;
		}
		else if (y == 3 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			ThemNhanVien(t);
			getch();
			goto Menu;
		}
		else if (y == 4 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.SuaNhanVien();
			getch();
			goto Menu;
		}
		else if (y == 5 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.DemNhanVien();
			getch();
			goto Menu;
		}
		else if (y == 6 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.TimKiemTen();
			getch();
			goto Menu;
		}
		else if (y == 7 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.TimKiemMa();
			getch();
			goto Menu;
		}
		else if (y == 8 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.XoaNhanVien();
			getch();
			goto Menu;
		}
		else if (y == 9 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.SapXepTen();
			t.XuatDS();
			getch();
			goto Menu;
		}
		else if (y == 10 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.SapXepMa();
			t.XuatDS();
			getch();
			goto Menu;
		}
		else if (y == 11 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.MaxLuong();
			getch();
			goto Menu;
		}
		else if (y == 12 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.MinLuong();
			getch();
			goto Menu;
		}
		else if (y == 13 && NhanNut == ENTER)
		{
			textcolor(15);
			system("cls");
			t.TongLuong();
			getch();
			goto Menu;
		}
		
		else if (y == 14 && NhanNut == ENTER)
		{
			exit(0);
			textcolor(15);
		}	
		
	} while (true);
}	
int main()
{
    Menu();
}
