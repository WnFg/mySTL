#mySTL

仿写STL里常用容器。

###容器内容：
* deque(双向队列)
 
* vector(动态数组)
 
* list(链表)
 
* rb_tree(红黑树)
 
* queue(队列)

* priority_queue(优先队列)

* map(映射)

* set(集合)

* stack(栈)

* heap(堆)

###一级容器：
* list

* vector

* rb_tree

* deque


###二级容器(对一级容器的封装)：
* queue(deque)

* stack(deque)
 
* map(rb_tree)
 
* set(rb_tree)
 
* heap(vector)

* priority_queue(heap) 
