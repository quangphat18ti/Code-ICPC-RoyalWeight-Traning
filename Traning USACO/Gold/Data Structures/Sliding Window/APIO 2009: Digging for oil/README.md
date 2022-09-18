
# APIO '09 P1 - Digging for Oil

## Link: 

[Digging for Oil](https://dmoj.ca/problem/apio09p1)

## Tóm tắt đề bài:

- Cho ma trận $A$ kích thước $M*N$ gồm các giá trị không âm.
- Bạn được phép chọn $3$ hình vuông kích thước $K*K$, sao cho không có $2$ hình vuông bất kì giao nhau.

**Yêu cầu:** Tìm tổng giá trị lớn nhất của 3 hình vuông.
**Giới hạn:** 
- $M,N\leq1500.$
- $K\leq M,N.$
- $A_{i,j}\leq 500.$
## Nhận xét:
Vì cách xử lý theo chiều dọc hay chiều ngang nhìn chung giống nhau, nên chỉ xét $1$ chiều làm mẫu.

Với mỗi cách chia đôi ma trận làm hai phần (theo chiều dọc), ta chỉ có $2$ cách chọn $3$ hình vuông như sau:

- Cách chọn 1: 
	- Có thể tiếp tục chia đôi ma trận (theo chiều dọc) làm hai phần $H_1$, $H_2$.

<figure>
<p align="center">
<img src="https://i.imgur.com/AHJngLO.png" alt="Raspberry pi" style="width:20%; border:0;">
</p>
</figure>


- Cách chọn 2:
	- Có thể tiếp tục chia đôi ma trận (theo chiều ngang) làm hai phần $H_1$, $H_2$.

<figure>
<p align="center">
<img src="https://i.imgur.com/X6cd2a9.png" style="width:20%; border:0;">
</p>
</figure>

## Hướng dẫn giải:
- Ta thấy kết quả bài toán là $max$ của hai cách chọn trên.
$\implies$ Tìm cách giải cho từng cách chọn và lấy $max$.
- Gọi $Max1[i][j][z]$ $(1\leq i\leq n, 1\leq j\leq m, 1\leq z\leq 4)$ là tổng tối đa của cách chọn $1$ hình vuông $K*K$ trong hình chữ nhật của góc phần tư thứ $z$.
	- Có thể tính quy hoạch động này bằng nhiều cách: RMQ2D, BIT2D, Deque2D.
- Gọi $Max2[i][j][z]$ $(1\leq i\leq n, 1\leq j\leq m, 1\leq z\leq 4)$ là tổng tối đa của cách chọn $2$ hình vuông $K*K$ trong hình chữ nhật của góc phần tư thứ $z$.
	- Tính quy hoạch động này dựa trên $Max1[i][j][z]$.
- Kết quả bài toán sẽ dựa vào hai quy hoạch động $Max2[i][j][z]$, $Max1[i][j][z]$. Ráng suy nghĩ xem sẽ làm sao nha 😊.

**Chú thích:** Góc phần tư của hình chữ nhật lần lượt là:
<figure>
<p align="center">
<img src="https://i.imgur.com/dC632Dy.png" style="width:20%; border:0;">
</p>
</figure>


