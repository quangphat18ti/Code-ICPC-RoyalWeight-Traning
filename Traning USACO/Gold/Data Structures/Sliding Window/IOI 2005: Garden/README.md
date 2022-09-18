
# IOI 2005 - A: Garden

## Link: 

[IOI 2005: Garden](https://contest.yandex.com/ioi/contest/566/problems/A/)

## Tóm tắt đề bài:
- Cho ma trận $A$ kích thước $N*M$, ban đầu bằng $0$.
- Có $Q$ lần tăng giá trị của một ô bất kì trong ma trận thêm 1.
- Cần tìm $2$ hình chữ nhật không giao nhau sao cho:
	- Tổng mỗi hình chữ nhật chỉ đúng bằng $K$.
	- Tổng chu vi hai hình chữ nhật là lớn nhất.


**Yêu cầu:** Xuất ra tổng chu vi hai hình tìm được.

**Giới hạn:** 
- $1\leq N, M \leq 250.$
- $2\leq Q \leq 5000.$
- $1\leq K \leq {Q \above 1pt 2}.$

## Hướng dẫn giải 1:
- Nhìn nhanh mình có thể phát hiện ngay đây là một bài QHD.
- Gọi $maxChuVi[i][j][z]$ $(1\leq i\leq N, 1\leq j\leq M,1\leq z \leq 4)$ là chu vi hình chữ nhật lớn nhất có tổng đúng bằng $K$ trong hình chữ nhật tới vị trí $[i,j]$ của góc phần tư thứ $z$.
- Như vậy, kết quả bài toán sẽ được tính thông qua QHD $maxChuVi[i][j][z]$, chỗ này ráng tự nghĩ nhen 😊.

## Hướng dẫn giải 2:
- Độ phức tạp bài toán sẽ phụ thuộc vào cách code $maxChuVi[i][j][z]$.
- Tiếp cận thông thường:
	- Duyệt $4$ vòng lặp để có thể tính được $maxChuVi[i][j][z]$.
	$\Rightarrow$ Bỏ qua vì quá thời gian.

**Cải tiến:**
- Ở đây mình thấy:
	- $2$ vòng lặp đầu duyệt từng điểm $[i,j]$ không thể bỏ.
	- Cải tiến $2$ vòng lặp dùng cập nhật QHD về chỉ còn $1$ vòng lặp hoặc $1$ vòng lặp chạy thêm $log2$.
- Có thể thấy khi duyệt từng điểm$[i,j]$.
	- Chúng ta cần tìm hình chữ nhật có chu vi lớn nhất có tổng đúng bằng $K$. 
	- Khi chiều dài của hình chữ nhật này tăng dần, thì chiều rộng của nó sẽ giảm dần.
	$\Rightarrow$ Cải tiến bằng chặt nhị phân, hoặc hai con trỏ.

**Chú thích:** Góc phần tư của hình chữ nhật lần lượt là:
<figure>
<p align="center">
<img src="https://i.imgur.com/dC632Dy.png" style="width:20%; border:0;">
</p>
</figure>
