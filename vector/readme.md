
# Public Interface

| API           | 功能                                               | 适用对象 |
| ------------- | -------------------------------------------------- | -------- |
| size()        | 报告向量当前的规模（元素总数）                     | 向量     |
| get(r)        | 获取秩为r元元素                                    | 向量     |
| put(r, e)     | 用e替换秩为r元素的数值                             | 向量     |
| insert(r, e)  | e作为秩为r元素插入，原后继元素依次后移             | 向量     |
| remove(r)     | 删除秩为r的元素，返回该元素中原存放的对象          | 向量     |
| disordered()  | 判断所有元素是否已按非降序排列                     | 有序向量 |
| sort()        | 调整各元素的位置，使之按非降序排列                 | 向量     |
| unsort()      | 随机置乱向量                                       | 有序向量 |
| find(e)       | 查找等于e且秩最大的元素                            | 向量     |
| search(e)     | 查找目标元素e，返回不大于e且秩最大的元素           | 有序向量 |
| deduplicate() | 剔除重复元素                                       | 向量     |
| uniquify()    | 剔除重复元素                                       | 有序向量 |
| traverse()    | 遍历向量幵统一处理所有元素，处理方法由函数对象指定 | 向量     |