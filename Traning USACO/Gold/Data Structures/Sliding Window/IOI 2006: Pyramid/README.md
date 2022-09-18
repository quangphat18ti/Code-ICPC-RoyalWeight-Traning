
# IOI 2006 - B: Pyramid

## Link: 

[IOI 2006: Pyramid](https://contest.yandex.com/ioi/contest/562/problems/B/)

## Tóm tắt đề bài:
- Cho ma trận $A$ kích thước $N*M$, gồm các giá trị nguyên dương.
- Cần tìm vị trí hai hình chữ nhật, sao cho:
	- Hình chữ nhật thứ nhất có kích thước $a*b$.
	- Hình chữ nhật thứ hai có kích thước $c*d$.
	- Hình chữ nhật thứ hai phải nằm trong hình chữ nhật thứ nhất, và hai hình chữ nhật không được chung cạnh.
	- $Sum(i,j,a,b) - Sum(x,y,c,d)$ đạt $max$. Trong đó, $Sum(i,j,a,b)$ là tổng của hình chữ nhật có ô trái trên là $[i,j]$ và kích thước $a*b$.

**Yêu cầu:** Xuất ra vị trí $2$ ô trái trên của $2$ hình chữ nhật thỏa yêu cầu.

**Giới hạn:** 
- $3\leq N, M \leq 1000.$
- $3\leq a\leq N$
- $3\leq b\leq M.$
- $1\leq c\leq a-2.$
- $1\leq d\leq b-2.$
- $1\leq A_{i,j}\leq 100.$

**Nhập:**
- Dòng đầu gồm $6$ số nguyên dương $N,M,a,b,c,d$.
- $N$ dòng tiếp theo, mỗi dòng gồm $M$ số nguyên dương là giá trị từng ô.

## Nhận xét:
- Ta duyệt từng vị trí $[i,j]$, khi đó:
	- Để $Sum(i,j,a,b) - Sum(x,y,c,d)$ đạt $max$
	$\Rightarrow$ $Sum(x,y,c,d)$ đạt $min$.

## Hướng dẫn giải:
- Duyệt từng vị trí $[i,j]$, dùng Deque2B, hoặc BIT2D, hoặc RMQ2D để tìm $[x,y]:=$ $([i+1,j+1] \rightarrow [i+a-c-1,j+b-d-1])$ có $Sum(x,y,c,d)$ đạt $min$.
