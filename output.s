.align 2
.text
.globl f
f:
addi	sp,sp,-32
sw	s0,28(sp)
addi	s0,sp,32
li a5, 5
sw a5, -20(s0)
li a5, 3
sw a5, -24(s0)
lw a5, -20(s0)
mv a4,a5
lw a5, -24(s0)
sgt a5,a4,a5
beqz a5, L0
li a5, 1
sw a5, -20(s0)
j L1
L0:
li a5, 1
sw a5, -24(s0)
L1:
lw a5, -20(s0)
mv a4,a5
lw a5, -24(s0)
slt a5,a4,a5
beqz a5, L2
li a5, 1
mv a0,a5
lw	s0,28(sp)
addi	sp,sp,32
ret
j L3
L2:
li a5, 0
mv a0,a5
lw	s0,28(sp)
addi	sp,sp,32
ret
L3:
