# Sirni Problem
## Link Đề
[Sirni](https://oj.uz/problem/view/COCI17_sirni)
## Tóm tắt đề
* Cho mảng A có N phần tử.
* Trọng số mỗi cặp cạnh A[i] và A[j] là: **min( A[i] % A[j], A[j] % A[i] )**
* Tìm cây khung nhỏ nhất liên kết N thằng.

## Hướng dẫn
### Vấn đề: _Số đỉnh quá lớn để có thể build tất cả cạnh và DSU, vì vậy nên ta chỉ có thể chọn 1 vài cạnh đặc biệt nào đó để build_ 

###  Nhận xét 1: _Các đỉnh nên có giá trị riêng biệt_
*   Và như vậy, các đỉnh có giá trị bằng nhau thì mình sẽ không cần xét đến nó.
*    Như vậy, ta sẽ chuyển bài toán về thành các giá trị khác nhau
 
### Nhận xét 2: _Duyệt bội số của từng giá trị_
*    Dễ dàng nhận thấy, vì $maxVal = 10^7$ nên ta có thể dễ dàng **lặp qua các bội số** của các giá trị trong mảng A
*    Và ta sẽ kết nối các giá trị này lại với trọng số cạnh = 0
 
### Nhận xét 3: _Cách chọn cạnh tối ưu_
*    Với mỗi A[i], ta lặp qua các bội số của $A_i$
*    Lúc này ta mặc định, trọng số $A_j$ và $A_i$ là $A_j - A_i$ luôn. Tự chứng minh
*    Ta sẽ thêm các cạnh với các giá trị gần nhất với bội số này 
*    Như vậy thì ta không còn phải thực hiện phép mod nữa mà dễ dàng so sánh các số.
 
### Nhận xét 4: _Nên chọn như thế nào_
*   Vì ta không biết từ 1 bội số  thì ta cần nối tới bao nhiêu cạnh
          gần nhất.
*   Nên ta sẽ **tìm kiếm nhị phân giá trị cạnh lớn nhất** để DSU 
*   Hoặc **tìm kiếm nhị phân số cạnh cần nối** từ 1 đỉnh đi ra để hoàn chỉnh cây DSU

### Nhận xét 5: _Những gì ghi ở nhận xét 4 là xàm lol_
* Tại sao xàm lol và làm sao để thay đổi thì mọi người tự suy nghĩ nhee