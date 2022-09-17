# Kingdom Of Criticism Problem
## Link Đề
[Kingdom Of Criticism](https://codeforces.com/contest/1725/problem/K)
## Tóm tắt đề
*  Cho 1 mảng A có N phần tử nguyên dương <= 1e9

* Có 3 truy vấn như sau:
    + 1 k w: a[k] = w
    + 2 k: Xuất a[k]
    + 3 l r: Tất cả các giá trị của A không thuộc đoạn [l -> r]  (r - l + 1 chẵn)

* Trong đó truy vấn 3:
    + 1 lượt bạn có thể tăng hoặc giảm giá trị của 1 a[i] đi 1
    + Bạn cần thực hiện ít bước nhất có thể, và dễ dàng chứng minh được chỉ có 1 cách thỏa.
    + Bạn chỉ cần biết giá trị cuối cùng của mảng chứ không nhất thiết phải biết sử dụng bao nhiêu cách.
## Hướng dẫn
### Nhận xét 1:
* Với mỗi đoạn l -> r thì các giá trị:
    * _l -> mid_: Giảm xuống l - 1  (Nhóm 1)
    * _mid + 1 -> r_: Tăng lên r + 1 (Nhóm 2)
* Như vậy, ta sẽ tách 1 truy vấn 3 thành 2 truy vấn tách biệt nhau

### Nhận xét 2: Khi rơi vào truy vấn 2
* Mình chỉ cần quan tâm với truy vấn 1 gần nhất
* Nếu có truy vấn 1 đè lên nó thì ta cũng không cần phải quan tâm tới truy vấn 3 gần nhất

###  Nhận xét 3:
* Khi cần truy cập vào thằng u thì ta lần lượt thực hiện:
    * Tìm kiếm truy vấn 1 gần nhất
    * Tìm kiếm truy vấn 3 từ truy vấn 1 đó đổ đi.
    * Như vậy nó sẽ liên quan với 1 chuỗi 3 liên tiếp nào đó và dựa vào truy vấn 1 gần nhất, ta có thể tìm thấy điểm bắt đầu của 1 chuỗi 3 đó.

### Câu hỏi:
* Khi có vị trí truy vấn 1 mới nhất
* Làm sao để tìm truy vấn 3 gần nhất ảnh hưởng tới nó.

> Nó tương tự như cách connect

### Đã giảng qua 1 lần gòi nên tui ghi tóm tắt ở đây thui nhen