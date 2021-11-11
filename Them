#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string>
using namespace std;


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
	float TienThuong;
	
public:
	//ham tao ham huy 
	Nguoi();
	Nguoi(string Ma, string HoTen, int Tuoi, string GioiTinh, string DiaChi, float Luong, float TienThuong);
	Nguoi(const Nguoi &nguoi);
	~Nguoi();
	virtual void Nhap();
	virtual void Xuat();
	virtual float TinhLuong() = 0;
	float getLuong();
	float getTienThuong();
};

Nguoi::Nguoi()
{
	this->Ma = "";
	this->HoTen = "";
	this->Tuoi = 0;
	this->GioiTinh = "";
	this->DiaChi = "";
	this->Luong = 0;
	this->TienThuong = 0;
}

Nguoi::Nguoi(string Ma, string HoTen, int Tuoi, string GioiTinh, string DiaChi, float Luong, float TienThuong)
{
	this->Ma = Ma;
	this->HoTen = HoTen;
	this->Tuoi = Tuoi;
	this->GioiTinh = GioiTinh;
	this->DiaChi = DiaChi;
	this->Luong = Luong;
	this->TienThuong = TienThuong;
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

float Nguoi::getLuong()
{
	return Luong;
}
float Nguoi::getTienThuong()
{
	return TienThuong;
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
}
void NhanVienChinhThuc::Xuat()
{
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"\tNhan Vien Chinh Thuc:"<<endl<<endl;
	Nguoi::Xuat();
	cout<<"\tChuc Vu cua nhan vien : "<<ChucVu<<endl;
	cout<<"\tTham Nien : "<<ThamNien<<endl;
	cout<<"\tBo Phan Lam Viec La: "<<BoPhan<<endl;
}


float NhanVienChinhThuc::TinhLuong()
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
//	friend class QuanLiNhanVien;
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
//	friend class QuanLiNhanVien;
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
	
}
//==============================Ham Nhap ================================


//==============================danh sach lien ke========================
/*
typedef class node* Node;
class node {
    private:
        Nguoi *data;
	    Node next;
    public:
       node(Node next);
       void SetNext(Node next);
       Node getNext();
       friend class QuanLiNhanVien;
};

void node::SetNext(Node next)
{
    this->next = next;
}
Node node::getNext()
{
    return next;
}
*/
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
void QuanLiNhanVien::XuatDS(){
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
		if(p->data->getTen()==TenTK){
			p->data->Xuat();
		}
	}
}
void QuanLiNhanVien::TimKiemMa(){
	string MaTK;
	cout<<"Nhap Ma Nhan Vien can tim:";
	fflush(stdin);
	getline(cin,MaTK);
	for(Node*p=head;p!=NULL;p=p->next){
		if(p->data->getMa()==TenTK){
			p->data->Xuat();
		}
	}
}



string Ten;
				cout<<"Nhap Vao Ten Nhan Vien Can Sua Can Sua:";
				fflush(stdin);
				getline(cin,Ten);
				for(Node*p=head;p!=NULL;p=p->next){
					if(TimKiemMa() = Ma){
						cout<<"Sua Ten Can Tim: "
					}
				}
				
				
void QuanLiNhanVien::SuaNhanVien(){
	int chon;
	int chon1;
	int Flat= 0;
	while (Flat)
	{
		cout<<"Sua chua:"<<endl;
		cout<<"1: Sua Thong Tin co Ban "<<end;
		
		
		cout<<" 6: Sua Chuc Vu"<<endl;
		cout<<"7: Sua Bon Phan || 8: Sua He So Luong"<<endl;
		cout<<"9: Sua So Gio Lam || 10: Sua So Luong Theo Gio"<<endl;
		cout<<"11: Sua Gia Hang || 12: Sua Luong Theo Gio"<<endl;
		cout<<"13: Sua Doi Nhan Vien chuyen Tu Cac Loai Hinh Nhan Vien"<<endl;
		cout<<"Hay Lua Chon Theo Yeu Cau Ban Muon (Bam So)";
		cin>>chon;
		switch(Chon)
		{
			case 1:
				{
					cout<<"1: Sua Ten  "<<endl; 
					cout<<"2: Sua Tuoi "<<endl;
					cout<<"3: Sua Nam Sinh "<<endl;
					cout<<"4: Sua Gioi Tinh"<<endl;
					cout<<"5: Sua Dia Chi "<<endl;
					cout<<"chon vao Thu can sua: ";
					cin>>
					switch()
				}
				
		}
	}
}
//----------------------------------------cac Ham --------------------------------



void NhapDS (QuanLiNhanVien &QL)
{
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

void ThemNhanVien(QuanLiNhanVien &QL){
	Nguoi *nv;
	int a;
	Node* p=QL.getHead();
	cout<<"1: Nhan vien Chinh Thuc." << endl;
	cout<<"2: Nhan Vien Lam Theo San Pham." <<endl;
	cout<<"3: Nhan Vien Ban Thoi Gian."<<endl;
	cout<<"4: Nhan Vien Thu Viec."<<endl;
	cout<<"Hay Chon mot chuc Nang Tren (Bam So): "<<endl;
	cin>>a;
	switch(a)
	{
		case 1:
			{
				
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
    			break;
			}
		case 2:
			{
			
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
    			break;
			}
		case 3:
			{
				
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
    			break;
			}
		case 4:
			{
				
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
    			break;
			}
	}
}

	
	int DemNhanVien();	// Count the number of students with low GPA (GPA < 4)
	void SapXepTen();
	void SapXepLuong();
	void HienThi();
	int TimKiemTen();
	int TimKiemMa();
	int SuaNhanVien();
	int SuaTen();
	int SuaMa();
	int SuaChuaVu();//tang chuc , giam chuc , duoi viec, thu viec  
	int MaxLuong();//min
	void TongLuong();
	void TongNhanVien();
	void Giaodien();

void Menu()
{
	QuanLiNhanVien t;
	int n;
	int Chon, Flat =1;
    int SL1,SL2,SL3,SL4;
	while(Flat)
	{
		cout<<"               Quan Li Nhan Vien              "<<endl;
		cout<<"----------------------------------------------"<<endl;
		cout<<"               CHUC NANG                      "<<endl;
		cout<<"1. nhap            ||    2. xuat              "<<endl;
		cout<<"3. Them Nhan Vien  ||    4. xoa               "<<endl;
		cout<<"                                              "<<endl;
		cout<<"----------------------------------------------"<<endl;
		cout<<"Hay Chon Mot Chuc Nang (Bam So): ";
		cin >> Chon;
		switch (Chon)
		{
			case 1:
				{
                    NhapDS(t);
					break;
				}
			case 2:
				{
					t.XuatDS();
					break;
				}
			case 3:
				{
					ThemNhanVien(t);
					break;
				}
			case 4:
				{
					break;
				}
			case 6:
				{
					break;
				}
			case 7:
				{
					break;
				}
			case 8:
				{
					break;
				}
			case 9:
				{
					break;
				}
			case 10:
				{
					break;
				}
			case 11:
				{
					break;
				}
			case 12:
				{
					break;
				}
			case 13:
				{
					break;
				}
			case 14:
				{
					break;
				}
			case 15:
				{
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

int main()
{
    Menu();
}
