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

main:
  addi $sp, $sp, -28
  li $t1, 0
  sw $t1,  16($sp)
  lw $t1,  16($sp)
  sw $t1,  12($sp)
  li $t1, 1
  sw $t1,  16($sp)
  lw $t1,  16($sp)
  sw $t1,  12($sp)
Label_1:
  li $t1, 10
  sw $t1,  20($sp)
  lw $t1,  12($sp)
  lw $t2,  20($sp)
  ble $t1,$t2,Label_2
  j Label_3
Label_2:
  li $t1, 2
  sw $t1,  16($sp)
  lw $t1,  12($sp)
  lw $t2,  16($sp)
  beq $t1,$t2,Label_5
  j Label_6
Label_5:
  j Label_4
Label_6:
  li $t1, 7
  sw $t1,  16($sp)
  lw $t1,  12($sp)
  lw $t2,  16($sp)
  beq $t1,$t2,Label_7
  j Label_8
Label_7:
  j Label_3
Label_8:
  lw $a0,  12($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
Label_4:
  lw $t1,  12($sp)
  sw $t1,  24($sp)
  addi $t3,$t1,1
  sw $t3,  12($sp)
  j Label_1
Label_3:
  li $t1, 0
  sw $t1,  16($sp)
  lw $v0,  16($sp)
  jr $ra
  li $v0,10
  syscall
