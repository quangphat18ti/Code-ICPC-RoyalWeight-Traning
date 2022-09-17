# FencedIn Problem
## Link Đề
[FenceIn](http://www.usaco.org/index.php?page=viewproblem2&cpid=625)
## Tóm tắt đề:
- Cho 1 bảng kích thước _A * B_ 
    * Bắt đầu là **[0,0]**
    * Kết thúc là **[A - 1, B - 1]**
    
- Cho n thanh bắt ngang cắt từ _(a[i], 0) -> (a[i], B)_;
- Cho m thanh dọc cắt từ _(0, b[i]) -> (A, b[i])_

- Hỏi chi phí nhỏ nhất để cắt bớt cạnh để các ô có thể đi đến nhau

## Hướng dẫn 1 
### _Solution: Coi mỗi ô là 1 đỉnh của đồ thị và thực hiện DSU_
* Với n đường ngang và m đường dọc thì ta sẽ có 1 bảng với các ô hcn con gồm:
    > n + 1 hàng \
    > m + 1 cột \
    > (n + 1) * (m + 1) ô 
* Như vậy, ta có thể coi 1 ô như 1 đỉnh của đồ thị:
    * Mỗi đỉnh có nhiều nhất 4 cạnh
    * Build tất cả các cạnh của đồ thị 
    * DSU như bình thường
### Hạn chế:
* Nếu làm như vậy thì chỉ qua được 50% số test của đề bài
* Những test còn lại thì $n * m >= 10^8$

## Hướng dẫn 2
### _Solution: Đừng phức tạp hóa vấn đề và nhìn lại bài 1 lần nữa, bạn sẽ nhận thấy điều khác biệt đấy :))_
* Nếu vẫn không nghĩ ra được thì hướng dẫn nằm trong phần code nhé 😁