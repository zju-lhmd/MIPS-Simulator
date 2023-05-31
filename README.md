# MIPS模拟器使用说明

> `/程序及源代码/MIPS/MIPS.exe`文件夹中是程序release版本
>
> `/程序及源代码/code`文件夹中是程序源码
>
> `/汇报PPT.txt`中是对本组汇报PPT的说明及PPT链接
>
> `/技术报告.pdf`文件是本组的MIPS模拟器技术报告

## 汇编功能

- 格式
  - 标签: （注释）
  - 标签：指令 （注释）
  - 指令 （注释）
  - 支持空格缩进的指令集详见报告
  -  只有标签的话不支持有注释,注释只支持写在指令的后面，不能单独一行

## 反汇编类

- 格式：
  - 32位
  - 指令集详见报告
- 反汇编请不要留有多余的空行
- 反汇编默认首行为main行，即调试时从第一行开始

## 执行器功能

- 用法
  - 按下DEBUG进入debug模式，从main标签（若没有则从0开始），点击NextStep或者Debug会进行单步执行。执行结束后点击Exit退出Debug模式

## 数据转换与计算

- 用法
  - 数据格式转换
    - 在input的选择框中选择您想要输入的类型，然后在输入框中输入该类型的数，并按下回车，其相应的转换格式会在下方的输出框中输出
    - 需要注意的是
      - 整数类型的整数、二进制数与十六进制数需要保持在int的范围内，-2147483648～2147483647。
      - Float类型的小数需要在float的精度内，二进制格式需要32位的浮点数格式，IEEE754
      - Double类型的小数需要在double的精度内，二进制格式需要64位浮点数格式，IEEE754
  - 数据计算
    - 在calculate的输入框中输入算式，算式中的数据格式应与input的选择框中选择的类型一致，然后点击calculate，运算结果会在input框中出现，并自动转换。
    - 支持加减乘除运算
    - 输入框中不能为空

## 参考代码

- 可以修改里面的值来观察

```assembly
main:
addi $s0, $zero, 0
addi $s1, $zero, 1
addi $s2, $zero, 2
addi $s3, $zero, 3
addi $s4, $zero, 4
addi $s5, $zero, 5
addi $s6, $zero, 6
addi $s7, $zero, 7
Start:
and $t0, $s0, $s1      # $t0 = $s0 & $s1
xor $t1, $s2, $s3      # $t1 = $s2 ^ $s3
nor $t2, $s4, $s5      # $t2 = ~($s4 | $s5)
add $t3, $s6, $s7      # $t3 = $s6 + $s7
sub $t4, $s0, $s1      # $t4 = $s0 - $s1
slt $t5, $s0, $s1      # $t5 = ($s0 < $s1) ? 1 : 0
jal Label8 # 跳转到Label8，并保存返回地址
sll $t6, $s2, 1        # $t6 = $s2 << 1
srl $t7, $s3, 1        # $t7 = $s3 >> 1
ori $t0, $s0, 15     # $t0 = $s0 | 0x0F
andi $t1, $s1, 255    # $t1 = $s1 & 0xFF
xori $t0, $s2, 85 # $t0 = $s2 ^ 0x55
lui $t1, 4095 # $t1 = 0x0FFF0000
addi $t2, $s3, 10 # $t2 = $s3 + 10
slti $t3, $s4, 5 # $t3 = ($s4 < 5) ? 1 : 0
lw $t4, 0($s0) # $t4 = (int)($s0)
sw $t5, 4($s1) # (int)($s1 + 4) = $t5
bgez $s4, Label1       # 如果$s4 >= 0，则跳转到Label1
bltz $s5, Label2       # 如果$s5 < 0，则跳转到Label2
bgtz $s6, Label3       # 如果$s6 > 0，则跳转到Label3
blez $s7, Label4       # 如果$s7 <= 0，则跳转到Label4
beq $s5, $s6, Label5 # 如果$s5 == $s6，则跳转到Label5
j Label6 # 无条件跳转到Label6
bne $s7, $s0, Label7 # 如果$s7 != $s0，则跳转到Label7
j End
Label1:
and $s0, $zero, $zero
j End
Label2:
and $s1, $zero, $zero
j End
Label3:
and $s2, $zero, $zero
j End
Label4:
and $s3, $zero, $zero
j End
Label5:
and $s4, $zero, $zero
j End
Label6:
and $s5, $zero, $zero
j End
Label7:
and $s6, $zero, $zero
j End
Label8:
and $s7, $zero, $zero
jr $ra #返回
End:
addi $t0,$zero,1
```

- 上述代码的反汇编代码

```assembly
00100000000100000000000000000000
00100000000100010000000000000001
00100000000100100000000000000010
00100000000100110000000000000011
00100000000101000000000000000100
00100000000101010000000000000101
00100000000101100000000000000110
00100000000101110000000000000111
00000010000100010100000000100100
00000010010100110100100000100110
00000010100101010101000000100111
00000010110101110101100000100000
00000010000100010110000000100010
00000010000100010110100000101010
00001100000000000000000000101111
00000000000100100111000001000000
00000000000100110111100001000010
00110110000010000000000000001111
00110010001010010000000011111111
00111010010010000000000001010101
00111100000010010000111111111111
00100010011010100000000000001010
00101010100010110000000000000101
10001110000011000000000000000000
10101110001011010000000000000100
00000110100000010000000000000111
00000110101000000000000000001000
00011110110000000000000000001001
00011010111000000000000000001010
00010010101101100000000000001011
00001000000000000000000000101011
00010110111100000000000000001101
00001000000000000000000000110001
00000000000000001000000000100100
00001000000000000000000000110001
00000000000000001000100000100100
00001000000000000000000000110001
00000000000000001001000000100100
00001000000000000000000000110001
00000000000000001001100000100100
00001000000000000000000000110001
00000000000000001010000000100100
00001000000000000000000000110001
00000000000000001010100000100100
00001000000000000000000000110001
00000000000000001011000000100100
00001000000000000000000000110001
00000000000000001011100000100100
00000011111000000000000000001000
00100000000010000000000000000001
```