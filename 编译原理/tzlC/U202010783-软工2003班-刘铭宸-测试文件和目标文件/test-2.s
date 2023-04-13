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
  addi $sp, $sp, -20
  li $t1, 0
  sw $t1,  16($sp)
  lw $t1,  16($sp)
  sw $t1,  12($sp)
  lw $t1,  12($sp)
  sw $t1,  16($sp)
  addi $t3,$t1,1
  sw $t3,  12($sp)
  lw $t1,  16($sp)
  lw $t2,  0($sp)
  beq $t1,$t2,Label_2
  lw $t1,  16($sp)
  lw $t2,  1($sp)
  beq $t1,$t2,Label_3
  lw $t1,  16($sp)
  lw $t2,  2($sp)
  beq $t1,$t2,Label_4
  j Label_5
Label_2:
  li $t1, 0
  sw $t1,  16($sp)
  lw $a0,  16($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
Label_3:
  li $t1, 1
  sw $t1,  16($sp)
  lw $a0,  16($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  j Label_1
Label_4:
  li $t1, 2
  sw $t1,  16($sp)
  lw $a0,  16($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  j Label_1
Label_5:
  lw $a0,  12($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  j Label_1
Label_1:
  li $t1, 0
  sw $t1,  16($sp)
  lw $v0,  16($sp)
  jr $ra
  li $v0,10
  syscall
