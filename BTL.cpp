#include <bits/stdc++.h>
using namespace std;
#include <fstream>
#include <ctime> // Thư viện hỗ trợ thời gian

// Thuốc

// khai báo cấu trúc thuốc
struct thuoc
{
    string TenThuoc;
    string MaThuoc;
    string TheLoaiThuoc;
    float DonGia;
    int SoLuong;
};
typedef struct thuoc THUOC;

struct node
{
    THUOC data;         // dữ liệu chứa trong 1 cái node
    struct node *pNext; // con trỏ dùng để liên kết giữa các node với nhau
};
typedef struct node NODE;

// khai báo cấu trúc cấu trúc của danh sách liên kết đơn các sinh viên
struct listt
{
    NODE *pHead; // node quản lí đầu danh sách
    NODE *pTail; // node quản lí cuối danh sách
};
typedef struct listt LIST;

// Khởi tạo

void KhoiTao(LIST &l)
{
    // cho 2 node trỏ đến NULL vì danh sách liên kết đơn chưa có phần tử
    l.pHead = NULL;
    l.pTail = NULL;
}
NODE *KhoiTaoNODE(THUOC x)
{
    NODE *p = new NODE; // cấp phát vùng nhớ cho NODE p
    if (p == NULL)
    {
        cout << "Không đủ bộ nhớ để cấp phát! ";
        return NULL;
    }
    p->data = x;     // truyển giá trị sinhvien x vào data
    p->pNext = NULL; // đầu tiên khai báo node thì node đó ch có liên kết đến nod
                     // ==> con trỏ của nó sẽ trỏ đến NULL
    return p;        // trả về NODE p vừa khởi tạo
}

// hàm thêm node vào đầu danh sách liên kết
void ThemVaoDau(LIST &l, NODE *p)
{
    // danh sách đang rỗng
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p; // node đầu cũng chính là node cuối và là p
    }
    else
    {
        p->pNext = l.pHead; // cho con trỏ của node cần thêm là node p liên kết đ
        l.pHead = p;        // cập nhật lại pHead chính là node p
    }
}

// hàm thêm node sinh viên vào cuối danh sách liên kết
void ThemVaoCuoi(LIST &l, NODE *p)
{
    // danh sách đang rỗng
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p; // node đầu cũng chính là node cuối và là p
    }
    else
    {
        l.pTail->pNext = p; // cho con trỏ của pTail liên kết vs node p
        l.pTail = p;        // cập nhật lại p là node pTail
    }
}

void XoaDau(LIST &l)
{
    // nếu danh sách trống
    if (l.pHead == NULL)
    {
        return;
    }
    else
    {
        NODE *p = l.pHead;        // NODE p là node sẽ xóa
        l.pHead = l.pHead->pNext; // cập nhật lại phần tử l.pHeaf là phần từ kế tiếp
        delete p;
    }
}
void XoaCuoi(LIST &l)
{
    if (l.pHead == NULL)
    {
        return;
    }
    // trường hợp danh sách có 1 phẩn tử
    if (l.pHead->pNext == NULL)
    {
        XoaDau(l);
        return;
    }
    // duyệt từ đầu danh sách đén thằng kế cuối
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->pNext == l.pTail)
        {
            // Duyệt đến thằng kế cuối
            delete l.pTail;
            k->pNext = NULL; // cho con trỏ của node kế cuối trỏ  đến vùng nhớ null
            l.pTail = k;     // cập nhật lại l.pTail
            return;
        }
    }
}

void Doc_Thong_Tin_1_Thuoc(ifstream &filein, THUOC &TH)
{
    // Đọc tên thuốc
    getline(filein, TH.TenThuoc, ','); // Đọc đến dấu "," thì dừng
    filein.ignore(1);                  // Bỏ khoảng trắng (nếu có)

    // Đọc mã thuốc
    getline(filein, TH.MaThuoc, ',');
    filein.ignore(1);

    // Đọc thể loại thuốc
    getline(filein, TH.TheLoaiThuoc, ',');
    filein.ignore(1);

    // Đọc đơn giá
    filein >> TH.DonGia;
    filein.ignore(); // Bỏ dấu ',' (nếu có)

    // Đọc số lượng
    filein >> TH.SoLuong;

    // Đọc dòng kết thúc để chuẩn bị cho lần đọc tiếp theo
    string temp;
    getline(filein, temp);
}

void Doc_Danh_Sach_Thuoc(ifstream &filein, LIST &l)
{
    // đọc đến file cuối cùng
    while (!filein.eof())
    {
        // Bước 1: Đọc thông tin sinh viên
        THUOC TH;
        Doc_Thong_Tin_1_Thuoc(filein, TH);
        // Bước 2: Khởi tạo 1 cái node sinh viên
        NODE *p = KhoiTaoNODE(TH);
        // Bước 3: Thêm sinh viêm vào danh sách liên kết đơn các sinh viên
        ThemVaoCuoi(l, p);
    }
}

// hàm xuất để test dữ liệu
void Xuat(THUOC TH)
{
    cout << left << setw(15) << TH.TenThuoc
         << setw(10) << TH.MaThuoc
         << setw(10) << TH.DonGia
         << setw(10) << TH.SoLuong
         << setw(12) << TH.TheLoaiThuoc
         << endl;
}

void XuatTieuDe()
{
    cout << "---------------------------------------------------------------" << endl;
    cout << left << setw(5) << "STT" << setw(15) << "TEN THUOC"
         << setw(10) << "MA THUOC"
         << setw(10) << "DON GIA"
         << setw(10) << "SO LUONG"
         << setw(12) << "THE LOAI"
         << endl;
    cout << "---------------------------------------------------------------" << endl;
}

void Xuat_Danh_Sach_Thuoc(LIST l)
{
    int STT = 0;
    XuatTieuDe();
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        STT++;
        cout << left << setw(5) << STT;
        Xuat(k->data);
        cout << endl;
    }
}

void Hoan_Vi(THUOC &x, THUOC &y)
{
    THUOC tam = x;
    x = y;
    y = tam;
}

void SapXepThuocTheoTen(LIST &l)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có một phần tử
    if (l.pHead == NULL || l.pHead->pNext == NULL)
    {
        return;
    }
    else
    {
        for (NODE *k = l.pHead; k != NULL; k = k->pNext)
        {
            for (NODE *h = k->pNext; h != NULL; h = h->pNext)
            {
                if (k->data.TenThuoc > h->data.TenThuoc)
                {
                    Hoan_Vi(k->data, h->data); // hoán vị 2 data của 2 cái node
                }
            }
        }
    }
}

void Ghi_Thong_Tin_1_Thuoc(ofstream &fileout, THUOC TH)
{
    fileout << TH.TenThuoc << ", ";
    fileout << TH.MaThuoc << ", ";
    fileout << TH.DonGia << ", ";
    fileout << TH.SoLuong << ", ";
    fileout << TH.TheLoaiThuoc;
}

void Luu_FIle_Sap_Xep_Thuoc_Theo_A_Z(LIST l)
{
    ofstream fileout;
    fileout.open("sapxepthuoca_z.txt", ios::out);
    // ƯỚC 1 : gọi lại hàm sắp xếp để sắp xếp danh sách sinh viên tăng dần theo điểm trung bình
    SapXepThuocTheoTen(l);
    // Bước 2: Dùng vòng lặp để lưu tất cả thông tin sinh viên vào file
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        Ghi_Thong_Tin_1_Thuoc(fileout, k->data);
        fileout << endl;
    }
    fileout.close();
}

void SapXepThuocTheoDonGia(LIST &l)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có một phần tử
    if (l.pHead == NULL || l.pHead->pNext == NULL)
    {
        return;
    }
    else
    {
        for (NODE *k = l.pHead; k != NULL; k = k->pNext)
        {
            for (NODE *h = k->pNext; h != NULL; h = h->pNext)
            {
                if (k->data.DonGia > h->data.DonGia)
                {
                    Hoan_Vi(k->data, h->data); // hoán vị 2 data của 2 cái node
                }
            }
        }
    }
}

void Tim_Kiem_Thuoc_Dua_Vao_Ten(LIST &l, string &tenTimKiem)
{
    NODE *p = l.pHead;  // khởi tạo con trỏ, bắt đầu duyệt từ đầu danh sách
    bool found = false; // Biến found có tác dụng xác định xem có tìm thấy thuốc nào
                        // Ban đầu, found là false (chưa tìm thấy).

    while (p != NULL)
    {
        if (p->data.TenThuoc.find(tenTimKiem) != string::npos)
        {
            cout << "Kết quả tìm kiếm cho thuốc có tên '" << tenTimKiem << "':" << endl;
            cout << "---------------------------------------------------" << endl;
            cout << left << setw(15) << "TEN THUOC"
                 << setw(10) << "MA THUOC"
                 << setw(10) << "DON GIA"
                 << setw(10) << "SO LUONG"
                 << setw(12) << "THE LOAI"
                 << endl;
            cout << "---------------------------------------------------" << endl;
            found = true;
            cout << left << setw(15) << p->data.TenThuoc
                 << setw(10) << p->data.MaThuoc
                 << setw(10) << p->data.DonGia
                 << setw(10) << p->data.SoLuong
                 << setw(12) << p->data.TheLoaiThuoc
                 << endl;
        }
        p = p->pNext;
    }

    if (!found)
    {
        cout << "Không tìm thấy thuốc nào có tên '" << tenTimKiem << "'." << endl;
    }
}

void XoaThongTinThuoc(LIST &l, string ThuocXoa)
{
    if (l.pHead == NULL)
    {
        return;
    }
    // nếu thuốc cần xóa nằm dầu danh sách
    if (l.pHead != NULL && l.pHead->data.TenThuoc == ThuocXoa)
    {
        XoaDau(l);
    }
    // nếu thuốc cần xóa nằm cuối danh sách
    if (l.pTail != NULL && l.pTail->data.TenThuoc == ThuocXoa)
    {
        XoaCuoi(l);
    }
    NODE *g = new NODE; // node g là node giữ lien kết trỏ đến node nằm trc node cần xóa
    // duyệt danh sách liên kết đơn để tìm
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.TenThuoc == ThuocXoa)
        {                        // node h chính là node nằm sau node k <=> node mà ta sẽ xóa
            g->pNext = k->pNext; // cập nhật mối liên kết giữa node
            delete k;            // xóa node
            return;
        }
        g = k; // cho node g trỏ đến node k
    }
}

void ThemThuoc(LIST &l, THUOC th)
{
    NODE *p = KhoiTaoNODE(th);
    if (p == NULL)
    {
        return;
    }

    // Nếu danh sách rỗng, thêm node đầu tiên
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p; // node đầu cũng chính là node cuối và là p
    }
    else
    {
        // Nếu danh sách không rỗng, thêm vào cuối
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

void Nhap_Thong_Tin_Thuoc(LIST &l)
{
    THUOC TH;
    cin.ignore();
    cout << "Nhập tên thuốc cần thêm: ";
    getline(cin, TH.TenThuoc);
    cout << "Nhập mã thuốc cần thêm: ";
    getline(cin, TH.MaThuoc);
    cout << "Nhập đơn giá thuốc: ";
    cin >> TH.DonGia;
    cin.ignore();
    cout << "Nhập số lượng thuốc: ";
    cin >> TH.SoLuong;
    cin.ignore();
    cout << "Nhập loại thuốc: ";
    getline(cin, TH.TheLoaiThuoc);
    ThemThuoc(l, TH);
}
void Sua_Thong_Tin_Thuoc(LIST &l, string mathuoc)
{
    // Tìm thuốc trong danh sách
    NODE *found = NULL;
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.MaThuoc == mathuoc)
        {
            found = k;
            break;
        }
    }

    // Kiểm tra xem có tìm thấy thuốc với mã đã nhập không
    if (found != NULL)
    {
        int lua_chon;
        cout << "Nhập lựa chọn cần sửa đổi: " << endl;
        cout << "1. Sửa tên thuốc" << endl;
        cout << "2. Sửa đơn giá thuốc" << endl;
        cout << "3. Sửa số lượng thuốc" << endl;
        cout << "4. Sửa thể loại thuốc" << endl;
        cout << "Lựa chọn của bạn: ";
        cin >> lua_chon;
        cin.ignore(); // Xóa newline sau khi nhập số

        // Sử dụng else if để kiểm tra lựa chọn
        if (lua_chon == 1)
        {
            cout << "Nhập tên thuốc mới: ";
            getline(cin, found->data.TenThuoc);
        }
        else if (lua_chon == 2)
        {
            cout << "Nhập đơn giá mới: ";
            cin >> found->data.DonGia;
        }
        else if (lua_chon == 3)
        {
            cout << "Nhập số lượng mới: ";
            cin >> found->data.SoLuong;
            cin.ignore();
        }
        else if (lua_chon == 4)
        {
            cin.ignore();
            cout << "Nhập thể loại thuốc mới: ";
            getline(cin, found->data.TheLoaiThuoc);
        }
        else
        {
            cout << "Lựa chọn không hợp lệ!" << endl;
        }

        cout << "Sửa thông tin thuốc thành công!" << endl;
    }
    else
    {
        cout << "Không tìm thấy thuốc với mã: " << mathuoc << endl;
    }
}
void Giai_Phong_Danh_Sach(LIST &l)
{
    // duyệt từ đầu danh sách đến cuối dnah sách
    NODE *p = NULL;
    while (l.pHead != NULL)
    {
        p = l.pHead;
        l.pHead = l.pHead->pNext;
        delete p;
    }
}

void Xuat_Ra_Thuoc_Co_Don_Gia_Lon_Nhat(LIST &l)
{
    float max = l.pHead->data.DonGia;
    for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
    {
        if (max < k->data.DonGia)
        {
            max = k->data.DonGia;
        }
    }
    cout << left << setw(15) << "TEN THUOC"
         << setw(10) << "MA THUOC"
         << setw(10) << "DON GIA"
         << setw(10) << "SO LUONG"
         << setw(12) << "THE LOAI"
         << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (max == k->data.DonGia)
        {
            cout << left << setw(15) << k->data.TenThuoc
                 << setw(10) << k->data.MaThuoc
                 << setw(10) << k->data.DonGia
                 << setw(10) << k->data.SoLuong
                 << setw(12) << k->data.TheLoaiThuoc
                 << endl;
        }
    }
}

void Xuat_Thuoc_Sap_Het_Hang(LIST &l)
{
    cout << "Danh sách thuốc sắp hết hàng (số lượng < 10):" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(15) << "TEN THUOC"
         << setw(10) << "MA THUOC"
         << setw(10) << "DON GIA"
         << setw(10) << "SO LUONG"
         << setw(12) << "THE LOAI"
         << endl;
    cout << "---------------------------------------------------" << endl;

    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.SoLuong < 10)
        {
            cout << left << setw(15) << k->data.TenThuoc
                 << setw(10) << k->data.MaThuoc
                 << setw(10) << k->data.DonGia
                 << setw(10) << k->data.SoLuong
                 << setw(12) << k->data.TheLoaiThuoc
                 << endl;
        }
    }
}

void Thong_Ke_Tong_So_Luong_Va_Gia_Tri_Theo_Ten(LIST &l)
{
    map<string, pair<int, float>> thongKe; // Map để lưu tên thuốc -> {tổng số lượng, tổng giá trị}

    // Duyệt qua danh sách để tính tổng số lượng và giá trị theo từng tên thuốc
    for (NODE *k = l.pHead; k != NULL; k = k->pNext)
    {
        string tenThuoc = k->data.TenThuoc; // Giả sử tên thuốc được lưu trong thuộc tính 'TenThuoc'
        int soLuong = k->data.SoLuong;
        float giaTri = k->data.DonGia * k->data.SoLuong;

        // Nếu tên thuốc đã tồn tại trong map, cập nhật giá trị
        if (thongKe.find(tenThuoc) != thongKe.end()) // kiểm tra xem tên thuốc (tenThuoc) đã tồn tại trong map (thongKe) hay chưa.
        {
            thongKe[tenThuoc].first += soLuong; // Truy cập vào giá trị (pair<int, float>) tương ứng với tenThuoc.
                                                // Lấy phần first (tổng số lượng).
                                                // Cộng thêm soLuong (số lượng thuốc mới).
            thongKe[tenThuoc].second += giaTri; // Cộng dồn giá trị
                                                // Truy cập vào phần second (tổng giá trị).
                                                // Cộng thêm giaTri (giá trị thuốc mới: DonGia * SoLuong).
        }
        else
        {
            // Nếu tên thuốc chưa tồn tại, khởi tạo mới
            thongKe[tenThuoc] = make_pair(soLuong, giaTri);
        }
    }

    // Xuất kết quả
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(30) << "TEN THUOC"
         << setw(15) << "TONG SO LUONG"
         << setw(20) << "TONG GIA TRI" << endl;
    cout << "---------------------------------------------------" << endl;

    for (const auto &entry : thongKe)
    {
        cout << left << setw(30) << entry.first
             << setw(15) << entry.second.first
             << setw(20) << entry.second.second << endl;
    }

    cout << "---------------------------------------------------" << endl;
}

void Tim_Kiem_Thuoc_Theo_The_Loai(LIST &l, string theloaithuoccantim)
{
    NODE *p = l.pHead;  // Khởi tạo con trỏ, bắt đầu duyệt từ đầu danh sách
    bool found = false; // Biến found xác định có tìm thấy thuốc không

    // Hiển thị tiêu đề trước nếu có thuốc được tìm thấy
    cout << "Cac thuoc thuoc the loai '" << theloaithuoccantim << "' gom:" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(15) << "TEN THUOC"
         << setw(10) << "MA THUOC"
         << setw(10) << "DON GIA"
         << setw(10) << "SO LUONG"
         << setw(12) << "THE LOAI" << endl;
    cout << "---------------------------------------------------" << endl;

    while (p != NULL)
    {
        // Kiểm tra xem thể loại thuốc có chứa từ cần tìm
        if (p->data.TheLoaiThuoc.find(theloaithuoccantim) != string::npos)
        {
            found = true; // Đánh dấu tìm thấy
            // In thông tin thuốc
            cout << left << setw(15) << p->data.TenThuoc
                 << setw(10) << p->data.MaThuoc
                 << setw(10) << p->data.DonGia
                 << setw(10) << p->data.SoLuong
                 << setw(12) << p->data.TheLoaiThuoc
                 << endl;
        }
        p = p->pNext;
    }

    // Nếu không tìm thấy thuốc nào
    if (!found)
    {
        cout << "Khong co thuoc nao thuoc the loai '" << theloaithuoccantim << "' trong danh sach." << endl;
    }
}

void Menu(LIST &l)
{
    int luachon;
    while (69)
    {
        cout << endl;
        cout << "------------------------- MENU -------------------------" << endl;
        cout << "0. Thoát khỏi menu" << endl;
        cout << "1. Đọc dữ liệu từ file 'Thong_tin_thuoc.txt'" << endl;
        cout << "2. Xuất danh sách thuốc" << endl;
        cout << "3. Xuất danh sách từ file 'Thong_tin_thuoc.txt' ra màn hình và lưu vào file 'sapxepthuoca_z.txt' " << endl;
        cout << "4. Sắp xếp thuốc theo đơn giá từ thấp đến cao" << endl;
        cout << "5. Tìm kiếm tên thuốc" << endl;
        cout << "6. Xóa đầu danh sách" << endl;
        cout << "7. Xóa sách" << endl;
        cout << "8. Thêm thuốc vào danh sách" << endl;
        cout << "9. Sửa thông tin thuốc" << endl;
        cout << "10. Xuất ra thuốc có đơn giá cao nhất" << endl;
        cout << "11. Xuất ra thuốc sắp hết hàng" << endl;
        cout << "12. Thống kê lại số thuốc còn tồn kho và tổng giá trị của chúng" << endl;
        cout << "13. Tìm kiếm thuốc theo thể loại thuốc" << endl;
        cout << "14. Giải phóng danh sách" << endl;
        cout << "------------------------- Endl -------------------------" << endl;

        cout << "Nhập lựa chọn: ";
        cin >> luachon;
        if (luachon == 0)
        {
            break;
        }
        else if (luachon == 1)
        {
            ifstream filein("Thong_tin_thuoc.txt");
            if (filein.is_open())
            {
                Doc_Danh_Sach_Thuoc(filein, l);
                cout << "Đọc thông tin từ file thành công." << endl;
                filein.close();
            }
            else
            {
                cout << "Không thể mở file 'Thong_tin_thuoc.txt'. Vui lòng kiểm tra lại!" << endl;
            }
        }
        else if (luachon == 2)
        {
            Xuat_Danh_Sach_Thuoc(l);
        }
        else if (luachon == 3)
        {
            SapXepThuocTheoTen(l);
            Luu_FIle_Sap_Xep_Thuoc_Theo_A_Z(l);
            cout << "Đã sắp xếp danh sách thuốc theo tên từ A-Z và lưu vào file 'Sapxepthuoca_z.txt'." << endl;
        }
        else if (luachon == 4)
        {
            SapXepThuocTheoDonGia(l);
            cout << "Đã sắp xếp danh sách thuốc theo thứ tự từ thấp đến cao." << endl;
        }
        else if (luachon == 5)
        {
            cin.ignore();
            string tenTimKiem;
            cout << "Nhập tên thuốc cần tìm: ";
            getline(cin, tenTimKiem);
            Tim_Kiem_Thuoc_Dua_Vao_Ten(l, tenTimKiem);
        }
        else if (luachon == 6)
        {
            XoaDau(l);
        }
        else if (luachon == 7)
        {
            cin.ignore();
            string ThuocCanXoa;
            cout << "Nhập tên thuốc cần xóa ";
            getline(cin, ThuocCanXoa);
            XoaThongTinThuoc(l, ThuocCanXoa);
        }
        else if (luachon == 8)
        {
            Nhap_Thong_Tin_Thuoc(l);
        }
        else if (luachon == 9)
        {
            cin.ignore();
            string mathuoc;
            cout << "Nhập mã thuốc cần sửa thông tin ";
            getline(cin, mathuoc);
            Sua_Thong_Tin_Thuoc(l, mathuoc);
        }
        else if (luachon == 10)
        {
            Xuat_Ra_Thuoc_Co_Don_Gia_Lon_Nhat(l);
        }
        else if (luachon == 11)
        {
            Xuat_Thuoc_Sap_Het_Hang(l);
        }
        else if (luachon == 12)
        {
            Thong_Ke_Tong_So_Luong_Va_Gia_Tri_Theo_Ten(l);
        }
        else if (luachon == 13)
        {
            cin.ignore();
            string theloaithuoccantim;
            cout << "hãy nhập thể loại thuốc cần tìm: ";
            getline(cin, theloaithuoccantim);
            cout << theloaithuoccantim;
            Tim_Kiem_Thuoc_Theo_The_Loai(l, theloaithuoccantim);
        }
        else if (luachon == 14)
        {
            Giai_Phong_Danh_Sach(l);
        }
    }
}

// Hóa đơn
struct DATE
{
    int ngay;
    int thang;
    int nam;
};
typedef struct DATE DATE;

void Doc_Ngay_Thang_Nam(ifstream &filein, DATE &date)
{
    filein >> date.ngay;
    filein.ignore(1);
    filein >> date.thang;
    filein.ignore(1); // dịch sang phải 1 byte để bỏ qua 1 kí tự
    filein >> date.nam;
}

struct HOADON
{
    string MaHoaDon;   // Mã hóa đơn, khác với mã thuốc
    string MAKH;       // Mã khách hàng
    string MANV;       // Mã nhân viên
    string TenThuoc;   // Tên thuốc mua
    string MaThuoc;    // Mã thuốc
    float DonGia;      // Đơn giá thuốc
    int SoLuong;       // Số lượng mua
    float GiamGia = 0; // Giảm giá tính theo phần trăm
    float ThanhTien;   // Tổng tiền (DonGia * SoLuong)
    DATE NgayMua;      // Ngày mua
};
typedef struct HOADON HOADON;

struct NODEE
{
    HOADON data;  // Dữ liệu chứa trong mỗi node là thông tin hóa đơn
    NODEE *pNext; // Con trỏ dùng để liên kết giữa các node
};
typedef struct NODEE NODEE;

struct LISTT
{
    NODEE *pHead; // Quản lý đầu danh sách
    NODEE *pTail; // Quản lý cuối danh sách
};
typedef struct LISTT LISTT;

// Khởi tạo danh sách liên kết
void KhoiTaoHoaDon(LISTT &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

// Khởi tạo một NODE hóa đơn
NODEE *KhoiTaoNODEHoaDon(HOADON x)
{
    NODEE *p = new NODEE;
    if (p == NULL)
    {
        cout << "Không đủ bộ nhớ để cấp phát!";
        return NULL;
    }
    p->data = x;
    p->pNext = NULL;
    return p;
}

// Thêm NODE hóa đơn vào đầu danh sách
void ThemVaoDauHoaDon(LISTT &l, NODEE *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        p->pNext = l.pHead;
        l.pHead = p;
    }
}

// Thêm NODE hóa đơn vào cuối danh sách
void ThemVaoCuoiHoaDon(LISTT &l, NODEE *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

// Xóa NODE đầu danh sách
void XoaDauHoaDon(LISTT &l)
{
    if (l.pHead == NULL)
    {
        return;
    }
    else
    {
        NODEE *p = l.pHead;
        l.pHead = l.pHead->pNext;
        delete p;
    }
}

void XoaCuoiHoaDon(LISTT &l)
{
    if (l.pHead == NULL)
    {
        return;
    }
    // trường hợp danh sách có 1 phẩn tử
    if (l.pHead->pNext == NULL)
    {
        XoaDauHoaDon(l);
        return;
    }
    // duyệt từ đầu danh sách đén thằng kế cuối
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->pNext == l.pTail)
        {
            delete l.pTail;
            k->pNext = NULL; // cho con trỏ của node kế cuối trỏ  đến vùng nhớ null
            l.pTail = k;     // cập nhật lại l.pTail
            return;
        }
    }
}

void Doc_Thong_Tin_File_Hoa_Don(ifstream &filein, HOADON &HD)
{
    // Đọc mã hóa đơn
    getline(filein, HD.MaHoaDon, ',');
    // Đọc mã nhân viên
    getline(filein, HD.MANV, ',');
    // Đọc mã khách hàng
    getline(filein, HD.MAKH, ',');
    // Đọc tên thuốc
    getline(filein, HD.TenThuoc, ',');
    // Đọc mã thuốc
    getline(filein, HD.MaThuoc, ',');
    // Đọc đơn giá
    filein >> HD.DonGia;
    filein.ignore(); // Bỏ qua dấu phẩy
    // Đọc số lượng
    filein >> HD.SoLuong;
    filein.ignore(); // Bỏ qua dấu phẩy
    // Đọc thành tiền
    filein >> HD.ThanhTien;
    filein.ignore(); // Bỏ qua dấu phẩy
    // Đọc ngày tháng năm mua
    Doc_Ngay_Thang_Nam(filein, HD.NgayMua);

    // Đọc dòng kết thúc (có thể bỏ qua dòng này nếu không cần)
    string temp;
    getline(filein, temp);
}

void Doc_Danh_Sach_HoaDon(ifstream &filein, LISTT &l)
{
    while (!filein.eof())
    {
        HOADON HD;
        Doc_Thong_Tin_File_Hoa_Don(filein, HD);

        // Kiểm tra nếu mã hóa đơn không rỗng
        if (!HD.MaHoaDon.empty())
        {
            NODEE *p = KhoiTaoNODEHoaDon(HD);
            ThemVaoCuoiHoaDon(l, p);
        }
    }
}

void XuatDanhSachHoaDon(LISTT &l)
{
    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(5) << "STT"
         << setw(10) << "MAHD"
         << setw(10) << " MANV"
         << setw(10) << " MAKH"
         << setw(20) << " TEN THUOC"
         << setw(15) << " MA THUOC"
         << setw(10) << "DON GIA"
         << setw(15) << "SO LUONG"
         << setw(15) << "THANH TIEN"
         << setw(15) << "GIAM GIA"
         << setw(15) << "NGAY MUA"
         << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;

    int stt = 1;
    for (NODEE *p = l.pHead; p != NULL; p = p->pNext)
    {
        cout << left << setw(5) << stt++
             << setw(10) << p->data.MaHoaDon
             << setw(10) << p->data.MANV
             << setw(10) << p->data.MAKH
             << setw(20) << p->data.TenThuoc
             << setw(15) << p->data.MaThuoc
             << setw(10) << p->data.DonGia
             << setw(15) << p->data.SoLuong
             << setw(15) << p->data.ThanhTien
             << setw(15) << p->data.GiamGia
             << p->data.NgayMua.ngay << "/" << p->data.NgayMua.thang << "/" << p->data.NgayMua.nam
             << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Hoan_Vii(HOADON &x, HOADON &y)
{
    HOADON tam = x;
    x = y;
    y = tam;
}

void Sap_Xep_Theo_Hoa_Don_Tu_Cao_Den_Thap(LISTT &l)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có một phần tử
    if (l.pHead == NULL || l.pHead->pNext == NULL)
    {
        return;
    }
    else
    {
        for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
        {
            for (NODEE *h = k->pNext; h != NULL; h = h->pNext)
            {
                if (k->data.ThanhTien > h->data.ThanhTien)
                {
                    Hoan_Vii(k->data, h->data); // hoán vị 2 data của 2 cái node
                }
            }
        }
    }
}

// Đọc file 1 hóa đơn
void Ghi_Thong_Tin_1_Hoa_Don(ofstream &fileout, HOADON HD)
{
    fileout << HD.MaHoaDon << ",";
    fileout << HD.MANV << ",";
    fileout << HD.MAKH << ",";
    fileout << HD.TenThuoc << ",";
    fileout << HD.MaThuoc << ",";
    fileout << HD.DonGia << ",";
    fileout << HD.SoLuong << ",";
    fileout << HD.ThanhTien << ",";
    fileout << HD.NgayMua.ngay << "/" << HD.NgayMua.thang << "/" << HD.NgayMua.nam;
}

void Lưu_FIle_Sap_Xep_Hoa_Don_Theo_Gia_Tri_Thap_Den_Cao(LISTT l)
{
    ofstream fileout;
    fileout.open("sap_xep_thuoc_tu_cao_den_thap.txt", ios::out);
    // ƯỚC 1 : gọi lại hàm sắp xếp để sắp xếp danh sách sinh viên tăng dần theo điểm trung bình
    Sap_Xep_Theo_Hoa_Don_Tu_Cao_Den_Thap(l);
    // Bước 2: Dùng vòng lặp để lưu tất cả thông tin sinh viên vào file
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        Ghi_Thong_Tin_1_Hoa_Don(fileout, k->data);
        fileout << endl;
    }
    fileout.close();
}

void XoaHoaDon(LISTT &l, string ma_hoa_don_xoa)
{
    if (l.pHead == NULL)
    {
        return;
    }
    // nếu thuốc cần xóa nằm dầu danh sách
    if (l.pHead != NULL && l.pHead->data.MaHoaDon == ma_hoa_don_xoa)
    {
        XoaDauHoaDon(l);
    }
    // nếu thuốc cần xóa nằm cuối danh sách
    if (l.pTail != NULL && l.pTail->data.MaHoaDon == ma_hoa_don_xoa)
    {
        XoaCuoiHoaDon(l);
    }
    NODEE *g = new NODEE; // node g là node giữ lien kết trỏ đến node nằm trc node cần xóa
    // duyệt danh sách liên kết đơn để tìm
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.MaHoaDon == ma_hoa_don_xoa)
        {                        // node h chính là node nằm sau node k <=> node mà ta sẽ xóa
            g->pNext = k->pNext; // cập nhật mối liên kết giữa node k(node q) với node sau node
            delete k;            // xóa node nằm sau node q
            return;
        }
        g = k; // cho node g trỏ đến node k
    }
}

void Giai_Phong_Danh_Sach_Hoa_Don(LISTT &l)
{
    // duyệt từ đầu danh sách đến cuối dnah sách
    NODEE *p = NULL;
    while (l.pHead != NULL)
    {
        p = l.pHead;
        l.pHead = l.pHead->pNext;
        delete p;
    }
}

// code thêm hóa đơn
void TinhGiamGia(HOADON &HD, float n)
{
    // Giảm giá tính theo phần trăm
    HD.GiamGia = (n / 100) * HD.ThanhTien;
    HD.ThanhTien -= HD.GiamGia; // Cập nhật thành tiền sau khi giảm giá
}

void Them_Hoa_Don(LISTT &l, HOADON hd)
{
    NODEE *p = KhoiTaoNODEHoaDon(hd);
    if (p == NULL)
    {
        return;
    }

    // Nếu danh sách rỗng, thêm node đầu tiên
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p; // node đầu cũng chính là node cuối
    }
    else
    {
        // Nếu danh sách không rỗng, thêm vào cuối
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

void Nhap_Thong_Tin_Hoa_Don(LISTT &l)
{
    HOADON HD;
    cin.ignore();
    // Nhập mã hóa đơn
    cout << "Nhập mã hóa đon cần thêm: ";
    getline(cin, HD.MaHoaDon);
    // Nhập mã nhân viên
    int luachonmanv;
    int dembienmanv = 1;
    cout << "Danh sách mã nhân viên: " << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << left << setw(5) << "STT" << setw(15) << " MANV" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        cout << left << setw(5) << dembienmanv << setw(15) << k->data.MANV << endl;
        dembienmanv++;
    }
    cout << "Bạn chọn ";
    cin >> luachonmanv;
    int dembienmanv2 = 1;
    bool foundd = true;
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (luachonmanv == dembienmanv2)
        {
            HD.MANV = k->data.MANV;
            foundd = true;
            break;
        }
        dembienmanv2++;
    }
    if (!foundd)
    {
        cout << "Lựa chọn không hợp lệ!" << endl;
        return;
    }
    cin.ignore();

    // Nhập mã KH
    cout << "Nhập mã khách hàng: ";
    getline(cin, HD.MAKH);

    // Nhập thuốc cần mua

    int luachon;
    int dembien = 1;
    cout << "Danh sách thuốc: \n";
    cout << left << setw(5) << "STT"
         << setw(20) << "TÊN THUỐC"
         << setw(20) << "ĐƠN GIÁ" << endl;
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        cout << left << setw(5) << dembien
             << setw(20) << k->data.TenThuoc
             << setw(20) << k->data.DonGia << endl;
        dembien++;
    }

    cout << "Bạn chọn:  ";
    cin >> luachon;

    int dembien2 = 1;
    bool found = false;
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (luachon == dembien2)
        {
            HD.TenThuoc = k->data.TenThuoc;
            HD.DonGia = k->data.DonGia;
            HD.MaThuoc = k->data.MaThuoc;
            found = true;
            break;
        }
        dembien2++;
    }

    if (!found)
    {
        cout << "Lựa chọn không hợp lệ!" << endl;
        return;
    }

    // Nhập số lượng thuốc cần mua

    float soluong;
    cout << "Hãy nhập số lượng thuốc cần mua: ";
    cin >> soluong;
    // Tự động tính thành tiền

    HD.SoLuong = soluong; // Add this field if it exists
    HD.ThanhTien = soluong * HD.DonGia;
    // code thêm hóa đơn
    float giamgia;
    cout << "Nhập tỷ lệ giảm giá (phần trăm): ";
    cin >> giamgia;
    // Tính giảm giá và cập nhật thành tiền
    TinhGiamGia(HD, giamgia);
    //
    // Lấy thời gian hiện tại
    time_t now = time(0);      // Lấy thời gian hiện tại theo timestamp
    tm *ltm = localtime(&now); // Chuyển đổi sang cấu trúc thời gian

    HD.NgayMua.ngay = ltm->tm_mday;       // Ngày
    HD.NgayMua.thang = 1 + ltm->tm_mon;   // Tháng (tm_mon tính từ 0)
    HD.NgayMua.nam = 1900 + ltm->tm_year; // Năm (tm_year tính từ 1900)

    // Add invoice to the list
    Them_Hoa_Don(l, HD);
}
// code thêm hóa đơn

void LuuHoaDonGiamGia(LISTT &l, float y)
{
    ofstream outFile("giamgia.txt");
    if (!outFile)
    {
        cout << "Không thể mở file để ghi!" << endl;
        return;
    }

    // Lọc và lưu các hóa đơn thỏa mãn điều kiện
    for (NODEE *p = l.pHead; p != NULL; p = p->pNext)
    {
        if (p->data.GiamGia >= y)
        {
            outFile << "Mã hóa đơn: " << p->data.MaHoaDon << endl;
            outFile << "Khách hàng: " << p->data.MAKH << endl;
            outFile << "Giảm giá: " << p->data.GiamGia << endl;
            outFile << "Thành tiền: " << p->data.ThanhTien << endl;
            outFile << "Ngày mua: " << p->data.NgayMua.ngay << "/" << p->data.NgayMua.thang << "/" << p->data.NgayMua.nam << endl;
            outFile << "--------------------------------------" << endl;
        }
    }

    outFile.close();
}

void XemHoaDonGiamGia(LISTT &l)
{
    float y;
    cout << "Nhập số tiền giảm giá tối thiểu: ";
    cin >> y;

    LuuHoaDonGiamGia(l, y);
}

void Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Don_Hang(LISTT &l, string mahoadon)
{
    NODEE *p = l.pHead; // khởi tạo con trỏ, bắt đầu duyệt từ đầu danh sách
    bool found = false; // Biến found có tác dụng xác định xem có tìm thấy thuốc nào
                        // Ban đầu, found là false (chưa tìm thấy).

    while (p != NULL)
    {
        if (p->data.MaHoaDon.find(mahoadon) != string::npos)
        {
            cout << "KẾT QUẢ TÌM KIẾM CHO MÃ HÓA ĐƠN: " << mahoadon << "':" << endl;
            cout << left << setw(5)
                 << setw(10) << "MAHD"
                 << setw(10) << " MANV"
                 << setw(10) << " MAKH"
                 << setw(20) << " TEN THUOC"
                 << setw(15) << " MA THUOC"
                 << setw(10) << "DON GIA"
                 << setw(15) << "SO LUONG"
                 << setw(15) << "THANH TIEN"
                 << setw(15) << "NGAY MUA"
                 << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            found = true;
            cout << left << setw(5)
                 << setw(10) << p->data.MaHoaDon
                 << setw(10) << p->data.MANV
                 << setw(10) << p->data.MAKH
                 << setw(20) << p->data.TenThuoc
                 << setw(15) << p->data.MaThuoc
                 << setw(10) << p->data.DonGia
                 << setw(15) << p->data.SoLuong
                 << setw(15) << p->data.ThanhTien
                 << p->data.NgayMua.ngay << "/" << p->data.NgayMua.thang << "/" << p->data.NgayMua.nam
                 << endl;
        }
        p = p->pNext;
    }
    if (!found)
    {
        cout << "KHÔNG TÌM THẤY MÃ HÓA ĐƠN: " << mahoadon << "'." << endl;
    }
}

void Hoa_Don_Max(LISTT &l)
{
    float max = l.pHead->data.ThanhTien;
    for (NODEE *k = l.pHead->pNext; k != NULL; k = k->pNext)
    {
        if (max < k->data.ThanhTien)
        {
            max = k->data.ThanhTien;
        }
    }
    cout << left
         << setw(10) << "MAHD"
         << setw(10) << " MANV"
         << setw(10) << " MA KH"
         << setw(20) << " TEN THUOC"
         << setw(15) << " MA THUOC"
         << setw(10) << "DON GIA"
         << setw(15) << "SO LUONG"
         << setw(15) << "THANH TIEN"
         << setw(15) << "NGAY MUA"
         << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (max == k->data.ThanhTien)
        {
            cout << left
                 << setw(10) << k->data.MaHoaDon
                 << setw(10) << k->data.MANV
                 << setw(10) << k->data.MAKH
                 << setw(20) << k->data.TenThuoc
                 << setw(15) << k->data.MaThuoc
                 << setw(10) << k->data.DonGia
                 << setw(15) << k->data.SoLuong
                 << setw(15) << k->data.ThanhTien
                 << k->data.NgayMua.ngay << "/" << k->data.NgayMua.thang << "/" << k->data.NgayMua.nam << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
}

void Xuat_Hoa_Don_Theo_Thang(LISTT &l, int thangcanxuat)
{
    NODEE *p = l.pHead; // khởi tạo con trỏ, bắt đầu duyệt từ đầu danh sách
    bool found = false; // Biến found có tác dụng xác định xem có tìm thấy thuốc nào
                        // Ban đầu, found là false (chưa tìm thấy).
    while (p != NULL)
    {
        if (p->data.NgayMua.thang == thangcanxuat)
        {
            cout << "TỔNG HỢP HÓA ĐƠN CỦA THÁNG CẦN XUẤT " << thangcanxuat << endl;
            cout << left << setw(5)
                 << setw(10) << "MAHD"
                 << setw(10) << " MANV"
                 << setw(10) << " MAKH"
                 << setw(20) << " TEN THUOC"
                 << setw(15) << " MA THUOC"
                 << setw(10) << "DON GIA"
                 << setw(15) << "SO LUONG"
                 << setw(15) << "THANH TIEN"
                 << setw(15) << "NGAY MUA"
                 << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            break;
        }
        else
        {
            cout << "THÁNG " << thangcanxuat << " CHƯA CÓ HÓA ĐƠN NÀO " << endl;
            break;
        }
    }

    while (p != NULL)
    {

        if (p->data.NgayMua.thang == thangcanxuat)
        {
            found = true;
            cout << left << setw(5)
                 << setw(10) << p->data.MaHoaDon
                 << setw(10) << p->data.MANV
                 << setw(10) << p->data.MAKH
                 << setw(20) << p->data.TenThuoc
                 << setw(15) << p->data.MaThuoc
                 << setw(10) << p->data.DonGia
                 << setw(15) << p->data.SoLuong
                 << setw(15) << p->data.ThanhTien
                 << p->data.NgayMua.ngay << "/" << p->data.NgayMua.thang << "/" << p->data.NgayMua.nam
                 << endl;
        }
        p = p->pNext;
    }
}

void TinhTongDoanhThuTrongNgay(LISTT &l, int ngay, int thang, int nam)
{
    float tongDoanhThu = 0;
    NODEE *p = l.pHead; // Bắt đầu từ đầu danh sách
    while (p != NULL)
    {
        // Kiểm tra nếu ngày, tháng, năm trùng với ngày cần tính
        if (p->data.NgayMua.ngay == ngay &&
            p->data.NgayMua.thang == thang &&
            p->data.NgayMua.nam == nam)
        {
            tongDoanhThu += p->data.ThanhTien; // Cộng tổng tiền của hóa đơn vào tổng doanh thu
        }
        p = p->pNext; // Duyệt tiếp hóa đơn tiếp theo
    }
    cout << "Tổng doanh thu của ngày " << ngay << "/" << thang << "/" << nam << " là: " << tongDoanhThu << endl;
}

void Tinh_Tong_Doanh_Thu_Theo_Tung_Loai_Thuoc(LISTT &l)
{
    map<string, pair<int, float>> thongke; // Map để lưu tên thuốc -> {tổng số lượng, tổng giá trị}
    // Duyệt qua danh sách để tính tổng số lượng và giá trị theo từng tên thuốc
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        string tenThuoc = k->data.TenThuoc; // Giả sử tên thuốc được lưu trong thuộc tính 'TenThuoc'
        int soLuong = k->data.SoLuong;
        float giaTri = k->data.DonGia * k->data.SoLuong;
        // Nếu tên thuốc đã tồn tại trong map, cập nhật giá trị
        if (thongke.find(tenThuoc) != thongke.end()) // kiểm tra xem tên thuốc (tenThuoc) đã tồn tại trong map (thongKe) hay chưa.
        {
            thongke[tenThuoc].first += soLuong; // Truy cập vào giá trị (pair<int, float>) tương ứng với tenThuoc.
                                                // Lấy phần first (tổng số lượng).
                                                // Cộng thêm soLuong (số lượng thuốc mới).
            thongke[tenThuoc].second += giaTri; // Cộng dồn giá trị
                                                // Truy cập vào phần second (tổng giá trị).
                                                // Cộng thêm giaTri (giá trị thuốc mới: DonGia * SoLuong).
        }
        else
        {
            // Nếu tên thuốc chưa tồn tại, khởi tạo mới
            thongke[tenThuoc] = make_pair(soLuong, giaTri);
        }
    }
    // Xuất kết quả
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(20) << "TEN THUOC"
         << setw(15) << "TONG SO LUONG"
         << setw(20) << "TONG GIA TRI" << endl;
    cout << "---------------------------------------------------" << endl;
    for (const auto &entry : thongke)
    {
        cout << left << setw(20) << entry.first
             << setw(15) << entry.second.first
             << setw(20) << entry.second.second << endl;
    }
    cout << "---------------------------------------------------" << endl;
}

void Luu_FIle(LISTT l)
{
    ofstream fileout;
    fileout.open("Hoa_Don.txt", ios::out);
    for (NODEE *k = l.pHead; k != NULL; k = k->pNext)
    {
        Ghi_Thong_Tin_1_Hoa_Don(fileout, k->data);
        fileout << endl;
    }
    fileout.close();
}

void Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Nhan_Vien(LISTT &l, string manhanvien)
{
    NODEE *p = l.pHead; // khởi tạo con trỏ, bắt đầu duyệt từ đầu danh sách
    bool found = false; // Biến found có tác dụng xác định xem có tìm thấy thuốc nào
                        // Ban đầu, found là false (chưa tìm thấy).

    while (p != NULL)
    {
        if (p->data.MANV.find(manhanvien) != string::npos)
        {
            cout << "KẾT QUẢ TÌM KIẾM CHO MÃ HÓA ĐƠN: " << manhanvien << "':" << endl;
            cout << left << setw(5)
                 << setw(10) << "MAHD"
                 << setw(10) << " MANV"
                 << setw(10) << " MAKH"
                 << setw(20) << " TEN THUOC"
                 << setw(15) << " MA THUOC"
                 << setw(10) << "DON GIA"
                 << setw(15) << "SO LUONG"
                 << setw(15) << "THANH TIEN"
                 << setw(15) << "NGAY MUA"
                 << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            found = true;
            cout << left << setw(5)
                 << setw(10) << p->data.MaHoaDon
                 << setw(10) << p->data.MANV
                 << setw(10) << p->data.MAKH
                 << setw(20) << p->data.TenThuoc
                 << setw(15) << p->data.MaThuoc
                 << setw(10) << p->data.DonGia
                 << setw(15) << p->data.SoLuong
                 << setw(15) << p->data.ThanhTien
                 << p->data.NgayMua.ngay << "/" << p->data.NgayMua.thang << "/" << p->data.NgayMua.nam
                 << endl;
        }
        p = p->pNext;
    }
    if (!found)
    {
        cout << "KHÔNG TÌM THẤY MANV: " << manhanvien << "'." << endl;
    }
}

void Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Khach_Hang(LISTT &l, string makhachang)
{
    NODEE *p = l.pHead; // khởi tạo con trỏ, bắt đầu duyệt từ đầu danh sách
    bool found = false; // Biến found có tác dụng xác định xem có tìm thấy thuốc nào
                        // Ban đầu, found là false (chưa tìm thấy).

    while (p != NULL)
    {
        if (p->data.MAKH.find(makhachang) != string::npos)
        {
            cout << "KẾT QUẢ TÌM KIẾM CHO MÃ KHÁCH HÀNG: " << makhachang << "':" << endl;
            cout << left << setw(5)
                 << setw(10) << "MAHD"
                 << setw(10) << " MANV"
                 << setw(10) << " MAKH"
                 << setw(20) << " TEN THUOC"
                 << setw(15) << " MA THUOC"
                 << setw(10) << "DON GIA"
                 << setw(15) << "SO LUONG"
                 << setw(15) << "THANH TIEN"
                 << setw(15) << "NGAY MUA"
                 << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            found = true;
            cout << left << setw(5)
                 << setw(10) << p->data.MaHoaDon
                 << setw(10) << p->data.MANV
                 << setw(10) << p->data.MAKH
                 << setw(20) << p->data.TenThuoc
                 << setw(15) << p->data.MaThuoc
                 << setw(10) << p->data.DonGia
                 << setw(15) << p->data.SoLuong
                 << setw(15) << p->data.ThanhTien
                 << p->data.NgayMua.ngay << "/" << p->data.NgayMua.thang << "/" << p->data.NgayMua.nam
                 << endl;
        }
        p = p->pNext;
    }
    if (!found)
    {
        cout << "KHÔNG TÌM THẤY MÃ KHÁCH HÀNG " << makhachang << "'." << endl;
    }
}

void Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Thuoc_Da_Ban(LISTT &l, string mathuoc)
{
    NODEE *p = l.pHead; // khởi tạo con trỏ, bắt đầu duyệt từ đầu danh sách
    bool found = false; // Biến found có tác dụng xác định xem có tìm thấy thuốc nào
                        // Ban đầu, found là false (chưa tìm thấy).

    while (p != NULL)
    {
        if (p->data.MaThuoc.find(mathuoc) != string::npos)
        {
            cout << "KẾT QUẢ TÌM KIẾM CHO MÃ THUỐC: " << mathuoc << "':" << endl;
            cout << left << setw(5)
                 << setw(10) << "MAHD"
                 << setw(10) << " MANV"
                 << setw(10) << " MAKH"
                 << setw(20) << " TEN THUOC"
                 << setw(15) << " MA THUOC"
                 << setw(10) << "DON GIA"
                 << setw(15) << "SO LUONG"
                 << setw(15) << "THANH TIEN"
                 << setw(15) << "NGAY MUA"
                 << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            break;
        }
        p = p->pNext;
    }

    while (p != NULL)
    {
        if (p->data.MaThuoc.find(mathuoc) != string::npos)
        {
            found = true;
            cout << left << setw(5)
                 << setw(10) << p->data.MaHoaDon
                 << setw(10) << p->data.MANV
                 << setw(10) << p->data.MAKH
                 << setw(20) << p->data.TenThuoc
                 << setw(15) << p->data.MaThuoc
                 << setw(10) << p->data.DonGia
                 << setw(15) << p->data.SoLuong
                 << setw(15) << p->data.ThanhTien
                 << p->data.NgayMua.ngay << "/" << p->data.NgayMua.thang << "/" << p->data.NgayMua.nam
                 << endl;
        }
        p = p->pNext;
    }
    if (!found)
    {
        cout << "KHÔNG TÌM THẤY MÃ THUÔC " << mathuoc << " đã bán" << endl;
    }
}

void Menu2(LISTT &l)
{
    int luachon;
    while (true)
    {
        cout << endl;
        cout << "------------------------- MENU -------------------------" << endl;
        cout << "0. Thoát khỏi menu" << endl;
        cout << "1. Đọc dữ liệu từ file 'Hoa_Don.txt'" << endl;
        cout << "2. Xuất danh sách hóa đơn" << endl;
        cout << "3. Sắp xếp Hóa Đơn theo giá trị từ cao đến thấp và lưu vào file 'sap_xep_thuoc_tu_cao_den_thap.txt'" << endl;
        cout << "4. Xóa hóa đơn theo mã hóa đơn" << endl;
        cout << "5. Thêm hóa đơn" << endl;
        cout << "6. Tìm kiếm hóa đơn theo mã hóa đơn" << endl;
        cout << "7. Xuất ra hóa đơn có giá trị lớn nhất" << endl;
        cout << "8. Tổng hợp hóa đơn và xuất hóa đơn theo tháng" << endl;
        cout << "9. Tính doanh thu trong ngày " << endl;
        cout << "10. Thống kê doanh thu theo từng loại thuốc" << endl;
        cout << "11. Lưu file" << endl;
        cout << "12. Tìm kiếm hóa đơn theo mã nhân viên" << endl;
        cout << "13. Tìm kiếm hóa đơn theo mã khách hàng" << endl;
        cout << "14. Xuất ra các hóa đơn đã bán theo mã thuốc" << endl;
        cout << "15. Giải phóng danh sách" << endl;
        cout << "16. Xem những hóa đơn dc giảm giá y" << endl;
        cout << "------------------------- ENDL --------------------------" << endl;

        cout << "Nhập lựa chọn: ";
        cin >> luachon;

        if (luachon == 0)
        {
            break;
        }
        else if (luachon == 1)
        {
            ifstream filein("Hoa_Don.txt");
            if (filein.is_open())
            {
                Doc_Danh_Sach_HoaDon(filein, l);
                cout << "Đọc thông tin từ file thành công." << endl;
                filein.close();
            }
            else
            {
                cout << "Không thể mở file 'Hoa_Don.txt'. Vui lòng kiểm tra lại." << endl;
            }
        }
        else if (luachon == 2)
        {
            XuatDanhSachHoaDon(l);
        }
        else if (luachon == 3)
        {
            Sap_Xep_Theo_Hoa_Don_Tu_Cao_Den_Thap(l);
            Lưu_FIle_Sap_Xep_Hoa_Don_Theo_Gia_Tri_Thap_Den_Cao(l);
        }
        else if (luachon == 4)
        {
            cin.ignore();
            string mahoadonxoa;
            cout << "Hãy nhập mã hóa đơn cần xóa ";
            getline(cin, mahoadonxoa);
            XoaHoaDon(l, mahoadonxoa);
        }
        else if (luachon == 5)
        {
            Nhap_Thong_Tin_Hoa_Don(l);
        }
        else if (luachon == 6)
        {
            cin.ignore();
            string Ma_Hoa_Don_Can_Tim;
            cout << "Hãy nhập mã hóa đơn cần tìm kiếm: ";
            getline(cin, Ma_Hoa_Don_Can_Tim);
            Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Don_Hang(l, Ma_Hoa_Don_Can_Tim);
        }
        else if (luachon == 7)
        {
            Hoa_Don_Max(l);
        }
        else if (luachon == 8)
        {
            cin.ignore();
            int thangcanxuat;
            cout << "Hãy nhập tháng cần xuất hóa đơn ";
            cin >> thangcanxuat;
            Xuat_Hoa_Don_Theo_Thang(l, thangcanxuat);
        }
        else if (luachon == 9)
        {
            cin.ignore();
            int ngay;
            int thang;
            int nam;
            cout << "Hãy nhập ngày cần tính tổng doanh thu: ";
            cin >> ngay;
            cout << "hãy nhập tháng cần tính doanh thu ";
            cin >> thang;
            cout << "Hãy nhập năm cần tính doanh thu ";
            cin >> nam;
            TinhTongDoanhThuTrongNgay(l, ngay, thang, nam);
        }
        else if (luachon == 10)
        {
            Tinh_Tong_Doanh_Thu_Theo_Tung_Loai_Thuoc(l);
        }
        else if (luachon == 11)
        {
            Luu_FIle(l);
        }
        else if (luachon == 12)
        {
            cin.ignore();
            string manhanvien;
            cout << "Hãy nhập mã nhân viên cần xuất hóa đơn" << endl;
            getline(cin, manhanvien);
            Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Nhan_Vien(l, manhanvien);
        }
        else if (luachon == 13)
        {
            cin.ignore();
            string makhachhang;
            cout << "Hãy nhập mã khách hàng cần xuất hóa đơn" << endl;
            getline(cin, makhachhang);
            Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Khach_Hang(l, makhachhang);
        }
        else if (luachon == 14)
        {
            cin.ignore();
            string mathuoc;
            cout << "Hãy nhập mã thuốc cần xuất hóa đơn" << endl;
            getline(cin, mathuoc);
            Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Thuoc_Da_Ban(l, mathuoc);
        }
        else if (luachon == 15)
        {
            Giai_Phong_Danh_Sach_Hoa_Don(l);
            cout << "Giải phóng danh sách hóa đơn thành công! ";
        }
        else if (luachon == 16)
        {
            XemHoaDonGiamGia(l);
        }
        else
        {
            cout << "Lựa chọn không hợp lệ, vui lòng chọn lại." << endl;
        }
    }
}

// Nhân viên - Cây - Đào Duy Bình

struct Date
{
    int ngay;
    int thang;
    int nam;
};

struct NhanVien
{
    string maNV;
    string hoTen;
    string chucVu;
    string phongBan;
    Date ngaySinh;
    string sdt;
    string diaChi;
    float luongCoBan;
    float khenThuong; // Thêm thuộc tính khen thưởng
};
struct NodeNV
{
    NhanVien nv;
    struct NodeNV *pLeft;
    struct NodeNV *pRight;
};

typedef struct NodeNV *Tree;

void khoiTaoCay(Tree &t)
{
    t = NULL;
}

void themNV(Tree &t, NhanVien nv)
{
    if (t == NULL)
    {
        Tree p = new NodeNV();
        p->nv = nv;
        p->pLeft = NULL;
        p->pRight == NULL;
        t = p;
    }
    else
    {
        if (t->nv.maNV > nv.maNV)
        {
            themNV(t->pLeft, nv);
        }
        else if (t->nv.maNV < nv.maNV)
        {
            themNV(t->pRight, nv);
        }
    }
}

NhanVien nhapThongTinNhanVien()
{
    NhanVien nv;
    cout << "Nhập mã nhân viên: ";
    cin >> nv.maNV;
    cin.ignore(); // Loại bỏ ký tự xuống dòng còn lại sau khi nhập mã nhân viên

    cout << "Nhập họ tên nhân viên: ";
    getline(cin, nv.hoTen);

    cout << "Nhập chức vụ: ";
    getline(cin, nv.chucVu);

    cout << "Nhập phòng ban: ";
    getline(cin, nv.phongBan);

    cout << "Nhập ngày sinh : ";
    cin >> nv.ngaySinh.ngay;

    cout << "Nhập tháng sinh : ";
    cin >> nv.ngaySinh.thang;

    cout << "Nhập năm sinh : ";
    cin >> nv.ngaySinh.nam;
    cin.ignore();

    cout << "Nhập số điện thoại: ";
    getline(cin, nv.sdt);

    cout << "Nhập địa chỉ: ";
    getline(cin, nv.diaChi);

    cout << "Nhập lương cơ bản: ";
    cin >> nv.luongCoBan;

    // Nhập giá trị khen thưởng
    cout << "Nhập giá trị khen thưởng: ";
    cin >> nv.khenThuong;

    return nv;
}

// code thêm cây

void inTieuDe()
{
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << left
         << setw(10) << "Mã NV"
         << setw(19) << " Họ tên"
         << setw(19) << "Chức vụ"
         << setw(15) << "Phòng ban"
         << setw(17) << "Ngày sinh"
         << setw(19) << "SĐT"
         << setw(18) << "Địa chỉ"
         << setw(19) << "Khen thưởng"
         << fixed << setprecision(2) << setw(15) << setw(15) << " Lương cơ bản" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

void xuatThongTinNhanVien(NhanVien nv)
{
    cout << left
         << setw(10) << nv.maNV
         << setw(15) << nv.hoTen
         << setw(15) << nv.chucVu
         << setw(14) << nv.phongBan
         << setw(2) << nv.ngaySinh.ngay << "/" << setw(2) << nv.ngaySinh.thang << "/" << setw(10) << nv.ngaySinh.nam
         << setw(18) << nv.sdt
         << setw(14) << nv.diaChi
         << setw(19) << nv.khenThuong
         << fixed << setprecision(2) << setw(15) << nv.luongCoBan << endl;
}

// code thêm cây
void trichLocNhanVienKhenThuong(Tree t, float x, float y)
{
    if (t != NULL)
    {
        // Nếu nhân viên có khen thưởng trong khoảng từ x đến y, ghi vào file
        if (t->nv.khenThuong >= x && t->nv.khenThuong <= y)
        {
            ofstream file("khenthuong.txt", ios::app); // Mở file để ghi (append mode)
            if (!file)
            {
                cout << "Không thể mở file!" << endl;
                return;
            }

            file << "Mã Nhân Viên: " << t->nv.maNV << endl;
            file << "Họ Tên: " << t->nv.hoTen << endl;
            file << "Chức Vụ: " << t->nv.chucVu << endl;
            file << "Phòng Ban: " << t->nv.phongBan << endl;
            file << "Ngày Sinh: " << t->nv.ngaySinh.ngay << "/" << t->nv.ngaySinh.thang << "/" << t->nv.ngaySinh.nam << endl;
            file << "Số Điện Thoại: " << t->nv.sdt << endl;
            file << "Địa Chỉ: " << t->nv.diaChi << endl;
            file << "Lương Cơ Bản: " << t->nv.luongCoBan << endl;
            file << "Khen Thưởng: " << t->nv.khenThuong << endl;
            file << "----------------------------------------" << endl;

            file.close(); // Đóng file sau khi ghi
        }

        // Duyệt đệ quy các nhánh trái và phải của cây
        trichLocNhanVienKhenThuong(t->pLeft, x, y);  // Duyệt nhánh trái
        trichLocNhanVienKhenThuong(t->pRight, x, y); // Duyệt nhánh phải
    }
}

// Hàm nhập giá trị khen thưởng cho các nhân viên trong cây
void NhapKhenThuongChoNhanVien(Tree &t)
{
    if (t == NULL)
    {
        return;
    }

    // Kiểm tra nếu nhân viên chưa có khen thưởng
    if (t->nv.khenThuong == 0) // Giả sử nhân viên chưa có khen thưởng sẽ có giá trị khen thưởng là 0
    {
        cout << "Nhập khen thưởng cho nhân viên " << t->nv.hoTen << " (Mã NV: " << t->nv.maNV << "): ";
        cin >> t->nv.khenThuong; // Nhập giá trị khen thưởng
    }

    // Duyệt qua các nhánh trái và phải của cây
    NhapKhenThuongChoNhanVien(t->pLeft);  // Duyệt nhánh trái
    NhapKhenThuongChoNhanVien(t->pRight); // Duyệt nhánh phải
}

// Hàm gọi nhập khen thưởng cho tất cả nhân viên trong cây
void Nhapdsthuong(Tree &t)
{
    if (t == NULL)
    {
        return;
    }
    // Gọi hàm nhập khen thưởng cho nhân viên
    NhapKhenThuongChoNhanVien(t);
    // Sau khi nhập xong khen thưởng cho tất cả nhân viên
    cout << "Đã nhập khen thưởng cho các nhân viên trong danh sách!" << endl;
}

void ghiifile(Tree t)
{
    float x, y;
    cout << "Nhập giá trị khen thưởng x: ";
    cin >> x;
    cout << "Nhập giá trị khen thưởng y: ";
    cin >> y;

    // Gọi hàm để trích lọc nhân viên có khen thưởng trong khoảng từ x đến y và ghi vào file
    trichLocNhanVienKhenThuong(t, x, y);
}

//

void inOrder(Tree t)
{
    if (t != NULL)
    {
        inOrder(t->pLeft);
        xuatThongTinNhanVien(t->nv);
        inOrder(t->pRight);
    }
}

Tree timKiemNhanVien(Tree t, string maNv)
{
    if (t == NULL)
    {
        return NULL;
    }

    if (t->nv.maNV > maNv)
    {
        return timKiemNhanVien(t->pLeft, maNv);
    }
    else if (t->nv.maNV < maNv)
    {
        return timKiemNhanVien(t->pRight, maNv);
    }
    else
    {
        return t;
    }
}

Tree timNhanVienCoLuongCaoNhat(Tree t)
{
    if (t == NULL)
    {
        return NULL;
    }

    Tree maxTree = t;

    Tree leftMax = timNhanVienCoLuongCaoNhat(t->pLeft);
    if (leftMax != NULL && leftMax->nv.luongCoBan > maxTree->nv.luongCoBan)
    {
        maxTree = leftMax;
    }

    Tree rightMax = timNhanVienCoLuongCaoNhat(t->pRight);
    if (rightMax != NULL && rightMax->nv.luongCoBan > maxTree->nv.luongCoBan)
    {
        maxTree = rightMax;
    }

    return maxTree;
}

Tree timNhanVienCoLuongThapNhat(Tree t)
{
    if (t == NULL)
    {
        return NULL;
    }

    Tree minTree = t;

    Tree leftMin = timNhanVienCoLuongThapNhat(t->pLeft);
    if (leftMin != NULL && leftMin->nv.luongCoBan < minTree->nv.luongCoBan)
    {
        minTree = leftMin;
    }

    Tree rightMin = timNhanVienCoLuongThapNhat(t->pRight);
    if (rightMin != NULL && rightMin->nv.luongCoBan < minTree->nv.luongCoBan)
    {
        minTree = rightMin;
    }

    return minTree;
}

// Hàm đọc file và thêm nhân viên vào cây
void docFile(const string &filename, Tree &t)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Không mở được file";
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        NhanVien nv;

        getline(ss, nv.maNV, ',');
        getline(ss, nv.hoTen, ',');
        getline(ss, nv.chucVu, ',');
        getline(ss, nv.phongBan, ',');
        ss >> nv.ngaySinh.ngay;
        ss.ignore(); // Bỏ qua dấu gạch chéo
        ss >> nv.ngaySinh.thang;
        ss.ignore(); // Bỏ qua dấu gạch chéo
        ss >> nv.ngaySinh.nam;
        ss.ignore(); // Bỏ qua dấu phẩy
        getline(ss, nv.sdt, ',');
        getline(ss, nv.diaChi, ',');
        ss >> nv.luongCoBan;

        themNV(t, nv);
    }

    file.close();
}

// add nv vào mảng vector
void addNV(Tree t, vector<NhanVien> &nv)
{
    if (t != NULL)
    {
        addNV(t->pLeft, nv);
        nv.push_back(t->nv);
        addNV(t->pRight, nv);
    }
}

// hoán vị
void hoanVi(vector<NhanVien> &nv)
{
    for (int i = 0; i < nv.size() - 1; ++i)
    {
        for (int j = i + 1; j < nv.size(); ++j)
        {
            if (nv[i].luongCoBan > nv[j].luongCoBan)
            {
                NhanVien tmp = nv[i];
                nv[i] = nv[j];
                nv[j] = tmp;
            }
        }
    }
}

// sắp xếp
void sapXep(Tree t)
{
    vector<NhanVien> nv;
    addNV(t, nv);
    hoanVi(nv);

    cout << "\nDanh sách nhân viên sắp xếp theo lương là : \n";
    inTieuDe();
    for (NhanVien a : nv)
    {
        xuatThongTinNhanVien(a);
    }
}

// ghi file Nhan_Vien_Theo_Luong.txt
void ghiFile(Tree t)
{
    vector<NhanVien> nv;
    addNV(t, nv);
    hoanVi(nv);

    ofstream file("Nhan_Vien_Theo_Luong.txt");

    if (!file.is_open())
    {
        cout << "Mở file không thành công";
        return;
    }

    // Ghi thông tin nhân viên vào file
    for (NhanVien a : nv)
    {
        file << a.maNV << ","
             << a.hoTen << ","
             << a.chucVu << ","
             << a.phongBan << ","
             << a.ngaySinh.ngay << "/" << a.ngaySinh.thang << "/" << a.ngaySinh.nam << ","
             << a.sdt << ","
             << a.diaChi << ","
             << fixed << setprecision(2) << a.luongCoBan << endl;
    }
    file.close();
    cout << "Đã ghi danh sách nhân viên vào file 'Nhan_Vien_Theo_Luong.txt'" << endl;
}

bool xoaNhanVien(Tree &t, string manhanvien)
{
    if (t == NULL)
    {
        return false;
    }

    if (t->nv.maNV > manhanvien)
    {
        return xoaNhanVien(t->pLeft, manhanvien);
    }
    else if (t->nv.maNV < manhanvien)
    {
        return xoaNhanVien(t->pRight, manhanvien);
    }
    else
    {
        Tree p = t;
        if (t->pLeft == NULL)
        {
            t = t->pRight;
        }
        else if (t->pRight == NULL)
        {
            t = t->pLeft;
        }
        else
        {
            Tree e = t->pRight;

            while (e->pLeft != NULL)
            {
                e = e->pLeft;
            }

            t->nv = e->nv;
            return xoaNhanVien(t->pRight, e->nv.maNV);
        }
        delete p;
    }
    return true;
}

void suaTTNV(Tree &t, string manhanvien)
{
    Tree tim = timKiemNhanVien(t, manhanvien);
    if (tim == NULL)
    {
        cout << "Không tìm thấy nhân viên có mã : " << manhanvien;
    }
    else
    {
        inTieuDe();
        xuatThongTinNhanVien(tim->nv);
        while (1)
        {
            int luachon;
            cout << "Nhập lựa chọn cần sửa đổi: " << endl;
            cout << "0. Thoát" << endl;
            cout << "1. Sửa tên nhân viên" << endl;
            cout << "2. Sửa chức vụ nhân viên" << endl;
            cout << "3. Sửa phòng ban nhân viên" << endl;
            cout << "4. Sửa ngày sinh" << endl;
            cout << "5. Sửa sdt" << endl;
            cout << "6. Sửa địa chỉ" << endl;
            cout << "7. Sửa lương cơ bản" << endl;
            cout << "Lựa chọn của bạn: ";
            cin >> luachon;

            if (luachon == 0)
            {
                break;
            }
            else if (luachon == 1)
            {
                cout << "Nhập tên :";
                cin >> tim->nv.hoTen;
                cout << "Sửa thành công .";
                inTieuDe();
                xuatThongTinNhanVien(tim->nv);
            }
            else if (luachon == 2)
            {
                cout << "Nhập chức vụ :";
                cin >> tim->nv.chucVu;
                cout << "Sửa thành công .";
                inTieuDe();
                xuatThongTinNhanVien(tim->nv);
            }
            else if (luachon == 3)
            {
                cout << "Nhập phòng ban :";
                cin >> tim->nv.phongBan;
                cout << "Sửa thành công .";
                inTieuDe();
                xuatThongTinNhanVien(tim->nv);
            }
            else if (luachon == 4)
            {
                while (1)
                {
                    int lc;
                    cout << "0. Thoát \n";
                    cout << "1. Ngày sinh\n";
                    cout << "2. Tháng sinh \n";
                    cout << "3. Năm sinh \n";
                    cout << "Bạn muốn sửa : ";
                    cin >> lc;
                    if (lc == 0)
                    {
                        break;
                    }
                    else if (lc == 1)
                    {
                        cout << "Nhập ngày : ";
                        cin >> tim->nv.ngaySinh.ngay;
                        cout << "Sửa thành công .\n";
                        inTieuDe();
                        xuatThongTinNhanVien(tim->nv);
                    }
                    else if (lc == 2)
                    {
                        cout << "Nhập tháng :";
                        cin >> tim->nv.ngaySinh.thang;
                        cout << "Sửa thành công .\n";
                        inTieuDe();
                        xuatThongTinNhanVien(tim->nv);
                    }
                    else if (lc == 3)
                    {
                        cin >> tim->nv.ngaySinh.nam;
                        cout << "Sửa thành công .ư\n";
                        inTieuDe();
                        cout << "Nhập năm : ";
                        xuatThongTinNhanVien(tim->nv);
                    }
                }
            }
            else if (luachon == 5)
            {
                cout << "Nhập sdt :";
                cin >> tim->nv.sdt;
                cout << "Sửa thành công .\n";
                inTieuDe();
                xuatThongTinNhanVien(tim->nv);
            }
            else if (luachon == 6)
            {
                cin.ignore();
                cout << "Nhập địa chỉ :";
                getline(cin, tim->nv.diaChi);
                cout << "Sửa thành công .\n";
                inTieuDe();
                xuatThongTinNhanVien(tim->nv);
            }
            else if (luachon == 7)
            {
                cout << "Nhập lương cơ bản :";
                cin >> tim->nv.luongCoBan;
                cout << "Sửa thành công .\n";
                inTieuDe();
                xuatThongTinNhanVien(tim->nv);
            }
        }
    }
}

void ttnhanVien(Tree t)
{
    vector<NhanVien> listNV;
    addNV(t, listNV);
    inTieuDe();
    for (NhanVien a : listNV)
    {
        if (a.chucVu == "Nhan Vien")
        {
            xuatThongTinNhanVien(a);
        }
    }
}

void Menu3(Tree t)
{
    int luachon;
    while (1)
    {
        cout << endl;
        cout << "------------------------- MENU -------------------------" << endl;
        cout << "0. Thoát khỏi menu" << endl;
        cout << "1. Đọc dữ liệu từ file 'Qly_NhanVien.txt'" << endl;
        cout << "2. Xuất danh sách nhân viên theo LNR" << endl;
        cout << "3. Ghi file 'Nhan_Vien_Theo_Luong.txt' " << endl;
        cout << "4. Sắp xếp nhân viên theo lương giá từ thấp đến cao" << endl;
        cout << "5. Tìm kiếm nhân viên theo mã nhân viên" << endl;
        cout << "6. Xóa nhân viên" << endl;
        cout << "7. Thêm nhân viên vào danh sách" << endl;
        cout << "8. Sửa thông tin nhân viên" << endl;
        cout << "9. Xuất ra nhân viên có lương cao nhất" << endl;
        cout << "10. Xuất ra thuốc có lương thấp nhất" << endl;
        cout << "11. In ra thông tin người có chức vụ nhân viên" << endl;
        cout << "13. Nhập khen thưởng cho danh sách" << endl;

        cout << "------------------------- Endl -------------------------" << endl;

        cout << "Nhập lựa chọn : ";
        cin >> luachon;

        if (luachon == 0)
        {
            break;
        }
        else if (luachon == 1)
        {
            docFile("Qly_NhanVien.txt", t);
            cout << "Đọc file thành công";
        }
        else if (luachon == 2)
        {
            cout << "\nDanh sách nhân viên:\n";
            inTieuDe();
            inOrder(t);
        }
        else if (luachon == 3)
        {
            ghiFile(t);
        }
        else if (luachon == 4)
        {
            sapXep(t);
        }
        else if (luachon == 5)
        {
            string manhanvien;
            cout << "Nhập mã nhân viên cần tìm : ";
            cin >> manhanvien;
            Tree timkiem = timKiemNhanVien(t, manhanvien);
            if (timkiem != NULL)
            {
                cout << "\nTÌM THẤY THÔNG TIN NHÂN VIÊN\n";
                inTieuDe();
                xuatThongTinNhanVien(timkiem->nv);
            }
            else
                cout << "\nKhông tìm thấy nhân viên với mã : " << manhanvien << endl;
        }
        else if (luachon == 6)
        {
            string manhanvien;
            cout << "Nhập mã nhân viên cần xoá : ";
            cin >> manhanvien;
            bool re = xoaNhanVien(t, manhanvien);
            if (re == true)
            {
                cout << "Xoá nhân viên có mã : " << manhanvien << " thành công" << endl;
            }
            else
                cout << "Lỗi";
        }
        else if (luachon == 7)
        {
            NhanVien NV = nhapThongTinNhanVien();
            themNV(t, NV);
        }
        else if (luachon == 8)
        {
            string manhanvien;
            cout << "Nhập mã nhân viên cần sửa : ";
            cin >> manhanvien;
            suaTTNV(t, manhanvien);
        }
        else if (luachon == 9)
        {
            Tree maxLuong = timNhanVienCoLuongCaoNhat(t);
            if (maxLuong != NULL)
            {
                cout << "\n Nhân viên có lương cao nhất : \n";
                inTieuDe();
                xuatThongTinNhanVien(maxLuong->nv);
            }
            else
                cout << "\nCây không có nhân viên\n";
        }
        else if (luachon == 10)
        {
            Tree minLuong = timNhanVienCoLuongThapNhat(t);
            vector<NhanVien> listNV;
            if (minLuong != NULL)
            {
                addNV(t, listNV);
            }

            inTieuDe();
            cout << "\n Nhân viên có lương thấp nhất : \n";
            for (NhanVien _nv : listNV)
            {
                if (_nv.luongCoBan == minLuong->nv.luongCoBan)
                {
                    xuatThongTinNhanVien(_nv);
                }
            }
        }
        else if (luachon == 11)
        {
            ttnhanVien(t);
        }
        else if (luachon == 12)
        {
            ghiifile(t);
        }
        else if (luachon == 13)
        {
            Nhapdsthuong(t);
        }
    }
}

// KHÁCH HÀNG
// thêm cấu trúc khách hàng
struct KHACHHANG
{
    string MaKH;        // Mã khách hàng
    string TenKH;       // Tên khách hàng
    string DiaChi;      // Địa chỉ
    string SoDienThoai; // Số điện thoại
    float KhenThuong = 0;
};
typedef struct KHACHHANG KHACHHANG;

// thêm danh sách liên kết khách hàng

struct NODEKH
{
    KHACHHANG data; // Dữ liệu chứa thông tin khách hàng
    NODEKH *pNext;  // Con trỏ liên kết các khách hàng
};
typedef struct NODEKH NODEKH;

struct LISTKH
{
    NODEKH *pHead; // Quản lý đầu danh sách
    NODEKH *pTail; // Quản lý cuối danh sách
};
typedef struct LISTKH LISTKH;

// Khởi tạo danh sách
void KhoiTaoKH(LISTKH &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

// hàm thêm khách hàng
void ThemKhachHang(LISTKH &l, KHACHHANG kh)
{
    NODEKH *p = new NODEKH;
    p->data = kh;
    p->pNext = NULL;
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

// hàm đọc ds khách hàng từ file
void DocDanhSachKhachHang(ifstream &filein, LISTKH &l)
{
    while (!filein.eof())
    {
        KHACHHANG kh;
        getline(filein, kh.MaKH, ',');
        getline(filein, kh.TenKH, ',');
        getline(filein, kh.DiaChi, ',');
        getline(filein, kh.SoDienThoai);

        if (!kh.MaKH.empty())
        { // Kiểm tra dòng không rỗng
            ThemKhachHang(l, kh);
        }
    }
}

void DocFileKhachHang(LISTKH &l)
{
    ifstream filein("KhachHang.txt");
    if (filein.is_open())
    {
        DocDanhSachKhachHang(filein, l);
        filein.close();
        cout << "Đọc danh sách khách hàng từ file thành công!\n";
    }
    else
    {
        cout << "Không thể mở file để đọc.\n";
    }
}

// Kh thêm

// Hàm xuất khách hàng từ file đã đọc
void XuatDanhSachKhachHangDaDoc(LISTKH l)
{
    if (l.pHead == NULL)
    {
        cout << "Danh sách khách hàng rỗng hoặc chưa được đọc từ file.\n";
        return;
    }

    cout << "Danh sách khách hàng từ file:\n";
    cout << left << setw(10) << "MaKH"
         << setw(20) << "TenKH"
         << setw(30) << "DiaChi"
         << setw(15) << "SoDienThoai"
         << setw(19) << "KHEN THUONG " << endl;
    cout << string(75, '-') << endl;

    for (NODEKH *p = l.pHead; p != NULL; p = p->pNext)
    {
        cout << left << setw(10) << p->data.MaKH
             << setw(20) << p->data.TenKH
             << setw(30) << p->data.DiaChi
             << setw(15) << p->data.SoDienThoai
             << setw(19) << p->data.KhenThuong << endl;
    }
}

// hàm nhập thông tin khách hàng
void NhapThongTinKhachHang(LISTKH &l)
{
    KHACHHANG kh;
    cout << "Nhập mã khách hàng: ";
    getline(cin, kh.MaKH);
    cout << "Nhập tên khách hàng: ";
    getline(cin, kh.TenKH);
    cout << "Nhập địa chỉ: ";
    getline(cin, kh.DiaChi);
    cout << "Nhập số điện thoại: ";
    getline(cin, kh.SoDienThoai);
    cout << "Nhập khen thưởng thêm: ";
    cin >> kh.KhenThuong;
    ThemKhachHang(l, kh);
}

// hàm xóa khách hàng
void XoaKhachHang(LISTKH &l, string MaKHXoa)
{
    if (l.pHead == NULL)
    {
        cout << "Danh sách khách hàng rỗng.\n";
        return;
    }

    // Trường hợp xóa đầu danh sách
    if (l.pHead->data.MaKH == MaKHXoa)
    {
        NODEKH *p = l.pHead;
        l.pHead = l.pHead->pNext;
        delete p;
        cout << "Đã xóa khách hàng có mã: " << MaKHXoa << endl;
        return;
    }

    // Trường hợp xóa giữa hoặc cuối danh sách
    NODEKH *prev = NULL; // con trỏ lưu trữ node trước đó
    for (NODEKH *curr = l.pHead; curr != NULL; curr = curr->pNext)
    {
        if (curr->data.MaKH == MaKHXoa)
        {
            prev->pNext = curr->pNext;
            if (curr == l.pTail)
                l.pTail = prev; // Cập nhật lại pTail nếu xóa cuối
            delete curr;
            cout << "Đã xóa khách hàng có mã: " << MaKHXoa << endl;
            return;
        }
        prev = curr;
    }

    cout << "Không tìm thấy khách hàng có mã: " << MaKHXoa << endl;
}

// hàm sửa thông tin khách hàng
void SuaKhachHang(LISTKH &l, string MaKHSua)
{
    NODEKH *p = l.pHead;
    while (p != NULL)
    {
        if (p->data.MaKH == MaKHSua)
        {
            int luachon;
            cout << "Khách hàng tìm thấy. Chọn thông tin cần sửa:\n";
            cout << "1. Sửa tên khách hàng\n";
            cout << "2. Sửa địa chỉ\n";
            cout << "3. Sửa số điện thoại\n";
            cout << "0. Quay lại\n";
            cout << "Lựa chọn: ";
            cin >> luachon;
            cin.ignore();

            if (luachon == 1)
            {
                cout << "Nhập tên mới: ";
                getline(cin, p->data.TenKH);
                cout << "Tên khách hàng đã được cập nhật.\n";
            }
            else if (luachon == 2)
            {
                cout << "Nhập địa chỉ mới: ";
                getline(cin, p->data.DiaChi);
                cout << "Địa chỉ khách hàng đã được cập nhật.\n";
            }
            else if (luachon == 3)
            {
                cout << "Nhập số điện thoại mới: ";
                getline(cin, p->data.SoDienThoai);
                cout << "Số điện thoại khách hàng đã được cập nhật.\n";
            }
            else if (luachon == 0)
            {
                return;
            }
            else
            {
                cout << "Lựa chọn không hợp lệ.\n";
            }
            return;
        }
        p = p->pNext;
    }

    cout << "Không tìm thấy khách hàng có mã: " << MaKHSua << endl;
}

// ghi ds khách hàng vào file
void GhiDanhSachKhachHang(ofstream &fileout, LISTKH l)
{
    for (NODEKH *p = l.pHead; p != NULL; p = p->pNext)
    {
        fileout << p->data.MaKH << ","
                << p->data.TenKH << ","
                << p->data.DiaChi << ","
                << p->data.SoDienThoai << endl;
    }
}

void LuuFileKhachHang(LISTKH l)
{
    ofstream fileout("KhachHang.txt");
    if (fileout.is_open())
    {
        GhiDanhSachKhachHang(fileout, l);
        fileout.close();
        cout << "Lưu danh sách khách hàng vào file thành công!\n";
    }
    else
    {
        cout << "Không thể mở file để ghi.\n";
    }
}

// hàm hoán đổi
void HoanViKhachHang(KHACHHANG &a, KHACHHANG &b)
{
    KHACHHANG temp = a;
    a = b;
    b = temp;
}

// hàm kiểm tra hóa đơn của 1 khách hàng
//  hàm xuất ds KH tự động
void XuatDanhSachKhachHangTungDong(const string &fileName)
{
    ifstream filein(fileName);
    if (!filein.is_open())
    {
        cout << "Không thể mở file " << fileName << " để đọc!\n";
        return;
    }

    string line;
    while (getline(filein, line))
    {
        cout << line << endl; // In ra mỗi dòng
    }

    filein.close();
    cout << "Đã xuất danh sách khách hàng từ file: " << fileName << endl;
}

//  hàm lưu danh sách vào file khác
void LuuDanhSachKhachHangVaoFile(LISTKH l, const string &fileName)
{
    ofstream fileout(fileName);
    if (!fileout.is_open())
    {
        cout << "Không thể mở file " << fileName << " để ghi!\n";
        return;
    }

    for (NODEKH *p = l.pHead; p != NULL; p = p->pNext)
    {
        fileout << p->data.MaKH << ","
                << p->data.TenKH << ","
                << p->data.DiaChi << ","
                << p->data.SoDienThoai << endl;
    }

    fileout.close();
    cout << "Danh sách khách hàng đã được lưu vào file: " << fileName << endl;
}

// sắp xếp danh sách và lưu vào file tu a-z sau khi sắp xếp
void SapXepKhachHangTheoTenVaLuuFile(LISTKH &l, const string &fileName)
{
    // Kiểm tra nếu danh sách rỗng hoặc chỉ có một phần tử
    if (l.pHead == NULL || l.pHead->pNext == NULL)
        return;

    // Thuật toán Bubble Sort để sắp xếp khách hàng theo tên (A-Z)
    for (NODEKH *i = l.pHead; i->pNext != NULL; i = i->pNext)
    {
        for (NODEKH *j = i->pNext; j != NULL; j = j->pNext)
        {
            if (i->data.TenKH > j->data.TenKH)
            {                                      // So sánh tên khách hàng
                HoanViKhachHang(i->data, j->data); // Hoán đổi thông tin khách hàng
            }
        }
    }

    cout << "Danh sách khách hàng đã được sắp xếp theo tên (A-Z).\n";

    // Lưu danh sách khách hàng đã sắp xếp vào file mới
    LuuDanhSachKhachHangVaoFile(l, fileName);

    // Hiển thị nội dung file vừa ghi
    XuatDanhSachKhachHangTungDong(fileName);
}

// xuất danh sách kh đã sắp xếp từ a-z
void XuatDanhSachKhachHangAZ(const string &fileName)
{
    ifstream filein(fileName);
    if (!filein.is_open())
    {
        cout << "Không thể mở file " << fileName << " để đọc!\n";
        return;
    }

    string line;
    while (getline(filein, line))
    {
        cout << line << endl; // In ra mỗi dòng
    }

    filein.close();
    cout << "Đã xuất danh sách khách hàng từ file: " << fileName << endl;
}

void NhapDSKHThem(LISTKH &l)
{
    for (NODEKH *p = l.pHead; p != NULL; p = p->pNext)
    {
        if (p->data.KhenThuong == 0)
        {
            cout << "Nhập khen thưởng cho khách hàng " << p->data.TenKH << " MAKH " << p->data.MaKH << ": ";
            cin >> p->data.KhenThuong;
        }
    }
}

void luufileKH(LISTKH l)
{
    ofstream fileout("Khenthuong.txt");
    cout << "Hãy nhập giá trị x";
    int x, y;
    cin >> x;
    cout << "Hãy nhập giá trị y ";
    cin >> y;
    for (NODEKH *p = l.pHead; p != NULL; p = p->pNext)
    {
        if (p->data.KhenThuong > x && p->data.KhenThuong < y)
        {
            fileout << p->data.MaKH << ", ";
            fileout << p->data.TenKH << ", ";
            fileout << p->data.DiaChi << ", ";
            fileout << p->data.SoDienThoai << ", ";
            fileout << p->data.KhenThuong << ", " << endl;
        }
    }
    fileout.close();
}

// menu khách hàng
void MenuKhachHang(LISTKH &lKhachHang, LISTT &lHoaDon)
{
    int chon;
    while (true)
    {
        cout << "------------------------- MENU -------------------------" << endl;
        cout << "1. Nhập thông tin khách hàng từ file ' DanhSachKhachHang.txt '" << endl;
        cout << "2. Xuất danh sách khách hàng đã đọc từ file" << endl;
        cout << "3. Xóa khách hàng" << endl;
        cout << "4. Sửa thông tin khách hàng" << endl;
        cout << "5. Kiểm tra hóa đơn của khách hàng" << endl;
        cout << "6. Lưu danh sách khách hàng vào file" << endl;
        cout << "7. Thêm khách hàng" << endl;
        cout << "8. Sắp xếp khách hàng theo tên (A-Z) và lưu vào file ' DanhSachKhachHang_SapXepTuA-Z.txt '" << endl;
        cout << "0. Quay lại" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Bạn chọn";
        cin >> chon;
        cin.ignore();

        if (chon == 0)
        {
            break;
        }
        else if (chon == 1)
        {
            DocFileKhachHang(lKhachHang);
        }
        else if (chon == 2)
        {
            XuatDanhSachKhachHangDaDoc(lKhachHang);
        }
        else if (chon == 3)
        {
            string MaKHXoa;
            cout << "Nhập mã khách hàng cần xóa: ";
            getline(cin, MaKHXoa);
            XoaKhachHang(lKhachHang, MaKHXoa);
        }
        else if (chon == 4)
        {
            string MaKHSua;
            cout << "Nhập mã khách hàng cần sửa: ";
            getline(cin, MaKHSua);
            SuaKhachHang(lKhachHang, MaKHSua);
        }
        else if (chon == 5)
        {
            string MaKH;
            cout << "Nhập mã khách hàng cần kiểm tra hóa đơn: ";
            getline(cin, MaKH);
            Tim_Kiem_Thong_Tin_Dua_Vao_Ma_Khach_Hang(lHoaDon, MaKH);
        }
        else if (chon == 6)
        {
            LuuFileKhachHang(lKhachHang);
        }
        else if (chon == 7)
        {
            NhapThongTinKhachHang(lKhachHang);
        }
        else if (chon == 8)
        {
            SapXepKhachHangTheoTenVaLuuFile(lKhachHang, "DanhSachKhachHang_SapXepTuA-Z.txt");
        }
        else if (chon == 9)
        {
            NhapDSKHThem(lKhachHang);
        }
        else if (chon == 10)
        {
            luufileKH(lKhachHang);
        }
        else
        {
            cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
        }
    }
}

// CODE Thêm

// Cấu trúc nhà cung cấp thuốc
// Sửa lại cấu trúc danh sách và các hàm tương ứng
struct NhaCungCap
{
    string MaThuocCC;
    string TenNCC;      // Tên nhà cung cấp
    string MaNCC;       // Mã nhà cung cấp
    string DiaChi;      // Địa chỉ nhà cung cấp
    string SoDienThoai; // Số điện thoại
};
typedef struct NhaCungCap NHACUNGCAP;

struct nodenhacc
{
    NhaCungCap data;         // dữ liệu chứa trong 1 cái node
    struct nodenhacc *pNext; // con trỏ dùng để liên kết giữa các node với nhau
};
typedef struct nodenhacc NODENCC;

// Khai báo cấu trúc danh sách liên kết đơn các nhà cung cấp
struct listncc
{
    NODENCC *pHead; // node quản lí đầu danh sách
    NODENCC *pTail; // node quản lí cuối danh sách
};
typedef struct listncc LISTNCC;

// Khởi tạo danh sách nhà cung cấp
void KhoiTaoNCC(LISTNCC &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

// Khởi tạo node nhà cung cấp
NODENCC *KhoiTaoNODENCC(NHACUNGCAP x)
{
    NODENCC *p = new NODENCC;
    if (p == NULL)
    {
        cout << "Không đủ bộ nhớ để cấp phát! ";
        return NULL;
    }
    p->data = x;
    p->pNext = NULL;
    return p;
}

// Thêm node vào đầu danh sách liên kết
void ThemVaoDauNCC(LISTNCC &l, NODENCC *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        p->pNext = l.pHead;
        l.pHead = p;
    }
}

// Thêm node vào cuối danh sách liên kết
void ThemVaoCuoiNCC(LISTNCC &l, NODENCC *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

// Xóa node đầu danh sách
void XoaDauNCC(LISTNCC &l)
{
    if (l.pHead == NULL)
        return;
    NODENCC *p = l.pHead;
    l.pHead = l.pHead->pNext;
    delete p;
}

// Xóa node cuối danh sách
void XoaCuoiNCC(LISTNCC &l)
{
    if (l.pHead == NULL)
        return;
    if (l.pHead->pNext == NULL)
    {
        XoaDauNCC(l);
        return;
    }
    for (NODENCC *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->pNext == l.pTail)
        {
            delete l.pTail;
            k->pNext = NULL;
            l.pTail = k;
            return;
        }
    }
}

// Thêm nhà cung cấp vào danh sách
void ThemNCC(LISTNCC &l, NHACUNGCAP NCC)
{
    NODENCC *p = KhoiTaoNODENCC(NCC);
    if (p == NULL)
    {
        return;
    }

    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

// Nhập thông tin nhà cung cấp

void Nhap_Thong_Tin_NCC(LISTNCC &l)
{
    NHACUNGCAP NCC;
    cout << "Nhập tên nhà cung cấp: ";
    getline(cin, NCC.TenNCC);
    cout << "Nhập mã nhà cung cấp: ";
    getline(cin, NCC.MaNCC);
    cout << "Nhập mã thuốc nhà cung cấp cung cấp: ";
    getline(cin, NCC.MaThuocCC);
    cout << "Nhập địa chỉ nhà cung cấp: ";
    getline(cin, NCC.DiaChi);
    cout << "Nhập số điện thoại nhà cung cấp: ";
    getline(cin, NCC.SoDienThoai);
    ThemNCC(l, NCC);
}

// In thông tin nhà cung cấp
void XuatNCC(NHACUNGCAP NCC)
{
    cout << left << setw(15) << NCC.TenNCC
         << setw(10) << NCC.MaNCC
         << setw(10) << NCC.MaThuocCC
         << setw(10) << NCC.DiaChi
         << setw(12) << NCC.SoDienThoai
         << endl;
}

// In tiêu đề danh sách nhà cung cấp
void XuatTieuDeNCC()
{
    cout << "---------------------------------------------------------------" << endl;
    cout << left << setw(5) << "STT" << setw(15) << "NHA CC"
         << setw(10) << "MA NCC"
         << setw(10) << "MA THUOC"
         << setw(10) << "DIA CHI"
         << setw(12) << "SO LUONG"
         << endl;
    cout << "---------------------------------------------------------------" << endl;
}

// In danh sách nhà cung cấp
void Xuat_Danh_Sach_NCC(LISTNCC &l)
{
    int STT = 0;
    XuatTieuDeNCC();
    for (NODENCC *k = l.pHead; k != NULL; k = k->pNext)
    {
        STT++;
        cout << left << setw(5) << STT;
        XuatNCC(k->data);
        cout << endl;
    }
}

// Lưu vào file
void LuufileNCC(LISTNCC l){
    ofstream fileout("NCC.txt");
    for(NODENCC *p = l.pHead ; p!= NULL ; p = p->pNext){
        fileout << p->data.MaNCC<<", " ; 
        fileout << p->data.TenNCC<<", ";
        fileout << p->data.MaThuocCC<<", ";
        fileout << p->data.DiaChi<<", ";
        fileout << p->data.SoDienThoai<< endl ; 
    }
    fileout.close();
}

void XoaThongTinNCC(LISTNCC &l, string NCCXoa)
{
    if (l.pHead == NULL)
    {
        return;
    }
    // nếu thuốc cần xóa nằm dầu danh sách
    if (l.pHead != NULL && l.pHead->data.MaNCC == NCCXoa)
    {
        XoaDauNCC(l);
    }
    // nếu thuốc cần xóa nằm cuối danh sách
    if (l.pTail != NULL && l.pTail->data.MaNCC == NCCXoa)
    {
        XoaCuoiNCC(l);
    }
    NODENCC *g = new NODENCC; // node g là node giữ lien kết trỏ đến node nằm trc node cần xóa
    // duyệt danh sách liên kết đơn để tìm
    for (NODENCC *k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.MaNCC == NCCXoa)
        {                        // node h chính là node nằm sau node k <=> node mà ta sẽ xóa
            g->pNext = k->pNext; // cập nhật mối liên kết giữa node
            delete k;            // xóa node
            return;
        }
        g = k; // cho node g trỏ đến node k
    }
}
// Menu thao tác với nhà cung cấp
void menu4(LISTNCC &l)
{
    int luachon;
    while (true)
    {
        cout << "0. Thoát" << endl;
        cout << "1. Thêm NCC" << endl;
        cout << "2. Hiện NCC" << endl;
        cout << "3. Lưu NCC vào file"<<endl ;
        cout << "4. Xóa thông tin NCC"<<endl; 
        cout << "Chọn thao tác: ";
        cin >> luachon;
        cin.ignore();

        if (luachon == 0)
        {
            break;
        }
        else if (luachon == 1)
        {
            Nhap_Thong_Tin_NCC(l);
        }
        else if (luachon == 2)
        {
            Xuat_Danh_Sach_NCC(l);
        }
        else if(luachon == 3){
            LuufileNCC(l) ; 
        }
        else if(luachon == 4){
            cout << "Hãy nhập mã NCC cần xóa: ";
            string NCCXoa ; 
            getline(cin,NCCXoa) ; 
            XoaThongTinNCC(l,NCCXoa) ;
        }
    }
}



int main()
{
    LIST l;
    KhoiTao(l);
    LISTT p;
    KhoiTaoHoaDon(p);
    Tree t;
    khoiTaoCay(t);
    LISTKH lKhachHang; // Danh sách khách hàng
    KhoiTaoKH(lKhachHang);
    LISTNCC NCC ; 
    KhoiTaoNCC(NCC) ; 

    while (69)
    {
        cout << "Hãy nhập thao tác" << endl;
        cout << "1. Thao tác với Thuốc" << endl;
        cout << "2. Thao tác trên hóa đơn thuốc" << endl;
        cout << "3. Thao tác với nhân viên" << endl;
        cout << "4. Thao tác với khách hàng" << endl;
        cout << "0. Thoát" << endl;
        cout << "test"<<endl;
        int luachon;
        cout << "Bạn chọn: ";
        cin >> luachon;
        cin.ignore();
        if (luachon == 1)
        {
            Menu(l);
        }
        else if (luachon == 2)
        {
            Menu2(p);
        }
        else if (luachon == 3)
        {
            Menu3(t);
        }
        else if (luachon == 4)
        {
            MenuKhachHang(lKhachHang, p);
        }
        else if(luachon == 5){
            menu4(NCC) ; 
        }
        else if (luachon == 0)
        {
            break;
        }
    }
} 