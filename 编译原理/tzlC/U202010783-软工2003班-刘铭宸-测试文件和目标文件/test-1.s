.data
_Prompt: .asciiz "Enter an integer:  "
_ret: .asciiz "\n"
.globl main
.text

read:
  li $v0,4
  la $a0,_Prompt
  syscall
  li $v0,5
  syscall
  jr $ra

write:
  li $v0,1
  syscall
  li $v0,4
  la $a0,_ret
  syscall
  move $v0,$0
  jr $ra

fibo:
  li $t1, 1
  sw $t1,  16($sp)
  lw $t1,  12($sp)
  lw $t2,  16($sp)
  beq $t1,$t2,Label_1
  j Label_3
Label_3:
  li $t1, 2
  sw $t1,  20($sp)
  lw $t1,  12($sp)
  lw $t2,  20($sp)
  beq $t1,$t2,Label_1
  j Label_2
Label_1:
  li $t1, 1
  sw $t1,  16($sp)
  lw $v0,  16($sp)
  jr $ra
Label_2:
  li $t1, 1
  sw $t1,  16($sp)
  lw $t1,  12($sp)
  lw $t2,  16($sp)
  sub $t3,$t1,$t2
  sw $t3,  20($sp)
  move $t0,$sp
  addi $sp, $sp, -44
  sw $ra,0($sp)
  lw $t1,  20($t0)
  sw $t1,  12($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,44
  sw $v0,  24($sp)
  li $t1, 2
  sw $t1,  28($sp)
  lw $t1,  12($sp)
  lw $t2,  28($sp)
  sub $t3,$t1,$t2
  sw $t3,  32($sp)
  move $t0,$sp
  addi $sp, $sp, -44
  sw $ra,0($sp)
  lw $t1,  32($t0)
  sw $t1,  12($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,44
  sw $v0,  36($sp)
  lw $t1,  24($sp)
  lw $t2,  36($sp)
  add $t3,$t1,$t2
  sw $t3,  40($sp)
  lw $v0,  40($sp)
  jr $ra

main:
  addi $sp, $sp, -156
  li $t1, 0
  sw $t1,  120($sp)
  lw $t1,  120($sp)
  sw $t1,  112($sp)
Label_4:
  li $t1, 5
  sw $t1,  124($sp)
  lw $t1,  112($sp)
  lw $t2,  124($sp)
  blt $t1,$t2,Label_5
  j Label_6
Label_5:
  li $t1, 0
  sw $t1,  120($sp)
  lw $t1,  120($sp)
  sw $t1,  116($sp)
Label_8:
  li $t1, 5
  sw $t1,  124($sp)
  lw $t1,  116($sp)
  lw $t2,  124($sp)
  blt $t1,$t2,Label_9
  j Label_10
Label_9:
  li $t1, 5
  sw $t1,  120($sp)
  lw $t1,  112($sp)
  lw $t2,  120($sp)
  mul $t3,$t1,$t2
  sw $t3,  124($sp)
  lw $t1,  124($sp)
  lw $t2,  116($sp)
  add $t3,$t1,$t2
  sw $t3,  128($sp)
  li $t1, 4
  sw $t1,  132($sp)
  lw $t1,  128($sp)
  lw $t2,  132($sp)
  mul $t3,$t1,$t2
  sw $t3,  136($sp)
  lw $t1,  112($sp)
  lw $t2,  116($sp)
  add $t3,$t1,$t2
  sw $t3,  144($sp)
  lw $t1,  144($sp)
  lw $t4,  136($sp)
  add $sp, $sp, $t4
  sw $t1,  12($sp)
  sub $sp, $sp, $t4
Label_11:
  lw $t1,  116($sp)
  sw $t1,  128($sp)
  addi $t3,$t1,1
  sw $t3,  116($sp)
  j Label_8
Label_10:
Label_7:
  lw $t1,  112($sp)
  sw $t1,  128($sp)
  addi $t3,$t1,1
  sw $t3,  112($sp)
  j Label_4
Label_6:
  li $t1, 0
  sw $t1,  120($sp)
  lw $t1,  120($sp)
  sw $t1,  112($sp)
Label_12:
  li $t1, 5
  sw $t1,  124($sp)
  lw $t1,  112($sp)
  lw $t2,  124($sp)
  blt $t1,$t2,Label_13
  j Label_14
Label_13:
  li $t1, 5
  sw $t1,  120($sp)
  lw $t1,  112($sp)
  lw $t2,  120($sp)
  mul $t3,$t1,$t2
  sw $t3,  124($sp)
  lw $t1,  124($sp)
  lw $t2,  112($sp)
  add $t3,$t1,$t2
  sw $t3,  128($sp)
  li $t1, 4
  sw $t1,  132($sp)
  lw $t1,  128($sp)
  lw $t2,  132($sp)
  mul $t3,$t1,$t2
  sw $t3,  136($sp)
  lw $t4,  136($sp)
  add $sp, $sp, $t4
  lw $t1,  12($sp)
  sub $sp, $sp, $t4
  sw $t1,  140($sp)
  lw $a0,  140($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
Label_15:
  lw $t1,  112($sp)
  sw $t1,  128($sp)
  addi $t3,$t1,1
  sw $t3,  112($sp)
  j Label_12
Label_14:
  li $t1, 1
  sw $t1,  120($sp)
  li $t1, 5
  sw $t1,  124($sp)
  lw $t1,  120($sp)
  lw $t2,  124($sp)
  mul $t3,$t1,$t2
  sw $t3,  128($sp)
  li $t1, 3
  sw $t1,  132($sp)
  lw $t1,  128($sp)
  lw $t2,  132($sp)
  add $t3,$t1,$t2
  sw $t3,  136($sp)
  li $t1, 4
  sw $t1,  140($sp)
  lw $t1,  136($sp)
  lw $t2,  140($sp)
  mul $t3,$t1,$t2
  sw $t3,  144($sp)
  lw $t4,  144($sp)
  add $sp, $sp, $t4
  lw $t1,  12($sp)
  sub $sp, $sp, $t4
  sw $t1,  148($sp)
  move $t0,$sp
  addi $sp, $sp, -44
  sw $ra,0($sp)
  lw $t1,  148($t0)
  sw $t1,  12($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,44
  sw $v0,  152($sp)
  lw $a0,  152($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  li $t1, 0
  sw $t1,  120($sp)
  lw $v0,  120($sp)
  jr $ra
  li $v0,10
  syscall
