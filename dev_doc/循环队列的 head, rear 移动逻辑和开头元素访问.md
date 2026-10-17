---
tags:
---
队列的 head 指向末尾元素的后一个。这样设计的原因是，刚开始 rear 和 head 为数组首位，如果head指向末尾元素，那么就需要先移动，后插入。于是就会发生 rear 位于开头元素的前一位，这样rear 的移动就会变成先移动后删除。我更倾向于用前一种设计。

## Head and Rear 移动逻辑

```
(head +1) % capacity
```

原理就是：我们要解决的是当head等于capacity（也就是最大下标的后一位）时，如何回到0。如果下标比size小，那么取模的结果是本身，如果相等，那么取模的结果就是0

## 访问开头元素

因为 head 指向最后一个元素的后一位，所以当 head = 0 时，没办法直接访问队列末尾元素

```
((head-1)+capacity)%capacity
```

(head-1)+capacity 可行吗？不可行，正常下标失效。当 0，为 0+capacity，当 1，为 capacity+1。怎么保证正常下标映射回 head-1 ? capacity%capacity = 0，利用这个特性，可以直接消除掉对正常下标映射的影响，同时由于先计算括号内的式子，当 head=0，(capacity-1)%capacity 直接映射到最后一个元素下标。


