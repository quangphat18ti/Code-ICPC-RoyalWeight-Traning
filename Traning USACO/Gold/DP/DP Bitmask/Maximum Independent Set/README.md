## Tóm tắt đề:

+Cho đồ thị vô hướng N đỉnh, M cạnh (1 <= N <= 40 , 0 <= M <= N(N-1)/2 ).

+Tập đỉnh độc lập a[i] (1 <= k <= n) khi và chỉ khi không có đường nối trực tiếp giữa a[i], a[j] (1 <= i,j <= k).

-**Yêu cầu**: Tìm tập độc lập có số lượng phần tử lớn nhất.

## Idea 1:

N = 40 --> duyệt phân tập (gọi là tập trái, tập phải) , (tập trái [1,20], tập phải [21 , 40]). Nếu N < 21 thì tập phải rỗng).

-Gọi 2 mảng: f[] , g[] đại diện cho tập trái và tập phải.

-Thực hiện độc lập trên 2 tập.

  - Trạng thái f[mask] (0 <= mask <= (2^20)-1) ) lưu số lượng phần tử tại trạng thái 'mask' thỏa mãn đề bài. (1)
  
  - Tương tự với g[mask].

## Idea 2: 

(bit[i] = 1 tương ứng với chọn đỉnh thứ i trong tập đó và ngược lại)

-**Nhận xét**: khi chọn được tập A có trạng thái thỏa đề bài, thì chắc chắn chọn được tập B có các bit mà tại các A[i] = 0 thì B[i] = 0, A[i] = 1 thì B[i] tùy ý.

  - VD: A = '1001101' thì chắc chắn chọn được B = '1001001' hoặc B = '1000001' hoặc B = '0001101' hoặc B = '0000000'.
  
==> Tối ưu g[A] = max(g[A] , g[B]) (với A, B theo mô tả trên) **(2)**
 
 ## Idea 1+2 = KẾT QUẢ:
 -Với mỗi trạng thái F[mask1] sẽ lấy được 1 tập các đỉnh trong tập phải độc lập với tập trái (các đỉnh TẬP PHẢI ĐỘC LẬP VỚI TẬP TRÁI, NHƯNG CÁC ĐỈNH TRONG TẬP TRÁI CÓ THỂ KHÔNG ĐỘC LẬP VỚI NHAU).
 
 -Tại bước này: tập trái chỉ quan tâm lấy được nhiều nhất các đỉnh của tập phải, còn trong các đỉnh 'tập bên phải lấy được' đó chọn ra nhiều đỉnh nhất độc lập với nhau là chuyện tại bước **(1)** và **(2)**.
 
 -Vậy kết quả bài toán sẽ là max của tất cả các trạng thái f[mask1] cộng với trạng thái g[mask2] thỏa
 
