#include "def.h"
#include <fstream>
#define YYSTYPE int   //此行是为了包含parser.tab.hpp不引起错误而加,可以在后面使用相关常量
#include "parser.tab.hpp"

void GenObject(list <IRCode> IRCodes)
{
    fstream ObjectFile;
    ObjectFile.open("ObjectFile.s",ios::out);

    /*预先给出read和write的目标代码*/
    ObjectFile<<".data\n";
    ObjectFile<<"_Prompt: .asciiz \"Enter an integer:  \"\n";
    ObjectFile<<"_ret: .asciiz \"\\n\"\n";
    ObjectFile<<".globl main\n";
    ObjectFile<<".text\n\n";
    ObjectFile<<"read:\n";
    ObjectFile<<"  li $v0,4\n";
    ObjectFile<<"  la $a0,_Prompt\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  li $v0,5\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  jr $ra\n\n";
    ObjectFile<<"write:\n";
    ObjectFile<<"  li $v0,1\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  li $v0,4\n";
    ObjectFile<<"  la $a0,_ret\n";
    ObjectFile<<"  syscall\n";
    ObjectFile<<"  move $v0,$0\n";
    ObjectFile<<"  jr $ra\n";

    for(list <IRCode>::iterator it=IRCodes.begin();it!=IRCodes.end();it++)
    {
      switch (it->Op)
        {
            case ASSIGN:
                if (it->Opn1.Name==string("_CONST"))  //这里只考虑了整常数
                    ObjectFile<< "  li $t1, "<<it->Opn1.constINT<<endl;
                else       //这里只考虑了简单变量，数组则需要扩充
                    ObjectFile<< "  lw $t1, "<<it->Opn1.Offset<<"($sp)"<<endl;
                ObjectFile<< "  sw $t1,  "<<it->Result.Offset<<"($sp)"<<endl;
                break;
            case PLUS:
            case MINUS:
            case STAR:
            case DIV:
                 ObjectFile<< "  lw $t1, "<<it->Opn1.Offset<<"($sp)"<<endl;
                 ObjectFile<< "  lw $t2, "<<it->Opn2.Offset<<"($sp)"<<endl;
                 if (it->Op==PLUS)       ObjectFile<< "  add $t3,$t1,$t2"<<endl;
                 else if (it->Op==MINUS) ObjectFile<< "  sub $t3,$t1,$t2"<<endl;
                 else if (it->Op==STAR)  ObjectFile<< "  mul $t3,$t1,$t2"<<endl;
                 else  {
                            ObjectFile<< "  div $t1, $t2"<<endl;
                            ObjectFile<< "  mflo $t3"<<endl;
                        }
                 ObjectFile<< "  sw $t3, "<<it->Result.Offset<<"($sp)"<<endl;
                 break;

            case RETURN:
                ObjectFile<< "  lw $v0,"<<it->Result.Offset<<"($sp)"<<endl; //返回值送到$v0
                ObjectFile<< "  jr $ra"<<endl;
                break;

            case FUNCTION:
                ObjectFile<< "\n"<<it->Result.Name<<":\n";
                if (it->Result.Name==string("main")) //特殊处理main
                    ObjectFile<< "  addi $sp, $sp, -"<<it->Result.Offset<<endl;
                break;
            case PARAM: break; //直接跳到后面一条
            case ARG:   break; //直接跳到后面一条,直到函数调用，回头提取实参值，传送到形参单元。
            case LABEL: ObjectFile<<it->Result.Name<<":"<<endl;  break;
            case GOTO:  ObjectFile<< "  j "<<it->Result.Name<<endl;  break;
            case END:
                ObjectFile<<"  li $v0,10\n  syscall"<<endl;
                break;
            case JLE:
            case JLT:
            case JGE:
            case JGT:
            case JEQ:
            case JNE:
                ObjectFile<< "  lw $t1, "<<it->Opn1.Offset<<"($sp)"<<endl;
                ObjectFile<< "  lw $t2, "<<it->Opn2.Offset<<"($sp)"<<endl;
                if (it->Op==JLE)      ObjectFile<< "  ble $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JLT) ObjectFile<< "  blt $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JGE) ObjectFile<< "  bge $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JGT) ObjectFile<< "  bgt $t1,$t2,"<<it->Result.Name<<endl;
                else if (it->Op==JEQ)  ObjectFile<< "  beq $t1,$t2,"<<it->Result.Name<<endl;
                else                  ObjectFile<< "  bne $t1,$t2,"<<it->Result.Name<<endl;
                break;

            case CALL:  case CALL0:
                list <IRCode>::iterator it0=it; it0--;  //it0指向前面可能的ARG
                if (it->Opn1.Name==string("read"))//特殊处理read
                {
                    ObjectFile<< "  addi $sp, $sp, -4\n";
                    ObjectFile<< "  sw $ra,0($sp)\n";      //保留返回地址
                    ObjectFile<< "  jal read\n";           //保留返回地址
                    ObjectFile<< "  lw $ra,0($sp)\n";      //恢复返回地址
                    ObjectFile<< "  addi $sp, $sp, 4\n";
                    ObjectFile<< "  sw $v0, "<<it->Result.Offset<<"($sp)\n";
                    break;
                }
                if (it->Opn1.Name==string("write"))//特殊处理write
                {
                    ObjectFile<< "  lw $a0, "<<it0->Result.Offset<<"($sp)\n";  //前面ARG的偏移量
                    ObjectFile<< "  addi $sp, $sp, -4\n";
                    ObjectFile<< "  sw $ra,0($sp)\n";
                    ObjectFile<< "  jal write\n";
                    ObjectFile<< "  lw $ra,0($sp)\n";
                    ObjectFile<< "  addi $sp, $sp, 4\n";
                    break;
                }
                ObjectFile<< "  move $t0,$sp"<<endl; //保存当前函数的sp到$t0中，为了取实参表达式的值


                ObjectFile<< "  addi $sp, $sp, -"<<static_cast <FuncSymbol *>(it->Opn1.SymPtr)->ARSize<<endl;  //开活动记录空间
                ObjectFile<< "  sw $ra,0($sp)"<<endl;                      //保留返回地址
                while (it0->Op==ARG)                       //依次取参数值传递到形参单元中
                {
                    //将原栈帧的偏移it0->Result.Offset数据取出，送到新栈帧的it0->Opn1.Offset
                    ObjectFile<< "  lw $t1, "<<it0->Result.Offset<<"($t0)"<<endl; //取实参值到$t1中
                    ObjectFile<< "  sw $t1,"<<it0->Opn1.Offset<<"($sp)"<<endl;    //送到被调用函数的形参单元
                    it0--;
                }
                ObjectFile<<"  jal "<<it->Opn1.Name<<endl;      //跳转到被调用函数
                ObjectFile<<"  lw $ra,0($sp)"<<endl;            //恢复返回地址
                ObjectFile<<"  addi $sp,$sp,"<<((FuncSymbol *)(it->Opn1.SymPtr))->ARSize<<endl; //释放活动记录空间
                ObjectFile<<"  sw $v0,"<<it->Result.Offset<<"($sp)"<<endl;  //取返回值,如void函数，不需要取值
                break;
        }
    }
    ObjectFile.close();
}
