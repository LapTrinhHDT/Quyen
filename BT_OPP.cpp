class Nguoi : public NgaySinh
{
private:
	string Name;
	int age;
	string sex;
	NgaySinh ns;
	string DiaChi;
	int SoGioLam;
	float Luong;
	float TienThuong;
public:
	virtual istream& operator >> (istream& is, Nguoi& Ng);
	virtual friend ostream& operator <<(ostream& os, const B& b);
	virtual void TinhLuong() = 0;
};
class NhanVienChinhThuc :public Nguoi
{
private:
	string ChucVu;
	int ThamNien;
	string BoPhan;
};
class NhanVienThuViec : public Nguoi
{
private:
	int SoGioLam;
	int SoLuongTheoGio;
};
class QuanLiNhanVien
{

};
