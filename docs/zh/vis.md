# Vis.c 文档

## 概述

`vis.c` 文件实现了构成摩天大楼谜题数学基础的可见性计数算法。本模块包含确定从网格周围每个方向能看到多少"摩天大楼"的核心逻辑。这些函数将谜题的可视化隐喻转换为精确的数学计算，验证提议的解决方案是否满足所有可见性线索。

## 文件目的

本模块处理：
- **可见性计数** - 从每个方向可见摩天大楼的数学计算
- **视线模拟** - 建模较高建筑如何隐藏较矮的建筑
- **方向遍历** - 从不同起点扫描行和列
- **高度比较逻辑** - 确定建筑何时变得可见
- **约束验证支持** - 为完整解决方案检查提供数据
- **算法优化** - 高效单次遍历可见性计数

## 摩天大楼谜题理论

### 可视化隐喻
想象一个4×4网格，其中每个单元格包含高度为1、2、3或4的"摩天大楼"。站在网格外面并看向一行或一列，您只能看到比前面所有摩天大楼都高的摩天大楼。谜题提供"线索"，表示从每个方向可以看到多少摩天大楼。

### 数学模型
- **网格值**：高度{1, 2, 3, 4}
- **可见性规则**：位置i的摩天大楼如果`height[i] > max(height[0..i-1])`则可见
- **线索验证**：可见摩天大楼的计数必须匹配给定线索
- **完整约束**：所有16个线索（4边×4方向）必须满足

### 视线算法
```
visible_count = 0
max_height = 0
for each position in direction:
    if height[position] > max_height:
        max_height = height[position]
        visible_count++
return visible_count
```

---

## 算法概述

### 可见性计数策略
1. **初始化跟踪变量** - 开始时没有看到建筑（`visible = 0`，`max_height = 0`）
2. **按查看方向遍历** - 从视角扫描行/列
3. **高度比较** - 检查当前建筑是否比之前最高的高
4. **更新可见性** - 如果更高，它可见并成为新高度阈值
5. **继续扫描** - 重复直到处理完整行/列
6. **返回计数** - 从此方向可见建筑的总数

### 方向扫描
- **左→右**：从列0到3扫描行
- **右→左**：从列3到0扫描行  
- **上→下**：从行0到3扫描列
- **下→上**：从行3到0扫描列

### 优化原则
- **单次遍历**：每个方向O(n)时间复杂度
- **最小状态**：只跟踪最大高度和计数
- **早期可见性**：遇到更高建筑时立即确定可见性
- **无回溯**：线性扫描足以进行可见性计数

---

## 函数文档

### 1. `ft_count_visible_left`

```c
int ft_count_visible_left(int *row)
```

**目的**：计算从行左侧看时多少摩天大楼可见（从左到右扫描）。

**参数**：
- `int *row` - 表示单行高度的4个整数数组

**返回值**：
- `int` - 可见摩天大楼数量（范围：1-4）

**算法**：
```c
max_height = 0;                          // 尚未看到建筑
visible = 0;                             // 可见建筑计数
i = 0;                                   // 从最左位置开始
while (i < SIZE)                         // 从左到右扫描
{
    if (row[i] > max_height)             // 当前建筑更高
    {
        max_height = row[i];             // 更新高度阈值
        visible++;                       // 增加可见计数
    }
    i++;                                 // 移动到下一个位置
}
return (visible);
```

**可视示例**：
```
行: [2, 1, 4, 3]
从左←看

位置0: 高度=2, max=0 → 2>0 ✓ 可见, max=2, 计数=1
位置1: 高度=1, max=2 → 1≤2 ✗ 被位置0的建筑隐藏
位置2: 高度=4, max=2 → 4>2 ✓ 可见, max=4, 计数=2  
位置3: 高度=3, max=4 → 3≤4 ✗ 被位置2的建筑隐藏

结果: 2个可见摩天大楼
```

**可见性逻辑**：
- **位置0的建筑**：总是可见（遇到的第一个建筑）
- **位置1的建筑**：被位置0更高建筑隐藏（高度2）
- **位置2的建筑**：可见因为它比之前最大值高（4 > 2）
- **位置3的建筑**：被位置2建筑隐藏（高度4）

**性能**：O(n)，其中n=4，单次遍历行

---

### 2. `ft_count_visible_right`

```c
int ft_count_visible_right(int *row)
```

**目的**：计算从行右侧看时多少摩天大楼可见（从右到左扫描）。

**参数**：
- `int *row` - 表示单行高度的4个整数数组

**返回值**：
- `int` - 可见摩天大楼数量（范围：1-4）

**算法**：
```c
max_height = 0;                          // 尚未看到建筑
visible = 0;                             // 可见建筑计数
i = SIZE - 1;                            // 从最右位置开始（3）
while (i >= 0)                           // 从右到左扫描
{
    if (row[i] > max_height)             // 当前建筑更高
    {
        max_height = row[i];             // 更新高度阈值
        visible++;                       // 增加可见计数
    }
    i--;                                 // 移动到前一个位置
}
return (visible);
```

**可视示例**：
```
行: [2, 1, 4, 3]
从右→看

位置3: 高度=3, max=0 → 3>0 ✓ 可见, max=3, 计数=1
位置2: 高度=4, max=3 → 4>3 ✓ 可见, max=4, 计数=2
位置1: 高度=1, max=4 → 1≤4 ✗ 被位置2建筑隐藏
位置0: 高度=2, max=4 → 2≤4 ✗ 被位置2建筑隐藏

结果: 2个可见摩天大楼
```

**与左视图的关键区别**：
- **相同行，不同视角**：不同建筑变得可见
- **扫描方向**：以相反顺序处理位置（3→2→1→0）
- **独立计算**：右视图计数可以与左视图计数不同
- **相同算法**：相同可见性逻辑，只是不同遍历方向

**对称性观察**：对于行[2,1,4,3]，左右视图都显示2个可见建筑，但这是巧合。

---

### 3. `ft_count_visible_top`

```c
int ft_count_visible_top(t_grid *grid, int col)
```

**目的**：计算从列顶部看时多少摩天大楼可见（从上到下扫描）。

**参数**：
- `t_grid *grid` - 包含所有单元格值的完整网格结构
- `int col` - 要分析的列索引（0-3）

**返回值**：
- `int` - 可见摩天大楼数量（范围：1-4）

**算法**：
```c
max_height = 0;                          // 尚未看到建筑
visible = 0;                             // 可见建筑计数
i = 0;                                   // 从顶部位置开始（行0）
while (i < SIZE)                         // 从上到下扫描
{
    if (grid->cells[i][col] > max_height)// 当前建筑更高
    {
        max_height = grid->cells[i][col]; // 更新高度阈值
        visible++;                        // 增加可见计数
    }
    i++;                                  // 移动到下一行
}
return (visible);
```

**列访问模式**：
```c
grid->cells[0][col]    // 列顶部（行0）
grid->cells[1][col]    // 从上数第二（行1）
grid->cells[2][col]    // 从下数第二（行2）  
grid->cells[3][col]    // 列底部（行3）
```

**可视示例**：
```
列1: [3, 2, 4, 1] (从grid->cells[i][1]提取)
从上↓看

行0: 高度=3, max=0 → 3>0 ✓ 可见, max=3, 计数=1
行1: 高度=2, max=3 → 2≤3 ✗ 被行0建筑隐藏
行2: 高度=4, max=3 → 4>3 ✓ 可见, max=4, 计数=2
行3: 高度=1, max=4 → 1≤4 ✗ 被行2建筑隐藏

结果: 2个可见摩天大楼
```

**数据结构访问**：
- **网格导航**：访问`grid->cells[i][col]`读取列值
- **列方向遍历**：固定列索引，迭代行索引
- **内存模式**：访问不同内存位置（不像行函数那样顺序）
- **缓存考虑**：列访问与行访问有不同缓存行为

---

### 4. `ft_count_visible_bottom`

```c
int ft_count_visible_bottom(t_grid *grid, int col)
```

**目的**：计算从列底部看时多少摩天大楼可见（从下到上扫描）。

**参数**：
- `t_grid *grid` - 包含所有单元格值的完整网格结构
- `int col` - 要分析的列索引（0-3）

**返回值**：
- `int` - 可见摩天大楼数量（范围：1-4）

**算法**：
```c
max_height = 0;                          // 尚未看到建筑
visible = 0;                             // 可见建筑计数
i = SIZE - 1;                            // 从底部位置开始（行3）
while (i >= 0)                           // 从下到上扫描
{
    if (grid->cells[i][col] > max_height)// 当前建筑更高
    {
        max_height = grid->cells[i][col]; // 更新高度阈值
        visible++;                        // 增加可见计数
    }
    i--;                                  // 移动到前一行
}
return (visible);
```

**反向列访问模式**：
```c
grid->cells[3][col]    // 列底部（行3） - 从这里开始
grid->cells[2][col]    // 从下数第二（行2）
grid->cells[1][col]    // 从上数第二（行1）
grid->cells[0][col]    // 列顶部（行0） - 在这里结束
```

**可视示例**：
```
列1: [3, 2, 4, 1] (从grid->cells[i][1]提取)
从下↑看

行3: 高度=1, max=0 → 1>0 ✓ 可见, max=1, 计数=1
行2: 高度=4, max=1 → 4>1 ✓ 可见, max=4, 计数=2
行1: 高度=2, max=4 → 2≤4 ✗ 被行2建筑隐藏
行0: 高度=3, max=4 → 3≤4 ✗ 被行2建筑隐藏

结果: 2个可见摩天大楼
```

**扫描方向影响**：
- **不同可见性**：从上vs从下看同列数据产生不同可见计数
- **从下往上视角**：行3建筑（高度1）首先可见
- **高度阈值演化**：`max_height`以不同方式进展（1→4 vs 3→4）
- **独立结果**：底视图计数独立于顶视图计数

---

## 数学分析

### 可见性函数属性

#### **单调性**
可见性计数算法表现出单调行为：
- **高度阈值**：`max_height`在扫描期间从不减少
- **可见性计数**：`visible`在扫描期间从不减少
- **确定性**：相同输入总是产生相同输出

#### **边界条件**

##### **最小可见性：1**
```c
// 任何非空行/列至少有1个可见建筑
// 方向上最高建筑总是可见
```

##### **最大可见性：4**
```c
// 完美升序序列：[1, 2, 3, 4]
// 每个建筑都比之前所有建筑高
```

### 复杂度分析

#### **时间复杂度**：O(n)其中n = SIZE = 4
- **单次遍历**：每个函数恰好扫描4个位置一次
- **常数操作**：高度比较和计数器增加是O(1)
- **线性扩展**：对更大网格大小将线性扩展

#### **空间复杂度**：O(1)
- **固定变量**：`max_height`，`visible`，`i`使用常数空间
- **无额外存储**：算法不存储中间结果
- **就地计算**：直接使用输入数据工作

### 模式识别

#### **最优可见性模式**

##### **最大可见性（4个可见）**：
```
[1, 2, 3, 4] → 所有建筑可见（升序）
```

##### **最小可见性（1个可见）**：
```
[4, 3, 2, 1] → 只有第一个建筑可见（降序）
```

##### **常见模式**：
```
[4, 1, 2, 3] → 2个可见（开始4，然后全部隐藏）
[1, 4, 2, 3] → 2个可见（1，然后4，然后全部隐藏）
[2, 3, 1, 4] → 3个可见（2，然后3，然后4突破）
```

---

## 与谜题求解的集成

### 在验证过程中的使用

#### **完整网格验证**
```c
// 在check.c: ft_check_visibility()中
for (int row = 0; row < SIZE; row++)
{
    if (input->clues[LEFT][row] != 0)
        if (ft_count_visible_left(grid->cells[row]) != input->clues[LEFT][row])
            return (0);  // 左线索违反
            
    if (input->clues[RIGHT][row] != 0)
        if (ft_count_visible_right(grid->cells[row]) != input->clues[RIGHT][row])
            return (0);  // 右线索违反
}

for (int col = 0; col < SIZE; col++)
{
    if (input->clues[TOP][col] != 0)
        if (ft_count_visible_top(grid, col) != input->clues[TOP][col])
            return (0);  // 上线索违反
            
    if (input->clues[BOTTOM][col] != 0)
        if (ft_count_visible_bottom(grid, col) != input->clues[BOTTOM][col])
            return (0);  // 下线索违反
}
```

### 在求解上下文中的性能

#### **验证频率**
- **每个完整解决方案调用一次**：只有当回溯填满所有16个位置时
- **16次可见性计算**：4个方向×4行/列= 16次函数调用
- **总操作**：16×4 = 64次高度比较每次验证
- **验证成本**：对4×4网格O(64) = O(1)

#### **关键路径分析**
```
回溯 → 完整网格 → ft_check_visibility() → vis.c函数 → 成功/失败
```

可见性计数函数代表最终验证步骤，确定完整网格分配是否满足所有谜题约束。

---

## 方向映射和线索集成

### 线索位置映射

#### **输入线索布局**：
```
    T0  T1  T2  T3     ← 上线索
L0  [1] [2] [3] [4] R0  ← 行0的左/右线索
L1  [1] [2] [3] [4] R1  ← 行1的左/右线索  
L2  [1] [2] [3] [4] R2  ← 行2的左/右线索
L3  [1] [2] [3] [4] R3  ← 行3的左/右线索
    B0  B1  B2  B3     ← 下线索
```

#### **函数到线索映射**：
```c
// 基于行的线索
input->clues[0] → ft_count_visible_top(grid, 0)     // T0
input->clues[4] → ft_count_visible_left(grid->cells[0])  // L0  
input->clues[8] → ft_count_visible_bottom(grid, 0)  // B0
input->clues[12] → ft_count_visible_right(grid->cells[0]) // R0
```

### 验证逻辑流程

#### **线索验证过程**：
1. **解析线索**：从输入中提取预期可见性计数
2. **计算实际值**：使用相应的vis.c函数计算可见性  
3. **比较值**：检查计算值是否匹配预期值
4. **返回结果**：成功（匹配）或失败（不匹配）

#### **选择性验证**：
```c
if (input->clues[position] != 0)  // 0 = 未提供线索
{
    int calculated = ft_count_visible_xxx(...);
    if (calculated != input->clues[position])
        return (0);  // 约束违反
}
```

---

## 算法变体和扩展

### 优化机会

#### **早期终止**
```c
// 如果我们看到高度4，所有剩余建筑都被隐藏
if (max_height == 4)
    break;  // 没有更多建筑可以可见
```

#### **基于线索的剪枝**
```c
// 如果线索是1，只有第一个建筑重要
if (expected_clue == 1 && visible > 1)
    return (0);  // 已经太多可见
```

#### **高度4特殊情况**
```c
// 高度4建筑总是创建可见性断点
if (current_height == 4)
{
    visible++;
    break;  // 高度4之后没有东西可见
}
```

### 推广到N×N网格

#### **可扩展实现**：
```c
int ft_count_visible_left_generic(int *row, int size)
{
    int max_height = 0;
    int visible = 0;
    
    for (int i = 0; i < size; i++)
    {
        if (row[i] > max_height)
        {
            max_height = row[i];
            visible++;
        }
    }
    return (visible);
}
```

#### **性能扩展**：
- **时间复杂度**：对n×n网格O(n)
- **空间复杂度**：保持O(1)
- **总验证**：完整网格检查O(n²)

---

## 测试和验证

### 单元测试策略

#### **已知可见性模式**：
```c
// 测试最大可见性
int ascending[4] = {1, 2, 3, 4};
assert(ft_count_visible_left(ascending) == 4);
assert(ft_count_visible_right(ascending) == 1);  // 从右只看到4

// 测试最小可见性  
int descending[4] = {4, 3, 2, 1};
assert(ft_count_visible_left(descending) == 1);  // 从左只看到4
assert(ft_count_visible_right(descending) == 4);

// 测试混合模式
int mixed[4] = {2, 1, 4, 3};
assert(ft_count_visible_left(mixed) == 2);   // 2，然后4
assert(ft_count_visible_right(mixed) == 2);  // 3，然后4
```

#### **列测试**：
```c
// 创建测试网格
t_grid test_grid;
// 设置列值：test_grid.cells[i][0] = heights[i]
int column_heights[4] = {3, 1, 4, 2};
for (int i = 0; i < 4; i++)
    test_grid.cells[i][0] = column_heights[i];

assert(ft_count_visible_top(&test_grid, 0) == 2);     // 3，然后4
assert(ft_count_visible_bottom(&test_grid, 0) == 2);  // 2，然后4
```

### 边界情况验证

#### **全相同高度**（在真实谜题中无效）：
```c
int same[4] = {2, 2, 2, 2};
// 结果：1个可见（只有第一个建筑）
// 注意：这违反摩天大楼唯一性约束
```

#### **高度4主导**：
```c
int height4_first[4] = {4, 1, 2, 3};
assert(ft_count_visible_left(height4_first) == 1);   // 只有4可见
int height4_last[4] = {1, 2, 3, 4};  
assert(ft_count_visible_left(height4_last) == 4);    // 全部可见
```

### 正确性验证

#### **对称性检查**：
```c
// 创建对称测试案例
void test_symmetry(int heights[4])
{
    // 用反向数组测试左右一致性
    int reversed[4];
    for (int i = 0; i < 4; i++)
        reversed[i] = heights[3-i];
        
    int left_count = ft_count_visible_left(heights);
    int right_reversed = ft_count_visible_right(reversed);
    assert(left_count == right_reversed);  // 应该相等
}
```

#### **网格一致性**：
```c
// 验证行/列提取匹配直接数组访问
void test_grid_consistency(t_grid *grid)
{
    for (int row = 0; row < SIZE; row++)
    {
        int left = ft_count_visible_left(grid->cells[row]);
        // 手动提取行并测试
        int extracted_row[4];
        for (int col = 0; col < SIZE; col++)
            extracted_row[col] = grid->cells[row][col];
        int left_extracted = ft_count_visible_left(extracted_row);
        assert(left == left_extracted);
    }
}
```

---

## 性能基准测试

### 执行时间分析

#### **单独函数性能**：
```bash
# 基准测试可见性计数函数
time_test() {
    for i in {1..1000000}; do
        ft_count_visible_left(test_row);
    done
}

# 预期：100万次迭代约1-2毫秒
# 表示4×4情况下优秀O(1)性能
```

#### **完整验证性能**：
```bash  
# 基准测试完整网格验证
validate_grid_test() {
    # 每次验证16次可见性计算
    # 4个方向×4行/列= 16次调用
    for i in {1..100000}; do
        ft_check_visibility(test_grid, test_input);
    done
}

# 预期：10万次验证约10-20毫秒
# 表示与求解算法的高效集成
```

### 内存使用分析

#### **函数内存占用**：
```c
// 每个可见性函数使用：
int max_height;    // 4字节
int visible;       // 4字节  
int i;            // 4字节
// 总计：每次函数调用12字节
// 栈开销：约32字节
// 每次调用总计：约44字节
```

#### **缓存性能**：
- **行函数**：优秀缓存局部性（顺序访问）
- **列函数**：中等缓存性能（跨步访问）
- **整体影响**：对4×4网格最小，对更大网格更显著

---

## 42规范合规性

### 函数标准
✅ **函数数量**：4个函数（低于5函数限制）  
✅ **函数长度**：所有函数≤25行  
✅ **函数命名**：全部使用`ft_`前缀和描述性名称  
✅ **参数清晰**：清晰参数名（`row`，`grid`，`col`）  
✅ **返回值**：一致整数返回类型

### 算法质量
✅ **单一职责**：每个函数处理一个方向视图  
✅ **代码重用**：函数间一致算法模式  
✅ **清晰逻辑**：可见性算法易于遵循  
✅ **无副作用**：函数不修改输入数据  
✅ **确定性**：相同输入总是产生相同输出

### 代码样式
✅ **缩进**：全程正确制表符缩进  
✅ **变量命名**：清晰、数学变量名  
✅ **循环结构**：一致while循环模式  
✅ **大括号**：一致应用K&R大括号样式  
✅ **逻辑流程**：清晰算法进展

---

## 集成总结

`vis.c`模块为验证摩天大楼谜题解决方案提供数学基础。其四个函数将"计算可见摩天大楼"的可视化隐喻转换为确定约束满足的精确算法。该模块高效的O(n)可见性计数使回溯求解器能够快速验证完整解决方案，使其成为整体谜题求解架构中的关键组件。

这些可见性函数在人类直觉（从不同角度看摩天大楼）和计算验证（检查提议解决方案满足所有数学约束）之间架起桥梁。它们的优雅简洁性和计算效率使它们成为娱乐数学和谜题求解应用中约束满足算法的理想构建块。